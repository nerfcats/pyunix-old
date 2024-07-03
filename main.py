import time
import random
import os

def realistic_delay():
    time.sleep(random.uniform(0.05, 0.1))

class BIOS:
    def initialize(self):
        print("BIOS: Initializing hardware components...")
        realistic_delay()
        print("BIOS: Performing POST...")
        realistic_delay()
        bootloader = Bootloader()
        kernel = bootloader.load_kernel()
        return kernel

class Bootloader:
    def load_kernel(self):
        print("Bootloader: Loading Linux kernel...")
        realistic_delay()
        kernel = Kernel()
        kernel.start()
        return kernel

class Kernel:
    def __init__(self):
        self.initramfs = Initramfs()
        self.init_system = InitSystem()
        self.memory_manager = MemoryManager()
        self.process_manager = ProcessManager()

    def start(self):
        print("Kernel: Starting initialization...")
        realistic_delay()
        self.initramfs.load()
        self.switch_to_real_root_filesystem()
        self.init_system.start()
        print("Kernel: Initialization complete.")
        realistic_delay()

    def switch_to_real_root_filesystem(self):
        print("Kernel: Switching to real root filesystem...")
        realistic_delay()

    def shutdown(self):
        print("Kernel: Shutting down system...")
        realistic_delay()
        print("Kernel: Stopping system services...")
        realistic_delay()
        print("Kernel: Unmounting filesystems...")
        realistic_delay()
        print("Kernel: Shutdown complete.")
        exit(0)

class Initramfs:
    def load(self):
        print("Initramfs: Loading initial RAM disk...")
        realistic_delay()

class InitSystem:
    def __init__(self):
        self.process_manager = ProcessManager()

    def start(self):
        print("Init System: Starting system services and processes...")
        realistic_delay()
        self.create_startup_processes()
        self.process_manager.schedule()

    def create_startup_processes(self):
        global global_process_manager
        global_process_manager = ProcessManager()  # Resetting the global process manager
        global_process_manager.create_process("InitProcess1")
        global_process_manager.create_process("InitProcess2")
        print("Initial processes created:", global_process_manager.list_processes())

class Process:
    def __init__(self, name):
        self.name = name
        self.state = "ready"
        self.memory_size = 0

    def run(self):
        self.state = "running"
        print(f"{self.name} is running...")

    def wait(self):
        self.state = "waiting"
        print(f"{self.name} is waiting...")

    def allocate_memory(self, size):
        self.memory_size = size

    def deallocate_memory(self):
        self.memory_size = 0

class ProcessManager:
    def __init__(self):
        self.processes = []

    def create_process(self, name):
        process = Process(name)
        self.processes.append(process)
        print(f"Process Manager: Created process {name}")
        return process

    def schedule(self):
        print("Process Manager: Scheduling processes...")
        for process in self.processes:
            process.run()
            realistic_delay()
            process.wait()

    def list_processes(self):
        return self.processes

    def get_process(self, name):
        for process in self.processes:
            if process.name.lower() == name.lower():
                return process
        return None

    def kill_process(self, name):
        for process in self.processes:
            if process.name.lower() == name.lower():
                print(f"Killing process: {process.name}")
                self.processes.remove(process)
                return
        print(f"Process {name} not found")

    def allocate_memory(self, process, size):
        process.allocate_memory(size)
        print(f"Memory Manager: Allocated {size}MB to {process.name}")

    def deallocate_memory(self, process):
        process.deallocate_memory()
        print(f"Memory Manager: Freed memory from {process.name}")

class MemoryManager:
    def __init__(self):
        self.memory = {}

    def allocate(self, process, size):
        self.memory[process.name] = size
        print(f"Memory Manager: Allocated {size}MB to {process.name}")

    def free(self, process):
        if process.name in self.memory:
            del self.memory[process.name]
            print(f"Memory Manager: Freed memory from {process.name}")

    def get_allocation(self, process):
        return self.memory.get(process.name, 0)

class Device:
    def __init__(self, name):
        self.name = name

    def initialize(self):
        print(f"Device {self.name}: Initialized")
        realistic_delay()

class DeviceManager:
    def __init__(self):
        self.devices = []

    def add_device(self, name):
        device = Device(name)
        self.devices.append(device)
        device.initialize()

    def list_devices(self):
        print("Device Manager: Listing devices...")
        for device in self.devices:
            print(f"- {device.name}")

class Terminal:
    def __init__(self, kernel):
        self.kernel = kernel
        self.process_manager = kernel.process_manager
        self.memory_manager = kernel.memory_manager

    def start(self):
        print("Terminal: Starting interactive shell. Type 'help' for commands.")
        while True:
            command = input("> ").strip().split()
            if not command:
                continue
            cmd = command[0]
            if cmd == "help":
                self.print_help()
            elif cmd == "allocate":
                self.allocate_memory(command)
            elif cmd == "free":
                self.free_memory(command)
            elif cmd == "start":
                self.start_process(command)
            elif cmd == "ps":
                self.list_processes()
            elif cmd == "kill":
                self.kill_process(command)
            elif cmd == "exit":
                self.kernel.shutdown()
            else:
                print(f"Unknown command: {cmd}")

    def print_help(self):
        print("Available commands:")
        print("  allocate <process> <size> - Allocate memory to a process")
        print("  free <process> - Free memory from a process")
        print("  start <process> <size> - Start a new process with specified memory")
        print("  ps - List all processes")
        print("  kill <process> - Kill a running process")
        print("  exit - Exit the terminal and shut down the system")

    def allocate_memory(self, command):
        if len(command) != 3:
            print("Usage: allocate <process> <size>")
            return
        process_name = command[1]
        size = int(command[2])
        process = self.process_manager.get_process(process_name)
        if process:
            self.memory_manager.allocate(process, size)
        else:
            print(f"Process {process_name} not found")

    def free_memory(self, command):
        if len(command) != 2:
            print("Usage: free <process>")
            return
        process_name = command[1]
        process = self.process_manager.get_process(process_name)
        if process:
            self.memory_manager.free(process)
        else:
            print(f"Process {process_name} not found")

    def start_process(self, command):
        if len(command) != 3:
            print("Usage: start <process> <size>")
            return
        process_name = command[1]
        size = int(command[2])
        process = self.process_manager.create_process(process_name)
        self.memory_manager.allocate(process, size)
        print(f"Started process {process_name} with {size}MB of memory")

    def list_processes(self):
        processes = self.process_manager.list_processes()
        if processes:
            print("Current running processes:")
            for process in processes:
                memory = self.memory_manager.get_allocation(process)
                print(f"  - {process.name}: {memory}MB")
        else:
            print("No running processes")

    def kill_process(self, command):
        if len(command) != 2:
            print("Usage: kill <process>")
            return
        process_name = command[1]
        self.process_manager.kill_process(process_name)
        print(f"Killed process {process_name}")

def main():
    os.system("cls")
    bios = BIOS()
    kernel = bios.initialize()

    device_manager = DeviceManager()
    device_manager.add_device("Disk")
    device_manager.add_device("Network Adapter")
    device_manager.list_devices()

    terminal = Terminal(kernel)
    terminal.start()

if __name__ == "__main__":
    main()
