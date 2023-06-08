#include <iostream>
#include <vector>

using namespace std;

#include "Game.h"

Game::Game() {
	// player ships pack
	playerShips.push_back(new Destroyer());
	playerShips.push_back(new Cruiser());
	playerShips.push_back(new Cruiser());
	playerShips.push_back(new Battleship());
	playerShips.push_back(new Battleship());
	playerShips.push_back(new Battleship());
	playerShips.push_back(new Carrier());
	playerShips.push_back(new Carrier());
	playerShips.push_back(new Carrier());
	playerShips.push_back(new Carrier());
	//

	// bot ships pack
	playerShips.push_back(new Destroyer());
	playerShips.push_back(new Cruiser());
	playerShips.push_back(new Cruiser());
	playerShips.push_back(new Battleship());
	playerShips.push_back(new Battleship());
	playerShips.push_back(new Battleship());
	playerShips.push_back(new Carrier());
	playerShips.push_back(new Carrier());
	playerShips.push_back(new Carrier());
	playerShips.push_back(new Carrier());
	//
}

Game::~Game() {
	for (Ship* ship : playerShips) {
		delete ship;
	}
	for (Ship* ship : botShips) {
		delete ship;
	}
}

void Game::Play() {
	int row, choice;
	char col;
	bool horizontal;

	cout << playerBoard;
	cout << "Place your ships!\nEnter row(1-10) and column(A-J) - '2 a'\n";
	for (int i = 0; i < playerShips.size(); i++) {
		while (playerShips[i]->getPlacedStatus() != true)
		{
			cin >> row >> col;
			col = toupper(col);
			cout << "Horizontal?\n1.YES / 2.NO\n";
			cin >> choice;
			switch (choice)
			{
			case 1:
				horizontal = true;
				break;
			case 2:
				horizontal = false;
				break;
			default:
				cout << "Horizontal?\n1.YES / 2.NO\n";
				break; // continue;
			}
			playerShips[i]->placeShip(row, col - 64, playerShips[i], &playerBoard, horizontal);
		}


	}
}

bool checkGameLost() {

	return true;
}

void saveGame() {

}

void loadGame() {

}