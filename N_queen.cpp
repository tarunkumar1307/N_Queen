#include <bits/stdc++.h>
using namespace std;

int boardSize, recursiveCalls = 0;
vector<vector<int>> board;
int iterationCount = 0;
int solutionCount = 0;
int delay = 500;
bool findAllSolutions = false;

void printBoard() {
    cout << "\033[2J\033[1;1H"; // Clear screen
    cout << "   ";
    for (int j = 0; j < boardSize; j++) {
        cout << setw(3) << (char)('a' + j);
    }
    cout << endl;
    
    for (int i = 0; i < boardSize; i++) {
        cout << setw(2) << boardSize - i << " ";
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j])
                cout << "\033[1;31m \u265B "; // Red queen
            else if ((i + j) % 2 == 0)
                cout << "\033[47m   "; // White square
            else
                cout << "\033[100m   "; // Gray square
        }
        cout << "\033[0m" << endl; // Reset color
    }
    cout << "\nIterations: " << iterationCount << " | Solutions: " << solutionCount << endl;
}

bool isSafe(int row, int col) {
    // Check this row on left side
    for (int i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Check upper diagonal on left side
    for (int i=row, j=col; i>=0 && j>=0; i--, j--)
        if (board[i][j])
            return false;

    // Check lower diagonal on left side
    for (int i=row, j=col; j>=0 && i<boardSize; i++, j--)
        if (board[i][j]) 
            return false;

    return true;
}

bool solveNQueensUtil(int col) {
    recursiveCalls++; // Increment the recursive calls counter

    if (col >= boardSize) {
        solutionCount++;
        printBoard();
        this_thread::sleep_for(chrono::milliseconds(delay));
        return findAllSolutions ? false : true;
    }
    
    for (int i = 0; i < boardSize; i++) {
        iterationCount++;
        
        if (isSafe(i, col)) {
            board[i][col] = 1;
            
            printBoard();
            this_thread::sleep_for(chrono::milliseconds(delay));

            if (solveNQueensUtil(col + 1)) return true;

            board[i][col] = 0; // Backtrack
            printBoard();
            this_thread::sleep_for(chrono::milliseconds(delay)); 
        }
    }

    return false;
}

void solveNQueens() {
    solveNQueensUtil(0);
    if (solutionCount == 0) {
        cout << "Solution does not exist" << endl;
    } else {
        cout << "Found " << solutionCount << " solution(s)" << endl;
    }
    printBoard();
}

int main() {
    cout << "Enter the size of the chessboard: ";
    cin >> boardSize;

    cout << "Find all solutions? (0 for No, 1 for Yes): ";
    cin >> findAllSolutions;

    cout << "Enter delay between steps (in milliseconds): ";
    cin >> delay;

    board = vector<vector<int>>(boardSize, vector<int>(boardSize, 0));

    auto start = chrono::high_resolution_clock::now();
    
    solveNQueens();
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Recursive calls made: " << recursiveCalls << endl;
}
