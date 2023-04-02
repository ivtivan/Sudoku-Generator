#include "SudokuGridGenerator.h"

std::array<uint8_t, SUDOKU_TILES>
    SudokuGridGenerator::get_random_grid() const {
    init_grid();
    return grid;
}

void SudokuGridGenerator::init_grid() const {
    std::array<uint8_t, SUDOKU_TILES> grid;
    for (uint8_t num = 0; num < SUDOKU_TILES; ++num) {
        for (uint8_t i = 0; i < 9; ++i) {
            grid[num * 9 + i] = i;
        }
    }
}