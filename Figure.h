#pragma once
#include <iostream>
using namespace std;
class Figure
{
public:
	Figure();
	Figure(char symbol, string name, int playerID);
	char getSymbol();
	int playerID;
private:
	string name;
	char symbol;
};

