#ifndef BOOTLOADER_H_INCLUDED
#define BOOTLOADER_H_INCLUDED

// Bootloader calls
void bootloader_load_kernel();
void kernel_start();

void bootloader_load_kernel() {
    printf("Press ENTER to boot PYunix...\n");
    getchar();
    printf("Loading PYunix kernel...\n\n");
    vwait();
    kernel_init();
    kernel_start();
}

#endif // BOOTLOADER_H_INCLUDED
