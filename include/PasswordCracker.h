#pragma once

#include <string>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <thread>
#include <atomic>

// TODO: right now assuming that the password will be find 
class PasswordCracker {
private:
    static constexpr int PASSWORD_SPACE = 1'000'000'000;
    static constexpr int BATCH_SIZE = 100'000'000; 
    
    int numOfThreads; 
    int target;
    
    // found is atomic to avoid caching when found is true in one thread but false in another
    std::atomic<bool> found;

    int result;
    
    std::vector<std::thread> threads;
    std::unordered_map<std::thread::id, int> threadStats; 

    std::mutex m_mutex; 

    

public:
    PasswordCracker(int password, int numOfThreads);

    int crackPassword();

    void worker(int start, int end);

    void displaySums() const; 
    

};