#include "SudokuGenerator.h"
#include <algorithm>
#include <vector>

std::array<uint8_t, Sudoku::SUDOKU_TILES>
    SudokuGenerator::get_random_grid() {

    reorder_correctly();
    init_grid();
    return grid;
}

void SudokuGenerator::init_grid() {
    std::array<uint8_t, Sudoku::SUDOKU_TILES> grid;
    for (uint8_t row = 0; row < Sudoku::SUDOKU_TILES; ++row) {
        for (uint8_t col = 0; col < Sudoku::SUDOKU_TILES; ++col) {
            get_at(row, col) = row;
        }
    }

    std::random_shuffle(grid.begin(), grid.end());
}

uint8_t SudokuGenerator::get_at(uint8_t row, uint8_t col) const {
    return grid[row * Sudoku::SUDOKU_TILES + col];
}
uint8_t& SudokuGenerator::get_at(uint8_t row, uint8_t col) {
    return grid[row * Sudoku::SUDOKU_TILES + col];
}

void SudokuGenerator::reorder_correctly() {
    std::vector<uint8_t> possible_values;
    for (uint8_t row = 0; row < Sudoku::SUDOKU_SIDE; ++row) {
        for (uint8_t col = 0; col < Sudoku::SUDOKU_SIDE; ++col) {
        }
    }
}