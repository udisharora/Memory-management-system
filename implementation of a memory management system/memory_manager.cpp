#include "memory_manager.hpp"
#include "config.hpp"
#include <algorithm>
#include <iostream>

// Constructor for Memory_manager class

// and sets the number of used frames to 0
Memory_manager::Memory_manager()
// Initializes the array to represent physical memory
    : frames(new int[NUMBER_OF_FRAMES]()), framesTaken(0) {
    // all the frames will be 0 such that they appear to be free initially.
    std::fill(frames, frames + NUMBER_OF_FRAMES, 0);
}

// Function to allocate a page in physical memory
// Returns the index of the allocated frame
unsigned long long int Memory_manager::allocate_page() {
    // Find the first free frame. frame value will be 0 if it is free.
    auto it = std::find(frames, frames + NUMBER_OF_FRAMES, 0);
    
    // If a free frame is found, mark it as used and return its index
    if (it != frames + NUMBER_OF_FRAMES) {
        *it = 1;
        ++framesTaken;
        return std::distance(frames, it);
    }
    else{
        // If no free frames are available, print an error message and return -1
        std::cerr << "Physical memory limit reached" << std::endl;
        return static_cast<unsigned long long int>(-1ULL);
    }
    

}
