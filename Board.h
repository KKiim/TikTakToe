#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include "Player.h"
#include "Figure.h"
using namespace std;

class Board
{
public:
	Board();
	Board(int width, int heigt);
	void constructHelper(int width, int heigt);
	void drawBoard();
	int getWidth();
	int getHeight();
	char getSymbolFromPos(pair<int, int>);
	void setFigOnPos(Figure, pair<int, int>);
	string getString();
	void getBoardFromString(string input);

protected:
	int width;
	int height;
	map<pair<int, int>, Figure> figurePosis;
};

