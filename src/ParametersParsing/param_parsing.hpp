#include "sudoku_types.hpp"
#include <cstdint>

typedef struct {
    SUDOKU_TYPE type;
    uint8_t max_givens;
    bool is_error_state;
    bool should_not_act;
} parsed_params;

parsed_params parse_params(int argc, char** argv);