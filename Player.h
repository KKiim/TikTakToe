#pragma once
#include <iostream>
#include "Figure.h"
#include <vector>

using namespace std;

class Player
{
public:
	Player();
	Player(string name, string color, int id, vector<Figure> figures);
	int getID();
	vector<Figure> figures;
private:
	int id;
	string color;
	string name;
};

