#pragma once
#include <iostream>
#include <vector>

using namespace std;

#include"Ship.h"

enum class CellStatus { EMPTY, SHIP, HIT, MISS }; // cell stutus

class Board {
private:
	bool isEnemyBoard; // to detect computers board
	vector<vector<CellStatus>> grid; // game table R x C
	vector<Ship*> shipsOnBoard; //active ships on the board
	int shipsCounter;

public:
	Board(); // constructor 10x10 game table
	~Board();
	void setCellStatus(int row, int column, CellStatus status); //
	CellStatus getCellStatus(int row, int column); //
	void setEnemyStatus(Board *board);
	bool getEnemyStatus(Board board);
	vector<Ship*>& getShipsOnBoard();
	int getShipsCounter();
	void clearShipsCounter();
	void decrementShipsCounter();
	Ship* hit(int row, int col);
	void removeSunkShips();
	vector<vector<CellStatus>> getGrid();
	void destroyAllBoard(); // made only for test
	void clearGrid();

	friend class Ship;
	friend ostream& operator<<(ostream& os, const Board& board);
};

