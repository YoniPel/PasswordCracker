#pragma once

#include <string>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <thread>
#include <atomic>

class PasswordCracker {
private:
    static constexpr int PASSWORD_SPACE = 1'000'000'000;
    static constexpr int BATCH_SIZE = 100'000'000; 
    
    int numOfThreads; 
    std::string target;
    
    // found is atomic to avoid caching when found is true in one thread but false in another
    std::atomic<bool> found;
    std::string result;
    
    std::vector<std::thread> threads;
    std::unordered_map<std::thread::id, int> threadStats; 

    std::mutex m_mutex; 
    

public:
    PasswordCracker(const std::string &password, int numOfThreads);

    std::string crackPassword();

    void worker(int start, int end);

    void displaySums() const; 

};