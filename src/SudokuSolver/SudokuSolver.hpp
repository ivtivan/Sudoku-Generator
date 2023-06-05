#ifndef SUDOKU_SOLVER_HPP
#define SUDOKU_SOLVER_HPP

#include "Sudoku/Sudoku.hpp"

/*
//  Works directly on the sudoku, passed to the functions through reference.
*/

class SudokuSolver {
    public:
        //  returns whether the whole sudoku was filled or not
        bool fill_by_bruteforce(Sudoku& sudoku) const;
        bool has_multiple_solutions(Sudoku sudoku) const;
    private:
        //  returns signed, so that -1 can be returned when no empty tiles are found
        int8_t find_empty(const Sudoku& sudoku) const;

        //  returns 1 if the solution is unique, or some other number if it isn't;
        //  values not equal to 1 do not correspond to the actual number of solutions;
        //  returns 0 if there is no solution
        uint8_t count_solutions_one_or_more(Sudoku sudoku) const;

        uint8_t get_possible_value() const;
        uint8_t get_next_possible_value(uint8_t curr_possible_value) const;
};
#endif