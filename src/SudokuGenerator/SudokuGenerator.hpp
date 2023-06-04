#ifndef SUDOKU_GENERATOR_HPP
#define SUDOKU_GENERATOR_HPP

#include <array>
#include <cstdint>
#include <map>
#include "Sudoku/Sudoku.hpp"

class SudokuGenerator {
    public:
        Sudoku generate_sudoku() const;
    private:
};

#endif