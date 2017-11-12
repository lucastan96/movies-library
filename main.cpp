//
//  main.cpp
//  movies-library
//
//  Created by Lucas Tan on 11/7/17.
//  Copyright © 2017 Lucas Tan. All rights reserved.
//

#include <iostream>
#include "Library.hpp"

int main() {
    vector<Movies> movies;
    movies = load(movies);
    int option = 0;
    
    cout << "----- Welcome to Movie Library! -------------------------------" << endl;
    while (option != 8) {
        menu();
        cin >> option;
        
        while (cin.fail()) {
            cout << "\nError: Input should be a integer!\n" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter your option again: ";
            cin >> option;
        }
        
        if (option == 1) {
            cout << "" << endl;
            option1(movies);
        } else if (option == 2) {
            cout << "" << endl;
            option2(movies);
        } else if (option == 3) {
            cout << "" << endl;
            option3(movies);
        } else if (option == 4) {
            cout << "" << endl;
            option4(movies);
        } else if (option == 5) {
            cout << "" << endl;
            option5(movies);
        } else if (option == 6) {
            cout << "" << endl;
            option6(movies);
        } else if (option == 7) {
            cout << "" << endl;
            option7(movies);
        } else if (option == 8) {
            cout << "\nNotice: Program will now exit.\n" << endl;
            break;
        } else {
            cout << "\nError: Please enter a valid option!\n" << endl;
        }
    }
    
    return 0;
}
