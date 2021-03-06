#include <util/def.h>
#include <arch/paging.h>
#include <arch/msr.h>
#include <arch/cpuid.h>
#include <mm/gdt.h>

#include "syscall.h"
#include "process.h"
#include "thread.h"

static syscall_handler_t handlers[SYS_MAX] = {
    [SYS_THRD_SPAWN] = sys_thrd_spawn,
    [SYS_THRD_SET_OPT] = sys_thrd_set_opt,
    [SYS_THRD_RAISE_TPL] = sys_thrd_raise_tpl,
    [SYS_THRD_RESTORE_TPL] = sys_thrd_restore_tpl,
};

void syscall_common_handler(syscall_context_t ctx) {
    err_t err = NO_ERROR;

    // check that the syscall number is valid
    CHECK_ERROR(ctx.syscall < ARRAY_LEN(handlers), ERROR_NOT_FOUND);

    // call the handler
    CHECK_AND_RETHROW(handlers[ctx.syscall](&ctx));

cleanup:
    WARN(!IS_ERROR(err), "Got error in syscall, ignoring");
    ctx.ret_error = err;
}

err_t verify_string(const char* str) {
    err_t err = NO_ERROR;

    // verify the base pointer is good
    CHECK_ERROR((uintptr_t)str < USERSPACE_END, ERROR_INVALID_POINTER);

    // TODO: instead of doing this kind of check it would be nicer to simply
    //       return an error on an invalid userspace access or something

    // will check that all the string is mapped and is null terminated
    int page_num = -1;
    do {
        // check if mapped if this is a new page
        if (ALIGN_DOWN(str, PAGE_SIZE) != page_num) {
            page_num = ALIGN_DOWN(str, PAGE_SIZE);
            CHECK_ERROR(vmm_is_mapped(current_vmm_handle, (uintptr_t)str, 1), ERROR_INVALID_POINTER);
        }
    } while(*str != 0);

cleanup:
    return err;
}

err_t verify_buffer(void* buf, size_t len, bool writable) {
    err_t err = NO_ERROR;

    // verify these are good
    CHECK_ERROR((uintptr_t)buf < USERSPACE_END, ERROR_INVALID_POINTER);
    CHECK_ERROR((uintptr_t)buf + len < USERSPACE_END, ERROR_INVALID_POINTER);

    // simply check the whole buffer is mapped
    // TODO: check writeable
    CHECK_ERROR(vmm_is_mapped(current_vmm_handle, (uintptr_t)buf, len), ERROR_INVALID_POINTER);

cleanup:
    return err;
}

extern void syscall_entry();

void init_syscalls_for_cpu() {
    // make sure the cpu supports syscall/sysret
    CPUID_EXTENDED_CPU_SIG_EDX extended_cpu_sig_edx = {0};
    cpuid(CPUID_EXTENDED_CPU_SIG, NULL, NULL, NULL, &extended_cpu_sig_edx.raw);
    ASSERT(extended_cpu_sig_edx.SYSCALL_SYSRET);

    // enable syscall/sysret in efer
    IA32_EFER efer = __read_efer();
    efer.SCE = 1;
    __write_efer(efer);

    // setup the values for the syscall
    uint64_t usercode = GDT_USER_CODE;
    usercode &= ~0b11;
    usercode -= 16;
    usercode |= 0b11;

    // set the flags to keep
    IA32_RFLAGS rflags = {
        .always_one = 1,
        .IF = 1,
    };

    __writemsr(MSR_IA32_STAR, (usercode << 48u) | (GDT_KERNEL_CODE << 32u));
    __writemsr(MSR_IA32_LSTAR, (uint64_t)syscall_entry);
    __writemsr(MSR_IA32_FMASK, ~rflags.raw & 0xFFFFFFFF);
}
