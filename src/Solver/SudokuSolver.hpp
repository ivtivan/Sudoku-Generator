#ifndef SUDOKU_SOLVER_HPP
#define SUDOKU_SOLVER_HPP

#include <memory>

#include "Sudoku/Sudoku.hpp"

/*
//  Works directly on the sudoku, passed to the constructor.
*/

class SudokuSolver {
    public:
        void set_sudoku(std::shared_ptr<Sudoku> sudoku);
        //  returns whether the whole sudoku was filled or not
        bool fill_by_bruteforce() const;
        bool finds_multiple_solutions() const;
    private:
        std::shared_ptr<Sudoku> sudoku;
        //  returns signed, so that -1 can be returned when no empty tiles are found
        int8_t find_empty() const;

        //  returns whether this leads to generating valid sudoku
        bool try_set_at(uint8_t index, uint8_t value) const;

        //  returns 1 if the solution is unique, or some other number if it isn't;
        //  values not equal to 1 do not correspond to the actual number of solutions;
        //  returns 0 if there is no solution
        uint8_t count_solutions_one_or_more() const;

        uint8_t get_random_possible_value() const;
        uint8_t get_next_possible_value(uint8_t curr_possible_value) const;
};
#endif