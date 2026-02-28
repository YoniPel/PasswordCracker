#pragma once

#include "ThreadPool.h"
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

    ThreadPool threadPool;
    
    int numOfThreads; 
    int target;

    int result;
    
    

public:
    PasswordCracker(int password, int numOfThreads);

    int crackPassword();


};