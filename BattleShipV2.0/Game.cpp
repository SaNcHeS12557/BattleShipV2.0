#include <iostream>
#include <vector>
#include<fstream>
#include<string>
#include <sstream>
#include <cstdlib>

using namespace std;

#include "Game.h"
#include "Menu.h"

Menu menu;

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
		if (loadGame() == false) {
			system("cls");
			cout << "\033[31mYou don't have any saves. Please create the new game!\033[0m\n\n";
			return;
		}
		loadGame();
	}
	else {
		// players board
		bool exitMenu = false;
		bool exitSubMenu = false;

		while (exitMenu != true)
		{
			srand(time(nullptr)); // to generate new boards every time
			system("cls");
			cout << playerBoard;
			cout << "1. \033[1;33mPlace your ships randomly\033[0m\n2. \033[1;33mPlace the ships yourself\033[0m\nEnter your choice: ";
			cin >> choice;
			switch (choice)
			{
			case 1:

				// random board generation
				for (int i = 0; i < playerShips.size(); i++) {
					while (playerShips[i]->getPlacedStatus() != true) {
						row = rand() % 10;
						col = rand() % 10;
						horizontal = rand() % 2 == 0;
						playerShips[i]->placeShip(row + 1, col + 1, playerShips[i], &playerBoard, horizontal);
					}
				}
				//

				while (exitSubMenu!=true)
				{
					system("cls");
					cout << playerBoard;
					cout << "What do you want to do next?\n1. \033[1;33mRegenerate Board\033[0m\n2. \033[1;33mKeep and Play\033[0m\nEnter your choice: ";
					cin >> choice;
					switch (choice)
					{
					case 1:
						// clear system
						for (auto ship : playerShips) {
							ship->setPlacedStatus(false);
						}
						playerBoard.clearShipsCounter();
						playerBoard.clearGrid();
						//

						// random board generation
						for (int i = 0; i < playerShips.size(); i++) {
							while (playerShips[i]->getPlacedStatus() != true) {
								row = rand() % 10;
								col = rand() % 10;
								horizontal = rand() % 2 == 0;
								playerShips[i]->placeShip(row + 1, col + 1, playerShips[i], &playerBoard, horizontal);
							}
						}
						//
						break;
					case 2:
						exitMenu = true;
						exitSubMenu = true;
					default:
						break;
					}
				}
				break;
			case 2:
				// clear system
				for (auto ship : playerShips) {
					ship->setPlacedStatus(false);
				}
				playerBoard.clearShipsCounter();
				playerBoard.clearGrid();
				//

				for (int i = 0; i < playerShips.size(); i++) {
					system("cls");
					cout << playerBoard;
					while (playerShips[i]->getPlacedStatus() != true)
					{
						cout << "Place your " << playerShips[i]->getShipType() << "(\033[32m" << playerShips[i]->getShipSize() << "\033[0m)\n" << "\n";
						do
						{
							cout << "Enter row(1-10) and column(A-J) - '1a': ";
							cin >> row >> col;
							col = toupper(col);
						} while (row < 1 || row>10 || col < 'A' || col>'J');
						cout << "Horizontal?\n\033[32m1.YES \033[0m/\033[31m 2.NO\033[0m\n";
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
				exitMenu = true;
				break;
			default:
				cout << "Invalid choice. Enter your choice (1-2): ";
				break;
			}
		}

		system("cls");


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

		cout << "\033[1m\033[1;36m======================================================\n";
		cout << "Do you want to save your && computer's loadouts?\n";
		cout << "======================================================\033[0m\n";
		cout << "1.\033[32m Yes \033[33m(return to Menu)\033[0m\n2.\033[32m Yes \033[33m(continue the game)\033[0m\n3.\033[31m No \033[33m(return to Menu)\033[0m\n4. \033[31mNo \033[33m(continue the game)\033[0m\nEnter your choise: ";
		exitMenu = false;
		do
		{
			cin >> choice;
			switch (choice)
			{
			case 1:
				// save with return
				saveGame();
				system("cls");
				menu.showMenu();
				exitMenu = true;
				break;
			case 2:
				// save with continue
				saveGame();
				exitMenu = true;
				break;
			case 3:
				//return to menu
				system("cls");
				menu.showMenu();
				exitMenu = true;
				break;
			case 4:
				// continue the game
				exitMenu = true;
				break;
			default:
				cout << "Please select 1-4:\n";
				break;
			}
		} while (!exitMenu);

	}

	while (true)
	{
		//players moves
		system("cls");
		cout << playerBoard;
		cout << botBoard;

		Ship* shipHitted; //get hitted ship
		do
		{
			do
			{
				cout << "Enter col and row to shoot - '1a': ";
				cin >> row >> col;
				col = toupper(col);

			} while (row < 1 || row < 1 || row>10 || col < 'A' || col>'J' || botBoard.getCellStatus(row, col - 64) == CellStatus::HIT || botBoard.getCellStatus(row, col - 64) == CellStatus::MISS);
			shipHitted = botBoard.hit(row, col - 64);
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
				system("cls");
				cout << "\033[1m\033[32m===========================	\n";
				cout << "	 YOU WIN     \n";
				cout << "===========================\033[0m\n";
				do
				{
					cout << "What do you want to do next?\n1.\033[1;33mMenu\033[0m\n2.\033[1;33mExit Game\033[0m\nEnter your choise: ";
					cin >> choice;
					switch (choice)
					{
					case 1:
						menu.showMenu();
						break;
					case 2:
						cout << "Exiting the game...\n";
						exit(0);
					default:
						cout << "Please choose 1-2!\n";
						break;
					}
				} while (true);
			}
		} while (shipHitted != nullptr);


		//bots moves
		do
		{
			do
			{
				row = rand() % 9;
				col = rand() % 9;

			} while (botBoard.getCellStatus(row + 1, col + 1) == CellStatus::HIT || botBoard.getCellStatus(row + 1, col + 1) == CellStatus::MISS);
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
				system("cls");
				cout << "\033[1m\033[31m===========================	\n";
				cout << "         YOU LOST     \n";
				cout << "===========================\033[0m\n";
				do
				{
					cout << "What do you want to do next?\n1.\033[1;33mMenu\033[0m\n2.\033[1;33mExit Game\033[0m\nEnter your choise: ";
					cin >> choice;
					switch (choice)
					{
					case 1:
						menu.showMenu();
						break;
					case 2:
						cout << "Exiting the game...\n";
						exit(0);
					default:
						cout << "Please choose 1-2!\n";
						break;
					}
				} while (true);
			}
		} while (shipHitted != nullptr);

	}
}

