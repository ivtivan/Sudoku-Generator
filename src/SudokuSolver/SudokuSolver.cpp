#include "SudokuSolver.hpp"
#include "helper.hpp"

#include <iostream>

bool SudokuSolver::fill_by_bruteforce(Sudoku& sudoku) const{
    int8_t first_empty = find_empty(sudoku);
    
    if (first_empty == -1) { //  no empty cells found
        return true;
    }

    uint8_t first_possible_value = sudoku.map_to_possible_value(get_random(Sudoku::SUDOKU_SIDE));
    uint8_t curr_possible_value = first_possible_value;
    do {
        
        sudoku.set_at(first_empty, curr_possible_value);

        if (sudoku.is_validly_placed_at(first_empty)
            && fill_by_bruteforce(sudoku)) {
                return true;
        }

        sudoku.reset_at(first_empty);

        curr_possible_value++;
        curr_possible_value = sudoku.map_to_possible_value(curr_possible_value);
    }
    while(curr_possible_value != first_possible_value);

    return false;
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

void SudokuSolver::solve_human_algos(Sudoku& /*sudoku*/) const {

}