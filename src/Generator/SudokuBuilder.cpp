#include "SudokuBuilder.hpp"

std::unique_ptr<Sudoku> SudokuBuilder::build_sudoku(SUDOKU_TYPE type) {
    if (type == X) {
        return std::make_unique<SudokuX>();
    }
    return std::make_unique<Sudoku>();
}