#include "board.h"

sudoku_board::sudoku_board(): board(std::vector<std::vector<std::pair<char, int>>>(9, std::vector<std::pair<char, int>>(9, std::make_pair(' ', 0)))) {}

void sudoku_board::load_config() {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            int input;
            fin >> input;
            if (!input) {
                board[i][j].first = ' ';
                board[i][j].second = 0;
            }
            else {
                board[i][j].first = input + '0';
                board[i][j].second = 1;
            }
        }
    }
}

void sudoku_board::print_board() const {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            std::cout << board[i][j].first;
            if (j == 2 || j == 5) std::cout << " | ";
            else if (j < board[i].size()) std::cout << " ";
        }
        std::cout << std::endl;
        if (i == 2 || i == 5) std::cout << "──────┼───────┼──────" << std::endl;
    }
}

void sudoku_board::make_move(int x, int y, int value) {
    if (x > 9 || y > 9 || x <= 0 || y <= 0) {
        std::cout << "Invalid position" << std::endl;
        return;
    }

    if (value <= 0 || value > 9) {
        std::cout << "Invalid value" << std::endl;
        return;
    }

    if (board[x - 1][y - 1].second) {
        std::cout << "Can't change default cell number" << std::endl;
        return;
    }

    board[x - 1][y - 1].first = value + '0';
    print_board();
}

void sudoku_board::clear_cell(int x, int y) {
    if (x > 9 || y > 9 || x <= 0 || y <= 0) {
        std::cout << "Invalid position" << std::endl;
        return;
    }

    if (board[x - 1][y - 1].second) {
        std::cout << "Can't clear default cell number" << std::endl;
        return;
    }

    board[x - 1][y - 1].first = ' ';
    print_board();
}

bool sudoku_board::check_correct(bool debug = false) const {
    bool all = true;
    //! First check rows
    for (int i = 0; i < 9; i++) {
        std::set<char> unique;
        int clear = 0;
        for (int j = 0; j < 9; j++) {
            if (board[i][j].first == ' ') clear++;
            else unique.insert(board[i][j].first);
        }

        all &= (clear == 0);

        if (unique.size() != 9 - clear) {
            if (!debug) std::cout << "Row " << i + 1 << " is not correct" << std::endl;
            return false;
        }
    }

    //! Then check columns
    for (int i = 0; i < 9; i++) {
        std::set<char> unique;
        int clear = 0;
        for (int j = 0; j < 9; j++) {
            if (board[j][i].first == ' ') clear++;
            else unique.insert(board[j][i].first);
        }

        all &= (clear == 0);

        if (unique.size() != 9 - clear) {
            if (!debug) std::cout << "Column " << i + 1 << " is not correct" << std::endl;
            return false;
        }
    }

    //! Lastly check squares
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::set<char> unique;
            int clear = 0;

            for (int x = 3 * i; x < 3 * i + 3; x++) {
                for (int y = 3 * j; y < 3 * j + 3; y++) {
                    if (board[x][y].first == ' ') clear++;
                    else unique.insert(board[x][y].first);
                }
            }

            all &= (clear == 0);

            if (unique.size() != 9 - clear) {
                if (!debug) std::cout << "Square at row " << i + 1 << ", column " << j + 1 << " is not correct" << std::endl;
                return false;
            }
        }
    }

    if (all && !debug) {
        std::cout << "All correct! Good job!" << std::endl;
        exit(0);
    }
    if (!debug) std::cout << "All correct for now!" << std::endl;
    return true;
}

void sudoku_board::generate(int quantity) {
    fill_full(0, 0);
    std::vector<int> perm;
    for (int i = 0; i < 81; i++) perm.push_back(i);

    std::random_device rd;
    std::mt19937 v(rd());
    std::shuffle(perm.begin(), perm.end(), v);

    int current = 0;
    int index = 0;
    while (current < 81 - quantity && index < 81) {
        int row = perm[index] / 9;
        int col = perm[index] % 9;

        if (delete_check(row, col, current)) {
            current++;
            board[row][col].second = 0;
        }

        index++;
    }
}

//! System functions

void sudoku_board::swap_rows(int row1, int row2) {
    std::swap(board[row1], board[row2]);
}

void sudoku_board::swap_cols(int col1, int col2) {
    for (int i = 0; i < 9; i++) {
        std::swap(board[col1][i], board[col2][i]);
    }
}

bool sudoku_board::fill_full(int row, int col) {
    if (row == 9) return true;

    //std::cout << row << " " << col << std::endl;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::vector<int> perm({1, 2, 3, 4, 5, 6, 7, 8, 9});
    std::shuffle(perm.begin(), perm.end(), mt);
    
    for (int i = 0; i < 9; i++) {
        board[row][col].first = perm[i] + '0';
        board[row][col].second = 1;
        if (check_correct(true) && fill_full(row + ((col + 1) > 8), (col + 1) % 9)) return true;
        board[row][col].first = ' ';
    }

    return false;
}

bool sudoku_board::solution_count(int count, int clear_left, int last_i = -1, int last_j = -1) {
    if (!clear_left) {
        count = count + check_correct(true);
        if (count > 1) return true;
    }

    std::random_device rd;
    std::mt19937 mt(rd());
    std::vector<int> perm({1, 2, 3, 4, 5, 6, 7, 8, 9});
    std::shuffle(perm.begin(), perm.end(), mt);

    bool found = false;
    int i = 0, j = 0;

    if (last_j == 8) {
        i = last_i + 1;
        j = 0;
    }

    for (; i < 9; i++) {
        if (found) break;
        for (; j < 9; j++) {
            if (board[i][j].first != ' ' || found) continue;

            found = true;
            int ans = count;

            for (int index = 0; index < 9; index++) {
                board[i][j].first = perm[index] + '0';
                if (check_correct(true)) {
                    ans += solution_count(count, clear_left - 1, i, j);
                    if (ans > 1) return true;
                }
            }

            board[i][j].first = ' ';

            if (ans > 1) return true;
        }
    }

    return false;
}

bool sudoku_board::delete_check(int row, int col, int left) {
    if (solution_count(0, left)) return false;
    board[row][col].first = ' ';
    return true;
}

void sudoku_board::clear_cells() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!board[i][j].second) board[i][j].first = ' ';
        }
    }
    print_board();
}