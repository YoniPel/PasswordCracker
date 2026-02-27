#pragma once

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue> 

class ThreadPool {
private:

    struct Task {
        int start; 
        int end; 
    }; 

    int passwordSpace; 
    int password; 

    int numOfThreads; 
    std::string result; 
    
    std::vector<std::thread> pool;

    std::mutex m_mutx; 
    std::condition_variable avalTasks; 

    std::queue<Task> tasks; 
    
    // when we finish to find the current password but might use the instance again 
    std::atomic<bool> finish = false; 

    // when we finish using the instnace 
    bool stop = false; 

public:
    ThreadPool(int numOfThreads, int passwordSpace, int password); 

    // to kill the theards 
    ~ThreadPool();

    void worker(); 

    void enqueue(Task t); 

    std::string activatePool(); 


};