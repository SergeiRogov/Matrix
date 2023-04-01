/** \file Matrix.cpp
 *  \brief     This file performs basic matrix operations.
 *  \details   The program shows a menu with 5 options and does matrix operations.
 *  \author    Sergei Rogov
 *  \date      01.04.2023
 *  \copyright University of Nicosia.
 */

#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <cassert>

using namespace std;

// Global constants
const int MAX_ROW = 20;
const int MAX_COL = 20;

// Function prototypes
void displayMenu();

class Matrix {
public:
    Matrix(); //initialize row and col to 0
    void ReadMatrix();
    void PrintMatrix() const;
    bool AddSubtract(char, const Matrix &, const Matrix &);
    bool Multiply(const Matrix &, const Matrix &);
    bool Inverse(const Matrix &);
    Matrix& operator=(const Matrix &);
private:
    int row, col;
    float entry[MAX_ROW][MAX_COL];
};

int main(){
    int choice;
    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
        case 1: // add

            break;
        case 2: // substruct
            
            break;
        case 3: // multiply
           
            break;
        case 4: // inverse
            
            break;
        case 5: // No code needed
            break;
        default:
            cerr << "Enter your choice again, please!\n";
            break;
        }
    } while (choice != 5);
    return 0;
}

/**
 * Function <code>displayMenu</code> displays the menu that is used from
 * the main program.
 */
void displayMenu(){
    cout <<  "\n1) Add two matrices";
    cout <<  "\n2) Substruct matrix from matrix";
    cout <<  "\n3) Multiply two matrices";
    cout <<  "\n4) Inverse of a matrix";
    cout <<  "\n5) Quit\n";
    cout <<  "\nEnter your choice: ";
}