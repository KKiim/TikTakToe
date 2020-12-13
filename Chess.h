#pragma once
#include "BoardGame.h"

class Chess :
    public BoardGame
{
public:
    Chess();
    bool didWin(int player) override;
    Board getInitBoard() override;
    vector<Board> getPosMoves();
};

