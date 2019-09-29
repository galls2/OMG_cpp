//
// Created by galls2 on 26/09/19.
//
#include "ctl_parser_data.h"

/* Auto generated code starts here */
ActionTable::ActionTable_t CtlParserData::action_table_ctl_parser = {
          { std::make_pair(0, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(0, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(0, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(0, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(0, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(1, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 8) }
        , { std::make_pair(1, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 9) }
        , { std::make_pair(1, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 10) }
        , { std::make_pair(1, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 11) }
        , { std::make_pair(1, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::ACCEPT, 0) }
        , { std::make_pair(2, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(3, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(3, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(3, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(3, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(3, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(4, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(4, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(4, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(4, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(4, Token("F")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(4, Token("G")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(4, Token("X")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(4, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 21) }
        , { std::make_pair(5, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 23) }
        , { std::make_pair(5, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 24) }
        , { std::make_pair(5, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(5, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(5, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(6, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(6, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(6, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(6, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(6, Token("F")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(6, Token("G")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(6, Token("X")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(6, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(7, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(7, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(7, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(7, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(7, Token("F")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(7, Token("G")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(7, Token("X")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(7, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(8, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(8, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(8, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(8, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(8, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(9, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(9, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(9, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(9, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(9, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(10, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(10, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(10, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(10, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(10, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(11, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(11, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(11, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(11, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(11, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(12, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(12, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(12, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(12, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(12, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(13, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(13, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(13, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(13, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(13, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(14, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 33) }
        , { std::make_pair(14, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 34) }
        , { std::make_pair(14, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 35) }
        , { std::make_pair(14, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 36) }
        , { std::make_pair(14, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 37) }
        , { std::make_pair(14, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 38) }
        , { std::make_pair(14, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 39) }
        , { std::make_pair(15, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(15, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(15, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(15, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(15, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(16, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(16, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(16, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(16, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(16, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 12) }
        , { std::make_pair(17, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(17, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(17, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(17, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(17, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 13) }
        , { std::make_pair(18, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(18, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(18, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(18, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(18, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(18, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(18, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(19, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(19, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(19, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(19, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(19, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 21) }
        , { std::make_pair(20, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(20, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(20, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(20, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(20, Token("F")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(20, Token("G")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(20, Token("X")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(20, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 21) }
        , { std::make_pair(21, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 23) }
        , { std::make_pair(21, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 24) }
        , { std::make_pair(21, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(21, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(21, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(22, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 45) }
        , { std::make_pair(22, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 46) }
        , { std::make_pair(22, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 47) }
        , { std::make_pair(22, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 48) }
        , { std::make_pair(22, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 44) }
        , { std::make_pair(23, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(23, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(23, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(23, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(23, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(24, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 23) }
        , { std::make_pair(24, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 24) }
        , { std::make_pair(24, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(24, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(24, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(25, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(25, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(25, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(25, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(25, Token("F")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 15) }
        , { std::make_pair(25, Token("G")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(25, Token("X")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(25, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 21) }
        , { std::make_pair(26, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 23) }
        , { std::make_pair(26, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 24) }
        , { std::make_pair(26, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(26, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(26, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(27, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 8) }
        , { std::make_pair(27, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 9) }
        , { std::make_pair(27, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 10) }
        , { std::make_pair(27, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(27, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(28, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(28, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 9) }
        , { std::make_pair(28, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 10) }
        , { std::make_pair(28, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(28, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(29, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(29, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(29, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 10) }
        , { std::make_pair(29, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(29, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(30, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5	) }
        , { std::make_pair(30, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 9) }
        , { std::make_pair(30, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 10) }
        , { std::make_pair(30, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 11) }
        , { std::make_pair(30, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(31, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 8) }
        , { std::make_pair(31, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 9) }
        , { std::make_pair(31, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 10) }
        , { std::make_pair(31, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 11) }
        , { std::make_pair(31, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(32, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(32, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(32, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(32, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(32, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(33, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(33, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(33, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(33, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(33, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 21) }
        , { std::make_pair(34, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(34, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(34, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(34, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(34, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 21) }
        , { std::make_pair(35, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(35, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(35, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(35, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(35, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 21) }
        , { std::make_pair(36, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(36, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(36, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(36, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(36, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 21) }
        , { std::make_pair(37, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(37, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(37, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(37, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(37, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(38, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(38, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(38, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(38, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(38, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(39, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(39, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(39, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(39, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(39, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(40, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(40, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(40, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(40, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(40, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(40, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(40, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(41, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(41, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(41, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(41, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(41, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 21) }
        , { std::make_pair(42, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 33) }
        , { std::make_pair(42, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 34) }
        , { std::make_pair(42, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 35) }
        , { std::make_pair(42, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 36) }
        , { std::make_pair(42, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 37) }
        , { std::make_pair(42, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 38) }
        , { std::make_pair(42, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 39) }
        , { std::make_pair(43, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 45) }
        , { std::make_pair(43, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 46) }
        , { std::make_pair(43, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 47) }
        , { std::make_pair(43, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 48) }
        , { std::make_pair(43, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 60) }
        , { std::make_pair(44, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(44, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(44, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(44, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(44, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(45, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 23) }
        , { std::make_pair(45, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 24) }
        , { std::make_pair(45, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(45, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(45, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(46, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 23) }
        , { std::make_pair(46, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 24) }
        , { std::make_pair(46, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(46, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(46, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(47, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 23) }
        , { std::make_pair(47, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 24) }
        , { std::make_pair(47, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(47, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(47, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(48, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 23) }
        , { std::make_pair(48, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 24) }
        , { std::make_pair(48, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(48, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(48, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(49, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(49, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(49, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(49, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(49, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(50, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 23) }
        , { std::make_pair(50, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 24) }
        , { std::make_pair(50, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(50, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(50, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(51, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 33) }
        , { std::make_pair(51, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 34) }
        , { std::make_pair(51, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 35) }
        , { std::make_pair(51, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 36) }
        , { std::make_pair(51, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 37) }
        , { std::make_pair(51, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 38) }
        , { std::make_pair(51, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 39) }
        , { std::make_pair(52, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 45) }
        , { std::make_pair(52, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 46) }
        , { std::make_pair(52, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 47) }
        , { std::make_pair(52, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 48) }
        , { std::make_pair(52, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 67) }
        , { std::make_pair(53, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 8) }
        , { std::make_pair(53, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 9) }
        , { std::make_pair(53, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 10) }
        , { std::make_pair(53, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 11) }
        , { std::make_pair(53, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(54, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 33) }
        , { std::make_pair(54, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 34) }
        , { std::make_pair(54, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 35) }
        , { std::make_pair(54, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(54, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(54, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(54, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(55, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(55, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 34) }
        , { std::make_pair(55, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 35) }
        , { std::make_pair(56, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(55, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(55, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(55, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(56, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(56, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(56, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 35) }
        , { std::make_pair(56, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(56, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(56, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(56, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(57, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(57, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 34) }
        , { std::make_pair(57, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 35) }
        , { std::make_pair(57, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 36) }
        , { std::make_pair(57, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(57, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(57, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(58, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 33) }
        , { std::make_pair(58, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 34) }
        , { std::make_pair(58, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 35) }
        , { std::make_pair(58, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 36) }
        , { std::make_pair(58, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(58, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(58, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(59, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(59, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 19) }
        , { std::make_pair(59, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(59, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(59, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 21) }
        , { std::make_pair(60, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(60, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(60, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(60, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(60, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(60, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(60, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(61, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 45) }
        , { std::make_pair(61, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 46) }
        , { std::make_pair(61, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 47) }
        , { std::make_pair(61, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(61, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(62, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(62, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 46) }
        , { std::make_pair(62, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 47) }
        , { std::make_pair(62, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(62, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(63, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(63, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(63, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 47) }
        , { std::make_pair(63, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(63, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(64, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(64, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 46) }
        , { std::make_pair(64, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 47) }
        , { std::make_pair(64, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 48) }
        , { std::make_pair(64, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(65, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 45) }
        , { std::make_pair(65, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 46) }
        , { std::make_pair(65, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 47) }
        , { std::make_pair(65, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 48) }
        , { std::make_pair(65, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(66, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 23) }
        , { std::make_pair(66, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 24) }
        , { std::make_pair(66, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(66, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(66, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 26) }
        , { std::make_pair(67, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(67, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(67, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(67, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(67, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(68, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 33) }
        , { std::make_pair(68, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 34) }
        , { std::make_pair(68, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 35) }
        , { std::make_pair(68, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 36) }
        , { std::make_pair(68, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(68, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(68, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(69, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 45) }
        , { std::make_pair(69, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 46) }
        , { std::make_pair(69, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 47) }
        , { std::make_pair(69, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 48) }
        , { std::make_pair(69, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
};

GotoTable::GotoTable_t CtlParserData::goto_table_ctl_parser = {
          { std::make_pair(0, 'S'), 1  }
        , { std::make_pair(0, 'P'), 4  }
        , { std::make_pair(3, 'S'), 12  }
        , { std::make_pair(3, 'P'), 4  }
        , { std::make_pair(4, 'S'), 14  }
        , { std::make_pair(4, 'P'), 20  }
        , { std::make_pair(4, 'T'), 13  }
        , { std::make_pair(5, 'S'), 22  }
        , { std::make_pair(5, 'P'), 25  }
        , { std::make_pair(8, 'S'), 27  }
        , { std::make_pair(8, 'P'), 4  }
        , { std::make_pair(9, 'S'), 28  }
        , { std::make_pair(9, 'P'), 4  }
        , { std::make_pair(10, 'S'), 29  }
        , { std::make_pair(10, 'P'), 4  }
        , { std::make_pair(11, 'S'), 30  }
        , { std::make_pair(11, 'P'), 4  }
        , { std::make_pair(13, 'S'), 31  }
        , { std::make_pair(13, 'P'), 4  }
        , { std::make_pair(14, 'Y'), 32  }
        , { std::make_pair(19, 'S'), 40  }
        , { std::make_pair(19, 'P'), 20  }
        , { std::make_pair(20, 'S'), 42  }
        , { std::make_pair(20, 'P'), 20  }
        , { std::make_pair(20, 'T'), 41  }
        , { std::make_pair(21, 'S'), 43  }
        , { std::make_pair(21, 'P'), 25  }
        , { std::make_pair(24, 'S'), 49  }
        , { std::make_pair(24, 'P'), 25  }
        , { std::make_pair(25, 'S'), 51  }
        , { std::make_pair(25, 'P'), 20  }
        , { std::make_pair(25, 'T'), 50  }
        , { std::make_pair(26, 'S'), 52  }
        , { std::make_pair(26, 'P'), 25  }
        , { std::make_pair(32, 'S'), 53  }
        , { std::make_pair(32, 'P'), 4  }
        , { std::make_pair(33, 'S'), 54  }
        , { std::make_pair(33, 'P'), 20  }
        , { std::make_pair(34, 'S'), 55  }
        , { std::make_pair(34, 'P'), 20  }
        , { std::make_pair(35, 'S'), 56  }
        , { std::make_pair(35, 'P'), 20  }
        , { std::make_pair(36, 'S'), 57  }
        , { std::make_pair(36, 'P'), 20  }
        , { std::make_pair(41, 'S'), 58  }
        , { std::make_pair(41, 'P'), 20  }
        , { std::make_pair(42, 'Y'), 59  }
        , { std::make_pair(45, 'S'), 61  }
        , { std::make_pair(45, 'P'), 25  }
        , { std::make_pair(46, 'S'), 62  }
        , { std::make_pair(46, 'P'), 25  }
        , { std::make_pair(47, 'S'), 63  }
        , { std::make_pair(47, 'P'), 25  }
        , { std::make_pair(48, 'S'), 64  }
        , { std::make_pair(48, 'P'), 25  }
        , { std::make_pair(50, 'S'), 65  }
        , { std::make_pair(50, 'P'), 25  }
        , { std::make_pair(51, 'Y'), 66  }
        , { std::make_pair(59, 'S'), 68  }
        , { std::make_pair(59, 'P'), 20  }
        , { std::make_pair(66, 'S'), 69  }
        , { std::make_pair(66, 'P'), 25  }
};
//f
/* Auto generated code ends here */



LR1CtlParser::Grammar CtlParserData::grammar_ctl = {
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('I', {'S'}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("AP")}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token('S'), Token("XOR"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token('S'), Token("OR"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token('S'), Token("AND"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token('S'), Token("ARROW"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("NOT"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token('P'), Token("T"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("P"), Token("S"), Token("Y"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('P', {Token('A')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('P', {Token('E')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('T', {Token('F')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('T', {Token('G')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('T', {Token('X')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('Y', {Token('U')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('Y', {Token('W')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('Y', {Token('R')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("("), Token('S'), Token(")")})
};

