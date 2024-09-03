#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <cmath>
#include <cstdint>

// Define constants and macros related to memory management

// Page size in bytes
#define PAGE_SIZE (1ULL << 11) 

// Virtual memory size in bytes
#define VIRTUAL_MEMORY_SIZE (1ULL << 30) 

// Physical memory size in bytes
#define PHYSICAL_MEMORY_SIZE (1ULL << 31) 

// Number of levels in the page table
#define NUMBER_OF_LEVELS 2

// Number of pages and frames
#define NUMBER_OF_PAGES (VIRTUAL_MEMORY_SIZE / PAGE_SIZE)
#define NUMBER_OF_FRAMES (PHYSICAL_MEMORY_SIZE / PAGE_SIZE)

// Size of the page table in bytes
#define PAGE_TABLE_SIZE (NUMBER_OF_PAGES * sizeof(uint32_t))

// Number of bits for page offset and addresses
#define OFFSET_BITS 11// log2(PAGE_SIZE)
#define VIRTUAL_MEMORY_SIZE_BITS 30 // log2(VIRTUAL_MEMORY_SIZE)
#define PHYSICAL_MEMORY_SIZE_BITS 31 // log2(PHYSICAL_MEMORY_SIZE)

// Bits used for virtual and physical page addresses
#define BITS_VIRTUAL_PAGE_ADDRESS (log2(VIRTUAL_MEMORY_SIZE) - log2(PAGE_SIZE))
#define BITS_PHYSICAL_PAGE_ADDRESS (log2(PHYSICAL_MEMORY_SIZE) - log2(PAGE_SIZE))

// Define starting addresses and section sizes
#define START_ADDR 0x10000000ULL // Example starting address for the task sections
#define FILE_NAME "tracefile_2KB_4GB_8GB.txt"
#define SECTION_SIZE (1ULL << 20) // Example section size of 1 MB

#endif
