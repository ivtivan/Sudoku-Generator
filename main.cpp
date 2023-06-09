#include <iostream>
#include <memory>

#include "Generator/SudokuGenerator.hpp"
#include "ParametersParsing/param_parsing.hpp"

std::unique_ptr<Sudoku> generate_sudoku_from_params(parsed_params params);
void print_sudoku_data(std::unique_ptr<Sudoku> sudoku);

int main(int argc, char** argv) {    
    parsed_params params = parse_params(argc, argv);
    
    if (params.is_error_state) {
        return 1;
    }

    if (params.should_not_act) {
        return 0;
    }
    
    auto sudoku = generate_sudoku_from_params(params);
    print_sudoku_data(std::move(sudoku));
    return 0;
}

std::unique_ptr<Sudoku> generate_sudoku_from_params(parsed_params params) {
    auto sudoku = std::make_unique<Sudoku>();
    while (sudoku->get_num_givens() > params.max_givens || sudoku->is_empty()) {
        SudokuGenerator generator;
        sudoku = generator.generate_sudoku(params.type);
    }

    return sudoku;
}

void print_sudoku_data(std::unique_ptr<Sudoku> sudoku) {
    std::cout << "Generated sudoku with "
        << (int)sudoku->get_num_givens() << " givens.\n\n";
    std::cout << std::move(sudoku) << "\n";
}