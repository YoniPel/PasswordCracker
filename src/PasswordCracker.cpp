#include "PasswordCracker.h"
#include <iostream>

PasswordCracker::PasswordCracker(int password, int numOfThreads) : target(password), numOfThreads(numOfThreads), threadPool(numOfThreads, PASSWORD_SPACE, password) {}

int PasswordCracker::crackPassword() {
    return threadPool.activatePool();
};
