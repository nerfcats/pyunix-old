#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

const char version[] = "PYUNIX KERNEL 0.1";

// Function to simulate realistic delay
void realistic_delay() {
    usleep((rand() % 50000) + 50000);  // sleep for 0.05 to 0.1 seconds
}

// BIOS class
void bios_initialize();
void load_kernel();

// Bootloader class
void bootloader_load_kernel();
void kernel_start();

// Kernel class
void kernel_init();
void kernel_start();
void kernel_switch_to_real_root_filesystem();
void kernel_shutdown();
void kernel_panic(const char* reason); // New function for kernel panic
void initramfs_load();
void init_system_start();
void init_system_create_startup_processes();
void process_manager_create_process(const char* name);
void process_manager_schedule();
void process_run(const char* name);
void process_wait(const char* name);
void process_allocate_memory(const char* name, int size);
void process_deallocate_memory(const char* name);
void memory_manager_allocate(const char* name, int size);
void memory_manager_free(const char* name);
void device_initialize(const char* name);
void device_manager_add_device(const char* name);
void device_manager_list_devices();
void terminal_start();
void terminal_print_help();
void terminal_allocate_memory(const char* process, int size);
void terminal_free_memory(const char* process);
void terminal_start_process(const char* process, int size);
void terminal_list_processes();
void terminal_kill_process(const char* process, bool is_kernel);
void kernel_shutdown();

typedef struct {
    char name[50];
    char state[10];
    int memory_size;
} Process;

Process processes[100];
int process_count = 0;
int memory_allocations[100];
int device_count = 0;
char devices[100][50];

int main() {
    srand(time(NULL));  // Seed the random number generator
    bios_initialize();
    device_manager_add_device("Disk");
    device_manager_add_device("Network Adapter");
    device_manager_list_devices();
    terminal_start();
    return 0;
}

void bios_initialize() {
    printf("BIOS: Initializing hardware components...\n");
    realistic_delay();
    printf("BIOS: Performing POST...\n");
    realistic_delay();
    bootloader_load_kernel();
}

void bootloader_load_kernel() {
    printf("Bootloader: Loading Linux kernel...\n\n");
    realistic_delay();
    kernel_init();
    kernel_start();
}

void kernel_init() {
    // Initialize Kernel components
}

void kernel_start() {
    printf("Kernel: Starting initialization...\n");
    realistic_delay();
    initramfs_load();
    kernel_switch_to_real_root_filesystem();
    init_system_start();
    printf("Kernel: Initialization complete.\n");
    realistic_delay();
}

void kernel_switch_to_real_root_filesystem() {
    printf("Kernel: Switching to real root filesystem...\n");
    realistic_delay();
}

void kernel_shutdown() {
    printf("Kernel: Shutting down system...\n");
    realistic_delay();
    printf("Kernel: Stopping system services...\n");
    realistic_delay();
    terminal_kill_process("init", true);
    realistic_delay();
    printf("Kernel: Unmounting filesystems...\n");
    realistic_delay();
    printf("Kernel: Shutdown complete.\n");
    exit(0);
}

void kernel_panic(const char* reason) {
    /*
    Print panic reason
    List devices from device manager
    Hang the system
    */
    printf("\n\n-[ KERNEL PANIC START\n\n");
    printf("panic: %s\n\n", reason);
    // Additional actions to handle kernel panic can be added here
    printf("panic: List devices\n");
    device_manager_list_devices();
    printf("panic: Version string: %s\n", version);
    printf("panic: We are hanging here...");
    printf("\n\nKERNEL PANIC END ]-\n\n");
    for (;; ) {
        usleep(1); // Infinite sleep timer
    }
}

void initramfs_load() {
    printf("Initramfs: Loading initial RAM disk...\n");
    realistic_delay();
}

void init_system_start() {
    printf("Init System: Starting system services and processes...\n");
    realistic_delay();
    init_system_create_startup_processes();
    process_manager_schedule();
}

void init_system_create_startup_processes() {
    process_manager_create_process("init");
    memory_manager_allocate("init", 31);
}

void process_manager_create_process(const char* name) {
    strcpy(processes[process_count].name, name);
    strcpy(processes[process_count].state, "ready");
    processes[process_count].memory_size = 0;
    process_count++;
    printf("Process Manager: Created process %s\n", name);
}

void process_manager_schedule() {
    printf("Process Manager: Scheduling processes...\n");
    for (int i = 0; i < process_count; i++) {
        process_run(processes[i].name);
        realistic_delay();
        process_wait(processes[i].name);
    }
}

