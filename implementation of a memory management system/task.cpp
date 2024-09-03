#include "task.hpp"
#include "memory_manager.hpp"
#include "config.hpp"
#include <iostream>

using namespace std;

//first is the map implementation of the pagetable
//this first function is to map 
unsigned long long int Map_Implementation::mappingPage(unsigned long long int virtualAddress, Memory_manager& physical_memory) {
    
    if (virtualAddress >= VIRTUAL_MEMORY_SIZE) {
        cout << "Invalid";
        return -1ULL;
    }

    unsigned long long int physicalAddress = physical_memory.allocate_page();
    if (physicalAddress == static_cast<unsigned long long int>(-1)) {
        return static_cast<unsigned long long int>(-1);
    }

    page_table[virtualAddress] = physicalAddress;
    return physicalAddress;
}

unsigned long long int Map_Implementation::check(unsigned long long int virtual_page_address) {
    if (page_table.find(virtual_page_address) != page_table.end()) {
        return -1ULL;
    }
    return 1;
}

//single level implementation

SinglePageTable::SinglePageTable() {
    page_table = new int[NUMBER_OF_PAGES];
    for (int i = 0; i < (static_cast<int>(NUMBER_OF_PAGES)); i++) {
        page_table[i] = 0;
    }
}

unsigned long long int SinglePageTable::mappingPage(unsigned long long int virtualAddress, Memory_manager& physical_memory) {
    if (virtualAddress >= NUMBER_OF_PAGES) {
        cout << "Invalid";
        return -1ULL;
    }

    unsigned long long int physicalAddress = physical_memory.allocate_page();
    if (physicalAddress == static_cast<unsigned long long int>(-1)) {
        return -1ULL;
    }

    page_table[static_cast<int>(virtualAddress)] = (physicalAddress << OFFSET_BITS) | 1;

    return physicalAddress;
}

bool SinglePageTable::check(unsigned long long int virtual_page_address) const {
    return (page_table[static_cast<int>(virtual_page_address)] & 1) == 0;
}


// Two-Level Page Table Implementation
MultiLevelPageTable::MultiLevelPageTable() {
    // Initialize bitmasks and bit lengths for each level
    bits_per_level[0] = (VIRTUAL_MEMORY_SIZE_BITS + 1) / 2;
    bitmask[0] = (1ULL << bits_per_level[0]) - 1;
    bits_per_level[1] = VIRTUAL_MEMORY_SIZE_BITS - bits_per_level[0];
    bitmask[1] = (1ULL << bits_per_level[1]) - 1;

    // Initialize the first level page table
    page_table_first.resize(1ULL << bits_per_level[0], nullptr);
}

unsigned long long int MultiLevelPageTable::mappingPage(unsigned long long int virtual_page_address, Memory_manager& physical_memory) {
    // Extract bits for each level from the virtual page address
    extract_bits(virtual_page_address);

    // If the first-level entry is null, create a new second-level page table
    if (page_table_first[address[0]] == nullptr) {
        page_table_first[address[0]] = new Level2(1ULL << bits_per_level[1]);
    }

    // Insert the page into the second-level page table and return the physical address
    return page_table_first[address[0]]->mappingPage(address[1], physical_memory);
}

bool MultiLevelPageTable::check(unsigned long long int virtual_page_address) {
    // Extract bits for each level from the virtual page address
    extract_bits(virtual_page_address);

    // Check if the first-level entry exists and is valid
    if (page_table_first[address[0]] == nullptr) {
        return false;
    }

    // Check if the page is valid in the second-level page table
    return page_table_first[address[0]]->is_page_valid(address[1]);
}

void MultiLevelPageTable::extract_bits(unsigned long long int virtual_page_address) {
    // Extract the relevant bits for each level of the page table
    for (unsigned long long int i = 0; i < 2; i++) {
        address[i] = virtual_page_address & bitmask[i];
        virtual_page_address >>= bits_per_level[i];
    }
}

// Level 2 Page Table Implementation
Level2::Level2(unsigned long long int number_of_pages)
    : page_table(number_of_pages, 0) {}

unsigned long long int Level2::mappingPage(unsigned long long int virtual_page_address, Memory_manager& physical_memory) {
    // Allocate a physical page
    unsigned long long int physical_frame_address = physical_memory.allocate_page();

    // If no physical memory is available, return -1
    if (physical_frame_address == static_cast<unsigned long long int>(-1)) {
        return static_cast<unsigned long long int>(-1ULL);
    }

    // Store the physical address in the page table with a valid bit
    page_table[virtual_page_address] = (physical_frame_address << OFFSET_BITS) | 1;
    return physical_frame_address;
}

bool Level2::is_page_valid(unsigned long long int virtual_page_address) const {
    // Check if the page is valid by examining the valid bit
    return (page_table[virtual_page_address] & 1) != 0;
}

unsigned long long int Level2::get_physical_frame(unsigned long long int virtual_page_address) const {
    // Return the physical frame address if the page is valid
    if (is_page_valid(virtual_page_address)) {
        return page_table[virtual_page_address] >> OFFSET_BITS;
    }
    return static_cast<unsigned long long int>(-1ULL);
}



