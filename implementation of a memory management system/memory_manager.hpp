#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

#include "config.hpp" 

class Memory_manager {
public:
    Memory_manager();
    unsigned long long int allocate_page();

private:
    int* frames;
    unsigned long long int framesTaken;
};

#endif 
