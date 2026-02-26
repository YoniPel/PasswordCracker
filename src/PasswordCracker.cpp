#include "PasswordCracker.h"

PasswordCracker::PasswordCracker(const std::string &password) : target(password), found(false) {
    threads.reserve(NUM_THREADS);
}

std::string PasswordCracker::crackPassword() {
    // update values for the case when using the same instance more than once
    found = false;
    result = "";
    threads.clear();

    // round up always 
    int size = (PASSWORD_SPACE + NUM_THREADS - 1) / NUM_THREADS;
    for (size_t i = 0; i < NUM_THREADS; i++) {
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
    for (size_t i = start; i < end; i++) {
        if (found) break;

        std::string guess = std::to_string(i);
        if (guess == target) {
            found = true;
            result = guess;
            break;
        }
    }
}
