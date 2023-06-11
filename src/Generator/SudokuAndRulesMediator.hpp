#ifndef SUDOKU_AND_RULES_MEDIATOR_HPP
#define SUDOKU_AND_RULES_MEDIATOR_HPP

#include <memory>

#include "Sudoku/Sudoku.hpp"
#include "SudokuRules/SudokuRules.hpp"
#include "sudoku_types.hpp"

class SudokuAndRulesMediator {
    public:
        SudokuAndRulesMediator(SUDOKU_TYPE type);

        std::shared_ptr<Sudoku> get_sudoku() const;
        std::shared_ptr<SudokuRules> get_sudoku_rules() const;
    private:
        std::shared_ptr<Sudoku> sudoku;
        std::shared_ptr<SudokuRules> sudoku_rules;
};

#endif