#include "process.h"
#include "thread.h"

map_t processes;

error_t process_create(process_t** process, void*(start_routine)(void*), int argc, const char* argv[]) {
    error_t err = NO_ERROR;
    thread_t* thread = NULL;

    // create a new process
    process_t* new_process = calloc(1, sizeof(process_t));

    // create a thread
    CHECK_AND_RETHROW(thread_create(new_process, start_routine, NULL, &thread));

    // set the main arguments
    thread->state.cpu.rdi = (uint64_t) argc;
    thread->state.cpu.rdi = (uint64_t) argv;

    // finished!
    *process = new_process;

cleanup:
    if(err == NO_ERROR) {
        // cancel process
    }
    return err;
}

bool process_validate(process_t* process) {
    error_t err = NO_ERROR;
    uintptr_t addr;

    // make sure this thread actually exists in memory
    CHECK_AND_RETHROW(vmm_virt_to_phys(kernel_address_space, (uintptr_t)process, &addr));
    CHECK_AND_RETHROW(vmm_virt_to_phys(kernel_address_space, (uintptr_t)((char*)process) + sizeof(process_t), &addr));

cleanup:
    return err == NO_ERROR;
}
