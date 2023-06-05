#ifndef SUDOKU_GENERATOR_HPP
#define SUDOKU_GENERATOR_HPP

#include <cstdint>
#include <map>
#include <set>

#include "Sudoku/Sudoku.hpp"
#include "SudokuSolver/SudokuSolver.hpp"

class SudokuGenerator {
    public:
        SudokuGenerator();

        Sudoku generate_sudoku();
    private:
        Sudoku sudoku;
        SudokuSolver solver;
        
        std::set<uint8_t> pairs_to_try_reset;
        std::set<uint8_t> uniques_to_try_reset;
        
        uint8_t tiles_reset;

        void reset_tiles();
        void reset_pairs();
        void reset_uniques();

        bool try_reset_pair(uint8_t pair_index);
        bool try_reset_unique(uint8_t index);
        
        void restore_at_to(uint8_t index, uint8_t original_value);

        void setup_pairs_to_try_reset();
        void setup_uniques_to_try_reset();

        uint8_t get_pair_first_el(uint8_t pair_index) const;
        uint8_t get_pair_second_el(uint8_t pair_index) const;
};

#endif