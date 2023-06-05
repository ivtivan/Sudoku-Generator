#include "SudokuSolver.hpp"
#include "helper.hpp"

#include <iostream>

bool SudokuSolver::fill_by_bruteforce(Sudoku& sudoku) const {
    int8_t first_empty = find_empty(sudoku);
    
    if (first_empty == -1) { //  no empty cells found
        return true;
    }

    const uint8_t first_possible_value = get_possible_value();
    uint8_t curr_possible_value = first_possible_value;
    do {
        sudoku.set_at(first_empty, curr_possible_value);

        if (sudoku.is_validly_placed_at(first_empty)
            && fill_by_bruteforce(sudoku)) {
                return true;
        }

        sudoku.reset_at(first_empty);

        curr_possible_value = get_next_possible_value(curr_possible_value);
    }
    while(curr_possible_value != first_possible_value);

    return false;
}

uint8_t SudokuSolver::get_next_possible_value(uint8_t curr_possible_value) const {
    curr_possible_value++;
    return Sudoku::map_to_possible_value(curr_possible_value);
}

uint8_t SudokuSolver::get_possible_value() const {
    return Sudoku::map_to_possible_value(get_random(Sudoku::SUDOKU_SIDE) + 1);
}

bool SudokuSolver::has_multiple_solutions(Sudoku sudoku) const {
    return (count_solutions_one_or_more(sudoku) > 1);
}

uint8_t SudokuSolver::count_solutions_one_or_more(Sudoku sudoku) const {
    int8_t first_empty = find_empty(sudoku);
    
    if (first_empty == -1) { //  no empty cells found
        return 1;
    }

    uint8_t solutions_count = 0;
    const uint8_t first_possible_value = get_possible_value();

    uint8_t curr_possible_value = first_possible_value;
    do {
        sudoku.set_at(first_empty, curr_possible_value);

        if (sudoku.is_validly_placed_at(first_empty)) {
            solutions_count += count_solutions_one_or_more(sudoku);
            if (solutions_count > 1) {
                return solutions_count;
            }
        }

        sudoku.reset_at(first_empty);

        curr_possible_value = get_next_possible_value(curr_possible_value);
    }
    while(curr_possible_value != first_possible_value);

    return solutions_count;
}

int8_t SudokuSolver::find_empty(const Sudoku& sudoku) const {
    uint8_t index = 0;
    while (index < Sudoku::SUDOKU_TILES) {
        if (sudoku.is_empty_at(index)){
            return index;
        }
        index++;
    } 

    return -1; //  no empty tiles found
}