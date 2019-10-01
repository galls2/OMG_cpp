cmake_minimum_required (VERSION 3.1)
cmake_policy(SET CMP0048 NEW)
set(CMAKE_CXX_STANDARD 17)

add_library(aiger /home/galls2/Desktop/OMG_cpp/code/utils/aiger-1.9.9/aiger.c)
add_library(aig_to_aig aig_to_aag.cpp)
target_link_libraries(aig_to_aig aiger)