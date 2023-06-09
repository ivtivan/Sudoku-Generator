#include "Sudoku/Sudoku.hpp"
#include "SudokuXRules.hpp"

SudokuXRules::SudokuXRules(std::shared_ptr<Sudoku> sudoku) :
    SudokuRules(sudoku) {
    ;
}

bool SudokuXRules::is_validly_placed_at(uint8_t index) const {
    bool are_general_rules_satified = SudokuRules::is_validly_placed_at(index);

    if (is_on_diagonal(index) && are_general_rules_satified) {
        are_general_rules_satified = 
            are_general_rules_satified && is_unique_in_diagonal(index);
    }

    return are_general_rules_satified;
}

bool SudokuXRules::is_on_diagonal(uint8_t index) const {
    return is_on_diagonal_from_u_l(index) 
        || is_on_diagonal_from_u_r(index);
}

bool SudokuXRules::is_on_diagonal_from_u_l(uint8_t index) const {
    return get_col(index) == get_row(index);
}

bool SudokuXRules::is_on_diagonal_from_u_r(uint8_t index) const {
    return get_row(index) == get_sudoku()->get_sudoku_side() - get_col(index) - 1;
}

bool SudokuXRules::is_unique_in_diagonal(uint8_t index) const {
    bool is_unique = true;
    if (is_on_diagonal_from_u_l(index)) {
        is_unique = is_unique && is_unique_in_diagonal_from_u_l(index);
    }
    if (is_on_diagonal_from_u_r(index)) {
        is_unique = is_unique && is_unique_in_diagonal_from_u_r(index);
    }

    return is_unique;
}

bool SudokuXRules::is_unique_in_diagonal_from_u_l(uint8_t index) const {
    for (uint8_t index_in_diag = 0;
        index_in_diag <get_sudoku()->get_sudoku_side(); ++index_in_diag) {
        
        if (get_sudoku()->get_at(index_in_diag, index_in_diag) == get_sudoku()->get_at(index)
                && get_sudoku()->map_row_col_to_index(index_in_diag, index_in_diag) != index) {
            return false;
        }
    }

    return true;
}

bool SudokuXRules::is_unique_in_diagonal_from_u_r(uint8_t index) const {
    uint8_t row_index, col_index;
    for (row_index = 0; row_index < get_sudoku()->get_sudoku_side(); ++row_index) {
        col_index = get_sudoku()->get_sudoku_side() - row_index - 1;
        if (get_sudoku()->get_at(row_index, col_index) == get_sudoku()->get_at(index) &&
            get_sudoku()->map_row_col_to_index(row_index, col_index) != index) {
            return false;
        }
    }

    return true;
}