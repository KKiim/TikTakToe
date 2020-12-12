#include "TikTakToe.h"

TikTakToe::TikTakToe(){
    idToChar = {
        {0, '_'},
        {1, 'O'},
        {2, 'X'}
    };

    Figure figP1 = Figure('O', "Kreis", 1);
    Figure figP2 = Figure('X', "Kreuz", 2);
    playerAtTurn    = Player("Spieler 1", "O", 1, {figP1});
    playerNotAtTurn = Player("Spieler 2", "X", 2, { figP2 });
}

bool TikTakToe::didWin(int player) {
    char symbol = ' ';
    if (player != 0) symbol = idToChar[player];

    for (int j = 0; j < board.getWidth(); j++) {
        int count = 0;
        int countInv = 0;
        for (int i = 0; i < board.getHeight(); i++) {
            pair<int, int> currPos(i, j);
            pair<int, int> currPosInv(j, i);
            if (board.getSymbolFromPos(currPos)    == symbol) count++;
            if (board.getSymbolFromPos(currPosInv) == symbol) countInv++;
        }
        if (count == 3 || countInv == 3) return true;
    }

    int count = 0;
    int countDiag = 0;
    for (int i = 0; i < 3; i++) {
        pair<int, int> currPos(i, i);
        pair<int, int> currPosDiag(i, 2 - i);
        if (board.getSymbolFromPos(currPos)     == symbol) count++;
        if (board.getSymbolFromPos(currPosDiag) == symbol) countDiag++;
    }
    if (count == 3 || countDiag == 3) return true;

    if (player == 0) {
        for (int j = 0; j < board.getWidth(); j++) {
            for (int i = 0; i < board.getHeight(); i++) {
                pair<int, int> currPos(i, j);
                if (board.getSymbolFromPos(currPos) == idToChar[0])
                    return false;
            }
        }
        return true;
    }

    return false;
}

Figure getFigFromToken(char token) {
    if (token == 'O')
        return Figure(token, "Kreis", 1);
    else if (token == 'X')
        return Figure(token, "Kreuz", 2);
    else
        return Figure('_', "leer", 0);
}

vector<pair<int, int>> getAllPositions() {
    vector<pair<int, int>> result;
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 3; i++) {
            pair<int, int> currPos(i, j);
            result.push_back(currPos);
        }
    }
    return result;
}

vector<Board> TikTakToe::getPosMoves()
{
    vector<Board> res;
    vector<pair<int, int>> allMoves = getAllPositions();

    for (pair<int, int> pos : allMoves) {
        if (board.getSymbolFromPos(pos) == idToChar[0]) {
            Board boardMove = board;
            boardMove.setFigOnPos(playerAtTurn.figures[0], pos);
            res.push_back(boardMove);
        }
    }
    return res;
}
