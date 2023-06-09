#ifndef SUDOKU_X_HPP
#define SUDOKU_X_HPP

#include "Sudoku/Sudoku.hpp"

class SudokuX: public Sudoku {
    public: 
        bool is_validly_placed_at(uint8_t index) const override;
    private:
        inline bool is_on_diagonal(uint8_t index) const;

        //  regarding diagonals starting from up left and up right
        inline bool is_on_diagonal_from_u_l(uint8_t index) const;
        inline bool is_on_diagonal_from_u_r(uint8_t index) const;

        bool is_unique_in_diagonal(uint8_t index) const;

        bool is_unique_in_diagonal_from_u_l(uint8_t index) const;
        bool is_unique_in_diagonal_from_u_r(uint8_t index) const;
};

#endif