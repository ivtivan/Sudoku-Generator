#include "SudokuBuilder.hpp"
#include "SudokuGenerator.hpp"
#include "helper.hpp"

SudokuGenerator::SudokuGenerator() : sudoku(), solver(),
    pairs_to_reset(), uniques_to_reset() {
    ;
}


std::unique_ptr<Sudoku> SudokuGenerator::generate_sudoku(SUDOKU_TYPE type) {
    SudokuBuilder builder;
    sudoku = builder.build_sudoku(type);
    solver.set_sudoku(sudoku);
    bool is_fillable = solver.fill_by_bruteforce();
    
    if (is_fillable) {
        reset_tiles();
    }
    else {
        return nullptr;
    }

    return std::make_unique<Sudoku>(*sudoku);
}

void SudokuGenerator::reset_tiles() {
    reset_pairs();
    reset_uniques();
    
    sudoku->set_num_givens(uniques_to_reset.size());
}

void SudokuGenerator::reset_pairs() {
    setup_pairs_to_reset();
    std::set<uint8_t> pairs_to_try_reset = pairs_to_reset;

    while (!pairs_to_try_reset.empty()) {
        pairs_to_try_reset = reset_random_pair(pairs_to_try_reset);
    }
}

void SudokuGenerator::setup_pairs_to_reset() {
    for (uint8_t curr_pair_index = 0; curr_pair_index <
        (Sudoku::get_num_sudoku_tiles() + 1) / 2; ++curr_pair_index) {
            pairs_to_reset.insert(curr_pair_index);
    }
}

std::set<uint8_t> SudokuGenerator::reset_random_pair(std::set<uint8_t> pairs) {
    uint8_t tile_to_reset = get_tile_to_reset(pairs);
    bool is_reset = try_reset_pair(tile_to_reset);

    if (is_reset) {
        pairs_to_reset.erase(tile_to_reset);
    }

    pairs.erase(tile_to_reset);

    return pairs;
}

uint8_t SudokuGenerator::get_tile_to_reset(std::set<uint8_t> els_to_try_reset) const {
    uint8_t tile_to_reset = get_random(els_to_try_reset.size());
    auto iterator_to_reset = els_to_try_reset.begin();
    std::advance(iterator_to_reset, tile_to_reset);
    return *iterator_to_reset;
}

bool SudokuGenerator::try_reset_pair(uint8_t pair_index) {
    uint8_t first_el_index = get_pair_first_el(pair_index);
    uint8_t second_el_index = get_pair_second_el(pair_index);

    uint8_t original_value_first_el = sudoku->at(first_el_index);
    uint8_t original_value_second_el = sudoku->at(second_el_index);

    sudoku->reset_at(first_el_index);
    sudoku->reset_at(second_el_index);

    if (solver.finds_multiple_solutions()) {
        restore_tile_at_to(first_el_index, original_value_first_el);
        restore_tile_at_to(second_el_index, original_value_second_el);
        
        return false;
    }

    return true;
}

inline void SudokuGenerator::restore_tile_at_to(uint8_t index, uint8_t original_value) {
    sudoku->set_at(index, original_value);
}

inline uint8_t SudokuGenerator::get_pair_first_el(uint8_t pair_index) const {
    return pair_index;
}

inline uint8_t SudokuGenerator::get_pair_second_el(uint8_t pair_index) const {
    return Sudoku::get_num_sudoku_tiles() - pair_index - 1;
}

void SudokuGenerator::reset_uniques() {
    setup_uniques_to_reset();
    std::set<uint8_t> uniques_to_try_reset = uniques_to_reset;
    
    while (!uniques_to_try_reset.empty()) {
        uniques_to_try_reset = reset_random_unique(uniques_to_try_reset);
    }
}

void SudokuGenerator::setup_uniques_to_reset() {
    for (uint8_t pair_index : pairs_to_reset) {
        uniques_to_reset.insert(get_pair_first_el(pair_index));
        uniques_to_reset.insert(get_pair_second_el(pair_index));
    }
}

std::set<uint8_t> SudokuGenerator::reset_random_unique(std::set<uint8_t> uniques) {
    uint8_t tile_to_reset = get_tile_to_reset(uniques);
    bool is_reset = try_reset_unique(tile_to_reset);
    if (is_reset) {
        uniques_to_reset.erase(tile_to_reset);
    }

    uniques.erase(tile_to_reset);
    return uniques;
}

bool SudokuGenerator::try_reset_unique(uint8_t index) {
    uint8_t original_value = sudoku->at(index);

    sudoku->reset_at(index);

    if (solver.finds_multiple_solutions()) {
        restore_tile_at_to(index, original_value);
        return false;
    }

    return true;
}