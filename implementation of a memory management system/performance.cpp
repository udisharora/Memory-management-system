#include "performance.hpp"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "config.hpp"
using namespace std;


unsigned long long int map_implementation(unsigned long long int logical_address, unsigned long long int memory_req, Map_Implementation& page_table, Memory_manager& physical_memory) {
    unsigned long long int num_pages = (memory_req + PAGE_SIZE - 1) / PAGE_SIZE; 
    unsigned long long int address = logical_address >> OFFSET_BITS;
    unsigned long long int offset = logical_address & ((1 << OFFSET_BITS) - 1);
    for (unsigned long long int i = 0; i < num_pages; i++) {
        if (page_table.check(address + i) == -1ULL) { 
            page_table.hit++;  
        } else {
            page_table.miss++; 
        }
    }
    for (unsigned long long int i = 0; i < num_pages; i++) {
        unsigned long long int physical_frame = page_table.mappingPage(address + i, physical_memory);
        if (physical_frame != -1ULL) {
            physical_frame = physical_frame << OFFSET_BITS;
            physical_frame += offset;
            
        }
    }
    return num_pages * PAGE_SIZE;
}

unsigned long long int single_implementation(unsigned long long int logical_address, unsigned long long int memory_req, SinglePageTable& page_table, Memory_manager& physical_memory) {
    unsigned long long int num_pages = (memory_req + PAGE_SIZE - 1) / PAGE_SIZE; 
    unsigned long long int address = logical_address >> OFFSET_BITS;
    unsigned long long int offset = logical_address & ((1 << OFFSET_BITS) - 1);
    for (unsigned long long int i = 0; i < num_pages; i++) {
        if (page_table.check(address + i) == 0) {
            page_table.hit++;  
        } else {
            page_table.miss++; 
        }
    }
    for (unsigned long long int i = 0; i < num_pages; i++) {
        unsigned long long int physical_frame = page_table.mappingPage(address + i, physical_memory);
        if (physical_frame != -1ULL) {
            physical_frame = physical_frame << OFFSET_BITS;
            physical_frame += offset;
            
        }
    }
    return num_pages * PAGE_SIZE;
}

unsigned long long int multi_implementation(unsigned long long int logical_address, unsigned long long int memory_req, MultiLevelPageTable& page_table, Memory_manager& physical_memory) {
    unsigned long long int num_pages = (memory_req + PAGE_SIZE - 1) / PAGE_SIZE;  
    unsigned long long int address = logical_address >> OFFSET_BITS;
    unsigned long long int offset = logical_address & ((1 << OFFSET_BITS) - 1);
    for (unsigned long long int i = 0; i < num_pages; i++) {
        if (page_table.check(address + i) == 1) {
            page_table.hit++;  
        } else {
            page_table.miss++; 
        }
    }
    for (unsigned long long int i = 0; i < num_pages; i++) {
        unsigned long long int physical_frame = page_table.mappingPage(address + i, physical_memory);
        if (physical_frame != -1ULL) {
            physical_frame = physical_frame << OFFSET_BITS;
            physical_frame += offset;
        }
    }
    return num_pages * PAGE_SIZE;
}

pair<int, int> method_1_mapping(const string& filename) {
    Memory_manager physical_memory;
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error: Could not open file " << filename << endl;
        return {-1, -1};
    }

    string input;
    unordered_map<int, Map_Implementation> task_table_map;
    unsigned long long int total_memory_allocated = 0, num_page_tables=0;
    while (getline(inputFile, input)) {
        unsigned long long int task_num, logical_address, memory_req;
        parseInput(input, task_num, logical_address, memory_req);

        // Create a PageTableMap if it does not exist
        if (task_table_map.find(task_num) == task_table_map.end()) {
            task_table_map[task_num] = Map_Implementation();
            num_page_tables++;
        }

        unsigned long long int memory_allocated = 0;
        // Process the task
        //memory allocation
        memory_allocated = map_implementation(logical_address, memory_req, task_table_map[task_num], physical_memory);
        total_memory_allocated += memory_allocated;
    }

    int total_hits = 0;
    int total_misses = 0;
    for (auto x : task_table_map) {
        Map_Implementation pt = x.second;
        unsigned long long int hit = pt.hit;
        unsigned long long int miss = pt.miss;
        total_hits += hit;
        total_misses += miss;
    }
    cout << "Total hits of map implementation: " << total_hits << " Total misses: " << total_misses << endl;
    return {total_memory_allocated, num_page_tables};
}

