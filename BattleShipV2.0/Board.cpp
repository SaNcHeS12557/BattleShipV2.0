#include <iostream>
#include <iomanip>
#include<vector>

using namespace std;

#include"Board.h"
#include"Ship.h"

void Board::setEnemyStatus(Board* board) {
    board->isEnemyBoard = true;
}
bool Board::getEnemyStatus(Board board) {
    return isEnemyBoard;
}
void Board::setCellStatus(int row, int column, CellStatus status) { // setting the cell status
    grid[row - 1][column - 1] = status;
}

CellStatus Board::getCellStatus(int row, int column) { // getting status of the cell
    return grid[row - 1][column - 1];
}

vector<Ship> Board::getShipsOnBoard() {
    return shipsOnBoard;
}

bool Board::hit(Board board, int row, int col) {
    auto it = find_if(board.shipsOnBoard.begin(), board.shipsOnBoard.end(), [row, col](Ship& ship) {
        vector<Deck*>& deckStatus = ship.getDeckStatus(); // getting deckStatus from Ship
        for (Deck* deck : deckStatus) { // finding ship with such row and col
            if (deck->getRow() == row && deck->getCol() == col) {
                deck->setDamagedStatus(true); // isDamaged = true
                return true; // the ship was hitted
            }
        }
        });
    return false; // there are no ships with such row and col coordinates
}

ostream& operator<<(ostream& os, const Board& board) {
    // column labels
    os << "   ";
    for (char col = 'A'; col <= 'J'; col++) {
        os << col << " ";
    }
    os << endl;

    int i = 1;
    for (auto row : board.grid) {
        os << setw(2) << i++ << " "; // row labels
        for (auto cell : row) {
            switch (cell) {
            case CellStatus::EMPTY:
                os << "\033[47m  \033[0m";
                break;
            case CellStatus::MISS:
                os << "\033[40m  \033[0m";
                break;
            case CellStatus::HIT:
                os << "\033[41m  \033[0m";
                break;
            case CellStatus::SHIP:
                if (board.isEnemyBoard==true)
                {
                    os << "\033[47m  \033[0m";
                }
                else {
                os << "\033[42m  \033[0m";
                }

                break;
            }
        }
        os << endl;
    }
    return os;
}