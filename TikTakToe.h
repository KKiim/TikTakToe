#pragma once
#include "BoardGame.h"

class TikTakToe :
    public BoardGame
{
public:
    TikTakToe();
    bool didWin(int player) override;
    Board playerOneMove(Board board) override;
    Board playerTwoMove(Board board) override;
    Board playerDepthFirstSearch(Board board, Player player);
    pair<int, int> getOwinXwin(int oWin, int xWin, Board board);
    vector<Board> getPosMoves();
private:
    map<int, char> idToChar;
    char currToken;
    int index;
};



