#include "chess.h"

Chess::Chess() {
    Figure figP1 = Figure('B', "Bauer", 1);
    Figure figP2 = Figure('b', "Bauer", 2);
    playerAtTurn = Player("Spieler 1", "Wiess", 1, { figP1 });
    playerNotAtTurn = Player("Spieler 2", "Schwarz", 2, { figP2 });
    board = getInitBoard();
}

bool Chess::didWin(int player)
{
	return false;
}

Board Chess::getInitBoard()
{
    return Board(8,8);
}

vector<Board> Chess::getPosMoves()
{
	return vector<Board>();
}
