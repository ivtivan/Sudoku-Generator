#include "SudokuFactory.hpp"

std::unique_ptr<Sudoku> SudokuFactory::get_sudoku(SUDOKU_TYPE type) {
    if (type == X) {
        return std::make_unique<SudokuX>();
    }
    return std::make_unique<Sudoku>();
}