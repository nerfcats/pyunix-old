#ifndef KERNEL_H_INCLUDED
#define KERNEL_H_INCLUDED

const char version[] = "PYunix microkernel v0.3.0-alpha";

// Kernel calls
void kernel_init();
void kernel_start();
void kernel_switch_to_real_root_filesystem();
void kernel_shutdown();
void kernel_panic(const char* reason);
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

void kernel_init() {
    // Initialize Kernel components
}

void kernel_start() {
    printf("kernel: Initializing...\n");
    vwait();
    initramfs_load();
    kernel_switch_to_real_root_filesystem();
    init_system_start();
    printf("kernel: Initialization complete.\n");
    vwait();
}

void kernel_switch_to_real_root_filesystem() {
    printf("kernel: Switching to root filesystem...\n");
    vwait();
}

void kernel_shutdown() {
    printf("kernel: Shutting down system...\n");
    printf("kernel: Stopping system services...\n");
    vwait();
    terminal_kill_process("init", true);
    vwait();
    printf("kernel: Unmounting filesystems...\n");
    vwait();
    printf("kernel: Ready to power off\n");
    exit(0);
}

void kernel_panic(const char* reason) {
    /*
    Print panic reason
    List devices from device manager
    Hang the system
    */
    vwait();
    printf("\n\n-[ KERNEL PANIC START\n\n");
    printf("KERNEL PANIC! ):\n");
    printf("Kernel panic - not syncing: %s\n\n", reason);
    // Additional actions to handle kernel panic can be added here
    vwait();
    device_manager_list_devices();
    printf("Version string: %s\n", version);
    printf("Dumping memory\n");
    for (int i = 0; i < process_count; i++) {
        printf("  - %s: %dMB\n", processes[i].name, processes[i].memory_size);
    }
    printf("Please report this error on Github if possible!\n");
    printf("We are hanging here...");
    printf("\n\nKERNEL PANIC END ]-\n");

    // Hang the system to prevent other stuff from happening
    for (;; ) {
        usleep(1);
    }
}

void initramfs_load() {
    printf("initramfs: Loading initial RAM disk...\n");
    vwait();
}

void init_system_start() {
    printf("init: Starting system services and processes...\n");
    vwait();
    init_system_create_startup_processes();
    process_manager_schedule();
}

void init_system_create_startup_processes() {
    process_manager_create_process("init");
    memory_manager_allocate("init", 32);
}

void process_manager_create_process(const char* name) {
    strcpy(processes[process_count].name, name);
    strcpy(processes[process_count].state, "ready");
    processes[process_count].memory_size = 0;
    process_count++;
    printf("process_manager: Created process %s\n", name);
}

void process_manager_schedule() {
    printf("process_manager: Scheduling processes...\n");
    for (int i = 0; i < process_count; i++) {
        process_run(processes[i].name);
        vwait();
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
    printf("mem_manager: Allocated %dMB to %s\n", size, name);
}

void memory_manager_free(const char* name) {
    for (int i = 0; i < process_count; i++) {
        if (strcmp(processes[i].name, name) == 0) {
            processes[i].memory_size = 0;
            break;
        }
    }
    printf("mem_manager: Freed memory from %s\n", name);
}

void device_initialize(const char* name) {
    printf("Device %s: Initialized\n", name);
    vwait();
}

void device_manager_add_device(const char* name) {
    strcpy(devices[device_count], name);
    device_count++;
    device_initialize(name);
}

void device_manager_list_devices() {
    printf("dev_manager: Listing devices...\n");
    for (int i = 0; i < device_count; i++) {
        printf("- %s\n", devices[i]);
    }
}

#endif // KERNEL_H_INCLUDED
