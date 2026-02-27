#include "PasswordCracker.h"
#include <iostream>

PasswordCracker::PasswordCracker(int password, int numOfThreads) : target(password), numOfThreads(numOfThreads), found(false) {
    threads.reserve(numOfThreads);
    threadStats.reserve(numOfThreads);
}

int PasswordCracker::crackPassword() {
    // update values for the case when using the same instance more than once
    found = false;
    result = -1; 
    threads.clear();

    // round up always 
    int size = (PASSWORD_SPACE + numOfThreads - 1) / numOfThreads;
    for (size_t i = 0; i < numOfThreads; i++) {
        int start = size * i;
        int end = std::min(start + size, PASSWORD_SPACE);
        threads.push_back(std::thread(&PasswordCracker::worker, this, start, end));
    }

    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
    return result;
}

void PasswordCracker::worker(int start, int end) {
    int numOfChecks = 0; 
    for (size_t i = start; i <= end; i++) {
        if (found) break;

        numOfChecks++;
        if (numOfChecks > BATCH_SIZE) {
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                threadStats[std::this_thread::get_id()] += numOfChecks; 
                
            }
            numOfChecks = 0; 
        }

        if (i == target) {
            found = true;
            result = i;
            break;
        }
    }
    std::lock_guard<std::mutex> lock(m_mutex);
    threadStats[std::this_thread::get_id()] += numOfChecks; 
}

void PasswordCracker::displaySums() const {
    for(const auto& pair : threadStats) {
        std::cout << "Number of checks for theard number " << pair.first << ": " << pair.second << std::endl;
    }
}
