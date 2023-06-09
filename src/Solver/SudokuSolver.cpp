#include "SudokuSolver.hpp"
#include "helper.hpp"

void SudokuSolver::set_sudoku(std::shared_ptr<Sudoku> sudoku) {
    this->sudoku = sudoku;
}

bool SudokuSolver::fill_by_bruteforce() const {
    int8_t first_empty = find_empty();
    
    if (first_empty == -1) { //  no empty cells found
        return true;
    }

    const uint8_t first_possible_value = get_possible_value();
    uint8_t curr_possible_value = first_possible_value;
    do {
        bool is_possible = try_set_at(first_empty, curr_possible_value);
        if (is_possible) {
            return true;
        }
        
        curr_possible_value = get_next_possible_value(curr_possible_value);
    }
    while(curr_possible_value != first_possible_value);

    return false;
}

int8_t SudokuSolver::find_empty() const {
    uint8_t index = 0;
    while (index < Sudoku::get_num_sudoku_tiles()) {
        if (sudoku->is_empty_at(index)){
            return index;
        }
        index++;
    } 

    return -1; //  no empty tiles found
}

uint8_t SudokuSolver::get_possible_value() const {
    return Sudoku::map_to_possible_value(get_random(Sudoku::get_sudoku_side()) + 1);
}

uint8_t SudokuSolver::get_next_possible_value(uint8_t curr_possible_value) const {
    curr_possible_value++;
    return Sudoku::map_to_possible_value(curr_possible_value);
}

bool SudokuSolver::try_set_at(uint8_t index, uint8_t value) const {
    sudoku->set_at(index, value);

    if (sudoku->is_validly_placed_at(index)
        && fill_by_bruteforce()) {
            return true;
    }

    sudoku->reset_at(index);
    return false;
}

bool SudokuSolver::finds_multiple_solutions() const {
    return (count_solutions_one_or_more() > 1);
}

uint8_t SudokuSolver::count_solutions_one_or_more() const {
    int8_t first_empty = find_empty();
    
    if (first_empty == -1) { //  no empty cells found
        return 1;
    }

    uint8_t solutions_count = 0;
    const uint8_t first_possible_value = get_possible_value();

    uint8_t curr_possible_value = first_possible_value;
    do {
        sudoku->set_at(first_empty, curr_possible_value);

        if (sudoku->is_validly_placed_at(first_empty)) {
            solutions_count += count_solutions_one_or_more();
            if (solutions_count > 1) {
                sudoku->reset_at(first_empty);
                return solutions_count;
            }
        }

        sudoku->reset_at(first_empty);

        curr_possible_value = get_next_possible_value(curr_possible_value);
    }
    while(curr_possible_value != first_possible_value);

    return solutions_count;
}