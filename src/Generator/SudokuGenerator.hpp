#ifndef SUDOKU_GENERATOR_HPP
#define SUDOKU_GENERATOR_HPP

#include <cstdint>
#include <set>

#include <memory>

#include "Solver/SudokuSolver.hpp"
#include "Sudoku/Sudoku.hpp"
#include "sudoku_types.hpp"

//  reset pairs of elements to creratet a symmetrical sudoku;
//  then resets unique elements which can be rermoved

class SudokuGenerator {
    public:
        SudokuGenerator();

        //  takes an empty board which has to be filled/generated and returned
        std::unique_ptr<Sudoku> generate_sudoku(SUDOKU_TYPE type);
    private:
        std::shared_ptr<Sudoku> sudoku;
        SudokuSolver solver;    
        
        std::set<uint8_t> pairs_to_reset;
        std::set<uint8_t> uniques_to_reset;
        
        void reset_tiles();
        void reset_pairs();
        void reset_uniques();

        void setup_pairs_to_reset();
        void setup_uniques_to_reset();

        //  gives back the resulting set of elements after removing one from the argument
        std::set<uint8_t> reset_random_pair(std::set<uint8_t> pairs);
        std::set<uint8_t> reset_random_unique(std::set<uint8_t> uniques);

        uint8_t get_tile_to_reset(std::set<uint8_t> els_to_try_reset) const;

        //  returns whether or not the tile(s) was(were) reset
        bool try_reset_pair(uint8_t pair_index);
        bool try_reset_unique(uint8_t index);
        
        inline void restore_tile_at_to(uint8_t index, uint8_t original_value);

        inline uint8_t get_pair_first_el(uint8_t pair_index) const;
        inline uint8_t get_pair_second_el(uint8_t pair_index) const;
};

#endif