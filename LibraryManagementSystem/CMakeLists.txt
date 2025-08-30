cmake_minimum_required(VERSION 3.23)
project(LibraryManagementSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(LibraryManagementSystem main.cpp users.cpp users.h books.h library.cpp library.h helpers.h books.cpp)