void process_run(const char* name) {
    printf("%s is running...\n", name);
}

void process_wait(const char* name) {
    printf("%s is waiting...\n", name);
}

void memory_manager_allocate(const char* name, int size) {
    for (int i = 0; i < process_count; i++) {
        if (strcmp(processes[i].name, name) == 0) {
            processes[i].memory_size = size;
            break;
        }
    }
    printf("Memory Manager: Allocated %dMB to %s\n", size, name);
}

void memory_manager_free(const char* name) {
    for (int i = 0; i < process_count; i++) {
        if (strcmp(processes[i].name, name) == 0) {
            processes[i].memory_size = 0;
            break;
        }
    }
    printf("Memory Manager: Freed memory from %s\n", name);
}

void device_initialize(const char* name) {
    printf("Device %s: Initialized\n", name);
    realistic_delay();
}

void device_manager_add_device(const char* name) {
    strcpy(devices[device_count], name);
    device_count++;
    device_initialize(name);
}

void device_manager_list_devices() {
    printf("Device Manager: Listing devices...\n");
    for (int i = 0; i < device_count; i++) {
        printf("- %s\n", devices[i]);
    }
}

void terminal_start() {
    printf("\nPYUNIX interactive shell. Type 'help' for commands.\n");
    printf("Kernel version string: %s\n", version);
    char command[100];
    while (1) {
        printf("# ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;  // Remove newline character
        char *cmd = strtok(command, " ");
        if (cmd == NULL) continue;

        if (strcmp(cmd, "help") == 0) {
            terminal_print_help();
        } else if (strcmp(cmd, "allocate") == 0) {
            char *process = strtok(NULL, " ");
            char *size_str = strtok(NULL, " ");
            if (process != NULL && size_str != NULL) {
                int size = atoi(size_str);
                terminal_allocate_memory(process, size);
            } else {
                printf("Usage: allocate <process> <size>\n");
            }
        } else if (strcmp(cmd, "free") == 0) {
            char *process = strtok(NULL, " ");
            if (process != NULL) {
                terminal_free_memory(process);
            } else {
                printf("Usage: free <process>\n");
            }
        } else if (strcmp(cmd, "start") == 0) {
            char *process = strtok(NULL, " ");
            char *size_str = strtok(NULL, " ");
            if (process != NULL && size_str != NULL) {
                int size = atoi(size_str);
                terminal_start_process(process, size);
            } else {
                printf("Usage: start <process> <size>\n");
            }
        } else if (strcmp(cmd, "ps") == 0) {
            terminal_list_processes();
        } else if (strcmp(cmd, "kill") == 0) {
            char *process = strtok(NULL, " ");
            if (process != NULL) {
                terminal_kill_process(process, false);
            } else {
                printf("Usage: kill <process>\n");
            }
        } else if (strcmp(cmd, "exit") == 0) {
            kernel_shutdown();
        } else {
            printf("Unknown command: %s\n", cmd);
        }
    }
}

void terminal_print_help() {
    printf("Available commands:\n");
    printf("  allocate <process> <size> - Allocate memory to a process\n");
    printf("  free <process> - Free memory from a process\n");
    printf("  start <process> <size> - Start a new process with specified memory\n");
    printf("  ps - List all processes\n");
    printf("  kill <process> - Kill a running process\n");
    printf("  exit - Exit the terminal and shut down the system\n");
}

void terminal_allocate_memory(const char* process, int size) {
    memory_manager_allocate(process, size);
}

void terminal_free_memory(const char* process) {
    memory_manager_free(process);
}

void terminal_start_process(const char* process, int size) {
    process_manager_create_process(process);
    memory_manager_allocate(process, size);
    printf("Started process %s with %dMB of memory\n", process, size);
}

void terminal_list_processes() {
    printf("Current running processes:\n");
    for (int i = 0; i < process_count; i++) {
        printf("  - %s: %dMB\n", processes[i].name, processes[i].memory_size);
    }
}

void terminal_kill_process(const char* process, bool is_kernel) {
    if (strcmp(process, "init") == 0 && !is_kernel) {
        kernel_panic("Attempted to kill init!");
        return;
    }

    for (int i = 0; i < process_count; i++) {
        if (strcmp(processes[i].name, process) == 0) {
            for (int j = i; j < process_count - 1; j++) {
                processes[j] = processes[j + 1];
            }
            process_count--;
            printf("Killed process %s\n", process);
            return;
        }
    }
    printf("Process %s not found\n", process);
}
