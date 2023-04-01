/** \file Matrix.cpp
 *  \brief     This file performs basic matrix operations.
 *  \details   The program shows a menu with 5 options and does matrix operations.
 *  \author    Sergei Rogov U231N0051
 *  \date      01.04.2023
 *  \copyright University of Nicosia.
 */

#include <iostream>
#include <cstdlib> 
#include <cassert>

using namespace std;

// Global constants
const int MAX_ROW = 20;
const int MAX_COL = 20;

// Function prototypes
void displayMenu();
void makeAction(const int);

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

/**
 * The <code>main</code> is the driver function that kick-starts the
 * program. Asks user to choose an option.
 * <BR>
 * @return Returns <code>0</code> on success, any other value otherwise.
 */
int main(){
    Matrix A;
    A.ReadMatrix();
    A.PrintMatrix();
    int choice;
    do {
        displayMenu();
        //executes loop if user inserts a number not in the range 1..5.
        while (cout << "\nEnter your choice: " && (!(cin >> choice) || choice < 1 || choice > MAX_ROW)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input; please enter a number from 1 to 5.\n";
        }
        makeAction(choice);
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
}

/**
 * Function <code>makeAction</code> executes the action corresponding to choice.
 * <BR>
 * @param choice Indicator of an option from menu.
 */
void makeAction(const int choice){
    switch (choice) {
    case 1: // add
        cout <<  "\n1)\n";
        break;
    case 2: // substruct
        cout <<  "\n2)\n";
        break;
    case 3: // multiply
        cout <<  "\n3)\n";
        break;
    case 4: // inverse
        cout <<  "\n4)\n";
        break;
    case 5: // No code needed
        break;
    default:
        cerr << "Enter your choice again, please!\n";
        break;
    }
}

/**
 * Function <code>Matrix</code> is a constructor of a Matrix class.
 * Initializes row and col to 0.
 */
Matrix::Matrix(){
    row = 0;
    col = 0;
}

/**
 * Function <code>ReadMatrix</code> asks user for matrix dimentions and its elements
 * and fills in these values.
 */
void Matrix::ReadMatrix(){
    while (cout << "\nEnter number of rows: " && (!(cin >> row) || row < 1 || row > MAX_ROW)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Invalid input; please enter a number from 1 to " << MAX_ROW << ".\n";
    }
    while (cout << "\nEnter number of columns: " && (!(cin >> col) || col < 1 || col > MAX_COL)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Invalid input; please enter a number from 1 to " << MAX_COL << ".\n";
    }
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cout << "\nElement [" << i+1 << "][" << j+1 << "] = ";
            cin >> entry[i][j];
        }
    }
}

/**
 * Function <code>PrintMatrix</code> displays the matrix.
 */
void Matrix::PrintMatrix() const {
    cout << "\n";
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            cout << entry[i][j] << " ";
        }
        cout << "\n";
    }
}