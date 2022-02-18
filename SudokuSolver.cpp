// Yathavi Nandakumar
// Recursive Sudoku Solver

#include <iostream>

// Set global variables
#define GRID_DIMENSIONS 9
#define BOX_DIMENSIONS 3
#define ROW_SEPERATOR "------------------------------------"
#define COLUMN_SEPERATOR "|"

using namespace std;

// Prints out the given grid
void printGrid(int grid[GRID_DIMENSIONS][GRID_DIMENSIONS]) {
	cout << ROW_SEPERATOR << endl;
	for (int i = 0; i < GRID_DIMENSIONS; i++) {
		// Iterate through each column in each row
		for (int j = 0; j < GRID_DIMENSIONS; j++) {
			cout << " ";
			if (grid[i][j] == 0) { // A value of 0 indicates an empty cell
				cout << " ";
			} else {
				cout << grid[i][j];
			}
			cout << " " << COLUMN_SEPERATOR;
		}

		cout << endl << ROW_SEPERATOR << endl;
	}
}

// Checks if the given number already exists in the given row
bool doesNumberExistInRow(int grid[GRID_DIMENSIONS][GRID_DIMENSIONS], int row, int num) {
	for (int col = 0; col < GRID_DIMENSIONS; col++) {
		if (grid[row][col] == num) {
			return true;
		}
	}

	return false;
}

// Checks if the given number already exists in the given column
bool doesNumberExistInColumn(int grid[GRID_DIMENSIONS][GRID_DIMENSIONS], int col, int num) {
	for (int row = 0; row < GRID_DIMENSIONS; row++) {
		if (grid[row][col] == num) {
			return true;
		}
	}

	return false;
}

// Checks if the given number already exists in the given box
bool doesNumberExistInBox(int grid[GRID_DIMENSIONS][GRID_DIMENSIONS], int boxRow, int boxColumn, int num) {
	for (int row = boxRow; row < BOX_DIMENSIONS + boxRow; row++) {
		for (int col = boxColumn; col < BOX_DIMENSIONS + boxColumn; col++) {
			if (grid[row][col] == num) {
				return true;
			}
		}
	}

	return false;
}

// Checks if the given number can be placed in the given cell
bool canNumberBePlaced(int grid[GRID_DIMENSIONS][GRID_DIMENSIONS], int row, int col, int num) {
	return !doesNumberExistInRow(grid, row, num) && 
		   !doesNumberExistInColumn(grid, col, num) && 
		   !doesNumberExistInBox(grid, row - (row % BOX_DIMENSIONS), col - (col % BOX_DIMENSIONS), num);
}


// Gets the row and column of the next empty cell for the given grid
pair<int, int> getNextEmptyCell(int grid[GRID_DIMENSIONS][GRID_DIMENSIONS]) {
	for (int row = 0; row < GRID_DIMENSIONS; row++) {
		for (int col = 0; col < GRID_DIMENSIONS; col++) {
			if (grid[row][col] == 0) { // A value of 0 indicates an empty cell
				return make_pair(row, col);
			}
		}
	}

	return make_pair(GRID_DIMENSIONS, GRID_DIMENSIONS); // Return the dimensions when the grid is completely filled in
}

// Attempts to solve the given grid (recursively)
bool solveGrid(int grid[GRID_DIMENSIONS][GRID_DIMENSIONS]) {
	pair<int, int> nextEmptyCell = getNextEmptyCell(grid);
	// Return if the grid is completely filled in
	if (make_pair(GRID_DIMENSIONS, GRID_DIMENSIONS) == nextEmptyCell) {
		return true; 
	}

	int row = nextEmptyCell.first;
	int col = nextEmptyCell.second;

	for (int num = 1; num <= 9; num++) {
		if (canNumberBePlaced(grid, row, col, num)) {
			// Assign the number to the cell
			grid[row][col] = num;

			// Attempt to solve the grid with the updated cell
			if (solveGrid(grid)) {
				return true;
			}

			// Reset the current cell (so another number can be tried)
			grid[row][col] = 0;
		}
	}

	// No values can be placed in the current cell (start backtracking)
	return false; 
}

int main() {
	int grid[GRID_DIMENSIONS][GRID_DIMENSIONS] = 
						 { { 0, 0, 0, 3, 6, 9, 0, 0, 0 },
						   { 0, 8, 0, 0, 0, 0, 0, 2, 0 },
						   { 0, 0, 5, 0, 1, 0, 4, 0, 0 },
						   { 8, 0, 0, 0, 0, 0, 0, 0, 7 },
						   { 4, 0, 1, 0, 5, 0, 6, 0, 3 },
						   { 5, 0, 0, 0, 0, 0, 0, 0, 4 },
						   { 0, 0, 6, 0, 2, 0, 1, 0, 0 },
						   { 0, 5, 0, 0, 0, 0, 0, 7, 0 },
						   { 0, 0, 0, 1, 9, 3, 0, 0, 0 } };

	cout << "Unsolved Sudoku:" << endl;
	printGrid(grid);

	cout << endl << endl;
	if (solveGrid(grid)) { // Check if the grid has a solution
		cout << "Solved Sudoku:" << endl;
		printGrid(grid);
	} else {
		cout << "This grid has no solution!" << endl;
	}

	return 0;
}