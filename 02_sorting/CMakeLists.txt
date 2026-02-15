cmake_minimum_required(VERSION 3.20)
project(sorting_algorithms)

set(CMAKE_CXX_STANDARD 23)

add_executable(insertion_sorting
        insertion_sorting/main.cpp)
add_executable(generate_sortable_data
        data_generation/generate_sortable_list.cpp)