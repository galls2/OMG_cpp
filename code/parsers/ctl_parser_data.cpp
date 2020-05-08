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
        , { std::make_pair(1, Token("EQUIV")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 12) }
        , { std::make_pair(1, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::ACCEPT, 0) }
        , { std::make_pair(2, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token("EQUIV")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(2, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 1) }
        , { std::make_pair(3, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(3, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(3, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(3, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(3, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(4, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(4, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(4, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(4, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(4, Token("F")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 16) }
        , { std::make_pair(4, Token("G")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 17) }
        , { std::make_pair(4, Token("X")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 18) }
        , { std::make_pair(4, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(5, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(5, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(5, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(5, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(5, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(6, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(6, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(6, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(6, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(6, Token("F")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(6, Token("G")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(6, Token("X")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(6, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 10) }
        , { std::make_pair(7, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(7, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(7, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(7, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(7, Token("F")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(7, Token("G")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(7, Token("X")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
        , { std::make_pair(7, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 11) }
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
        , { std::make_pair(12, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(12, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(12, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(12, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(12, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(13, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) } // reduce NOT before logical op
        , { std::make_pair(13, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(13, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(13, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(13, Token("EQUIV")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(13, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(13, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(13, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(13, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(13, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 7) }
        , { std::make_pair(14, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(14, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(14, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(14, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(14, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(15, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 8) }
        , { std::make_pair(15, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 9) }
        , { std::make_pair(15, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 10) }
        , { std::make_pair(15, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 11) }
        , { std::make_pair(15, Token("EQUIV")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 12) }
        , { std::make_pair(15, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 27) }
        , { std::make_pair(15, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 28) }
        , { std::make_pair(15, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 29) }
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
        , { std::make_pair(18, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(18, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(18, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(18, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(18, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 14) }
        , { std::make_pair(19, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 8) }
        , { std::make_pair(19, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 9) }
        , { std::make_pair(19, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 10) }
        , { std::make_pair(19, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 11) }
        , { std::make_pair(19, Token("EQUIV")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 12) }
        , { std::make_pair(19, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 30) }
        , { std::make_pair(20, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(20, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 8) }
        , { std::make_pair(20, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 8) }
        , { std::make_pair(20, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }  // ?
        , { std::make_pair(20, Token("EQUIV")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(20, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(20, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(20, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(20, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(20, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 2) }
        , { std::make_pair(21, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(21, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(21, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 10) }
        , { std::make_pair(21, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(21, Token("EQUIV")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(21, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(21, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(21, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(21, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(21, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 3) }
        , { std::make_pair(22, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(22, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(22, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(22, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(22, Token("EQUIV")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(22, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(22, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(22, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(22, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(22, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 4) }
        , { std::make_pair(23, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(23, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 9) }
        , { std::make_pair(23, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 10) }
        , { std::make_pair(23, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(23, Token("EQUIV")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(23, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(23, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(23, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(23, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(23, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 5) }
        , { std::make_pair(24, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(24, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 9) }
        , { std::make_pair(24, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 10) }
        , { std::make_pair(24, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 11) }
        , { std::make_pair(24, Token("EQUIV")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(24, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(24, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(24, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(24, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(24, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 6) }
        , { std::make_pair(25, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(25, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(25, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(25, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(25, Token("EQUIV")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(25, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(25, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(25, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(25, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(25, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 8) }
        , { std::make_pair(26, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 2) }
        , { std::make_pair(26, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 3) }
        , { std::make_pair(26, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 6) }
        , { std::make_pair(26, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 7) }
        , { std::make_pair(26, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::SHIFT, 5) }
        , { std::make_pair(27, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(27, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(27, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(27, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(27, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 15) }
        , { std::make_pair(28, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(28, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(28, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(28, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(28, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 16) }
        , { std::make_pair(29, Token("AP")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(29, Token("NOT")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(29, Token("A")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(29, Token("E")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(29, Token("(")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 17) }
        , { std::make_pair(30, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(30, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(30, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(30, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(30, Token("EQUIV")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(30, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(30, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(30, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(30, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(30, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 18) }
        , { std::make_pair(31, Token("XOR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(31, Token("OR")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(31, Token("AND")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(31, Token("ARROW")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(31, Token("EQUIV")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(31, Token("U")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(31, Token("W")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(31, Token("R")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(31, Token(")")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
        , { std::make_pair(31, Token("$")), ActionTable::LrTableEntry(ActionTable::LrAction::REDUCE, 9) }
};

GotoTable::GotoTable_t CtlParserData::goto_table_ctl_parser = {
          { std::make_pair(0, 'S'), 1  }
        , { std::make_pair(0, 'P'), 4  }
        , { std::make_pair(3, 'S'), 13  }
        , { std::make_pair(3, 'P'), 4  }
        , { std::make_pair(4, 'S'), 15  }
        , { std::make_pair(4, 'P'), 4  }
        , { std::make_pair(4, 'T'), 14  }
        , { std::make_pair(5, 'S'), 19  }
        , { std::make_pair(5, 'P'), 4  }
        , { std::make_pair(8, 'S'), 20  }
        , { std::make_pair(8, 'P'), 4  }
        , { std::make_pair(9, 'S'), 21  }
        , { std::make_pair(9, 'P'), 4  }
        , { std::make_pair(10, 'S'), 22  }
        , { std::make_pair(10, 'P'), 4  }
        , { std::make_pair(11, 'S'), 23  }
        , { std::make_pair(11, 'P'), 4  }
        , { std::make_pair(12, 'S'), 24  }
        , { std::make_pair(12, 'P'), 4  }
        , { std::make_pair(14, 'S'), 25  }
        , { std::make_pair(14, 'P'), 4  }
        , { std::make_pair(15, 'Y'), 26  }
        , { std::make_pair(26, 'S'), 31  }
        , { std::make_pair(26, 'P'), 4  }
};

/* Auto generated code ends here */



LR1CtlParser::Grammar CtlParserData::grammar_ctl = {
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('I', {VarName('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("AP")}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {VarName ('S'), Token("XOR"), VarName('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {VarName('S'), Token("OR"), Token('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {VarName('S'), Token("AND"), VarName('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {VarName('S'), Token("ARROW"), VarName('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {VarName('S'), Token("EQUIV"), VarName('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("NOT"), VarName('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {VarName('P'), VarName('T'), VarName('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {VarName('P'), VarName('S'), VarName('Y'), VarName('S')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('P', {Token('A')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('P', {Token('E')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('T', {Token('F')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('T', {Token('G')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('T', {Token('X')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('Y', {Token('U')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('Y', {Token('W')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('Y', {Token('R')}),
        std::make_pair<VarName, std::vector<GrammarRuleEntity>>('S', {Token("("), VarName('S'), Token(")")})
};

CtlParserData::CtlFormulaCreator empty_creator = [] (std::vector<Token>, std::vector<std::unique_ptr<CtlFormula>>)
{
    throw CtlParserException("Cannot use this rule to create formula!");
    return nullptr;
};

CtlParserData::CtlFormulaCreator ap_creator = [] (std::vector<Token> tokens, std::vector<std::unique_ptr<CtlFormula>> operands)
{
    assert(tokens.size() == 1 && tokens[0].get_token_type().get_data() == std::string("AP"));
    assert(tokens[0].is_ap());
    assert(operands.empty());
    std::string ap_text = tokens[0].get_data();
    return std::make_unique<CtlFormula>(ap_text);
};

CtlParserData::CtlFormulaCreator logical_creator = [] (std::vector<Token> tokens, std::vector<std::unique_ptr<CtlFormula>> operands)
{
    assert(tokens.size() == 1 && !tokens[0].is_ap());
    assert(operands.size() == 2);

    std::string logical_operand = tokens[0].get_data();
    return std::make_unique<CtlFormula>(logical_operand, std::move(operands));
};

CtlParserData::CtlFormulaCreator not_creator = [] (std::vector<Token> tokens, std::vector<std::unique_ptr<CtlFormula>> operands)
{
    assert(tokens.size() == 1 && !tokens[0].is_ap() && tokens[0].get_data() == "NOT");
    assert(operands.size() == 1);

    std::string not_op = tokens[0].get_data();
    return std::make_unique<CtlFormula>(not_op, std::move(operands));
};

CtlParserData::CtlFormulaCreator temp_single_op_creator = [] (std::vector<Token> tokens, std::vector<std::unique_ptr<CtlFormula>> operands)
{
    assert(tokens.empty() && operands.size() == 3);

    std::vector<std::unique_ptr<CtlFormula>> new_ops;

    std::unique_ptr<CtlFormula> operand(std::move(operands.back()));
    operands.pop_back();

    std::unique_ptr<CtlFormula> temporal_operator(std::move(operands.back()));
    operands.pop_back();

    std::unique_ptr<CtlFormula> path_quantifier(std::move(operands.back()));
    operands.pop_back();


    new_ops.emplace_back(std::move(operand));

    return std::make_unique<CtlFormula>((*path_quantifier).get_data()+(*temporal_operator).get_data(), std::move(new_ops));

};

CtlParserData::CtlFormulaCreator temp_two_op_creator = [] (std::vector<Token> tokens, std::vector<std::unique_ptr<CtlFormula>> operands)
{
    assert(tokens.empty() && operands.size() == 4);

    std::vector<std::unique_ptr<CtlFormula>> new_ops;


    std::unique_ptr<CtlFormula> second_operand(std::move(operands.back()));
    operands.pop_back();

    std::unique_ptr<CtlFormula> temporal_operator(std::move(operands.back()));
    operands.pop_back();

    std::unique_ptr<CtlFormula> first_operand(std::move(operands.back()));
    operands.pop_back();

    std::unique_ptr<CtlFormula> path_quantifier(std::move(operands.back()));
    operands.pop_back();


    new_ops.emplace(new_ops.begin(), std::move(second_operand));
    new_ops.emplace(new_ops.begin(), std::move(first_operand));

    return std::make_unique<CtlFormula>((*path_quantifier).get_data()+(*temporal_operator).get_data(), std::move(new_ops));

};


CtlParserData::CtlFormulaCreator token_to_formula = [] (std::vector<Token> tokens, std::vector<std::unique_ptr<CtlFormula>> operands) {
    assert(tokens.size() == 1 && operands.empty());
    std::string op = tokens[0].get_data();
    return std::make_unique<CtlFormula>(op);
};

CtlParserData::CtlFormulaCreator identity = [] (std::vector<Token> tokens, std::vector<std::unique_ptr<CtlFormula>> operands) {
    assert(tokens.size() == 2 && operands.size() == 1);
    return std::move(operands[0]);
};

std::vector<CtlParserData::CtlFormulaCreator> CtlParserData::formula_builders =
        {
       empty_creator,
       ap_creator,
       logical_creator, logical_creator, logical_creator, logical_creator,  logical_creator,
        not_creator,
       temp_single_op_creator,
       temp_two_op_creator,
       token_to_formula, token_to_formula, token_to_formula, token_to_formula,
       token_to_formula, token_to_formula, token_to_formula, token_to_formula,
       identity
        };
