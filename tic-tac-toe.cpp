#include <iostream>
#include <vector>
using namespace std;

const int COMPUTER = 1;
const int HUMAN = 2;
const int SIDE = 3;
const char COMPUTERMOVE = 'O';
const char HUMANMOVE = 'X';

// Function to show the current state of the board
void showBoard(const vector<vector<char> >& board) {
    cout << "\t\t\t " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n";
}

// Function to show instructions to the user
void showInstructions() {
    cout << "\nChoose a cell numbered from 1 to 9 as below and play\n";
    cout << "\t\t\t 1 | 2 | 3 \n";
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t 4 | 5 | 6 \n";
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t 7 | 8 | 9 \n";
}

// Function to initialize the game board with '*'
void initialise(vector<vector<char> >& board) {
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            board[i][j] = '*';
        }
    }
}

// Function to declare the winner
void declareWinner(int whoseTurn) {
    if (whoseTurn == COMPUTER)
        cout << "COMPUTER has won\n";
    else
        cout << "HUMAN has won\n";
}

// Check if any row is crossed
bool rowCrossed(const vector<vector<char> >& board) {
    for (int i = 0; i < SIDE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '*')
            return true;
    }
    return false;
}

// Check if any column is crossed
bool columnCrossed(const vector<vector<char> >& board) {
    for (int i = 0; i < SIDE; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '*')
            return true;
    }
    return false;
}

// Check if any diagonal is crossed
bool diagonalCrossed(const vector<vector<char> >& board) {
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '*')
        return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '*')
        return true;
    return false;
}

// Function to check if the game is over
bool gameOver(const vector<vector<char> >& board) {
    return rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board);
}

// Minimax function for the AI to find the best move
int minimax(vector<vector<char> >& board, int depth, bool isAI) {
    int score;
    int bestScore;
    if (gameOver(board)) {
        if (isAI)
            return -10;
        else
            return 10;
    } else {
        if (depth < 9) {
            if (isAI) {
                bestScore = -999;
                for (int i = 0; i < SIDE; i++) {
                    for (int j = 0; j < SIDE; j++) {
                        if (board[i][j] == '*') {
                            board[i][j] = COMPUTERMOVE;
                            score = minimax(board, depth + 1, false);
                            board[i][j] = '*';
                            if (score > bestScore) {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            } else {
                bestScore = 999;
                for (int i = 0; i < SIDE; i++) {
                    for (int j = 0; j < SIDE; j++) {
                        if (board[i][j] == '*') {
                            board[i][j] = HUMANMOVE;
                            score = minimax(board, depth + 1, true);
                            board[i][j] = '*';
                            if (score < bestScore) {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
        } else {
            return 0;
        }
    }
}

// Function to find the best move for the computer
int bestMove(vector<vector<char> >& board, int moveIndex) {
    int x = -1, y = -1;
    int score;
    int bestScore = -999;
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (board[i][j] == '*') {
                board[i][j] = COMPUTERMOVE;
                score = minimax(board, moveIndex + 1, false);
                board[i][j] = '*';
                if (score > bestScore) {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x * 3 + y;
}

// Main function to play the game
void playTicTacToe(int whoseTurn) {
    vector<vector<char> > board(SIDE, vector<char>(SIDE, '*'));
    int moveIndex = 0;
    int x = 0, y = 0;
    initialise(board);
    showInstructions();

    while (!gameOver(board) && moveIndex != SIDE * SIDE) {
        int n;
        if (whoseTurn == COMPUTER) {
            n = bestMove(board, moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = COMPUTERMOVE;
            cout << "COMPUTER has put an " << COMPUTERMOVE << " in cell " << (n + 1) << "\n";
            showBoard(board);
            moveIndex++;
            whoseTurn = HUMAN;
        } else if (whoseTurn == HUMAN) {
            cout << "You can insert in the following positions: ";
            for (int i = 0; i < SIDE; i++) {
                for (int j = 0; j < SIDE; j++) {
                    if (board[i][j] == '*') {
                        cout << (i * 3 + j) + 1 << " ";
                    }
                }
            }
            cout << "\nEnter the position: ";
            cin >> n;
            n--;
            x = n / SIDE;
            y = n % SIDE;

            if (board[x][y] == '*' && n < 9 && n >= 0) {
                board[x][y] = HUMANMOVE;
                cout << "\nHUMAN has put an " << HUMANMOVE << " in cell " << (n + 1) << "\n";
                showBoard(board);
                moveIndex++;
                whoseTurn = COMPUTER;
            } else if (board[x][y] != '*' && n < 9 && n >= 0) {
                cout << "\nPosition is occupied, select another place\n";
            } else if (n < 0 || n > 8) {
                cout << "Invalid position\n";
            }
        }
    }

    if (!gameOver(board) && moveIndex == SIDE * SIDE)
        cout << "It's a draw\n";
    else {
        whoseTurn = (whoseTurn == COMPUTER) ? HUMAN : COMPUTER;
        declareWinner(whoseTurn);
    }
}

// Main driver function
int main() {
    cout << "\n-------------------------------------------------------------------\n";
    cout << "\t\t\t Tic-Tac-Toe\n";
    cout << "-------------------------------------------------------------------\n";

    char cont = 'y';
    do {
        char choice;
        cout << "Do you want to start first? (y/n): ";
        cin >> choice;
        if (choice == 'n')
            playTicTacToe(COMPUTER);
        else if (choice == 'y')
            playTicTacToe(HUMAN);
        else
            cout << "Invalid choice\n";

        cout << "\nDo you want to quit (y/n): ";
        cin >> cont;
    } while (cont == 'n');

    return 0;
}

