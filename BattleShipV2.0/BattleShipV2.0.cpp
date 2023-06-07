#include <iostream>
#include <vector>

using namespace std;

#include"Board.h"

int main()
 {
    Board grid;
    Board computer;
    computer.setEnemyStatus(&computer);
    Destroyer* a = new Destroyer;
    Battleship* b = new Battleship;
    Cruiser *c = new Cruiser;
    Carrier *d = new Carrier;
    a->placeShip(1, 1, a, &grid, false);
    b->placeShip(1, 3, b, &grid, false);
    c->placeShip(1, 4, c, &computer, true);
    d->placeShip(3, 1, d, &computer, false);
    cout << grid;
    grid.hit(1, 3);
    grid.hit(2, 3);
    grid.hit(3, 2);
    grid.hit(4, 1);

    if (a->isSunk() == true) {
        cout << "The ship blblbl :(\n";
    }
    else {
        cout << "The ship not blblbl\n";
    }

    cout << grid;
    //cout << computer;
    cout << "test\n";

}
