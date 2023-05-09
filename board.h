#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <set>
#include <random>
#include <algorithm>
#include <iterator>

std::ifstream fin("config.txt");

class sudoku_board {
private:
    std::vector<std::vector<std::pair<char, int>>> board;
public:
    sudoku_board();

    void load_config();
    void print_board() const;
    void make_move(int x, int y, int number);
    bool check_correct(bool debug) const;
    void generate(int quantity);
    void clear_cell(int x, int y);
private:
    bool solution_count(int current, int clear_left);
    void swap_rows(int row1, int row2);
    void swap_cols(int col1, int col2);
    bool fill_full(int row, int col);
    bool delete_check(int row, int col, int left);
};

#endif // BOARD_H