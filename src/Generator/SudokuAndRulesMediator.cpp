#include "SudokuAndRulesMediator.hpp"
#include "SudokuRules/SudokuXRules.hpp"

SudokuAndRulesMediator::SudokuAndRulesMediator(SUDOKU_TYPE type) {
    sudoku = std::make_shared<Sudoku>();
    switch (type) {
        case X:
            sudoku_rules = std::make_shared<SudokuXRules>(sudoku);
            break;
        case NORMAL:
            sudoku_rules = std::make_shared<SudokuRules>(sudoku);
            break;
    }
}

std::shared_ptr<Sudoku> SudokuAndRulesMediator::get_sudoku() const {
    return sudoku;
}

std::shared_ptr<SudokuRules> SudokuAndRulesMediator::get_sudoku_rules() const {
    return sudoku_rules;
}