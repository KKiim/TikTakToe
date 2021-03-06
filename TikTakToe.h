#pragma once
#include "BoardGame.h"

class TikTakToe :
    public BoardGame
{
public:
    TikTakToe();
    bool didWin(int player) override;
    Board getInitBoard() override;
    vector<Board> getPosMoves();
private:
    map<int, char> idToChar;
    char currToken;
    int index;
};



