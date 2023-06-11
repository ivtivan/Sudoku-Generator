#ifndef SUDOKU_X_RULES_HPP
#define SUDOKU_X_RULES_HPP

#include <cstdint>
#include <memory>

#include "SudokuRules.hpp"

class SudokuXRules : public SudokuRules {
    public:
        SudokuXRules(std::shared_ptr<Sudoku> sudoku);

        bool is_validly_placed_at(uint8_t index) const override;
    private:
        bool is_on_diagonal(uint8_t index) const;

        //  regarding diagonals starting from up left and up right
        bool is_on_diagonal_from_u_l(uint8_t index) const;
        bool is_on_diagonal_from_u_r(uint8_t index) const;

        bool is_unique_in_diagonal(uint8_t index) const;

        bool is_unique_in_diagonal_from_u_l(uint8_t index) const;
        bool is_unique_in_diagonal_from_u_r(uint8_t index) const;   

};

#endif