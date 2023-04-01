#ifndef SUDOKU_H
#define SUDOKU_H

#include <array>
#include <string>
#include <cstdint>

class Sudoku {
    private:
        static constexpr uint8_t SUDOKU_SIDE = 9;
        static constexpr uint8_t SUDOKU_TILES = SUDOKU_SIDE * SUDOKU_SIDE;

        std::array<uint8_t, SUDOKU_TILES> tiles;

        uint8_t& get_tile_at(uint8_t row, uint8_t col);
        uint8_t get_tile_at(uint8_t row, uint8_t col) const;
        char* get_as_c_string() const;
    public:
        Sudoku();
        Sudoku(const std::string& src);

        std::string get_as_formated_grid() const;
        
        friend std::ostream& operator<<(std::ostream& os, Sudoku sudoku);
};

#endif