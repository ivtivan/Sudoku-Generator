#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <array>
#include <cstdint>
#include <string>

class Sudoku {
    public:
        Sudoku();

        static constexpr uint8_t get_subsquare_side() { return SUBSQUARE_SIDE; }
        static constexpr uint8_t get_sudoku_side() { return SUDOKU_SIDE; }
        static constexpr uint8_t get_num_sudoku_tiles() { return SUDOKU_TILES; }

        void set_num_givens(uint8_t num_givens);
        uint8_t get_num_givens() const;

        bool is_empty() const;

        uint8_t at(uint8_t row, uint8_t col) const;
        uint8_t at(uint8_t index) const;

        void set_at(uint8_t row, uint8_t col, uint8_t value);
        void set_at(uint8_t index, uint8_t value);

        void reset_at(uint8_t index);

        //  a tile is empty if it's value is 0
        bool is_empty_at(uint8_t index) const;
        bool is_validly_placed_at(uint8_t index) const;

        static uint8_t map_to_possible_value(uint8_t src);

        friend std::ostream& operator<<(std::ostream& os, Sudoku sudoku);

    private:
        static constexpr uint8_t SUBSQUARE_SIDE = 3;
        static constexpr uint8_t SUDOKU_SIDE = SUBSQUARE_SIDE * SUBSQUARE_SIDE;
        static constexpr uint8_t SUDOKU_TILES = SUDOKU_SIDE * SUDOKU_SIDE;

        static constexpr uint8_t EMPTY_TILE = 0;
        uint8_t num_givens;

        std::array<uint8_t, SUDOKU_TILES> tiles;

        std::string get_as_formated_grid() const;
        void append_tile_value_at(std::string& string_representation,
            uint8_t row, uint8_t col) const;
        void append_row_break(std::string& string_representation) const;
        void append_col_break(std::string& string_representation) const;
        char map_tile_value_to_char(uint8_t row, uint8_t col) const;

        uint8_t map_row_col_to_index(uint8_t row, uint8_t col) const;
        uint8_t get_beginning_row_index(uint8_t index) const;
        uint8_t get_beginning_col_index(uint8_t index) const;
        uint8_t get_beginning_square_index(uint8_t index) const;

        bool is_unique_in_row(uint8_t index) const;
        bool is_unique_in_col(uint8_t index) const;
        bool is_unique_in_square(uint8_t index) const;
};

#endif