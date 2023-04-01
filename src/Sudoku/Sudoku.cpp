#include "Sudoku.h"
#include <fstream>

Sudoku::Sudoku() {
    ;
}

Sudoku::Sudoku(const std::string& src) {
    for(uint8_t i = 0; i < SUDOKU_TILES; ++i) {
        tiles[i] = src[i] - '0';
    }
}

std::string Sudoku::get_as_formated_grid() const {
    std::string formated_grid;
    for (uint8_t row = 0; row < SUDOKU_SIDE; ++row) {
        for (uint8_t col = 0; col < SUDOKU_SIDE; ++col) {
            formated_grid += '[' + get_tile_at(row, col) + "] ";
        }
        formated_grid += '\n';
    }

    return formated_grid;
}

uint8_t Sudoku::get_tile_at(uint8_t row, uint8_t col) const {
    return tiles[row * SUDOKU_SIDE + col];
}

uint8_t& Sudoku::get_tile_at(uint8_t row, uint8_t col) {
    return tiles[row * SUDOKU_SIDE + col];
}

std::ostream& operator<<(std::ostream& os, Sudoku sudoku) {
    char* representation = sudoku.get_as_c_string();
    os.write(representation, Sudoku::SUDOKU_TILES + 1 + 2);
    delete[] representation;
    return os;
}

char* Sudoku::get_as_c_string() const {
    char* representation = new char[SUDOKU_TILES + 1 + 2 + 1];
    if (!representation) {
        return nullptr;
    }

    uint8_t num_digits = 0;
    for(uint8_t i = 0; i < SUDOKU_TILES; ++i) {
        if(tiles[i] != 0) {
            ++num_digits;
        }
        representation[i] = '0' + tiles[i];
    }
    representation[SUDOKU_TILES] = ' ';
    representation[SUDOKU_TILES + 1] = '0' + num_digits / 10;
    representation[SUDOKU_TILES + 2] = '0' + num_digits % 10;
    representation[SUDOKU_TILES + 3] = '\0';;

    return representation;
}