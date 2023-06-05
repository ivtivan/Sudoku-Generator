#include "SudokuGenerator.hpp"
#include "helper.hpp"

SudokuGenerator::SudokuGenerator() : sudoku(), solver(),
    pairs_to_try_reset(), uniques_to_try_reset(), tiles_reset(0) {
    ;
}


Sudoku SudokuGenerator::generate_sudoku() {
    bool is_fillable = solver.fill_by_bruteforce(sudoku);
    
    if (is_fillable) {
        reset_tiles();
    }

    return sudoku;
}

void SudokuGenerator::reset_tiles() {
    reset_pairs();
    reset_uniques();
}

void SudokuGenerator::reset_pairs() {
    setup_pairs_to_try_reset();
    uint8_t num_left_to_try_reset = pairs_to_try_reset.size();
    bool is_reset;

    while (num_left_to_try_reset != 0) {
        uint8_t index_to_erase = get_random(num_left_to_try_reset);
        is_reset = try_reset_pair(index_to_erase);
        if (is_reset) {
            tiles_reset++;
        }

        pairs_to_try_reset.erase(index_to_erase);
        num_left_to_try_reset--;
    }
}

void SudokuGenerator::setup_pairs_to_try_reset() {
    for (uint8_t curr_pair_index = 0; curr_pair_index <
        (Sudoku::SUDOKU_TILES + 1) / 2; ++curr_pair_index) {
            pairs_to_try_reset.insert(curr_pair_index);
    }
}

bool SudokuGenerator::try_reset_pair(uint8_t pair_index) {
    uint8_t first_el_index = get_pair_first_el(pair_index);
    uint8_t second_el_index = get_pair_second_el(pair_index);

    uint8_t original_value_first_el = sudoku.at(first_el_index);
    uint8_t original_value_second_el = sudoku.at(second_el_index);

    sudoku.reset_at(first_el_index);
    sudoku.reset_at(second_el_index);

    if (solver.has_multiple_solutions(sudoku)) {
        restore_at_to(first_el_index, original_value_first_el);
        restore_at_to(second_el_index, original_value_second_el);
        
        return false;
    }

    return true;
}

void SudokuGenerator::restore_at_to(uint8_t index, uint8_t original_value) {
    sudoku.set_at(index, original_value);
}

uint8_t SudokuGenerator::get_pair_first_el(uint8_t pair_index) const {
    return pair_index;
}

uint8_t SudokuGenerator::get_pair_second_el(uint8_t pair_index) const {
    return Sudoku::SUDOKU_TILES - pair_index - 1;
}

void SudokuGenerator::reset_uniques() {
    setup_uniques_to_try_reset();
    uint8_t num_left_to_try_reset = uniques_to_try_reset.size();
    bool is_reset;

    while (num_left_to_try_reset != 0) {
        uint8_t index_to_erase = get_random(num_left_to_try_reset);
        is_reset = try_reset_unique(index_to_erase);
        if (is_reset) {
            tiles_reset++;
        }

        uniques_to_try_reset.erase(index_to_erase);
        num_left_to_try_reset--;
    }
    
}

void SudokuGenerator::setup_uniques_to_try_reset() {
    for (uint8_t pair_index : pairs_to_try_reset) {
        uniques_to_try_reset.insert(get_pair_first_el(pair_index));
        uniques_to_try_reset.insert(get_pair_second_el(pair_index));
    }
}

bool SudokuGenerator::try_reset_unique(uint8_t index) {
    uint8_t original_value = sudoku.at(index);

    sudoku.reset_at(index);

    if (solver.has_multiple_solutions(sudoku)) {
        restore_at_to(index, original_value);
        return false;
    }

    return true;
}