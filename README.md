# PYunix
PYunix (pico unix) is a tiny kernel/microkernel simulation program with a functional terminal and multiple kernel system calls. It mimics and is basically an oversimplifed version of the Linux kernel, that you can run as one program itself.
## Installation
You can build with a C/C++ compiler such as GCC, or download and run the already compiled .exe file. Building from source builds the latest version, but it may not be stable.

I tested this on Windows and Linux, you need something like gcc or mingw because PYunix uses some libraries only available in Unix (e.g. unistd.h).

It is possible to run this on Android since there are some C/C++ IDEs for Android.
## Contributing and Editing

Contributions to PYUNIX are very welcome. I am a beginner so help is appreciated :)
## Terminal Commands
Running `help` in the terminal shows available commands. Updated as of `0.1.0`
```
allocate <process> <size> - Allocate memory to a process
free <process> - Free memory from a process
start <process> <size> - Start a new process with specified memory
ps - List all processes that are currently running
kill <process> - Kill a running process
exit - Exit the terminal and shut down the system
```
Currently only commands are for managing processes (that do nothing, lol). I plan to add more, for example creating, editing, deleting files, etc.
## System Calls
These are the various system calls you can use to interact with the mini PYUNIX kernel. Updated as of `0.1.0`
```
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
void terminal_start();
void terminal_print_help();
void terminal_allocate_memory(const char* process, int size);
void terminal_free_memory(const char* process);
void terminal_start_process(const char* process, int size);
void terminal_list_processes();
void terminal_kill_process(const char* process, bool is_kernel);
```
The `terminal_kill_process()` call includes a `is_kernel` attribute. Attempting to kill a system process such as `init` initiates a kernel panic.
However, if `is_kernel` is set to true, the system process protection is overrided.

`kernel_init()`: This call is ran before the kernel is started. It does nothing, but you can put code to run there before the kernel is started.

`kernel_start()`: Initializes the kernel.

`kernel_switch_to_real_root_file_system()`: Switches from initramfs to root file system.

`kernel_shutdown()`: Kills init and shuts down system. (TO-DO: kill all running processes).

`kernel_panic(reason)`: Initiates a kernel panic. Reason, connected devices, and version string spat out before hanging the system.
