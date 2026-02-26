#include <iostream>
#include <chrono>
#include <random>
#include "PasswordCracker.h"



int main()
{
    std::string secret; 
    
    std::cout << "=== Password Cracker ===" << std::endl; 
    std::cout << "Enter a numeric password between 0 to 100,000" << std::endl; 

    std::getline(std::cin, secret);

    if (secret.empty()) {
        std::cout << "You didn't enter anything" << std::endl; 
        return 1; 
    }


    PasswordCracker cracker(secret);

    std::cout << "Cracking password with " << 8 << " threads" << std::endl; 

    auto start = std::chrono::high_resolution_clock::now();

    std::string result = cracker.crackPassword();

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "The password is: " << result << std::endl; 
    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl; 
 
    return 0;
}