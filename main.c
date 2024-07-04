/*
TO-DO:
Put stuff as modules so not everything is one file
Put limit on how much memory you can allocate to a process
    - Setting the allocated memory too high or in the negatives bugs out the memory manager.
    - Setting the allocated memory too high or in the negatives while creating the process bugs out the process creator, process doesn't appear in ps (Process Show)
Out of memory manager to terminate processes using too much memory
Prevent user from creating same process twice, bugs out the system
Add more commands
    - echo
    - reboot (reboot the PYunix system)
    File management
        Create, modify, delete files on real users PC
        Add warning saying that PYunix is NOT responsible for any damage the user causes from running file management commands
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#include "BIOS/bios.h"
#include "bootloader/bootloader.h"
#include "kernel/kernel.h"
#include "terminal/terminal.h"

void vwait() {
    srand(time(NULL));
    usleep((rand() % 50000) + 50000);
}

int main() {
    bios_initialize(); // Initialize the system and start the kernel

    // Add devices
    device_manager_add_device("Disk");
    device_manager_add_device("Network Adapter");
    device_manager_add_device("Display Adapter");
    device_manager_list_devices();

    // Start the terminal
    terminal_start();
    return 0;
}
