#include <iostream>
#include <vector>

using namespace std;

#include"Board.h"

int main()
{
    Board grid;
    //grid.setEnemyStatus(&grid);
    Destroyer* a = new Destroyer;
    Battleship *b = new Battleship;
    Cruiser *c = new Cruiser;
    Carrier *d = new Carrier;
    a->placeShip(1, 1, a, &grid, false);
    b->placeShip(1, 2, b, &grid, false);
    //c->placeShip(1, 1, c, grid, false);
    //d->placeShip(1, 1, d, grid, false);
    cout << grid;
    cout << "test";
}
