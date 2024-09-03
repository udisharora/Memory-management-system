#include <iostream>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <vector>
#include <random>
#include <chrono>
#include "config.hpp" 
#include <mutex>

using namespace std;

mutex fileMutex; // Global mutex for synchronizing file access

struct ThreadData {
    ThreadData(int i, fstream& file) : taskID(i), fileStream(file), startAddr(0), sectionSize(0), pageSize(0) {}
    int taskID;
    fstream& fileStream;
    unsigned long long int startAddr;
    unsigned long long int sectionSize;
    unsigned long long int pageSize;
};

void* generateTask(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    unsigned long long int addr = data->startAddr;
    unsigned long long int endAddr = addr + data->sectionSize;
    unsigned long long int pageSize = data->pageSize;
    
    // Random number generator setup
    mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<unsigned long long int> dist(addr, endAddr - 1);
    
    // Generate memory requests
    for (int i = 0; i < 1000; ++i) { // 1000 requests per task
        unsigned long long int reqAddr = dist(rng) & ~(pageSize - 1); // Align to page boundary
        
        // Generate a size that is a multiple of the page size
        unsigned long long int reqSize = ((dist(rng) % 64/(pageSize>>10)) + 1) * pageSize; // Size between 1 and 64 pages
        
        // Lock the mutex before writing to the file
        lock_guard<mutex> guard(fileMutex);
        data->fileStream << "T" << data->taskID << ":0x" << uppercase << hex << reqAddr << ":" << dec << (reqSize / 1024) << "KB" << endl;
    }


    
    pthread_exit(nullptr);
}

void generateTraces(int numTasks, const string& filePath) {
    fstream file(filePath, ios::out);
    if (!file) {
        cerr << "Error: Could not open file " << filePath << endl;
        return;
    }

    pthread_t threads[numTasks];
    ThreadData* threadData[numTasks];
    
    // Set up thread data
    for (int i = 0; i < numTasks; ++i) {
        threadData[i] = new ThreadData(i + 1, file);
        threadData[i]->startAddr = START_ADDR + i * SECTION_SIZE; // Assuming section size is equal for all tasks
        threadData[i]->sectionSize = SECTION_SIZE;
        threadData[i]->pageSize = PAGE_SIZE;
        
        if (pthread_create(&threads[i], nullptr, generateTask, threadData[i])) {
            cerr << "Error: Unable to create thread " << i << endl;
            return;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < numTasks; ++i) {
        pthread_join(threads[i], nullptr);
        delete threadData[i]; // Clean up the allocated memory
    }
    
    file.close();
}

int main() {
    int numTasks = 10; // Number of tasks
    string filePath = "trace.txt"; // Output file path

    generateTraces(numTasks, filePath);
    return 0;
}

