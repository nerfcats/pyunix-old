#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED

void vwait();

// Terminal functions
void terminal_start(); // Start terminal
void terminal_print_help(); // Print help
void terminal_allocate_memory(const char* process, int size); // Allocate
void terminal_free_memory(const char* process); // Free memory from process
void terminal_start_process(const char* process, int size); // Start process
void terminal_list_processes(); // List processes
void terminal_kill_process(const char* process, bool is_kernel); // Kill process
void terminal_echo(const char* text);

void terminal_start()
{
    printf("\nPYunix interactive shell. Type 'help' for commands.\n");
    printf("Version: %s\n", version);
    printf("WARNING: This is a development version of PYunix. Things may break.\n");
    printf("For the latest version of PYunix, go to https://github.com/noahdossan/pyunix/releases\n\n");
    char command[100];
    while (1 && strcmp(kernel_state, "running") == 0)
    {
        printf("# ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;  // Remove newline character
        char *cmd = strtok(command, " ");
        if (cmd == NULL) continue;

        if (strcmp(cmd, "help") == 0)
        {
            terminal_print_help();
        }
        else if (strcmp(cmd, "allocate") == 0)
        {
            char *process = strtok(NULL, " ");
            char *size_str = strtok(NULL, " ");
            if (process != NULL && size_str != NULL)
            {
                int size = atoi(size_str);
                terminal_allocate_memory(process, size);
            }
            else
            {
                printf("Usage: allocate <process> <size>\n");
            }
        }
        else if (strcmp(cmd, "free") == 0)
        {
            char *process = strtok(NULL, " ");
            if (process != NULL)
            {
                terminal_free_memory(process);
            }
            else
            {
                printf("Usage: free <process>\n");
            }
        }
        else if (strcmp(cmd, "start") == 0)
        {
            char *process = strtok(NULL, " ");
            char *size_str = strtok(NULL, " ");
            if (process != NULL && size_str != NULL)
            {
                int size = atoi(size_str);
                terminal_start_process(process, size);
            }
            else
            {
                printf("Usage: start <process> <size>\n");
            }
        }
        else if (strcmp(cmd, "ps") == 0)
        {
            terminal_list_processes();
        }
        else if (strcmp(cmd, "kill") == 0)
        {
            char *process = strtok(NULL, " ");
            if (process != NULL)
            {
                terminal_kill_process(process, false);
            }
            else
            {
                printf("Usage: kill <process>\n");
            }
        }
        else if (strcmp(cmd, "exit") == 0)
        {
            kernel_shutdown(false);
        }
        else if (strcmp(cmd, "echo") == 0)
        {
            char *text = command + 5;  // Skip "echo "
            if (*text != '\0')
            {
                terminal_echo(text);
            }
            else
            {
                printf("Usage: echo <string>\n");
            }
        }
        else if (strcmp(cmd, "reboot") == 0)
        {
            kernel_shutdown(true);
        }
        else
        {
            printf("Unknown command: %s; type 'help' for available commands\n", cmd);
        }
    }
    kernel_oops("Terminal loop broken");
}



void terminal_print_help()
{
    printf("Available commands:\n");
    printf("  allocate <process> <size> - Allocate memory to a process\n");
    printf("  free <process> - Free memory from a process\n");
    printf("  start <process> <size> - Start a new process with specified memory\n");
    printf("  ps - List all processes\n");
    printf("  kill <process> - Kill a running process\n");
    printf("  echo <string> - Repeat text with specified string\n");
    printf("  exit - Exit the terminal and shut down the system\n");
}

void terminal_allocate_memory(const char* process, int size)
{
    memory_manager_allocate(process, size);
}

void terminal_free_memory(const char* process)
{
    memory_manager_free(process);
}

void terminal_start_process(const char* process, int size)
{
    process_manager_create_process(process);
    memory_manager_allocate(process, size);
    printf("Started process %s with %dMB of memory\n", process, size);
}

void terminal_list_processes()
{
    printf("Current running processes:\n");
    for (int i = 0; i < process_count; i++)
    {
        printf("  - %s: %dMB\n", processes[i].name, processes[i].memory_size);
    }
}

void terminal_kill_process(const char* process, bool is_kernel)
{
    if (strcmp(process, "init") == 0 && !is_kernel)
    {
        kernel_panic("Attempted to kill init! Process protected: is_kernel from system call was false");
        return;
    }

    for (int i = 0; i < process_count; i++)
    {
        if (strcmp(processes[i].name, process) == 0)
        {
            memory_manager_free(process);
            for (int j = i; j < process_count - 1; j++)
            {
                processes[j] = processes[j + 1];
            }
            process_count--;
            printf("Killed process %s\n", process);
            return;
        }
    }
    printf("Process %s not found.\n", process);
}

void terminal_echo(const char* text)
{
    printf("%s\n", text);
}

#endif // TERMINAL_H_INCLUDED
