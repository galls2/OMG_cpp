cmake_minimum_required (VERSION 3.1)
cmake_policy(SET CMP0048 NEW)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS "-O3")
include_directories(code)
project (OMG_CPP)

add_executable(OMG main.cpp

        code/utils/version_manager.cpp code/utils/string_utils.cpp
        code/parsers/aig_parser.cpp code/parsers/lexer.cpp code/parsers/ctl_parser.cpp
        code/parsers/ctl_file_parser.cpp code/parsers/ctl_parser_data.cpp
        code/temporal/ctl_formula.cpp code/structures/kripke_structure.cpp
        code/formulas/prop_formula.cpp code/configuration/omg_config.cpp
        code/structures/unwinding_tree.cpp code/structures/concrete_state.cpp
        code/model_checking/omg_model_checker.cpp code/abstraction/abstract_structure.cpp
        code/formulas/sat_solver.cpp
        code/utils/z3_utils.cpp code/abstraction/abstract_state.cpp code/abstraction/abstraction_classifier.cpp
        code/utils/omg_utils.cpp code/utils/aiger-1.9.9/aig_to_aag.cpp code/utils/aiger-1.9.9/aiger.c code/model_checking/goal.cpp code/formulas/epr_solver.cpp)

target_link_libraries(OMG libz3.so)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(OMG PUBLIC DEBUG=1)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(OMG PUBLIC DEBUG=0)
endif()
