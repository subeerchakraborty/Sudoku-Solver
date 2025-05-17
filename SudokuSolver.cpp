#include <iostream>
using namespace std;

// Function to print the Sudoku grid
void printGrid(int grid[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            cout << grid[row][col] << " ";
            if (col == 2 || col == 5)
                cout << "| ";
        }
        cout << endl;
        if (row == 2 || row == 5) {
            for (int i = 0; i < 21; i++)
                cout << "-";
            cout << endl;
        }
    }
}

// Check if a number can be placed in the given cell
bool isValid(int grid[9][9], int row, int col, int num) {
    // Check row
    for (int c = 0; c < 9; c++)
        if (grid[row][c] == num)
            return false;

    // Check column
    for (int r = 0; r < 9; r++)
        if (grid[r][col] == num)
            return false;

    // Check subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (grid[startRow + r][startCol + c] == num)
                return false;

    return true;
}

// Find the next empty cell (represented by 0)
bool findEmptyCell(int grid[9][9], int &row, int &col) {
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}

// Backtracking solver function
bool solveSudoku(int grid[9][9]) {
    int row, col;

    // If no empty cells, puzzle is solved
    if (!findEmptyCell(grid, row, col))
        return true;

    // Try numbers 1-9
    for (int num = 1; num <= 9; num++) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid))
                return true;

            // Backtrack if solution not found
            grid[row][col] = 0;
        }
    }
    return false;
}

int main() {
    int grid[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Original Sudoku:" << endl;
    printGrid(grid);

    if (solveSudoku(grid)) {
        cout << "\nSolved Sudoku:" << endl;
        printGrid(grid);
    } else {
        cout << "\nNo solution exists" << endl;
    }

    return 0;
}