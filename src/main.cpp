#include <iostream>
#include <chrono>
#include <random>
#include "PasswordCracker.h"



int main()
{
    std::string numOfThreadsString; 

    std::cout << "=== Password Cracker ===" << std::endl; 
    std::cout << "Enter the number of threads you want to use: "; 
    
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

    // secret is a string for future use when using hash function 
    std::string secret; 
    
    std::cout << "Enter a numeric password between 0 to 1,000,000,000: "; 

    std::getline(std::cin, secret);

    if (secret.empty()) {
        std::cout << "You didn't enter anything" << std::endl; 
        return 1; 
    }


    PasswordCracker cracker(secret, numOfThreads);

    std::cout << "Cracking password with " << numOfThreads << " threads" << std::endl; 

    auto start = std::chrono::high_resolution_clock::now();

    std::string result = cracker.crackPassword();

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "The password is: " << result << std::endl; 
    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl; 
    cracker.displaySums();
 
    return 0;
}