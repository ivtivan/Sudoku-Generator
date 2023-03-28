# Sudoku-Generator

## Introduction
The idea of the project is to find a way to generate sudokus of different difficulty for personal use.

## Summarized
A number of sudokus of random difficulty is created and all are saved in a parsed way (inspired by FEN, used in chess) with their difficulty in a file. The abbreviation used for the notation for state in this repo is Sudoku Data Notation or SDN. It is possible to pass a SSN and get the sudoku displayed in the terminal.

## Sudoku Data Notation or SDN
SDN contains three fields separated by space:
1.  Digit placement data: Each row is described, starting with the upper one, with a '/' inserted between two each one. Within each row, the contents are described from left to right and each number i is represented by the ith letter of the alpahbet (a - 1, b -2, c - 3,...,i - 9). A set of one or more ampty spaces on a row is represented by a digit from 1 to 9 corresponding to their count.
2.  Difficulty - a number , with higher being more difficult.
3.  Number of digits in the puzzle

## Usage
Using the makefile run make generate cnt=<number> to generate cnt sudokus and make draw SDM="<SDM for puzzle>" to draw the sudoku.

## Ranking difficulty

##
