#pragma once
#include <iostream>
#include <vector>


using namespace std;

class Deck {
private:
	int row, col;
	bool isDamaged;

public:
	Deck() {};
	Deck(int row, int col) : row(row), col(col), isDamaged(false) {};
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
	string type; // type of ship
	int size;
	vector<Deck*> deckStatus;

public:
	Ship(int size, string type);
	~Ship();
	vector<Deck*>& getDeckStatus();
	void placeShip(int row, int col, Ship* ship, Board* board, bool horizontal);
	bool isSunk();


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


