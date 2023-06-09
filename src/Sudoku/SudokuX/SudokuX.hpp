#ifndef SUDOKU_X_HPP
#define SUDOKU_X_HPP

#include "Sudoku/Sudoku.hpp"

class SudokuX: public Sudoku {
    public: 
        bool is_validly_placed_at(uint8_t index) const override;
    private:
        inline bool is_on_diagonal(uint8_t index) const {
            return is_on_diagonal_from_u_l(index) 
                || is_on_diagonal_from_u_r(index);
        }

        //  regarding diagonals starting from up left and up right
        inline bool is_on_diagonal_from_u_l(uint8_t index) const {
            return get_col(index) == get_row(index);
        }

        inline bool is_on_diagonal_from_u_r(uint8_t index) const {
            return get_row(index) == get_sudoku_side() - get_col(index) - 1;
        }

        bool is_unique_in_diagonal(uint8_t index) const;

        bool is_unique_in_diagonal_from_u_l(uint8_t index) const;
        bool is_unique_in_diagonal_from_u_r(uint8_t index) const;
};

#endif