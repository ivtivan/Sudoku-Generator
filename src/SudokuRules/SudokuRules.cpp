#include "Sudoku/Sudoku.hpp"
#include "SudokuRules.hpp"

SudokuRules::SudokuRules(std::shared_ptr<Sudoku> sudoku) :
    sudoku(sudoku) { 
    ;
}

std::shared_ptr<Sudoku> SudokuRules::get_sudoku() const {
    return sudoku;
}

bool SudokuRules::is_validly_placed_at(uint8_t index) const {
    return is_unique_in_row(index)
        && is_unique_in_col(index)
        && is_unique_in_square(index);
}

bool SudokuRules::is_unique_in_row(uint8_t index) const {
    const uint8_t beginning_row_index = get_beginning_row_index(index); 
    for (uint8_t curr_index = beginning_row_index;
            curr_index < beginning_row_index + get_sudoku()->get_sudoku_side(); 
            ++curr_index) {
        if (curr_index != index 
                && get_sudoku()->get_at(curr_index) == get_sudoku()->get_at(index)) {
            return false;
        }
    }

    return true;
}

uint8_t SudokuRules::get_beginning_row_index(uint8_t index) const {
    return get_row(index) * get_sudoku()->get_sudoku_side();
}

bool SudokuRules::is_unique_in_col(uint8_t index) const {
    const uint8_t beginning_col_index = get_beginning_col_index(index);
    for (uint8_t curr_index = beginning_col_index; 
            curr_index < get_sudoku()->get_num_sudoku_tiles();
            curr_index += get_sudoku()->get_sudoku_side()) {
        if (curr_index != index 
            && get_sudoku()->get_at(curr_index) == get_sudoku()->get_at(index)) {
                return false;
        }
    }

    return true;
}

uint8_t SudokuRules::get_beginning_col_index(uint8_t index) const {
    return get_col(index); //  implementation might change 
}

bool SudokuRules::is_unique_in_square(uint8_t index) const {
    const uint8_t beginning_square_index = get_beginning_square_index(index);
    for (uint8_t curr_square_row_index = 0;
        curr_square_row_index < get_sudoku()->get_subsquare_side(); ++curr_square_row_index) {
            
            for (uint8_t curr_square_col_index = 0;
                    curr_square_col_index < get_sudoku()->get_subsquare_side();
                    ++curr_square_col_index) {
                    
                const uint8_t curr_sudoku_index = beginning_square_index 
                    + curr_square_col_index
                    + curr_square_row_index *get_sudoku()-> get_sudoku_side();
                
                if (curr_sudoku_index != index 
                        && get_sudoku()->get_at(curr_sudoku_index) == get_sudoku()->get_at(index)) {
                    return false;
                }
            }
    }

    return true;
}

uint8_t SudokuRules::get_beginning_square_index(uint8_t index) const {
    const uint8_t beginning_row_index = get_beginning_row_index(index);
    const uint8_t beginning_col_index = get_beginning_col_index(index);

    const uint8_t square_starting_row =
        (beginning_row_index 
            / (get_sudoku()->get_sudoku_side() * get_sudoku()->get_subsquare_side()))
            * get_sudoku()->get_subsquare_side();
    const uint8_t square_starting_col =
        (beginning_col_index / get_sudoku()->get_subsquare_side()) 
        * get_sudoku()->get_subsquare_side();

    return get_sudoku()->map_row_col_to_index(square_starting_row, square_starting_col);
}

uint8_t SudokuRules::get_row(uint8_t index) const {
    return index / get_sudoku()->get_sudoku_side();
}


uint8_t SudokuRules::get_col(uint8_t index) const {
    return index % get_sudoku()->get_sudoku_side();
}