#include <iostream>
#include <vector>

using namespace std;

#include "Ship.h"
#include "Board.h"

Ship::Ship(int size, string type) : size(size), type(type), isPlaced(false) {}

Destroyer::Destroyer() : Ship(4, "Destroyer") {
	for (int i = 0; i < size; i++) {
		deckStatus.push_back(new Deck);
	}
}
Cruiser::Cruiser() : Ship(3, "Cruiser") {
	for (int i = 0; i < size; i++) {
		deckStatus.push_back(new Deck);
	}
}

Battleship::Battleship() : Ship(2, "Battleship") {
	for (int i = 0; i < size; i++) {
		deckStatus.push_back(new Deck);
	}
}

Carrier::Carrier() : Ship(1, "Carrier") {
	for (int i = 0; i < size; i++) {
		deckStatus.push_back(new Deck);
	}
}

int Deck::getRow() {
	return row;
}
void Deck::setRow(Deck* deck, int row) {
	deck->row = row;
}

int Deck::getCol() {
	return col;
}
void Deck::setCol(Deck* deck, int col) {
	deck->col = col;
}

bool Deck::setDamagedStatus(bool hit) {
	return isDamaged = true;
}
bool Deck::getDamagedStatus() {
	return isDamaged;
}

vector<Deck*>& Ship::getDeckStatus() {
	return deckStatus;
}

string Ship::getShipType() {
	return type;
}

bool Ship::getPlacedStatus() {
	return isPlaced;
}

void Ship::setPlacedStatus(bool status) {
	isPlaced = status;
}

int Ship::getShipSize() {
	return size;
}

bool Ship::getIsHorizontal() {
	return isHorizontal;
}

void Ship::setHorizontalStatus(bool orientation) {
	isHorizontal = orientation;
}

void Ship::placeShip(int row, int col, Ship* ship, Board* board, bool horizontal) {

	vector<Ship*> shipsOnBoard = board->getShipsOnBoard(); // getting boards ships vector
	ship->setHorizontalStatus(horizontal);

	if ((horizontal && col + ship->size > 11) || (!horizontal && row + ship->size > 11)) { // checking if there are enough space for the ship
		ship->setPlacedStatus(false);
		return;
	}

	if (horizontal == true) // placing the ship (horizontal)
	{
		for (int i = row - 1; i <= row + 1; ++i) {   // checking if there  are not other ships nearby (HORIZONTAL)
			for (int j = col - 1; j <= col + ship->size + 1; ++j) {
				if (i >= 1 && i <= 10 && j >= 1 && j <= 10) {
					if (board->grid[i - 1][j - 1] == CellStatus::SHIP) {
						ship->setPlacedStatus(false);
						return; // TODO: cancelling the remove function from vector / repeat the place attempt 
					}
				}
			}
		}
		for (int j = col; j < col + ship->size; ++j) {
			board->grid[row - 1][j - 1] = CellStatus::SHIP;
		}
		for (int i = 0; i < ship->size; i++)
		{
			ship->deckStatus[i]->setRow(deckStatus[i], row);
			ship->deckStatus[i]->setCol(deckStatus[i], col + i);
		}
	}
	else {	// placing the ship (vertical)
		for (int i = row - 1; i <= row + ship->size; ++i) {   // checking if there  are not other ships nearby (VERTICAL)
			for (int j = col - 1; j <= col + 1; ++j) {
				if (i >= 1 && i <= 10 && j >= 1 && j <= 10) {
					if (board->grid[i - 1][j - 1] == CellStatus::SHIP) {
						ship->setPlacedStatus(false);
						return; // TODO: cancelling the remove function from vector / repeat the place attempt 
					}
				}
			}
		}
		for (int i = row; i < row + ship->size; ++i) {
			board->grid[i - 1][col - 1] = CellStatus::SHIP;
		}
		for (int i = 0; i < ship->size; i++)
		{
			ship->deckStatus[i]->setRow(deckStatus[i], row + i);
			ship->deckStatus[i]->setCol(deckStatus[i], col);

		}
	}
	ship->setPlacedStatus(true);
	board->shipsOnBoard.push_back(ship); // adding ship to shipsOnBoard vector
	board->shipsCounter++;
}

bool Ship::isSunk() {
	for (Deck* deck : deckStatus) {
		if (!deck->getDamagedStatus()) {
			return false;
		}
	}
	return true;
}

Ship::~Ship() {
	for (Deck* deck : deckStatus) {
		delete deck;
	}
}