#ifndef SUDOKU_GRID_GENERATOR_H
#define SUDOKU_GRID_GENERATOR_H

#include <array>
#include <map>
#include "../helpers.h"

class SudokuGridGenerator {
    private:
        std::array<uint8_t, SUDOKU_TILES> grid;

        void init_grid();
        void reorder_correctly();

        uint8_t get_at(uint8_t row, uint8_t col) const;
        uint8_t& get_at(uint8_t row, uint8_t col);
    public:
        std::array<uint8_t, SUDOKU_TILES> get_random_grid();
};

#endif