bool Game::checkGameLost() {
	vector<Ship*> shipsOnBoard = playerBoard.getShipsOnBoard();
	for (auto ship : shipsOnBoard) {
		for (int i = 0; i < ship->getShipSize(); i++)
		{
			if (ship->getDeckStatus()[i]->getDamagedStatus() == false)
				return false;
		}
	}
	return true;
	//if (playerBoard.getShipsOnBoard().size() == 0)
	//	return true;
	//return false;
}

bool Game::checkGameWin() {
	vector<Ship*> shipsOnBoard = botBoard.getShipsOnBoard();
	for (auto ship : shipsOnBoard) {
		for (int i = 0; i < ship->getShipSize(); i++)
		{
			if (ship->getDeckStatus()[i]->getDamagedStatus() == false)
				return false;
		}
	}
	return true;
	//if (botBoard.getShipsOnBoard().size() == 0)
	//	return true;
	//return false;
}

void Game::saveGame() {
	ofstream file("savegame.txt");
	if (!file) {
		cout << "Hmm... you can't create a savegame file :( " << endl;
	}

	// save player ships
	file << "Player Ships:" << endl;
	for (Ship* ship : playerShips) {
		file << ship->getDeckStatus()[0]->getRow() << " " << ship->getDeckStatus()[0]->getCol() << " " << ship->getIsHorizontal() << endl;
	}

	// save bot ships
	file << "Bot Ships:" << endl;
	for (Ship* ship : botShips) {
		file << ship->getDeckStatus()[0]->getRow() << " " << ship->getDeckStatus()[0]->getCol() << " " << ship->getIsHorizontal() << endl;
	}

	file.close();
}

bool Game::loadGame() {
	ifstream file("savegame.txt");
	if (!file) {
		cout << "You can't load the savegame file!" << endl;
		return false;
	}

	int row, col, i = 0;
	bool horizontal;
	string line;

	while (getline(file, line)) {
		if (line == "Player Ships:") {
			while (getline(file, line) && line != "Bot Ships:") {
				istringstream iss(line);
				if (iss >> row >> col >> horizontal) {
					if (i < playerShips.size()) {
						playerShips[i]->placeShip(row, col, playerShips[i], &playerBoard, horizontal);
					}
				}
				i++;
			}
		}
		if (line == "Bot Ships:") {
			i = 0;
			botBoard.setEnemyStatus(&botBoard);
			while (getline(file, line)) {
				istringstream iss(line);
				if (iss >> row >> col >> horizontal) {
					if (i < botShips.size()) {
						botShips[i]->placeShip(row, col, botShips[i], &botBoard, horizontal);
					}
				}
				i++;
			}
		}

	}

	file.close();
	return true;
}