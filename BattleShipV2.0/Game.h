#pragma once
#include <iostream>
#include <vector>

using namespace std;

#include "Board.h"
#include "Ship.h"

class Game
{
private:
	Board playerBoard;
	Board botBoard;
	vector<Ship*> playerShips;
	vector<Ship*> botShips;

public:
	Game();
	~Game();
	void Play();
	void saveGame();
	void loadGame();

};

