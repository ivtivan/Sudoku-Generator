#ifndef SUDOKU_GENERATOR_H
#define SUDOKU_GENERATOR_H

#include <array>
#include <map>
#include <cstdint>
#include <Sudoku.h>

class SudokuGenerator {
    public:
        std::array<uint8_t, Sudoku::SUDOKU_TILES> get_random_grid();
    private:
        std::array<uint8_t, Sudoku::SUDOKU_TILES> grid;

        void init_grid();
        void reorder_correctly();

        uint8_t get_at(uint8_t row, uint8_t col) const;
        uint8_t& get_at(uint8_t row, uint8_t col);
};

#endif