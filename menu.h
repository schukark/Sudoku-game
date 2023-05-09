#pragma once
#ifndef MENU_H
#define MENU_H

#include "board.cpp"
#include <stdexcept>

class menu : public sudoku_board {
public:
    menu() {
        init();
    }

    void print_menu();
    void init();
    void action();
};

#endif // MENU_H