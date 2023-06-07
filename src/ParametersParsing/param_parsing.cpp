#include "param_parsing.hpp"

#include <iostream>
#include <limits>
#include <unistd.h>

void parse_option(const char option, const char* arg, parsed_params params);

//  logic outside of parsed_param structure
void set_type(parsed_params& params, const char* value);
void set_max_givens(parsed_params& params, const char* value);
void print_help_menu();

parsed_params parse_params(int argc, char** argv) {
    parsed_params params {
        NORMAL,                                 //  type
        std::numeric_limits<uint8_t>::max(),    //  max_givens
        false,                                  //  is_error_state
        false                                   //  should_not_act
    };

    char curr_opt;
    const char* opt_string = "t::g:h";   //  refers to the optstring name used in getopt man page
    while ((curr_opt = getopt(argc, argv, opt_string)) != -1) {
        switch (curr_opt) {
            case 't':
                set_type(params, optarg);
                break;
            case 'g':
                set_max_givens(params, optarg);
                break;
            case 'h':
                print_help_menu();
                params.should_not_act = true;
                break;
        }
    }

    return params;
}

void parse_option(const char option, const char* arg, parsed_params params) {
    switch (option) {
        case 't':
            set_type(params, arg);
            break;
        case 'g':
            set_max_givens(params, arg);
            break;
        case 'h':
            print_help_menu();
            break;
    }
}

void set_type(parsed_params& params, const char* value) {
    if(!value || std::atoi(value) == 0) {
        params.type = NORMAL;
    }
    else if (std::atoi(value) == 1) {
        params.type = X;
    }
    else {
        params.is_error_state = true;
        std::cout << "Type of sudoku not valid\n";
    }
}

void set_max_givens(parsed_params& params, const char* value) {
    params.max_givens = std::atoi(value);
}

void print_help_menu() {
    std::cout << "Accepted commands are:\n";
    std::cout << "-t[opt_arg]       - type of sudoku; default 0; 0 - normal, 1 - X, not implemented\n";
    std::cout << "-g[arg]           - maximum number of givens, below 21 might run forever\n";
    std::cout << "-h                - prints help menu\n";
}