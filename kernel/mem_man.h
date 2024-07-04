#ifndef MEM_MAN_H_INCLUDED
#define MEM_MAN_H_INCLUDED

void vwait();

void memory_manager_allocate(const char* name, int size)
{
    for (int i = 0; i < process_count; i++)
    {
        if (strcmp(processes[i].name, name) == 0)
        {
            processes[i].memory_size = size;
            break;
        }
    }
    printf("mem_manager: Allocated %dMB to %s\n", size, name);
}

void memory_manager_free(const char* name)
{
    for (int i = 0; i < process_count; i++)
    {
        if (strcmp(processes[i].name, name) == 0)
        {
            processes[i].memory_size = 0;
            break;
        }
    }
    printf("mem_manager: Freed memory from %s\n", name);
}

#endif // MEM_MAN_H_INCLUDED
