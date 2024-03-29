/** \file Matrix.cpp
 *  \brief     This file performs basic matrix operations.
 *  \details   The program shows a menu with 5 options and does matrix operations.
 *  \author    Sergei Rogov U231N0051
 *  \date      09.04.2023
 *  \copyright University of Nicosia.
 */
#include <iostream>
#include <iomanip> 
#include <cassert>

using namespace std;

// Global constants
const int MAX_ROW = 20;
const int MAX_COL = 20;

// Function prototypes
void displayMenu();
void makeAction(const int);

/** 
 * Matrix class.
 * A class to perform basic matrix operations.
 */
class Matrix {
public:
    Matrix();
    void ReadMatrix();
    void PrintMatrix() const;
    bool AddSubtract(const char, const Matrix &, const Matrix &);
    bool Multiply(const Matrix &, const Matrix &);
    bool Inverse(const Matrix &);
    Matrix& operator=(const Matrix &);
private:
    int row, col;
    double entry[MAX_ROW][MAX_COL];
    double IdentityMatrix[MAX_ROW][MAX_COL];
};

/**
 * The <code>main</code> is the driver function that kick-starts the
 * program. Asks user to choose an option.
 * <BR>
 * @return Returns <code>0</code> on success, any other value otherwise.
 */
int main(){
    int choice;
    do {
        displayMenu();
        //executes loop if user inserts not a number or number not in the range 1..5.
        while (cout << "\nEnter your choice: " && (!(cin >> choice) || choice < 1 || choice > 5)) {
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
    assert(choice>0 && choice<6);
    Matrix A, B, ResultMatrix;
    switch (choice) {
    case 1: // add
        A.ReadMatrix();
        B.ReadMatrix();
        if (!ResultMatrix.AddSubtract('+', A, B))
            cout << "\nCan't be calculated\n";
        else 
            ResultMatrix.PrintMatrix();
        break;
    case 2: // substruct
        A.ReadMatrix();
        B.ReadMatrix();
        if (!ResultMatrix.AddSubtract('-', A, B))
            cout << "\nCan't be calculated\n";
        else
            ResultMatrix.PrintMatrix();
        break;
    case 3: // multiply
        A.ReadMatrix();
        B.ReadMatrix();
        if (!ResultMatrix.Multiply(A, B))
            cout << "\nCan't be calculated\n";
        else
            ResultMatrix.PrintMatrix();
        break;
    case 4: // inverse
        A.ReadMatrix();
        if (!ResultMatrix.Inverse(A))
            cout << "\nCan't be calculated\n";
        else
            ResultMatrix.PrintMatrix();
        break;
    case 5: // No code needed
        break;
    default:
        assert(false);
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
            while (cout << "\nElement [" << i+1 << "][" << j+1 << "] = " && (!(cin >> entry[i][j]))) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "Invalid input; please enter a real number\n";
            }
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
            cout << setw(10) << entry[i][j] << " ";
        }
        cout << "\n";
    }
}

/**
 * Function <code>AddSubtract</code> performs addition or substraction of two matrices.
 * <BR>
 * @param ch Indicates '+' or '-': which operation to perform.
 * @param A Left-side matrix.
 * @param B Right-side matrix.
 * @return Returns <code>false</code> if operation can't be performed,
 * <code>true</code> otherwise.
 */
bool Matrix::AddSubtract(const char ch, const Matrix &A, const Matrix &B){
    assert(ch=='+'|| ch=='-');
    assert(A.row>0 && A.row<MAX_ROW);
    assert(A.col>0 && A.col<MAX_COL);
    assert(B.row>0 && B.row<MAX_ROW);
    assert(B.col>0 && B.col<MAX_COL);
    // can be performed only if dimentionality is the same
    if (A.row != B.row || A.col != B.col) return false;
    row = A.row;
    col = A.col;
    if(ch == '+'){
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                entry[i][j] = A.entry[i][j] + B.entry[i][j];
            }
        }
    } else if (ch == '-'){
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                entry[i][j] = A.entry[i][j] - B.entry[i][j];
            }
        }
    }
    return true;
}

/**
 * Function <code>Multiply</code> performs multiplication of two matrices.
 * <BR>
 * @param A Left-side matrix.
 * @param B Right-side matrix.
 * @return Returns <code>false</code> if operation can't be performed,
 * <code>true</code> otherwise.
 */
