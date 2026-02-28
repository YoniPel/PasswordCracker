#include <iostream>
#include <chrono>
#include <random>
#include "PasswordCracker.h"



int main()
{
    std::string numOfThreadsString; 

    std::cout << R"(
--- Password Cracker Menu ---
1. Choose the number of thread you want to use to crack the password
2. Configure a password to be cracked 
3. That's it :) 
    )" << std::endl; 
    
    std::cout << "Enter the number of thread you want to use: "; 

    std::getline(std::cin, numOfThreadsString);

    int numOfThreads = 1; 
    try {
        numOfThreads = std::stoi(numOfThreadsString);

        int maxNumOfThreads = std::thread::hardware_concurrency();
        if (numOfThreads < 1 || numOfThreads > maxNumOfThreads) {
            std::cout << "Invalid number, the number should be between 1 to " << maxNumOfThreads << std::endl; 
            return 1; 
        }
    } catch (const std::exception& e) {
        std::cout << "That's not a valid number" << std::endl; 
        return 1; 
    }

    std::string secret; 
    
    std::cout << "Enter a numeric password between 0 to 1,000,000,000: "; 

    std::getline(std::cin, secret);

    if (secret.empty()) {
        std::cout << "You didn't enter anything" << std::endl; 
        return 1; 
    }


    PasswordCracker cracker(std::stoi(secret), numOfThreads);

    std::cout << "Cracking password with " << numOfThreads << " threads" << std::endl; 

    auto start = std::chrono::high_resolution_clock::now();

    int result = cracker.crackPassword();

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "The password is: " << result << std::endl; 
    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl; 
 
    return 0;
}