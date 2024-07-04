#ifndef PROC_MAN_H_INCLUDED
#define PROC_MAN_H_INCLUDED

void vwait();

void process_manager_create_process(const char* name)
{
    strcpy(processes[process_count].name, name);
    strcpy(processes[process_count].state, "ready");
    processes[process_count].memory_size = 0;
    process_count++;
    printf("process_manager: Created process %s\n", name);
}

void process_manager_schedule()
{
    printf("process_manager: Scheduling processes...\n");
    for (int i = 0; i < process_count; i++)
    {
        process_run(processes[i].name);
        vwait();
        process_wait(processes[i].name);
    }
}

void process_run(const char* name)
{
    printf("%s is running...\n", name);
}

void process_wait(const char* name)
{
    printf("%s is waiting...\n", name);
}

#endif // PROC_MAN_H_INCLUDED
