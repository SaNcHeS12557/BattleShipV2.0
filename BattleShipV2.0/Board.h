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

public:
	Board() : grid(10, vector<CellStatus>(10, CellStatus::EMPTY)), isEnemyBoard(false){}; // constructor 10x10 game table
	void setCellStatus(int row, int column, CellStatus status);//
	CellStatus getCellStatus(int row, int column);//

	void setEnemyStatus(Board *board);
	bool getEnemyStatus(Board board);
	vector<Ship*> getShipsOnBoard(); 
	Ship* hit(int row, int col);

	friend class Ship;
	friend ostream& operator<<(ostream& os, const Board& board);
};

