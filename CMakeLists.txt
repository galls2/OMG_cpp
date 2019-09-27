cmake_minimum_required (VERSION 2.6)
cmake_policy(SET CMP0048 NEW)
set(CMAKE_CXX_STANDARD 17)

include_directories(code)
project (OMG_CPP)
#LINK_DIRECTORIES(/home/galls2/Desktop/z3/build/) #MAY BE NEEDED :O

add_executable(OMG main.cpp code/parsers/aig_parser.cpp code/utils/version_manager.cpp code/utils/string_utils.cpp code/parsers/lexer.cpp code/parsers/ctl_parser.cpp code/utils/omg_exception.h code/parsers/ctl_file_parser.cpp code/parsers/ctl_file_parser.h code/parsers/ctl_parser_data.cpp)
target_link_libraries(OMG libz3.so)
