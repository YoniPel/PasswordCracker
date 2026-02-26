#pragma once

#include <string>
#include <vector>
#include <thread>
#include <atomic>

class PasswordCracker {
private:
    static constexpr int PASSWORD_SPACE = 1'000'000;
    int numOfThreads; 
    std::string target;
    // found is atomic to avoid caching when found is true in one thread but false in another
    std::atomic<bool> found;
    std::string result;
    std::vector<std::thread> threads;

public:
    PasswordCracker(const std::string &password, int numOfThreads);

    std::string crackPassword();

    void worker(int start, int end);
};