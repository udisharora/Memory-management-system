#ifndef PERFORMANCE_HPP
#define PERFORMANCE_HPP

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "io.hpp"

using namespace std;

// Function to handle memory allocation for Map_Implementation page table
unsigned long long int map_implementation(unsigned long long int logical_address, unsigned long long int memory_req, Map_Implementation& page_table, Memory_manager& physical_memory);

// Function to handle memory allocation for SinglePageTable
unsigned long long int single_implementation(unsigned long long int logical_address, unsigned long long int memory_req, SinglePageTable& page_table, Memory_manager& physical_memory);

// Function to handle memory allocation for MultiLevelPageTable
unsigned long long int multi_implementation(unsigned long long int logical_address, unsigned long long int memory_req, MultiLevelPageTable& page_table, Memory_manager& physical_memory);

// Function to process tasks using Map_Implementation page table
pair<int, int> method_1_mapping(const string& filename, ofstream& outFile);

// Function to process tasks using SinglePageTable
pair<int, int> method2_2_single(const string& filename, ofstream& outFile);

// Function to process tasks using MultiLevelPageTable
pair<int, int> method3_3_multi(const string& filename, ofstream& outFile);

#endif // PERFORMANCE_HPP
