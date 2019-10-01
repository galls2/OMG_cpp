cmake_minimum_required (VERSION 3.1)
cmake_policy(SET CMP0048 NEW)
set(CMAKE_CXX_STANDARD 17)

include_directories(code)
project (OMG_CPP)
#LINK_DIRECTORIES(/home/galls2/Desktop/z3/build/) #MAY BE NEEDED :O

#add_subdirectory(code/utils/aiger-1.9.9)

add_executable(OMG main.cpp

        code/utils/version_manager.cpp code/utils/string_utils.cpp
        code/parsers/aig_parser.cpp code/parsers/lexer.cpp code/parsers/ctl_parser.cpp
        code/parsers/ctl_file_parser.cpp code/parsers/ctl_parser_data.cpp
        code/temporal/ctl_formula.cpp code/structures/kripke_structure.cpp
        code/formulas/prop_formula.cpp code/configuration/omg_config.cpp
        )



target_link_libraries(OMG libz3.so)
#target_link_libraries(aig_to_aig)