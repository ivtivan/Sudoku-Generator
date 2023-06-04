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
        void solve_human_algos(Sudoku& sudoku) const;
    private:
        //  returns signed, so that -1 can be returned when no empty tiles are found
        int8_t find_empty(const Sudoku& sudoku) const;
};

#endif