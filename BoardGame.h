#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "board.h"
#include <thread>         // std::thread


using namespace std;


struct SCORE {
	int myDwin;
	int opDwin;
	int myTotalWins;
	int opTotalWins;
};


class BoardGame
{
private:
	int aiRekDepth;

public:
	BoardGame();
	virtual bool didWin(int player) = 0;
	virtual vector<Board> getPosMoves() = 0;
	void changePlayerAtMove();
	void doAiMove();
	Board getBestMove(const vector<Board>& moves, const Player& p1, const Player& p2);
	void findScoreRecursive(Board& move, SCORE& score);
	int getRoundNo();
	void nextRound();

	Board board;
	Player playerAtTurn;
	Player playerNotAtTurn;
	Player aiMyself;
	Player aiOponent;

protected:
	int roundNo;
};