pair<int, int> method2_2_single(const string& filename) {
    Memory_manager physical_memory;
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error: Could not open file " << filename << endl;
        return {-1, -1};
    }

    string input;
    unordered_map<int, SinglePageTable> task_table_single;
    unsigned long long int total_memory_allocated = 0, num_page_tables = 0;
    while (getline(inputFile, input)) {
        unsigned long long int task_num, logical_address, memory_req;
        parseInput(input, task_num, logical_address, memory_req);

        // Create a SinglePageTable if it does not exist
        if (task_table_single.find(task_num) == task_table_single.end()) {
            task_table_single[task_num] = SinglePageTable();
            num_page_tables++;
        }

        // Process the task
        unsigned long long int memory_allocated = 0;
        memory_allocated = single_implementation(logical_address, memory_req, task_table_single[task_num], physical_memory);
        total_memory_allocated += memory_allocated;
        
    }
    int total_hits = 0;
    int total_misses = 0;
    for (auto x : task_table_single) {
        SinglePageTable pt = x.second;
        unsigned long long int hit = pt.hit;
        unsigned long long int miss = pt.miss;
        total_hits += hit;
        total_misses += miss;
    }
    cout << "Total hits of single implementation: " << total_hits << " Total misses: " << total_misses << endl;
    return {total_memory_allocated, num_page_tables};
}

pair<int, int> method3_3_multi(const string& filename) {
    Memory_manager physical_memory;
    ifstream inputFile(filename);

    string input;
    unordered_map<int, MultiLevelPageTable> task_table_multi;
    unsigned long long int totall_memory_allocated = 0, num_page_tables = 0;
    while (getline(inputFile, input)) {
        unsigned long long int task_num, logical_address, memory_req;
        parseInput(input, task_num, logical_address, memory_req);

        // Create a MultiLevelPageTable if it does not exist
        if (task_table_multi.find(task_num) == task_table_multi.end()) {
            task_table_multi[task_num] = MultiLevelPageTable();
            num_page_tables++;
        }

        // Process the task
        unsigned long long int memory_allocated;
        memory_allocated = multi_implementation(logical_address, memory_req, task_table_multi[task_num], physical_memory);
        totall_memory_allocated += memory_allocated;
        

    }
    int total_hits = 0;
    int total_misses = 0;
    for (auto x : task_table_multi) {
        MultiLevelPageTable pageTable = x.second;
        unsigned long long int hit = pageTable.hit;
        unsigned long long int miss = pageTable.miss;
        total_hits += hit;
        total_misses += miss;
    }
    cout << "Total hits of 2 level inplementation: " << total_hits << " Total misses: " << total_misses << endl;
    return {totall_memory_allocated, num_page_tables};

}

int main() {
    string filename = FILE_NAME;
    

    unsigned long long int tot_alloc = 0, num_page_tables = 0;

    // Record start time
    clock_t startTime1 = clock();
    pair<int, int> mem_map = method_1_mapping(filename);
    clock_t endTime1 = clock();
    double execTime1 = double(endTime1 - startTime1) / CLOCKS_PER_SEC;
    cout << "Execution Time of mapping based page table: " << execTime1  << endl;

    clock_t startTime2 = clock();
    pair<int, int> mem_single = method2_2_single(filename);
    clock_t endTime2 = clock();
    double execTime2 = double(endTime2 - startTime2) / CLOCKS_PER_SEC;
    cout << "Execution Time of single based page table: " << execTime2 << endl;

    clock_t startTime3 = clock();
    pair<int, int> mem_multi = method3_3_multi(filename);
    clock_t endTime3 = clock();
    double execTime3 = double(endTime3 - startTime3) / CLOCKS_PER_SEC;
    cout << "Execution Time of multi based page table: " << execTime3 << endl;


    tot_alloc = mem_map.first + mem_single.first + mem_multi.first;
    num_page_tables = mem_map.second + mem_single.second + mem_multi.second;

    unsigned long long int avail = (PHYSICAL_MEMORY_SIZE > tot_alloc) ? (PHYSICAL_MEMORY_SIZE - tot_alloc) : 0;
    string mem_avail = formatSize(avail);

    cout << "Free Available Memory: " << mem_avail << endl;
    unsigned long long int mem_for_page_table = num_page_tables * PAGE_TABLE_SIZE;
    cout << "Memory allocated to the page tables: " << mem_for_page_table << endl;

    return 0; 
}

