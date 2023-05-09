#include "menu.h"

void menu::init() {
    std::cout << "Type:" << std::endl;
    std::cout << "0 - if you want to load a config" << std::endl;
    std::cout << "1 - if you want to generate a random config" << std::endl;
    
    int state = 0;
    std::cin >> state;

    if (state == 0) {
        load_config();
        print_menu();
    }
    else if (state == 1) {
        int difficulty = 0;
        std::cout << "Set difficulty from 1 to 10" << std::endl;
        std::cin >> difficulty;

        int quantity = 60 - 4 * difficulty;
        generate(quantity);
        print_menu();
        //throw std::runtime_error("Not implemented");
    }
    else {
        std::cout << "Incorrect input" << std::endl;
    }
}

void menu::print_menu() {
    print_board();
    std::cout << "Type:" << std::endl;
    std::cout << "move - if you want to make a move" << std::endl;
    std::cout << "undo - if you want to clear a cell" << std::endl;
    std::cout << "check - if you want to check correctness" << std::endl;
    std::cout << "menu - if you want to see the menu" << std::endl;
    std::cout << "return - if you want to return to the main menu" << std::endl;
    std::cout << "exit - if you want to exit" << std::endl;
    action();
}

void menu::action() {
    std::string state;
    std::cin >> state;

    if (state == "move") {
        int x, y, value;
        std::cout << "Place number: ";
        std::cin >> value;
        std::cout << "at row: ";
        std::cin >> x;
        std::cout << "at col: ";
        std::cin >> y;
        std::cout << std::endl;
        make_move(x, y, value);
    }
    else if (state == "check") {
        check_correct();
    }
    else if (state == "undo") {
        int x, y;
        std::cout << "Clear at row: ";
        std::cin >> x;
        std::cout << "at col: ";
        std::cin >> y;
        std::cout << std::endl;
        clear_cell(x, y);
    }
    else if (state == "menu") {
        print_menu();
    }
    else if (state == "return") {
        init();
    }
    else if (state == "exit") {
        exit(0);
    }
    else {
        std::cout << "Incorrect input" << std::endl;
    }
    action();
}