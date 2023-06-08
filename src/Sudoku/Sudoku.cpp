#include "Sudoku.hpp"
#include <algorithm>

Sudoku::Sudoku() : num_givens(0) {
    for(uint8_t i = 0; i < get_num_sudoku_tiles(); ++i) {
        tiles[i] = EMPTY_TILE;
    }
}

void Sudoku::set_num_givens(uint8_t num_givens) {
    this->num_givens = num_givens;
}

uint8_t Sudoku::get_num_givens() const {
    return num_givens;
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

    return '0' + at(row, col);
}

void Sudoku::append_row_break(std::string& string_representation) const {
    uint8_t row_length = 2 * (get_subsquare_side() + 1) + 4 * get_sudoku_side() - 1;
    string_representation.append(std::string(row_length,'-'));
    string_representation += "\n";
}

void Sudoku::append_col_break(std::string& string_representation) const {
    string_representation.append("| ");
}

uint8_t Sudoku::at(uint8_t row, uint8_t col) const {
    return at(map_row_col_to_index(row, col));
}

uint8_t Sudoku::at(uint8_t index) const {
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

bool Sudoku::is_empty_at(uint8_t index) const {
    if (at(index) == EMPTY_TILE) {
        return true;
    }

    return false;
}

bool Sudoku::is_validly_placed_at(uint8_t index) const {
    return is_unique_in_row(index)
        && is_unique_in_col(index)
        && is_unique_in_square(index);
}

bool Sudoku::is_unique_in_row(uint8_t index) const {
    const uint8_t beginning_row_index = get_beginning_row_index(index); 
    for (uint8_t curr_index = beginning_row_index;
        curr_index < beginning_row_index + get_sudoku_side(); ++curr_index) {
        if (curr_index != index 
            && at(curr_index) == at(index)) {
                return false;
        }
    }

    return true;
}

uint8_t Sudoku::get_beginning_row_index(uint8_t index) const {
    return get_row(index) * get_sudoku_side();
}

uint8_t Sudoku::get_row(uint8_t index) const {
    return index / get_sudoku_side();
}

bool Sudoku::is_unique_in_col(uint8_t index) const {
    const uint8_t beginning_col_index = get_beginning_col_index(index);
    for (uint8_t curr_index = beginning_col_index; 
        curr_index < get_num_sudoku_tiles(); curr_index += get_sudoku_side()) {
        if (curr_index != index 
            && at(curr_index) == at(index)) {
                return false;
        }
    }

    return true;
}

uint8_t Sudoku::get_beginning_col_index(uint8_t index) const {
    return get_col(index); //  implementation might change 
}

uint8_t Sudoku::get_col(uint8_t index) const {
    return index % get_sudoku_side();
}

bool Sudoku::is_unique_in_square(uint8_t index) const {
    const uint8_t beginning_square_index = get_beginning_square_index(index);
    for (uint8_t curr_square_row_index = 0;
        curr_square_row_index < get_subsquare_side(); ++curr_square_row_index) {
            
            for (uint8_t curr_square_col_index = 0;
                curr_square_col_index < get_subsquare_side(); ++curr_square_col_index) {
                    
                    const uint8_t curr_sudoku_index = beginning_square_index 
                        + curr_square_col_index
                        + curr_square_row_index * get_sudoku_side();
                    
                    if (curr_sudoku_index != index 
                        && at(curr_sudoku_index) == at(index)) {
                            return false;
                    }
            }
    }

    return true;
}

uint8_t Sudoku::get_beginning_square_index(uint8_t index) const {
    const uint8_t beginning_row_index = get_beginning_row_index(index);
    const uint8_t beginning_col_index = get_beginning_col_index(index);

    const uint8_t square_starting_row =
        (beginning_row_index / (get_sudoku_side() * get_subsquare_side()))
            * get_subsquare_side();
    const uint8_t square_starting_col =
        (beginning_col_index / get_subsquare_side()) * get_subsquare_side();

    return map_row_col_to_index(square_starting_row, square_starting_col);
}

uint8_t Sudoku::map_to_possible_value(uint8_t src) {
    return src % get_sudoku_side() + 1;
}

std::ostream& operator<<(std::ostream& os, std::unique_ptr<Sudoku> sudoku) {
    os << sudoku->get_as_formated_grid();
    return os;
}