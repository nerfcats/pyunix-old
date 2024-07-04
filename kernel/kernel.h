#ifndef KERNEL_H_INCLUDED
#define KERNEL_H_INCLUDED

#include <stdbool.h> // for bool type
#include <stdio.h>   // for printf
#include <string.h>  // for strcpy

void vwait();
void terminal_kill_process(const char* process, bool is_kernel);

/*
Main kernel
Provides very basic system calls.
Add more functionality by adding another module and defining it in "setup.h"
*/

char kernel_state[] = "running";

#include "setup.h"
#include "init.h"
#include "proc_man.h"
#include "mem_man.h"
#include "dev_man.h"
#include "panic.h"

void kernel_init()
{
    // Initialize Kernel components
}

void kernel_start()
{
    printf("kernel: Initializing...\n");
    vwait();
    initramfs_load();
    kernel_switch_to_real_root_filesystem();
    init_system_start();
    printf("kernel: Initialization complete.\n");
    vwait();
}

void kernel_switch_to_real_root_filesystem()
{
    printf("kernel: Switching to root filesystem...\n");
    vwait();
}

void kernel_shutdown(bool reset)
{
    printf("kernel: Shutting down system...\n");
    printf("kernel: Stopping system services...\n");
    vwait();
    terminal_kill_process("init", true);
    vwait();
    printf("kernel: Unmounting filesystems...\n");
    vwait();
    printf("kernel: Ready to power off\n");
    strcpy(kernel_state, "stopped");
    if (!reset)
    {
        exit(0);
    }
}

#endif // KERNEL_H_INCLUDED
