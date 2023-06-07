#include <iostream>
#include "ParametersParsing/param_parsing.hpp"
#include "SudokuGenerator/SudokuGenerator.hpp"

Sudoku generate_sudoku_from_params(parsed_params params);
void print_sudoku_data(Sudoku sudoku);

int main(int argc, char** argv) {    
    parsed_params params = parse_params(argc, argv);
    
    if (params.is_error_state) {
        return 1;
    }

    if (params.should_not_act) {
        return 0;
    }
    
    Sudoku sudoku = generate_sudoku_from_params(params);
    print_sudoku_data(sudoku);
    return 0;
}

Sudoku generate_sudoku_from_params(parsed_params params) {
    Sudoku sudoku;
    while (sudoku.get_num_givens() > params.max_givens || sudoku.is_empty()) {
        SudokuGenerator generator;
        sudoku = generator.generate_sudoku();
    }

    return sudoku;
}

void print_sudoku_data(Sudoku sudoku) {
    std::cout << "Generated sudoku with "
        << (int)sudoku.get_num_givens() << " givens.\n\n";
    std::cout << sudoku << "\n";
}