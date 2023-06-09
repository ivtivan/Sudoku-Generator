#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <array>
#include <cstdint>
#include <memory>
#include <string>

class Sudoku {
    public:
        Sudoku();
        Sudoku(const Sudoku& other) = default;
        Sudoku& operator=(const Sudoku& other) = default;

        static constexpr uint8_t get_subsquare_side() { return SUBSQUARE_SIDE; }
        static constexpr uint8_t get_sudoku_side() { return SUDOKU_SIDE; }
        static constexpr uint8_t get_num_sudoku_tiles() { return SUDOKU_TILES; }

        void set_num_givens(uint8_t num_givens);
        uint8_t get_num_givens() const;

        bool is_empty() const;

        inline uint8_t at(uint8_t row, uint8_t col) const {
            return at(map_row_col_to_index(row, col));
        }
        
        inline uint8_t at(uint8_t index) const {
            return tiles[index];
        }

        inline void set_at(uint8_t row, uint8_t col, uint8_t value) {
            set_at(map_row_col_to_index(row, col), value);
        }
        inline void set_at(uint8_t index, uint8_t value) {
            tiles[index] = value;
        }

        inline void reset_at(uint8_t index) {
            tiles[index] = EMPTY_TILE;
        }

        //  a tile is empty if it's value is 0
        bool is_empty_at(uint8_t index) const;
        virtual bool is_validly_placed_at(uint8_t index) const;

        inline static uint8_t map_to_possible_value(uint8_t src) {
            return src % get_sudoku_side() + 1;
        }

        friend std::ostream& operator<<(std::ostream& os, std::unique_ptr<Sudoku> sudoku);

    protected:
        inline uint8_t get_row(uint8_t index) const {
            return index / get_sudoku_side();
        }

        inline uint8_t get_col(uint8_t index) const {
            return index % get_sudoku_side();
        }
        inline uint8_t map_row_col_to_index(uint8_t row, uint8_t col) const {
            return row * get_sudoku_side() + col;
        }
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

        inline uint8_t get_beginning_row_index(uint8_t index) const {
            return get_row(index) * get_sudoku_side();
        }
        inline uint8_t get_beginning_col_index(uint8_t index) const {
            return get_col(index); //  implementation might change 
        }
        uint8_t get_beginning_square_index(uint8_t index) const;

        bool is_unique_in_row(uint8_t index) const;
        bool is_unique_in_col(uint8_t index) const;
        bool is_unique_in_square(uint8_t index) const;
};

#endif