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
    int result; 
    
    std::vector<std::thread> pool;
    std::queue<Task> tasks; 

    // the lock for accessing the queue 
    std::mutex m_mutx; 

    // condition variable for when there are tasks in the queue 
    std::condition_variable avalTasks; 
    // condition variable for when we cound the password to take the main thread 
    std::condition_variable foundPassword; 

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

    int activatePool(); 


};