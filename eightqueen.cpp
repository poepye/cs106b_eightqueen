/* 8 Queen Problem */
#include <iostream>
#include "grid.h"
using namespace std;

const int NUM_BOARD = 8;

void ClearBoard(Grid<bool>& board);
bool Solve(Grid<bool>& board, int col);
bool IsSafe(Grid<bool>& board, int row, int col);
void placeQueen(Grid<bool>& board, int row, int col);
void removeQueen(Grid<bool>& board, int row, int col);
bool rowSafe(Grid<bool>& board, int row, int col);
bool colSafe(Grid<bool>& board, int row, int col);
bool DiagSafe(Grid<bool>& board, int row, int col);

int main() {
	Grid<bool> board(NUM_BOARD, NUM_BOARD);
	ClearBoard(board);
	cout << Solve(board, 0) << endl;
	for (int row = 0; row < NUM_BOARD; row++) {
		for (int col = 0; col < NUM_BOARD; col++)
			cout << board[row][col] << " ";
		cout << endl;
	}
	return 0;
}

void ClearBoard(Grid<bool>& board)
{
	for (int row = 0; row < board.numRows(); row++)
		for (int col = 0; col < board.numCols(); col++)
			board.set(row, col, false);
}

// Solve the 8-Queen col by col recursively
bool Solve(Grid<bool>& board, int col) {
	// Base case. If the col > board size, solution found
	if (col >= NUM_BOARD) return true;
	else {
		// 
		for (int row = 0; row < NUM_BOARD; row++) {
			/* If the tile is safe, place a Queen there
			 * and use recursion to check if the rest of
			 * the board can be solved. If not, remove the
			 * Queen and try the next row.
			*/
			if (IsSafe(board, row, col)) {
				placeQueen(board, row, col);
				if (Solve(board, col+1)) return true;
				removeQueen(board, row, col);
			}
		}
	}
	// If no row in this col can solve the problem, then the last
	// col must be wrong, return false to backtrack.
	return false;
}

bool IsSafe(Grid<bool>& board, int row, int col) {
	if (rowSafe(board, row, col) && colSafe(board, row, col) && DiagSafe(board, row, col))
		return true;
	else
		return false;
}

void placeQueen(Grid<bool>& board, int row, int col) {
	board.set(row, col, true);
}

void removeQueen(Grid<bool>& board, int row, int col) {
	board.set(row, col, false);
}

bool rowSafe(Grid<bool>& board, int row, int col){
	for (int i = 0; i < col; i++)
		if (board.get(row, i))
			return false;
	if (col < NUM_BOARD-1) {
		for (int i = col + 1; i < NUM_BOARD; i++)
			if (board.get(row, i))
				return false;
	}
	return true;
}

bool colSafe(Grid<bool>& board, int row, int col) {
	for (int i = 0; i < row; i++)
		if (board.get(i, col))
			return false;
	if (row < NUM_BOARD-1) {
		for (int i = row + 1; i < NUM_BOARD; i++)
			if (board.get(i, col))
				return false;
	}
	return true;
}

bool DiagSafe(Grid<bool>& board, int row, int col) {
	int i, j;
	for (i = row, j = col; i >= 0 && j >= 0 && i < NUM_BOARD && j < NUM_BOARD; i--, j--) // Northwest
		if (board.get(i, j))
			return false;
	for (i = row, j = col; i >= 0 && j >= 0 && i < NUM_BOARD && j < NUM_BOARD; i--, j++) // Northeast
		if (board.get(i, j))
			return false;
	for (i = row, j = col; i >= 0 && j >= 0 && i < NUM_BOARD && j < NUM_BOARD; i++, j--) // Southwest
		if (board.get(i, j))
			return false;
	for (i = row, j = col; i >= 0 && j >= 0 && i < NUM_BOARD && j < NUM_BOARD; i++, j++) // Southeast
		if (board.get(i, j))
			return false;
	return true;
}