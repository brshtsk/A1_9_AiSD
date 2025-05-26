cmake_minimum_required(VERSION 3.30)
project(A1_9_AiSD)

set(CMAKE_CXX_STANDARD 20)

add_executable(A1_9_AiSD main.cpp
        StringGenerator.cpp
        StringSortTester.cpp
        StandardMergeSort.cpp
        StandardQuickSort.cpp
        StringMergeSort.cpp
        StringQuickSort.cpp
        StringSortTester.cpp
        BasicMsdRadixSort.cpp
        BoostedMsdRadixSort.cpp
        CompareStrings.cpp)
