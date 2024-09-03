# Memory-management-system

Project Overview

This project implements a memory management system in C++, designed to simulate how an operating system manages physical and virtual memory. It includes different implementations of page tables (map-based, single-level, and multi-level) and tracks memory usage, page hits, and misses. The system processes memory access requests from tasks, using trace files to simulate real-world scenarios.

Directory Structure

config/: Contains configuration files defining parameters such as page sizes and memory limits.
src/:
memory_manager.cpp, memory_manager.hpp: Implements the memory manager responsible for tracking physical pages and allocating memory.
task.cpp, task.hpp: Manages tasks, including their page tables and memory requests.
io.cpp, io.hpp: Handles input/output operations, including reading trace files and parsing memory requests.
performance.cpp, performance.hpp: Evaluates the performance of different page table implementations, tracking memory usage, hits, and misses.
test.cpp: Contains tests for the system, including generating trace files and validating memory management logic.
traces/: Includes sample trace files used to simulate memory access patterns.
