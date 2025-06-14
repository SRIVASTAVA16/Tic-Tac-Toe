#include <iostream>
#include <vector>
using namespace std;

const int COMPUTER = 1;
const int HUMAN = 2;
const int SIDE = 3;
const char COMPUTERMOVE = 'O';
const char HUMANMOVE = 'X';

void showBoard(const vector<vector<char>>& board) {
    cout << "\n\n";
    for (int i = 0; i < SIDE; i++) {
        cout << "\t\t\t ";
        for (int j = 0; j < SIDE; j++) {
            cout << board[i][j];
            if (j < SIDE - 1) cout << " | ";
        }
        cout << "\n";
        if (i < SIDE - 1) cout << "\t\t\t-----------\n";
    }
    cout << "\n";
}

void showInstructions() {
    cout << "\nChoose a cell numbered from 1 to 9 as below and play\n";
    cout << "\t\t\t 1 | 2 | 3 \n";
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t 4 | 5 | 6 \n";
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t 7 | 8 | 9 \n";
}

void initialise(vector<vector<char>>& board) {
    for (int i = 0; i < SIDE; i++)
        for (int j = 0; j < SIDE; j++)
            board[i][j] = '*';
}

void declareWinner(int whoseTurn) {
    if (whoseTurn == COMPUTER)
        cout << "COMPUTER has won!\n";
    else
        cout << "HUMAN has won!\n";
}

bool rowCrossed(const vector <vector<char>>& board) {		
    for (int i = 0; i < SIDE; i++)
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != '*')
            return true;
    return false;
}

bool columnCrossed(const vector<vector<char>>& board) {
    for (int i = 0; i < SIDE; i++)
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] &&
            board[0][i] != '*')
            return true;
    return false;
}

bool diagonalCrossed(const vector<vector<char>>& board) {
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != '*')
        return true;

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        board[0][2] != '*')
        return true;

    return false;
}

// Check if game is over
bool gameOver(const vector<vector<char>>& board) {
    return rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board);
}

// Minimax algorithm for computer move
int minimax(vector<vector<char>>& board, int depth, bool isAI) {
    if (gameOver(board)) {
        return isAI ? -10 : 10;
    }
    if (depth == SIDE * SIDE) return 0;

    int bestScore = isAI ? -1000 : 1000;
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (board[i][j] == '*') {
                board[i][j] = isAI ? COMPUTERMOVE : HUMANMOVE;
                int score = minimax(board, depth + 1, !isAI);
                board[i][j] = '*';
                bestScore = isAI ? max(bestScore, score) : min(bestScore, score);
            }
        }
    }
    return bestScore;
}

int bestMove(vector<vector<char>>& board, int moveIndex) {
    int bestScore = -1000, x = -1, y = -1;

    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (board[i][j] == '*') {
                board[i][j] = COMPUTERMOVE;
                int score = minimax(board, moveIndex + 1, false);
                board[i][j] = '*';
                if (score > bestScore) {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x * SIDE + y;
}

void playTicTacToe(int whoseTurn) {
    vector<vector<char>> board(SIDE, vector<char>(SIDE));
    int moveIndex = 0, x = 0, y = 0;

    initialise(board);
    showInstructions();

    while (!gameOver(board) && moveIndex < SIDE * SIDE) {
        int n;

        if (whoseTurn == COMPUTER) {
            n = bestMove(board, moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = COMPUTERMOVE;
            cout << "COMPUTER placed " << COMPUTERMOVE << " in cell " << (n + 1) << "\n";
            showBoard(board);
            moveIndex++;
            whoseTurn = HUMAN;
        } else {
            cout << "Available positions: ";
            for (int i = 0; i < SIDE * SIDE; i++) {
                x = i / SIDE;
                y = i % SIDE;
                if (board[x][y] == '*') cout << (i + 1) << " ";
            }
            cout << "\nEnter your move: ";
            cin >> n;
            n--;
            x = n / SIDE;
            y = n % SIDE;

            if (n >= 0 && n < 9 && board[x][y] == '*') {
                board[x][y] = HUMANMOVE;
                cout << "HUMAN placed " << HUMANMOVE << " in cell " << (n + 1) << "\n";
                showBoard(board);
                moveIndex++;
                whoseTurn = COMPUTER;
            } else {
                cout << "Invalid move. Try again.\n";
            }
        }
    }

    if (!gameOver(board) && moveIndex == SIDE * SIDE) {
        cout << "It's a draw!\n";
    } else {
        whoseTurn = (whoseTurn == COMPUTER) ? HUMAN : COMPUTER;
        declareWinner(whoseTurn);
    }
}

int main() {
    cout << "\n-------------------------------------------------\n";
    cout << "\t\tTic-Tac-Toe Game\n";
    cout << "-------------------------------------------------\n";

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
            cout << "Invalid choice. Please choose 'y' or 'n'.\n";

        cout << "\nDo you want to play again? (y/n): ";
        cin >> cont;
    } while (cont == 'y');

    cout << "Thank you for playing!\n";
    return 0;
}






















