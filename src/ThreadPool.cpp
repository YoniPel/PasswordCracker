#include "ThreadPool.h"

#include <algorithm>

ThreadPool::ThreadPool(int numOfThreads, int password) : numOfThreads(numOfThreads), password(password) {
    for (size_t i = 0; i < numOfThreads; i++) {
        pool.push_back(std::thread(&ThreadPool::worker, this));
    }
}


void ThreadPool::worker() {
    while (true) {
        Task currentTask; 

        std::unique_lock<std::mutex> lock(m_mutx);

        while (tasks.empty() && !stop) {
            avalTasks.wait(lock);
        }

        // the lock is released when we'll be out of his scope 
        if (stop) return;
 
        currentTask = tasks.front();
        tasks.pop();

        lock.unlock();

        // preform the task 
        for (int i = currentTask.start; i < currentTask.end; i++) {
            if (finish) break; 
            if (i == password) {
                std::unique_lock<std::mutex> lock(m_mutx);
                result = i;
                finish = true;
                lock.unlock();

                foundPassword.notify_one();
                break; 
            }
        }
    }
}

void ThreadPool::enqueue(Task t) {
    std::unique_lock<std::mutex> lock(m_mutx);
    tasks.push(t);
    lock.unlock();
    avalTasks.notify_one();
}


int ThreadPool::activatePool(int start, int end) {
    finish = false;
    result = -1;

    // empty the queue from previous use 
    {
        std::unique_lock<std::mutex> lock(m_mutx);
        while (!tasks.empty()) {
            tasks.pop();
        }
    }

    // calc the blockSize based on the number of threads and the range to be checked 
    int blockSize = ((end - start) + numOfThreads - 1) / numOfThreads; 

    // make sure the blockSize is between minSizeBlockSize and maxSizeBlockSize
    int optimalBlockSize = std::clamp(blockSize, minSizeBlockSize, maxSizeBlockSize);

    for (int i = start; i < end; i += optimalBlockSize) {
        Task t = {i, std::min(i + optimalBlockSize, end)}; 
        enqueue(t);
    }

    // the main thread waiting for the password to be found 
    {
        std::unique_lock<std::mutex> lock(m_mutx);
        while (!finish) {
            foundPassword.wait(lock); 
        }
    }

    return result; 
}


ThreadPool::~ThreadPool(){
    // forces stop to be saved in the RAM and not in the cache  
    std::unique_lock<std::mutex> lock(m_mutx);
    stop = true; 
    lock.unlock();

    avalTasks.notify_all();

    for (std::thread& worker : pool) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}