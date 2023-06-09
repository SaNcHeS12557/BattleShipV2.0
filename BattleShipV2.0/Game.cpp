#include <iostream>
#include <vector>
#include<fstream>
#include<string>

using namespace std;

#include "Game.h"
#include "Menu.h"

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

void Game::Play(bool isLoadPlay) {
	int row, choice;
	char col;
	bool horizontal;
	if (isLoadPlay == true) {
		loadGame();
	}
	else {
		// players board
		system("cls");
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
				row = rand() % 10;
				col = rand() % 10;
				horizontal = rand() % 2 == 0;
				botShips[i]->placeShip(row + 1, col + 1, botShips[i], &botBoard, horizontal);
			}
		}

		cout << "Do you want to save your && computer's loadouts?\n1. Yes\n2. No\n3. Menu\n4. Start Game\n";
		do
		{
			cin >> choice;
			switch (choice)
			{
			case 1:
				saveGame();
				break;
			case 2:
				// nothing to copy
				break;
			case 3:
				//return to menu
				system("cls");
				Menu menu;
				menu.showMenu();
				break;
			default:
				cout << "Please select 1-4:\n";
				break;
			}
		} while (true);

	}


	while (true)
	{
		//players moves
		system("cls");
		cout << playerBoard;
		cout << botBoard;

		cout << "Enter col and row to shoot - '1a': ";
		cin >> row >> col;
		col = toupper(col);

		Ship* shipHitted = botBoard.hit(row, col - 64);
		if (shipHitted != nullptr && shipHitted->isSunk()) {
			vector<Deck*>& deckStatus = shipHitted->getDeckStatus();
			for (Deck* deck : deckStatus) {
				int row = deck->getRow();
				int col = deck->getCol();
				for (int i = row - 1; i <= row + 1; ++i) {
					for (int j = col - 1; j <= col + 1; ++j) {
						if (i >= 1 && i <= 10 && j >= 1 && j <= 10 && botBoard.getCellStatus(i, j) != CellStatus::HIT) {
							botBoard.setCellStatus(i, j, CellStatus::MISS);
						}
					}
				}
			}
			botBoard.decrementShipsCounter(); // if the ship isSunk() -1 ship
			botBoard.removeSunkShips(); // removing sunk ships from shipsOnBoard vector
		}
		system("cls");
		cout << playerBoard;
		cout << botBoard;
		if (checkGameWin() == true) {
			break;
		}



		//bots moves
		row = rand() % 9;
		col = rand() % 9;
		shipHitted = playerBoard.hit(row + 1, col + 1); //getting hitted ship
		if (shipHitted != nullptr && shipHitted->isSunk()) { // if the ship was hitted and sunk
			vector<Deck*>& deckStatus = shipHitted->getDeckStatus(); //getting ships decks
			for (Deck* deck : deckStatus) {
				int row = deck->getRow();
				int col = deck->getCol();
				for (int i = row - 1; i <= row + 1; ++i) {
					for (int j = col - 1; j <= col + 1; ++j) {
						if (i >= 1 && i <= 10 && j >= 1 && j <= 10 && playerBoard.getCellStatus(i, j) != CellStatus::HIT) {
							playerBoard.setCellStatus(i, j, CellStatus::MISS);
						}
					}
				}
			}
			playerBoard.decrementShipsCounter(); // if the ship isSunk() -1 ship
			playerBoard.removeSunkShips(); // removing sunk ships from shipsOnBoard vector
		}
		system("cls");
		cout << playerBoard;
		cout << botBoard;
		if (checkGameLost() == true) {
			break;
		}
	}
}

bool Game::checkGameLost() {
	if (playerBoard.getShipsOnBoard().size() == 0)
		return true;
	return false;
}

bool Game::checkGameWin() {
	if (botBoard.getShipsOnBoard().size() == 0)
		return true;
	return false;
}

void Game::saveGame() {
	ofstream file("savegame.txt");
	if (!file) {
		cout << "Error: Unable to create save file." << endl;
		return;
	}

	// Save player ships
	file << "Player Ships:" << endl;
	for (Ship* ship : playerShips) {
		file << ship->getDeckStatus()[0]->getRow() << " " << ship->getDeckStatus()[0]->getCol() << " " << ship->getIsHorizontal() << endl;
	}

	// Save bot ships
	file << "Bot Ships:" << endl;
	for (Ship* ship : botShips) {
		file << ship->getDeckStatus()[0]->getRow() << " " << ship->getDeckStatus()[0]->getCol() << " " << ship->getIsHorizontal() << endl;
	}

	file.close();
}

void Game::loadGame() {

}
