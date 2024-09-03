#include "io.hpp"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;


string formatSize(unsigned long long int mem) {
    if (mem < 1024) return to_string(mem) + " B";
    if (mem < 1024 * 1024) return to_string(mem / 1024) + " KB";
    return to_string(mem / (1024 * 1024)) + " MB";
}


void parseInput(const std::string& line, unsigned long long int& taskID, unsigned long long int& addr, unsigned long long int& size) {
    std::stringstream ss(line);
    std::string task, address, memory;
    getline(ss, task, ':');
    getline(ss, address, ':');
    getline(ss, memory, ':');

    // Parsing the task ID
    taskID = std::stoull(task.substr(1));

    // Parsing the address in hex format
    addr = std::stoull(address, nullptr, 16);

    // Parsing the size and handling the units (KB, MB)
    if (memory.back() == 'B') {
        if (memory[memory.size() - 2] == 'K') {
            size = std::stoull(memory.substr(0, memory.size() - 2)) * 1024; // KB to bytes
        } else if (memory[memory.size() - 2] == 'M') {
            size = std::stoull(memory.substr(0, memory.size() - 2)) * 1024 * 1024; // MB to bytes
        } else {
            size = std::stoull(memory.substr(0, memory.size() - 1)); // If no unit specified, assume bytes
        }
    } else {
        size = std::stoull(memory); // Default case if no unit is provided
    }
}


