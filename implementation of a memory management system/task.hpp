#ifndef TASK_MODULE_HPP
#define TASK_MODULE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include "config.hpp" // For NUMBER_OF_PAGES and other configuration constants
#include "memory_manager.hpp" // For PhysicalMemory class

using namespace std;


// Level 2 Page Table
class Level2 {
public:
    vector<int> page_table;

    Level2(unsigned long long int number_of_pages);
    unsigned long long int mappingPage(unsigned long long int virtual_page_address, Memory_manager& physical_memory);
    bool is_page_valid(unsigned long long int virtual_page_address) const;
    unsigned long long int get_physical_frame(unsigned long long int virtual_page_address) const;
    void print_page_table();
};

// Multi Level Page Table
class MultiLevelPageTable {
public:
    unsigned long long int hit = 0, miss = 0;
    vector<Level2*> page_table_first;
    unsigned long long int bits_per_level[NUMBER_OF_LEVELS];
    unsigned long long int bitmask[NUMBER_OF_LEVELS];
    unsigned long long int address[NUMBER_OF_LEVELS];
    


    MultiLevelPageTable();
    unsigned long long int mappingPage(unsigned long long int virtual_page_address, Memory_manager& physical_memory);
    bool check(unsigned long long int virtual_page_address);
    void extract_bits(unsigned long long int virtual_page_address);
};

// Single Level Page Table
class SinglePageTable {
public:
    int* page_table;
    unsigned long long int hit = 0, miss = 0;

    SinglePageTable();
    unsigned long long int mappingPage(unsigned long long int virtual_page_address, Memory_manager& physical_memory);
    bool check(unsigned long long int virtual_page_address) const;
};

// Page Table using a Map
class Map_Implementation {
public:
    unordered_map<int, int> page_table;
    unsigned long long int hit = 0, miss = 0;

    unsigned long long int mappingPage(unsigned long long int virtual_page_address, Memory_manager& physical_memory);
    unsigned long long int check(unsigned long long int virtual_page_address);
    // void print_page_table(); // Uncomment if needed
};

#endif // TASK_MODULE_HPP
