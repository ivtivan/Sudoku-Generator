#include "SudokuGenerator.hpp"
#include "helper.hpp"

SudokuGenerator::SudokuGenerator() : sudoku(), solver(),
    pairs_still_not_reset(), uniques_still_not_reset() {
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
    sudoku.set_num_givens(uniques_still_not_reset.size());
}

void SudokuGenerator::reset_pairs() {
    setup_pairs_still_not_reset();
    std::set<uint8_t> pairs_to_try_reset = pairs_still_not_reset;
    uint8_t num_left_to_try_reset = pairs_to_try_reset.size();
    bool is_reset;

    while (num_left_to_try_reset != 0) {
        uint8_t index_to_reset = get_random(num_left_to_try_reset);
        auto iterator_to_reset = pairs_to_try_reset.begin();
        std::advance(iterator_to_reset, index_to_reset);
        is_reset = try_reset_pair(*iterator_to_reset);
        if (is_reset) {
            pairs_still_not_reset.erase(*iterator_to_reset);
        }

        pairs_to_try_reset.erase(*iterator_to_reset);
        num_left_to_try_reset--;
    }
}

void SudokuGenerator::setup_pairs_still_not_reset() {
    for (uint8_t curr_pair_index = 0; curr_pair_index <
        (Sudoku::SUDOKU_TILES + 1) / 2; ++curr_pair_index) {
            pairs_still_not_reset.insert(curr_pair_index);
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
    setup_uniques_still_not_reset();
    std::set<uint8_t> uniques_to_try_reset = uniques_still_not_reset;
    uint8_t num_left_to_try_reset = uniques_to_try_reset.size();
    bool is_reset;

    while (num_left_to_try_reset != 0) {
        uint8_t index_to_reset = get_random(num_left_to_try_reset);
        auto iterator_to_reset = uniques_to_try_reset.begin();
        std::advance(iterator_to_reset, index_to_reset);
        is_reset = try_reset_unique(*iterator_to_reset);
        if (is_reset) {
            uniques_still_not_reset.erase(*iterator_to_reset);
        }

        uniques_to_try_reset.erase(*iterator_to_reset);
        num_left_to_try_reset--;
    }
    
}

void SudokuGenerator::setup_uniques_still_not_reset() {
    for (uint8_t pair_index : pairs_still_not_reset) {
        uniques_still_not_reset.insert(get_pair_first_el(pair_index));
        uniques_still_not_reset.insert(get_pair_second_el(pair_index));
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