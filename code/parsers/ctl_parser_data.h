//
// Created by galls2 on 26/09/19.
//

#ifndef OMG_CPP_CTL_PARSER_DATA_H
#define OMG_CPP_CTL_PARSER_DATA_H

#include <utility>
#include <parsers/ctl_parser.h>

ActionTable::ActionTable_t action_table_t = {
          { std::make_pair(0, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(0, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(0, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(0, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(0, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(1, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(1, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 8) }
        , { std::make_pair(1, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 9) }
        , { std::make_pair(1, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::ACCEPT, 0) }
        , { std::make_pair(2, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(3, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(3, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(3, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(3, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(3, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(4, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(4, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(4, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(4, Token("G")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 11) }
        , { std::make_pair(4, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(4, Token("F")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 12) }
        , { std::make_pair(4, Token("X")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 14) }
        , { std::make_pair(4, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(5, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(5, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(5, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(5, Token("G")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 20) }
        , { std::make_pair(5, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(5, Token("F")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 21) }
        , { std::make_pair(5, Token("X")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 23) }
        , { std::make_pair(5, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(6, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(6, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(6, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(6, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(6, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(7, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(7, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(7, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(7, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(7, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(8, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(8, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(8, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(8, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(8, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(9, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(9, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(9, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(9, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(9, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(10, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(10, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(10, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(10, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(11, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(11, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(11, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(11, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(11, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(12, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(12, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(12, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(12, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(12, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(13, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 38) }
        , { std::make_pair(13, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 39) }
        , { std::make_pair(13, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 40) }
        , { std::make_pair(13, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 35) }
        , { std::make_pair(13, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 36) }
        , { std::make_pair(13, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 37) }
        , { std::make_pair(14, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(14, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(14, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(14, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(14, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(15, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(15, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(15, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(15, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(15, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(15, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(16, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(16, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(16, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(16, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(16, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(17, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(17, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(17, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(17, Token("G")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 43) }
        , { std::make_pair(17, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(17, Token("F")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 44) }
        , { std::make_pair(17, Token("X")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 46) }
        , { std::make_pair(17, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(18, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(18, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(18, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(18, Token("G")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 47) }
        , { std::make_pair(18, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(18, Token("F")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 48) }
        , { std::make_pair(18, Token("X")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 50) }
        , { std::make_pair(18, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(19, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(19, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(19, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(19, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(19, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(20, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(20, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(20, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(20, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(20, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(21, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(21, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(21, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(21, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(21, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(22, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 38) }
        , { std::make_pair(22, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 39) }
        , { std::make_pair(22, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 40) }
        , { std::make_pair(22, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 54) }
        , { std::make_pair(22, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 55) }
        , { std::make_pair(22, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 56) }
        , { std::make_pair(23, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(23, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(23, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(23, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(23, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(24, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 59) }
        , { std::make_pair(24, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 60) }
        , { std::make_pair(24, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 61) }
        , { std::make_pair(24, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 58) }
        , { std::make_pair(25, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(25, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(25, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(25, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(26, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(26, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(26, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(26, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(26, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(27, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(27, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(27, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(27, Token("G")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 63) }
        , { std::make_pair(27, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(27, Token("F")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 64) }
        , { std::make_pair(27, Token("X")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 66) }
        , { std::make_pair(27, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(28, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(28, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(28, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(28, Token("G")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 67) }
        , { std::make_pair(28, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(28, Token("F")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 68) }
        , { std::make_pair(28, Token("X")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 70) }
        , { std::make_pair(28, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(29, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(29, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(29, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(29, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(29, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(30, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(30, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(30, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(30, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(31, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(31, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(31, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(31, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(32, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(32, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(32, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(32, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(33, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(33, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(33, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(33, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(34, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(34, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(34, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(34, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(35, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(35, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(35, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(35, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(35, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(36, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(36, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(36, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(36, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(36, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(37, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(37, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(37, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(37, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(37, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(38, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(38, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(38, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(38, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(38, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(39, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(39, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(39, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(39, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(39, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(40, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(40, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(40, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(40, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(40, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(41, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(41, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(41, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(41, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(42, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(42, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(42, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(42, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(42, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(42, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(43, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(43, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(43, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(43, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(43, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(44, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(44, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(44, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(44, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(44, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(45, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 38) }
        , { std::make_pair(45, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 39) }
        , { std::make_pair(45, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 40) }
        , { std::make_pair(45, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 80) }
        , { std::make_pair(45, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 81) }
        , { std::make_pair(45, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 82) }
        , { std::make_pair(46, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(46, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(46, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(46, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(46, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(47, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(47, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(47, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(47, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(47, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(48, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(48, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(48, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(48, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(48, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(49, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 38) }
        , { std::make_pair(49, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 39) }
        , { std::make_pair(49, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 40) }
        , { std::make_pair(49, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 86) }
        , { std::make_pair(49, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 87) }
        , { std::make_pair(49, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 88) }
        , { std::make_pair(50, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(50, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(50, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(50, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(50, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(51, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 59) }
        , { std::make_pair(51, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 60) }
        , { std::make_pair(51, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 61) }
        , { std::make_pair(51, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 90) }
        , { std::make_pair(52, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(52, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(52, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(52, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(53, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(53, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(53, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(53, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(54, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(54, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(54, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(54, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(54, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(55, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(55, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(55, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(55, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(55, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(56, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(56, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(56, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 4) }
        , { std::make_pair(56, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(56, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(57, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(57, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(57, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(57, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(58, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(58, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(58, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(58, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(59, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(59, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(59, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(59, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(59, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(60, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(60, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(60, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(60, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(60, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(61, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(61, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(61, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(61, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(61, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(62, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(62, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(62, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(62, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(63, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(63, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(63, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(63, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(63, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(64, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(64, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(64, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(64, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(64, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(65, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 38) }
        , { std::make_pair(65, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 39) }
        , { std::make_pair(65, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 40) }
        , { std::make_pair(65, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 99) }
        , { std::make_pair(65, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 100) }
        , { std::make_pair(65, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 101) }
        , { std::make_pair(66, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(66, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(66, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(66, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(66, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(67, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(67, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(67, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(67, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(67, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(68, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(68, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(68, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(68, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(68, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(69, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 38) }
        , { std::make_pair(69, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 39) }
        , { std::make_pair(69, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 40) }
        , { std::make_pair(69, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 105) }
        , { std::make_pair(69, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 106) }
        , { std::make_pair(69, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 107) }
        , { std::make_pair(70, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(70, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(70, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(70, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(70, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(71, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 59) }
        , { std::make_pair(71, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 60) }
        , { std::make_pair(71, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 61) }
        , { std::make_pair(71, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 109) }
        , { std::make_pair(72, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(72, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(72, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(72, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(73, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(73, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(73, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(73, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(74, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(74, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(74, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(74, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(75, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(75, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(75, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(75, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(75, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(75, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(76, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(76, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(76, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(76, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(76, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(76, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(77, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(77, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(77, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(77, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(77, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(77, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(78, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(78, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(78, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(78, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(78, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(78, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(79, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(79, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(79, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(79, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(79, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(79, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(80, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(80, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(80, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(80, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(80, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(81, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(81, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(81, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(81, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(81, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(82, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(82, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(82, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(82, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(82, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(83, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(83, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(83, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(83, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(83, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(83, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(84, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(84, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(84, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(84, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(84, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(84, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(85, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(85, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(85, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(85, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(85, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(85, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(86, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(86, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(86, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(86, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(86, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(87, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(87, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(87, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(87, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(87, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(88, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(88, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(88, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(88, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(88, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(89, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(89, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(89, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(89, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(89, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(89, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(90, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(90, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(90, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(90, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(90, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(90, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(91, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(91, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(91, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(91, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(92, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(92, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(92, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(92, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(93, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(93, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(93, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(93, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(94, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(94, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(94, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(94, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(95, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(95, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(95, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(95, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(96, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(96, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(96, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(96, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(97, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(97, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(97, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(97, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(98, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(98, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(98, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(98, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(99, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(99, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(99, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(99, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(99, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(100, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(100, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(100, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(100, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(100, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(101, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(101, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(101, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(101, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(101, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(102, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(102, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(102, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(102, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(103, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(103, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(103, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(103, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(104, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(104, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(104, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(104, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(105, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(105, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(105, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(105, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(105, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(106, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(106, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(106, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(106, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(106, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(107, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 25) }
        , { std::make_pair(107, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(107, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(107, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(107, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
        , { std::make_pair(108, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(108, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(108, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(108, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(109, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(109, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(109, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(109, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(110, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(110, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(110, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(110, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(110, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(110, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(111, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(111, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(111, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(111, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(111, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(111, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(112, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(112, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(112, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(112, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(112, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(112, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(113, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(113, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(113, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(113, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(113, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(113, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(114, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(114, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(114, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(114, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(114, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(114, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(115, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(115, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(115, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(115, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(115, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(115, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(116, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(116, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(116, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(116, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(117, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(117, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(117, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(117, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(118, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(118, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(118, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(118, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(119, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(119, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(119, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(119, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(120, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(120, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(120, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(120, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(121, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(121, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(121, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(121, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
};

GotoTable::GotoTable_t goto_table_t = {
          { std::make_pair(0, 'S'), 1  }
        , { std::make_pair(3, 'S'), 10  }
        , { std::make_pair(4, 'S'), 13  }
        , { std::make_pair(5, 'S'), 22  }
        , { std::make_pair(6, 'S'), 24  }
        , { std::make_pair(7, 'S'), 30  }
        , { std::make_pair(8, 'S'), 31  }
        , { std::make_pair(9, 'S'), 32  }
        , { std::make_pair(11, 'S'), 33  }
        , { std::make_pair(12, 'S'), 34  }
        , { std::make_pair(14, 'S'), 41  }
        , { std::make_pair(16, 'S'), 42  }
        , { std::make_pair(17, 'S'), 45  }
        , { std::make_pair(18, 'S'), 49  }
        , { std::make_pair(19, 'S'), 51  }
        , { std::make_pair(20, 'S'), 52  }
        , { std::make_pair(21, 'S'), 53  }
        , { std::make_pair(23, 'S'), 57  }
        , { std::make_pair(26, 'S'), 62  }
        , { std::make_pair(27, 'S'), 65  }
        , { std::make_pair(28, 'S'), 69  }
        , { std::make_pair(29, 'S'), 71  }
        , { std::make_pair(35, 'S'), 72  }
        , { std::make_pair(36, 'S'), 73  }
        , { std::make_pair(37, 'S'), 74  }
        , { std::make_pair(38, 'S'), 75  }
        , { std::make_pair(39, 'S'), 76  }
        , { std::make_pair(40, 'S'), 77  }
        , { std::make_pair(43, 'S'), 78  }
        , { std::make_pair(44, 'S'), 79  }
        , { std::make_pair(46, 'S'), 83  }
        , { std::make_pair(47, 'S'), 84  }
        , { std::make_pair(48, 'S'), 85  }
        , { std::make_pair(50, 'S'), 89  }
        , { std::make_pair(54, 'S'), 91  }
        , { std::make_pair(55, 'S'), 92  }
        , { std::make_pair(56, 'S'), 93  }
        , { std::make_pair(59, 'S'), 94  }
        , { std::make_pair(60, 'S'), 95  }
        , { std::make_pair(61, 'S'), 96  }
        , { std::make_pair(63, 'S'), 97  }
        , { std::make_pair(64, 'S'), 98  }
        , { std::make_pair(66, 'S'), 102  }
        , { std::make_pair(67, 'S'), 103  }
        , { std::make_pair(68, 'S'), 104  }
        , { std::make_pair(70, 'S'), 108  }
        , { std::make_pair(80, 'S'), 110  }
        , { std::make_pair(81, 'S'), 111  }
        , { std::make_pair(82, 'S'), 112  }
        , { std::make_pair(86, 'S'), 113  }
        , { std::make_pair(87, 'S'), 114  }
        , { std::make_pair(88, 'S'), 115  }
        , { std::make_pair(99, 'S'), 116  }
        , { std::make_pair(100, 'S'), 117  }
        , { std::make_pair(101, 'S'), 118  }
        , { std::make_pair(105, 'S'), 119  }
        , { std::make_pair(106, 'S'), 120  }
        , { std::make_pair(107, 'S'), 121  }
};

LR1CtlParser::Grammar grammar = {
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('I', {'S'}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("AP")}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token('S'), Token("XOR"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token('S'), Token("OR"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token('S'), Token("AND"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("NOT"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token('S'), Token("AND"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("A"), Token("G"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("E"), Token("G"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("A"), Token("F"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("E"), Token("F"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("A"), Token('S'), Token("W"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("EA"), Token('S'), Token("W"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("A"), Token('S'), Token("U"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("E"), Token('S'), Token("U"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("A"), Token('S'), Token("R"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("E"), Token('S'), Token("R"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("A"), Token("X"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("E"), Token("X"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("("), Token('S'), Token(")")})
};


#endif //OMG_CPP_CTL_PARSER_DATA_H
