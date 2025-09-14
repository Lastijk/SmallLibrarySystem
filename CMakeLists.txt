cmake_minimum_required(VERSION 3.22)
project(SmallLibrarySystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(SmallLibrarySystem main.cpp
        Users.h
        Users.cpp
        Rules.cpp
        Library.cpp
        Library.h
        Book.cpp
        Book.h
        Rules.h
        BorrowingRecord.h)
