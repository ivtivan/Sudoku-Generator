#include "SudokuGridGenerator.h"
#include <algorithm>
//  algorithm: https://github.com/mfgravesjr/finished-projects/tree/master/SudokuGridGenerator

std::array<uint8_t, SUDOKU_TILES>
    SudokuGridGenerator::get_random_grid() {
    init_grid();
    return grid;
}

void SudokuGridGenerator::init_grid() {
    std::array<uint8_t, SUDOKU_TILES> grid;
    for (uint8_t row = 0; row < SUDOKU_TILES; ++row) {
        for (uint8_t col = 0; col < SUDOKU_TILES; ++col) {
            get_at(row, col) = row;
        }
    }

    std::random_shuffle(grid.begin(), grid.end());
}

uint8_t SudokuGridGenerator::get_at(uint8_t row, uint8_t col) const {
    return grid[row * SUDOKU_TILES + col];
}
uint8_t& SudokuGridGenerator::get_at(uint8_t row, uint8_t col) {
    return grid[row * SUDOKU_TILES + col];
}

void SudokuGridGenerator::reorder_correctly() {
    uint16_t bitwise_used = 0;
    for (uint8_t row = 0; row < SUDOKU_SIDE; ++row) {
        for (uint8_t col = 0; col < SUDOKU_SIDE; ++col) {
        }
    }
}