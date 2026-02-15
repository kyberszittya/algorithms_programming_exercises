cmake_minimum_required(VERSION 3.20)
project(sorting_algorithms)

set(CMAKE_CXX_STANDARD 23)

add_executable(insertion_sorting
        sorting_algos/sort_algorithms.h
        sorting_algos/insertion_sort.cpp
        sorting_algos/sort_executor.cpp
        sorting_algos/main.cpp)
add_executable(generate_sortable_data
        data_generation/generate_sortable_list.cpp)