#include <iostream>

using namespace std;

#include "Menu.h"

void Menu::showMenu() {
	int choice;

	while (true) {
		cout << "===== BATTLESHIP MENU =====\n";
		cout << "1. Start New Game\n";
		cout << "2. Start with Previous Save\n";
		cout << "3. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			Game game;
			game.Play(false);
			break;
		}
		case 2: {
			Game game;
			game.Play(true);
			break;
		}
		case 3: {
			cout << "Exiting the game...\n";
			return;
		}
		default: {
			cout << "Invalid choice. Please try again!\n";
			break;
		}
		}
	}
}
