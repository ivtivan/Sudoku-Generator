#include "Sudoku.hpp"
#include <algorithm>

Sudoku::Sudoku() {
    for(uint8_t i = 0; i < get_num_sudoku_tiles(); ++i) {
        tiles[i] = EMPTY_TILE;
    }
}

uint8_t Sudoku::get_num_givens() const {
    uint8_t num_givens;
    for (uint8_t i = 0; i < SUDOKU_TILES; ++i) {
        if (!is_empty_at(i)) {
            ++num_givens;
        }
    }
    return num_givens;
}

uint8_t Sudoku::get_at(uint8_t row, uint8_t col) const {
    return get_at(map_row_col_to_index(row, col));
}

uint8_t Sudoku::get_at(uint8_t index) const {
    return tiles[index];
}

uint8_t Sudoku::map_row_col_to_index(uint8_t row, uint8_t col) const {
    return row * get_sudoku_side() + col;
}

void Sudoku::set_at(uint8_t row, uint8_t col, uint8_t value) {
    set_at(map_row_col_to_index(row, col), value);
}

void Sudoku::set_at(uint8_t index, uint8_t value) {
    tiles[index] = value;
}


void Sudoku::reset_at(uint8_t index) {
    tiles[index] = EMPTY_TILE;
}

bool Sudoku::is_empty() const {
    return get_num_givens() == 0;
}

std::string Sudoku::get_as_formated_grid() const {
    std::string formated_grid = "";
    
    for (uint8_t row = 0; row < get_sudoku_side(); ++row) {
        if(row % get_subsquare_side() == 0) {
            append_row_break(formated_grid);
        }
        for (uint8_t col = 0; col < get_sudoku_side(); ++col) {
            if(col % get_subsquare_side() == 0) {
                append_col_break(formated_grid);
            }

            append_tile_value_at(formated_grid, row, col);
        }

        append_col_break(formated_grid);
        formated_grid += "\n";
    }
    append_row_break(formated_grid);

    return formated_grid;
}

void Sudoku::append_tile_value_at(std::string& string_representation,
    uint8_t row, uint8_t col) const {
    
    char tile_value_digit = map_tile_value_to_char(row, col);
    string_representation.push_back('[');
    string_representation.push_back(tile_value_digit);
    string_representation += "] ";
}

char Sudoku::map_tile_value_to_char(uint8_t row, uint8_t col) const {
    if (is_empty_at(map_row_col_to_index(row, col))) {
        return ' ';
    }

    return '0' + get_at(row, col);
}

void Sudoku::append_row_break(std::string& string_representation) const {
    uint8_t row_length = 2 * (get_subsquare_side() + 1) + 4 * get_sudoku_side() - 1;
    string_representation.append(std::string(row_length,'-'));
    string_representation += "\n";
}

void Sudoku::append_col_break(std::string& string_representation) const {
    string_representation.append("| ");
}

bool Sudoku::is_empty_at(uint8_t index) const {
    if (get_at(index) == EMPTY_TILE) {
        return true;
    }

    return false;
}

std::ostream& operator<<(std::ostream& os, std::unique_ptr<Sudoku> sudoku) {
    os << sudoku->get_as_formated_grid();
    return os;
}

uint8_t Sudoku::map_to_possible_value(uint8_t src) {
    return src % get_sudoku_side() + 1;
}