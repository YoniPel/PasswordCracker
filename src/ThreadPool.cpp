#include "ThreadPool.h"


ThreadPool::ThreadPool(int numOfThreads, int passwordSpace, int password) : numOfThreads(numOfThreads), passwordSpace(passwordSpace), password(password) {
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
                // only one thread should find the password so no need to lock 
                result = i;
                finish = true;
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


std::string ThreadPool::activatePool() {
    finish = false;
    result = "";

    std::unique_lock<std::mutex> lock(m_mutx);
    while (!tasks.empty()) {
        tasks.pop();
    }
    lock.unlock();
    
    int size = (passwordSpace + numOfThreads - 1) / numOfThreads; 
    for (int i = 0; i < passwordSpace; i += size) {
        Task t = {i, std::min(i + size, passwordSpace)}; 
        enqueue(t);
    }

    // TODO: logic to retrieve the restuls 

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