#ifndef SUDOKU_GRID_GENERATOR_H
#define SUDOKU_GRID_GENERATOR_H

#include <array>
#include "../helpers.h"

class SudokuGridGenerator {
    private:
        std::array<uint8_t, SUDOKU_TILES> grid;

        void init_grid() const;
    public:
        std::array<uint8_t, SUDOKU_TILES> get_random_grid() const;
};

#endif