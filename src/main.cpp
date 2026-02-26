#include <iostream>
#include <chrono>
#include <random>
#include "PasswordCracker.h"



int main()
{
    // Generate a radnom password between 1 and 100,000
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(0, 100000);

    int randomNum = dis(gen);
    std::string secret = std::to_string(randomNum);

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