bool Matrix::Multiply(const Matrix &A, const Matrix &B){
    assert(A.row>0 && A.row<MAX_ROW);
    assert(A.col>0 && A.col<MAX_COL);
    assert(B.row>0 && B.row<MAX_ROW);
    assert(B.col>0 && B.col<MAX_COL);
    // number of columns of first matrix
    // should be equal to number of rows of second matrix
    // in order to perform multiplication
    if (A.col != B.row) return false;
    row = A.row;
    col = B.col;
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            entry[i][j] = 0;
        }
    }
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            for(int k=0; k<A.col; k++){
                entry[i][j] += A.entry[i][k]*B.entry[k][j];
            }
        }
    }
    return true;
}

/**
 * Function <code>operator=</code> overloads the assignment statement.
 * <BR>
 * @param original original matrix which we want to assign to.
 * @return Returns an equal matrix.
 */
Matrix& Matrix::operator=(const Matrix &original){
    if(this != &original){
        row = original.row;
        col = original.col;
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                entry[i][j] = original.entry[i][j];
            }
        }
    }
    return *this;
}

/**
 * Function <code>Inverse</code> inverses an nxn matrix.
 * <BR>
 * @param A A matrix to be inversed.
 * @return Returns <code>false</code> if operation can't be performed,
 * <code>true</code> otherwise.
 */
bool Matrix::Inverse(const Matrix &A){
    assert(A.row>0 && A.row<MAX_ROW);
    assert(A.col>0 && A.col<MAX_COL);
    // should be a square matrix in order to perform inversion
    if(A.row != A.col) return false; 
    // performing same operations on matrix and identity matrix
    // in the end matrix (variable IdentityMatrix) -> turns into identity matrix
    // and identity matrix (variable entry) -> turns into inverse matrix (answer)
    row = A.row;
    col = A.col;
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            IdentityMatrix[i][j] = A.entry[i][j];
            if(i==j) entry[i][j] = 1;
            else entry[i][j] = 0;
        }
    }
    // GAUSS algorithm to turn our matrix into identity matrix
    double tempElement;
    // finding a row with the biggest first element (on absolute value)
    for(int i=0; i<row; i++){
        float amax=IdentityMatrix[i][i];
        int i_max = i;
        for(int j=i+1; j<row; j++){
            if(abs(IdentityMatrix[j][i])>abs(amax)){
                amax = IdentityMatrix[j][i];
                i_max = j;
            }
        }
        // swapping rows - row with biggest absolute value 
        // of the first element (after zeros) should come first
        if(i!=i_max){
            for(int j=0; j<col; j++){
                tempElement = IdentityMatrix[i][j];
                IdentityMatrix[i][j]=IdentityMatrix[i_max][j];
                IdentityMatrix[i_max][j] = tempElement;
                tempElement = entry[i][j];
                entry[i][j]=entry[i_max][j];
                entry[i_max][j] = tempElement;
            }
        }
        tempElement = IdentityMatrix[i][i];
        // dividing a row by first element
        // (making first element [after zeros] in row to be 1)
        if (tempElement!=0){
            for (int j=0; j<col; j++){
                IdentityMatrix[i][j] /= static_cast<double>(tempElement);
                entry[i][j] /= static_cast<double>(tempElement);
            }
        }
        // substructing [first element * first element in next (following) row] 
        // from all rows below.
        // It creates zeros underneath
        for(int k=i+1; k<row; k++){
            tempElement = IdentityMatrix[k][i];
            for(int j=0; j<col; j++){
                IdentityMatrix[k][j] -= IdentityMatrix[i][j]*tempElement;
                entry[k][j] -= entry[i][j]*tempElement;
                // when substructing a fraction from equal fraction,
                // program might calculate it as a close to zero number but not exactly zero
                // so, I hardcode zero in that case
                if(abs(IdentityMatrix[k][j])<0.00001) IdentityMatrix[k][j]=0;
            }
        }
    }
    // at this point we have a triangular matrix
    // all elements below main diagonal are zeros
    // check if determinant == 0
    double unscaledDeterminant = 1;
    for(int j=0; j<row; j++){
        unscaledDeterminant *= IdentityMatrix[j][j];
    }
    if(unscaledDeterminant == 0) return false;
    // BACK
    // now making all elements above main diagonal zeros as well
    for (int i=row-1; i>=0; i--){
        for(int k=i-1; k>=0; k--){
            tempElement = IdentityMatrix[k][i];
            for(int j=col-1; j>=0; j--){
                IdentityMatrix[k][j] -= IdentityMatrix[i][j]*tempElement;
                entry[k][j] -= entry[i][j]*tempElement;
            }
        }
    }
    return true;
}
