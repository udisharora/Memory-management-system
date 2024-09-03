#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "memory_manager.hpp"
#include "task.hpp"

using namespace std;

// Function to format memory size for output
string formatSize(unsigned long long int mem);

// Function to parse a line of input and extract task ID, address, and memory size
void parseInput(const string& input, unsigned long long int& task_num, unsigned long long int& logical_address, unsigned long long int& mem);

#endif // IO_HPP
