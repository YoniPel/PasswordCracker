#include "PasswordCracker.h"
#include <iostream>

PasswordCracker::PasswordCracker(int password, int numOfThreads) : target(password), numOfThreads(numOfThreads), threadPool(numOfThreads, password) {}

int PasswordCracker::crackPassword() {
    // first check the range 0-10,000 as the most chosen passwords 
    int result = threadPool.activatePool(0, 10000); 
    if (result != -1) return result; 

    // then check for birthday dates exluding 0-10000
    result = threadPool.activatePool(10001, 31122026);
    if (result != -1) return result; 

    // then the rest 
    return threadPool.activatePool(31122027, 1'000'000'000);

};
