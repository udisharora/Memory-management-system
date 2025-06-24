# 🧠 Implementation of a Memory Management System

A simulation-based **C++** project by **Udish Arora** that models **virtual memory management** using three approaches to page table implementation: **map-based**, **single-level**, and **two-level page tables**. It processes a trace file containing memory access requests and evaluates memory usage and performance metrics like page hits and misses.

---

## 📌 Features

- Supports 3 types of page table implementations:
  - Map-based
  - Single-level page table
  - Two-level page table
- Reads a large trace file (~1,000,000 entries)
- Calculates:
  - Page hits and misses per task
  - Physical memory allocated
  - Total memory required for page tables
  - Execution time for each method
- Configurable virtual and physical memory parameters
- Modular design with separate components:
  - Memory Manager
  - Task Manager
  - I/O Module
  - Performance Module
  - Trace Generator (Test Module)

---

## 📁 Project Structure

```
memory_management_system/
│
├── 📁 include/                 # Header files
│   ├── config.h               # Configurable parameters
│   ├── MemoryManager.h
│   ├── Task.h
│   ├── IO_Module.h
│   └── PerformanceModule.h
│
├── 📁 src/                     # Implementation files
│   ├── MemoryManager.cpp
│   ├── Task.cpp
│   ├── IO_Module.cpp
│   └── PerformanceModule.cpp
│
├── 📁 traces/                  # Sample and generated trace files
│   └── trace.txt
│
├── 📁 test/                    # Test module for generating traces
│   └── generate_trace.cpp
│
├── main.cpp                   # Main entry point
├── Makefile                   # Build configuration
└── README.md                  # Project documentation
```

---

## 🛠️ Installation & How to Run the Project

### Step 1: Clone the Repository

```bash
git clone https://github.com/yourusername/memory-management-system.git
cd memory-management-system
```

### Step 2: Build the Project

```bash
make
```

### Step 3: Run the Executable

```bash
./main
```

> 💡 **Note for Windows users:** Use `main.exe` instead of `./main`:
> ```bash
> main.exe
> ```

### Step 4 (Optional): Clean the Build

```bash
make clean
```

This will remove all object files and the compiled executable.

---

## 📦 Trace File Format

Each line in the trace:
```
<TaskID>: <HexAddress>: <Size>
```

Example:
```
T1: 0x00401000: 4KB
T2: 0x00802000: 1MB
```

---

## 📊 Output Example

```
--- MAP IMPLEMENTATION ---
Task T1: Hits = 5000, Misses = 1200
Task T2: Hits = 4000, Misses = 1500
Total Page Table Memory = 64 KB
Execution Time = 2.1 seconds

--- SINGLE-LEVEL IMPLEMENTATION ---
...

--- TWO-LEVEL IMPLEMENTATION ---
...
```

---

## 🔧 Configuration

Modify `include/config.h` to adjust:

- Virtual memory size (`2^N`)
- Physical memory size (`2^M`)
- Page sizes
- Multi-level table parameters

---

## 📉 Limitations

- Assumes address alignment to page boundaries  
- Trace parsing assumes strict input format  
- Does not simulate actual page replacement algorithms  

---

## 🚀 Future Improvements

- Add page replacement (LRU, FIFO)  
- GUI for real-time simulation  
- Support for variable-size pages  
- More accurate physical memory modeling  

---

## 📬 Author

Made with 🧡 by **Udish Arora**

---

## 📜 License

This project is licensed under the [MIT License](LICENSE)
