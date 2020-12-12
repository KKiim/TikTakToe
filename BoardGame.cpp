#include "boardGame.h"
#include <algorithm>    // std::sort



BoardGame::BoardGame()
{
    roundNo   = 0;
	aiRekDepth = 0;
}

void switchPlayer(Player& p1, Player& p2) {
	Player copy = p1;
	p1 = p2;
	p2 = copy;
}

void BoardGame::changePlayerAtMove()
{
	switchPlayer(playerAtTurn, playerNotAtTurn);
}

void BoardGame::doAiMove()
{
	Player oldplayerAtTurn    = aiMyself = playerAtTurn;
	Player oldplayerNotAtTurn = aiOponent = playerNotAtTurn;

	vector<Board> moves;
	moves = getPosMoves();

	Board move;
	move = getBestMove(moves, oldplayerAtTurn, oldplayerNotAtTurn);

	board = move;
	playerAtTurn = oldplayerAtTurn;
	playerNotAtTurn = oldplayerNotAtTurn;
}

float scoreToFloat(SCORE score) {
	float sO = 0.000000001;
	return (score.myTotalWins + sO) / (score.opTotalWins + sO);
}

float scoreToFloat2(SCORE score) {
	if (score.myDwin % 2 == 1) return 999999999;
	if (score.opDwin % 2 == 1) return 0;
	return scoreToFloat(score);
}

bool sortbysec(const pair<int, int>& a, const pair<int, int>& b)
{
	return (a.second < b.second);
}

/*
void sortVecBySec(vector<pair<int, int>>& res) {
	
}
*/

int getBestMoveID(const vector<SCORE>& res) {
	int bestID = 0;
	float bestScore = -1;
	for (int i = 0; i < res.size(); i++) {
		float fScrore = scoreToFloat(res[i]);
		if (fScrore > bestScore) {
			bestID = i;
			bestScore = fScrore;
		}
	}
	return bestID;
}

Board BoardGame::getBestMove(const vector<Board>& moves, const Player& pAtMove, const Player& pNotAtMove) {
	vector<SCORE> res;
	int mID = 0;

	for (Board move : moves) {
		aiRekDepth = 0;
		SCORE score;
		score.myDwin = 0;
		score.myTotalWins = 0;
		score.opDwin = 0;
		score.opTotalWins = 0;
		playerAtTurn    = pAtMove;
		playerNotAtTurn = pNotAtMove;
		//thread name(bar, 0, 0);
		findScoreRecursive(move, score);
		res.push_back(score);
	}
	
	int bestMoveID = getBestMoveID(res);

	return moves[bestMoveID];
}

void BoardGame::findScoreRecursive(Board& move, SCORE& score) {
	vector<Board> moves;
	Board oldBoard = board;
	board = move;
	if (aiRekDepth > 5) return;
	int badity = 10 - aiRekDepth;
	int howBad = pow(2, badity);

	if (score.myDwin % 2 == 1 || score.opDwin % 2 == 1) {
		return;
	}
	if ((aiRekDepth % 2 == 0) && didWin(aiMyself.getID())) {
		if (aiRekDepth == 0) score.myDwin = score.myDwin | 1;
		score.myTotalWins++;
		return;
	}
	else if ((aiRekDepth % 2 == 1) && didWin(aiOponent.getID())) {
		if (aiRekDepth == 1)  score.opDwin = score.opDwin | 1;
		score.opTotalWins++;
		return;
	}
	else if (didWin(0)) {
		return;
	}

	changePlayerAtMove();
	moves = getPosMoves();
	changePlayerAtMove();

	for (Board newMove : moves) {
		aiRekDepth++;
		changePlayerAtMove();
		findScoreRecursive(newMove, score);
		changePlayerAtMove();
		aiRekDepth--;
	}

	board = oldBoard;
	return;
}



int BoardGame::getRoundNo()
{
	return roundNo;
}

void BoardGame::nextRound()
{
	roundNo++;
}


