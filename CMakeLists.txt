cmake_minimum_required(VERSION 3.10)

project(PasswordCracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

include_directories(include)

add_executable(
    main 
    src/main.cpp
    src/PasswordCracker.cpp
    src/ThreadPool.cpp
)

target_link_libraries(main PRIVATE Threads::Threads)