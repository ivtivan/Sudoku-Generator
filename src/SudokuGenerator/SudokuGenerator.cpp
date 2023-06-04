#include "SudokuGenerator.hpp"
#include "SudokuSolver/SudokuSolver.hpp"

#include <vector>

//  TODO: change return type
Sudoku SudokuGenerator::generate_sudoku() const {
    Sudoku sudoku;
    SudokuSolver solver;
    bool is_fillable = solver.fill_by_bruteforce(sudoku);
    if (!is_fillable) {
        //  TODO
    }
    return sudoku;
}