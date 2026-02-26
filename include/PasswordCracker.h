#pragma once

#include <string>
#include <vector>
#include <thread>
#include <atomic>

class PasswordCracker {
private:
    static constexpr int PASSWORD_SPACE = 100'000;
    static constexpr int NUM_THREADS = 8;
    std::string target;
    std::atomic<bool> found;
    std::string result;
    std::vector<std::thread> threads;

public:
    PasswordCracker(const std::string &password);

    std::string crackPassword();

    void worker(int start, int end);
};