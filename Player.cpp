#include "Player.h"


Player::Player()
{
    id = 0;
    name = "";
    color = "";
    figures = {};
}

Player::Player(string name, string color, int id, vector<Figure> figures) {
    this->name    = name;
    this->color   = color;
    this->id      = id;
    this->figures = figures;
}

int Player::getID() {
    return id;
}
