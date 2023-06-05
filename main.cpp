#include <iostream>
#include "SudokuGenerator/SudokuGenerator.hpp"

int main() {
    Sudoku sudoku;
    SudokuGenerator generator;
    std::cout << generator.generate_sudoku() << "\n";
    return 0;
}