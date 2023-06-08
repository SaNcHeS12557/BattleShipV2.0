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
	botShips.push_back(new Destroyer());
	botShips.push_back(new Cruiser());
	botShips.push_back(new Cruiser());
	botShips.push_back(new Battleship());
	botShips.push_back(new Battleship());
	botShips.push_back(new Battleship());
	botShips.push_back(new Carrier());
	botShips.push_back(new Carrier());
	botShips.push_back(new Carrier());
	botShips.push_back(new Carrier());
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

	// players board
	for (int i = 0; i < playerShips.size(); i++) {
		cout << playerBoard;
		while (playerShips[i]->getPlacedStatus() != true)
		{
			cout << "Place your " << playerShips[i]->getShipType() << "(" << playerShips[i]->getShipSize() << ")\n" << "\nEnter row(1-10) and column(A-J) - '1a': ";
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
		system("cls");
	}

	// bot board generator
	botBoard.setEnemyStatus(&botBoard);
	for (int i = 0; i < botShips.size(); i++) {
		srand(time(nullptr)); // to generate new boards every play()
		while (botShips[i]->getPlacedStatus() != true) { 
			int row = rand() % 10;
			int col = rand() % 10;
			bool horizontal = rand() % 2 == 0;
			botShips[i]->placeShip(row+1, col+1, botShips[i], &botBoard, horizontal);
		}
	}
	cout << playerBoard;
	cout << botBoard;
}


bool checkGameLost() {

	return true;
}

void saveGame() {

}

void loadGame() {

}