#include <iostream>
#include <vector>

using namespace std;

#include"Game.h"

int main()
{
	//Board grid;
	//Board computer;
	//computer.setEnemyStatus(&computer);
	//Destroyer* a = new Destroyer;
	//Battleship* b = new Battleship;
	//Cruiser* c = new Cruiser;
	//Carrier* d = new Carrier;
	//a->placeShip(1, 1, a, &grid, false);
	//b->placeShip(1, 3, b, &grid, false);
	//c->placeShip(1, 5, c, &computer, false);
	//d->placeShip(1, 7, d, &computer, false);

	//grid.hit(1, 1);
	//grid.hit(2, 1);
	//grid.hit(3, 1);
	//Ship* ap = grid.hit(4, 1);

	//if (ap != nullptr && ap->isSunk()) {
	//	vector<Deck*>& deckStatus = ap->getDeckStatus();
	//	for (Deck* deck : deckStatus) {
	//		int row = deck->getRow();
	//		int col = deck->getCol();
	//		for (int i = row - 1; i <= row + 1; ++i) {
	//			for (int j = col - 1; j <= col + 1; ++j) {
	//				if (i >= 1 && i <= 10 && j >= 1 && j <= 10 && grid.getCellStatus(i, j) != CellStatus::HIT) {
	//					grid.setCellStatus(i, j, CellStatus::MISS);
	//				}
	//			}
	//		}
	//	}
	//	grid.decrementShipsCounter();
	//}
	//cout << grid;
	//cout << grid.getShipsCounter() << endl;
	//cout << computer.getShipsCounter();

	Game game;
	game.Play();





	//vector<Ship*> shipsPack;
	//shipsPack.push_back(new Destroyer);
	//shipsPack.push_back(new Cruiser);
	//shipsPack.push_back(new Battleship);
	//shipsPack.push_back(new Carrier);

	//int x;
	//char y;
	//int choice;
	//bool orientation;

	//for (int i = 0; i < shipsPack.size(); i++)
	//{
	//	cout << grid;
	//	cout << "Enter 1-10 A-J where do u want to place the " << shipsPack[i]->getShipType() << endl;
	//	cin >> x >> y;
	//	y = toupper(y);
	//	cout << "Horizontal?\n1.YES / 2.NO\n";
	//	cin >> choice;
	//	switch (choice)
	//	{
	//	case 1:
	//		orientation = true;
	//		break;
	//	case 2:
	//		orientation = false;
	//		break;
	//	default:
	//		cout << "Horizontal?\n1.YES / 2.NO\n";
	//		continue;
	//	}
	//	shipsPack[i]->placeShip(x, y - 64, shipsPack[i], &grid, orientation); // -64 is used to convert char to int
	//}
	//cout << grid << endl;

	//for (int i = 0; i < 10; i++)
	//{
	//	cout << "Lets pew pew)\n";
	//	cout << "Where do u want to make pew pew?\n";
	//	int hitRow;
	//	char hitCol;
	//	cin >> hitRow >> hitCol;
	//	hitCol = toupper(hitCol);

	//	Ship* shipHitted = grid.hit(hitRow, hitCol-64);
	//	grid.hit(hitRow, hitCol - 64);
	//	
	//	if (shipHitted != nullptr && shipHitted->isSunk()) {
	//		vector<Deck*>& deckStatus = shipHitted->getDeckStatus();
	//		for (Deck* deck : deckStatus) {
	//			int row = deck->getRow();
	//			int col = deck->getCol();
	//			for (int i = row - 1; i <= row + 1; ++i) {
	//				for (int j = col - 1; j <= col + 1; ++j) {
	//					if (i >= 1 && i <= 10 && j >= 1 && j <= 10 && grid.getCellStatus(i, j) != CellStatus::HIT) {
	//						grid.setCellStatus(i, j, CellStatus::MISS);
	//					}
	//				}
	//			}
	//		}
	//	}
	//	cout << grid << endl;
	//}
}
