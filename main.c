/*
TO-DO:
Out of memory manager to terminate processes using too much memory
Prevent user from creating same process twice, bugs out the system
Add more commands
    - reboot (reboot the PYunix system [bugged out, idk how to implement that])
    File management
        Create, modify, delete files on real users PC
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#include "bios/bios.h"
#include "bootloader/bootloader.h"
#include "kernel/kernel.h"
#include "terminal/terminal.h"

void vwait()
{
    // Adds a simulated delay running everything. Comment the following code to disable.
    // srand(time(NULL));
    // usleep((rand() % 50000) + 50000);
}

int main()
{
    bios_initialize(); // Initialize the system and start the kernel

    // Add devices
    device_manager_add_device("Terminal");
    device_manager_list_devices();

    printf("Press ENTER to continue...");
    getchar();
    clear_scr();

    // Start the terminal
    terminal_start();
    
    // Start a kernel panic if loop is broken
    kernel_panic("Program loop broken; was the system shutdown correctly?");
    return 0;
}
