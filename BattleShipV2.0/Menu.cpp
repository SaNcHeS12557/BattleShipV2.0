#include <iostream>

using namespace std;

#include "Menu.h"

void Menu::showMenu() {
	int choice;
	Game game;
	system("cls");
	while (true) {
		cout << "\033[1m\033[1;36m===========================	\n";
		cout << "     BATTLESHIP MENU     \n";
		cout << "===========================\033[0m\n";
		cout << "1. \033[1;33mCreate New Game\033[0m\n";
		cout << "2. \033[1;33mStart with Previous Save\033[0m\n";
		cout << "3. \033[1;33mExit\033[0m\n";
		cout << "Enter your choice:\033[32m ";
		cin >> choice;
		cout << "\033[0m\n";

		switch (choice) {
		case 1: {
			game.Play(false);
			break;
		}
		case 2: {
			game.Play(true);
			break;
		}
		case 3: {
			cout << "Exiting the game...\n";
			exit(0);
		}
		default: {
			system("cls");
			cout << "\033[31mInvalid choice. Please try again!\033[0m\n\n";
			break;
		}
		}
	}
}
