#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

void vwait();

void initramfs_load()
{
    printf("initramfs: Loading initial RAM disk...\n");
    vwait();
}

void init_system_start()
{
    printf("init: Starting system services and processes...\n");
    vwait();
    init_system_create_startup_processes();
    process_manager_schedule();
}

void init_system_create_startup_processes()
{
    process_manager_create_process("init");
    memory_manager_allocate("init", 32);
}

#endif // INIT_H_INCLUDED
