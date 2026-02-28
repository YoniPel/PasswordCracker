# Multi-Threaded Password Cracker 
A C++ tool designed to demonstrate multi-threading concepts and synchronization techniques. 

## Features 
* **Multi-threading** uses `std::thread` to distribute workload across CPU cores. 
* **Synchronization:** uses `std::atomic` for efficient thread communication and early exit.
* **Condition Variables** implements `std::condition_variable` for optimal thread signaling and waiting, minimizin CPU usege.

## How it works 
* You choose the number of threads you want to use in order to crack the password
* You randomize a password
* The Password Cracker will divide the password space into chunks, each worker thread works on a different chunk and report when the target was found

## Requirements
* C++20 compiler 
* CMake (optional, for building)
