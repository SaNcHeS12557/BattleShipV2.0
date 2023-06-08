#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Deck {
private:
	int row, col;
	bool isDamaged = false;

public:
	Deck() {};
	Deck(int row, int col) : row(row), col(col) {};
	int getRow();
	void setRow(Deck* deck, int row);
	int getCol();
	void setCol(Deck* deck, int col);
	bool setDamagedStatus(bool hit);
	bool getDamagedStatus();


	friend class Board;
};

class Ship : public	Deck
{
private:
	string type; // name of ship
	int size;
	vector<Deck*> deckStatus;
	bool isPlaced;

public:
	Ship(int size, string type);
	~Ship();
	vector<Deck*>& getDeckStatus();
	string getShipType();
	void placeShip(int row, int col, Ship* ship, Board* board, bool horizontal);
	bool isSunk();
	bool getPlacedStatus();
	void setPlacedStatus(bool status);
	int getShipSize();


	friend class Destroyer;
	friend class Cruiser;
	friend class Battleship;
	friend class Carrier;
};

class Destroyer : public Ship { // (4) cells
public:
	Destroyer();
};

class Cruiser : public Ship { // (3) cells
public:
	Cruiser();
};

class Battleship : public Ship { // (2) cells
public:
	Battleship();
};

class Carrier : public Ship { // (1) cell
public:
	Carrier();
};


