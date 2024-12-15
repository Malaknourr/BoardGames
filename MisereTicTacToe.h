#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "BoardGame_Classes.h"

template <typename T>
class X_O_Board__ : public Board<T> {
public:
    X_O_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win(); // Will detect if a player forces a win (in Misere, this means they lose)
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class X_O_Player__ : public Player<T> {
public:
    X_O_Player__(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class X_O_Random_Player__ : public RandomPlayer<T> {
public:
    X_O_Random_Player__(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
X_O_Board__<T>::X_O_Board__() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0; // Initialize empty spaces
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool X_O_Board__<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
        this->n_moves++;
        this->board[x][y] = toupper(mark); // Capitalize mark (X or O)
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void X_O_Board__<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Misere Tic Tac Toe: A player loses if they complete a row, column, or diagonal
template <typename T>
bool X_O_Board__<T>::is_win() {
    // Check rows and columns for a winning line
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;  // A winning line is found, the player who made this move loses
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;  // A winning diagonal is found, the player who made this move loses
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool X_O_Board__<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

// Check if the game is over (win or draw)
template <typename T>
bool X_O_Board__<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
X_O_Player__<T>::X_O_Player__(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player__<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
X_O_Random_Player__<T>::X_O_Random_Player__(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X_O_Random_Player__<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

#endif //_3X3X_O_H
