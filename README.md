# Multi-Threaded Password Cracker 
A C++ tool designed to demonstrate multi-threading concepts and synchronization techniques. 

## Features 
* **Multi-threading** using `std::thread` to distribute workload across CPU cores. 
* **Synchronization:** Uses `std::atomic` for efficient thread communication and early exit.

## How it works 
The applicaion splits the search space (all possible password combinations) into chunks. Each worker thread works on a different chunk and report when the target was found.  

## Requirements
* C++20 compiler 
* CMake (optional, for building)
