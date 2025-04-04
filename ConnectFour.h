// Created by MALAK on 12/3/2024.

#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include "BoardGame_Classes.h"

// Template class for the Connect Four game board, inheriting from the Board<T> class.
template <typename T>
class ConnectFourBoard : public Board<T> {
public:
    // Constructor initializes the Connect Four board with default rows and columns.
    ConnectFourBoard ();

    // Updates the board with a move, returns true if successful, false otherwise.
    bool update_board (int x , int y , T symbol) override;

    // Displays the board to the console.
    void display_board () override;

    // Checks if a win condition is met.
    bool is_win() override;

    // Checks if the game is a draw.
    bool is_draw() override;

    // Checks if the game is over (win or draw).
    bool game_is_over() override;
};

// Template class for a human Connect Four player, inheriting from the Player<T> class.
template <typename T>
class ConnectFourPlayer : public Player<T> {
    public:
    // Constructor initializes a player with a name and symbol.
    ConnectFourPlayer (string name , T symbol);

    // Prompts the player to input their move.
    void getmove(int& x, int& y) override;
};

// Template class for a random AI Connect Four player, inheriting from RandomPlayer<T>.
template <typename T>
class ConnectFourRandomPlayer : public RandomPlayer<T> {
    public:
    // Constructor initializes the random AI player with a symbol.
    ConnectFourRandomPlayer (T symbol);

    // Generates a random move for the AI player.
    void getmove(int& x, int& y) override;
};

//------------- IMPLEMENTATION-------------------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

// Constructor for Connect Four board.
template<typename T>
ConnectFourBoard<T>::ConnectFourBoard() {
    // Set board dimensions.
    this -> columns = 7;  // Connect Four board has 7 columns.
    this -> rows = 6;     // Connect Four board has 6 rows.

    // Dynamically allocate memory for the board.
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];

        // Initialize each cell with a space to indicate it's empty.
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;  // Initialize the number of moves to zero.
}

template<typename T>
bool ConnectFourBoard<T>::update_board(int x, int y, T symbol) {
    // Handle moves for human and random players.
    if (this->board[x][y] != ' ') {
        return false;
    }

    // Place the symbol in the lowest available row for the given column.
    for (int i = this -> rows - 1 ; i >= 0; --i) {
        if(this->board[i][y] == ' ') {
            if (x != i) {
                return false; //Not in the lowest row
            }
            if (x == i) { //IN the lowest row
                this->board[x][y] = toupper(symbol);
                ++this->n_moves;
                return true;
            }
        }
    }

}

// Display the Connect Four board to the console.
template<typename T>
void ConnectFourBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|";
        for (int j = 0; j < this->columns; j++) {
            // Display the row and column indices and the symbol in each cell.
            cout << "[" << i << "," << j << "]   " << this->board[i][j] << "| ";
        }
    }
    cout << endl;
}

// Check for a win condition on the board.
template<typename T>
bool ConnectFourBoard<T>::is_win() {
    // Check horizontal, vertical, and diagonal for the given player ('O' or 'X')

    // Loop through each cell in the board
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            // Horizontal check (row is same , col increases)
            if (j + 3 < this->columns &&
                this->board[i][j] == this->board[i][j + 1]  && this->board[i][j + 1] == this->board[i][j + 2] &&
                this->board[i][j + 2] == this->board[i][j + 3] && this->board[i][j] != ' ') {
                return true;
                }

            // Vertical check (row increases , col is same)
            if (i + 3 < this->rows &&
                this->board[i][j] == this->board[i + 1][j] && this->board[i + 1][j] == this->board[i + 2][j] &&
                this->board[i + 2][j] == this->board[i + 3][j] && this->board[i][j] != ' ') {
                return true;
                }

            // Diagonal (top-left to bottom-right)
            if (i + 3 < this->rows && j + 3 < this->columns &&
                this->board[i][j] == this->board[i + 1][j + 1] && this->board[i + 1][j + 1] == this->board[i + 2][j + 2] &&
                this->board[i + 2][j + 2] == this->board[i + 3][j + 3] && this->board[i][j] != ' ' ) {
                return true;
                }

            // Diagonal (bottom-left to top-right)
            if (i - 3 >= 0 && j + 3 < this->columns &&
                this->board[i][j] == this->board[i - 1][j + 1] && this->board[i - 1][j + 1] ==this->board[i - 2][j + 2]&&
                this->board[i - 2][j + 2] == this->board[i - 3][j + 3] && this->board[i][j] != ' ' ) {
                return true;
                }
        }
    }
    return false;
}

template<typename T>
bool ConnectFourBoard<T>::is_draw() {
    // Check if the board is full and there is no winner.
    return this-> n_moves == 7 * 6 && !is_win();
}

template<typename T>
bool ConnectFourBoard<T>::game_is_over() {
    // The game is over if there's a win or a draw.
    return is_win() || is_draw();
}

// Constructor for Connect Four player.
template<typename T>
ConnectFourPlayer<T>::ConnectFourPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void ConnectFourPlayer<T>::getmove(int &x, int &y) {
    while (true) {
        cout << "Please enter the coordinates of the move (row and column between 0 and 6):\n";

        // Input validation for numeric and within bounds
        if (!(cin >> x >> y)) {
            cin.clear(); // Clear invalid input flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter two numbers separated by a space.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear remaining input buffer

        // Validate that coordinates are within board limits (assuming a 7x6 grid)
        if (x >= 0 && x < 6 && y >= 0 && y < 7) {
            break; // Valid input
        } else {
            cout << "Invalid coordinates! Row must be between 0-5 and column must be between 0-6.\n";
        }
    }
}

// Constructor for random AI player.
template<typename T>
ConnectFourRandomPlayer<T>::ConnectFourRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->name = (symbol == 'X') ? "Random Player 1" : "Random Player 2";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator.
}

template<typename T>
void ConnectFourRandomPlayer<T>::getmove(int &x, int &y) {
    // Generate random coordinates for the move.
    x = rand() % 6;  // Random number between 0 and 5 (rows).
    y = rand() % 7;  // Random number between 0 and 6 (columns).
}

#endif //CONNECTFOUR_H
