#ifndef SUDOKU_RULES_HPP
#define SUDOKU_RULES_HPP

#include <cstdint>
#include <memory>

class Sudoku;

class SudokuRules {
    public:
        SudokuRules(std::shared_ptr<Sudoku> sudoku);
        
        virtual bool is_validly_placed_at(uint8_t index) const;
        virtual ~SudokuRules() = default;
    protected:
        std::shared_ptr<Sudoku> get_sudoku() const;

        uint8_t get_col(uint8_t index) const;
        uint8_t get_row(uint8_t index) const;

    private:
        std::shared_ptr<Sudoku> sudoku;

        uint8_t get_beginning_row_index(uint8_t index) const;
        uint8_t get_beginning_col_index(uint8_t index) const;
        uint8_t get_beginning_square_index(uint8_t index) const;

        bool is_unique_in_row(uint8_t index) const;
        bool is_unique_in_col(uint8_t index) const;
        bool is_unique_in_square(uint8_t index) const;
};

#endif