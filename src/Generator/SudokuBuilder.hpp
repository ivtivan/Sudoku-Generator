#ifndef SUDOKU_BUILDER_HPP
#define SUDOKU_BUILDER_HPP

#include <memory>

#include "Sudoku/Sudoku.hpp"
#include "Sudoku/SudokuX/SudokuX.hpp"
#include "sudoku_types.hpp"

class SudokuBuilder {
    public:
        std::unique_ptr<Sudoku> build_sudoku(SUDOKU_TYPE type);
};

#endif