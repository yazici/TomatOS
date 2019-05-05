//
// Created by Itay on 24/03/2019.
//

#include <common/common.h>
#include <common/string.h>
#include <common/buf.h>
#include <memory/vmm.h>
#include <memory/mm.h>
#include <memory/gdt.h>
#include "thread.h"
#include "process.h"
#include "cpu/rflags.h"

void thread_init(thread_t* thread) {
    thread->tid = thread->parent->next_tid++;

    thread->state = THREAD_NORMAL;

    if(thread->parent->kernel) {
        // will have the ring set to 0
        thread->cpu_state.rflags = RFLAGS_DEFAULT;
        thread->cpu_state.ss = GDT_KERNEL_DATA;
        thread->cpu_state.ds = GDT_KERNEL_DATA;
        thread->cpu_state.cs = GDT_KERNEL_CODE;
    }else {
        // will have the ring set to 3
        thread->cpu_state.rflags = RFLAGS_DEFAULT_USER;
        thread->cpu_state.ss = GDT_USER_DATA;
        thread->cpu_state.ds = GDT_USER_DATA;
        thread->cpu_state.cs = GDT_USER_CODE;
    }

    thread->cpu_state.rip = (uint64_t) thread->start;
}

error_t thread_find(struct process* process, int tid, thread_t** thread) {
    error_t err = NO_ERROR;
    thread_t* th = NULL;

    CHECK_ERROR(process, ERROR_INVALID_ARGUMENT);

    for(thread_t* it = process->threads; it < buf_end(process->threads); it++) {
        if(it->state != THREAD_DEAD && it->tid == tid) {
            th = it;
            break;
        }
    }

    CHECK_ERROR(th != NULL, ERROR_NOT_FOUND);
    
    if(thread != NULL) *thread = th;

cleanup:
    return err;
}

void thread_kill(thread_t* thread) {
    thread->state = THREAD_DEAD;
}