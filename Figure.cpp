#include "Figure.h"

Figure::Figure()
{
	this->symbol = '_';
	this->name = "leer";
	this->playerID = 0;
}

Figure::Figure(char symbol, string name, int playerID)
{
	this->symbol = symbol;
	this->name = name;
	this->playerID = playerID;
}

char Figure::getSymbol()
{
	return symbol;
}
