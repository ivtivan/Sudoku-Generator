#ifndef SUDOKU_FACTORY_HPP
#define SUDOKU_FACTORY_HPP

#include <memory>

#include "Sudoku/Sudoku.hpp"
#include "Sudoku/SudokuX/SudokuX.hpp"
#include "sudoku_types.hpp"

class SudokuFactory {
    public:
        std::unique_ptr<Sudoku> get_sudoku(SUDOKU_TYPE type);
};

#endif