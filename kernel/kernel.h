#ifndef KERNEL_H_INCLUDED
#define KERNEL_H_INCLUDED

#include <stdbool.h> // for bool type
#include <stdio.h>   // for printf
#include <string.h>  // for strcpy
#include <stdlib.h>  // for exit

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
#include "color.h"

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
    
    // Weird bug in which the loop doesn't terminate all processes, run the loop 100 times to make sure all processes are terminated
    for (int i = 0; i < 100; i++) 
    {
        for (int i = 0; i < process_count; i++)
        {
            terminal_kill_process(processes[i].name, true);
        }
    }

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

