cmake_minimum_required(VERSION 3.23)
project(LibraryManagementSystem)


if (MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

set(CMAKE_CXX_STANDARD 20)

add_executable(LibraryManagementSystem main.cpp users.cpp users.h books.h library.cpp library.h helpers.h books.cpp)



