#include "TikTakToe.h"

TikTakToe::TikTakToe(){
    idToChar = {
        {0, '_'},
        {1, 'O'},
        {2, 'X'}
    };

    Figure figP1 = Figure('O', "Kreis", 1);
    Figure figP2 = Figure('X', "Kreuz", 2);
    playerAtTurn = Player("Spieler 1", "O", 1, {figP1});
    playerNotAtTurn = Player("Spieler 1", "X", 2, { figP2 });
}

bool TikTakToe::didWin(int player) {
    char symbol = idToChar[player];

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
                if (board.getSymbolFromPos(currPos) == ' ')
                    return false;
            }
        }
        return true;
    }

    return false;
}

Board TikTakToe::playerOneMove(Board board)
{
    char myToken = 'O';
    int playerID = 1;
    Figure figure = Figure(myToken, "Kreis", playerID);
    Player player = Player("Spieler O", "", playerID, {figure});
    player.figures = { figure };
    return playerDepthFirstSearch(board, player);
}

Board TikTakToe::playerTwoMove(Board board)
{
    char myToken = 'X';
    int playerID = 2;
    Figure figure = Figure(myToken, "Kreuz", playerID);
    Player player = Player("Spieler X", "", playerID, { figure });
    player.figures = { figure };
    return playerDepthFirstSearch(board, player);
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


// globBoard currToken index


Board TikTakToe::playerDepthFirstSearch(Board board, Player player) {
    vector<pair<int, int>> allMoves = getAllPositions();
    vector<pair<int, int>> validMoves;
    char myToken = player.figures[0].getSymbol();
    char gegenToken;
    if (myToken == 'O') gegenToken = 'X';
    else                gegenToken = 'O';
    currToken = gegenToken;


    for (pair<int, int> move : allMoves) {
        if (board.getSymbolFromPos(move) == ' ') validMoves.push_back(move);
    }

    if (validMoves.size() == 0) return board;
    Board boardCopy = board;
    map<pair<int, int>, pair<int, int>> result;
    for (pair<int, int> move : validMoves) {
        board.setFigOnPos(player.figures[0] , move);
        pair<int, int> win;
        win = getOwinXwin(0, 0, board);
        result[move] = win;
        index++;
        board = boardCopy;
    }

    pair<int, int> bestMove;
    double bestQuotient = 0;
    for (pair<int, int> move : validMoves) {
        double quotient = (result[move].first + 0.001) / (result[move].second + 0.001);
        cout << "Move: " << move.first << ": " << move.second << '\n';
        cout << "winsO: " << result[move].first << "winsX: " << result[move].second << '\n';

        quotient = myToken == 'O' ? quotient : (1 / quotient);
        cout << "some" << quotient << '\n';
        if (quotient > bestQuotient) {
            bestQuotient = quotient;
            bestMove = move;
        }
    }

    cout << "best" << bestQuotient << '\n';
    board = boardCopy;
    board.setFigOnPos(player.figures[0], bestMove);
    return board;
}

Figure getFigFromToken(char token) {
    if (token == 'O')
        return Figure(token, "Kreis", 1);
    else if (token == 'X')
        return Figure(token, "Kreuz", 2);
    else
        return Figure(' ', "leer", 0);
}

pair<int, int> TikTakToe::getOwinXwin(int oWin, int xWin, Board board) {
    vector<pair<int, int>> allMoves = getAllPositions();
    vector<pair<int, int>> validMoves;
    for (pair<int, int> move : allMoves) {
        if (board.getSymbolFromPos(move) == ' ') validMoves.push_back(move);
    }

    pair<int, int> res(oWin, xWin);
    if (validMoves.size() == 0) return res;

    if (didWin(1)) {
        res.first++;
        return res;
    }
    if (didWin(2)) {
        res.second++;
        return res;
    }
 

    pair<int, int> winSum;
    for (pair<int, int> move : validMoves) {
        Figure figure = getFigFromToken(currToken);
        board.setFigOnPos(figure, move);
        currToken = currToken == 'O' ? 'X' : 'O';
        pair<int, int> win;
        win = getOwinXwin(oWin, xWin, board);
        currToken = currToken == 'O' ? 'X' : 'O';
        board.setFigOnPos(getFigFromToken(' '), move);
        winSum.first += win.first;
        winSum.second += win.second;
    }
    return winSum;
}

vector<Board> TikTakToe::getPosMoves()
{
    vector<Board> res;
    vector<pair<int, int>> allMoves = getAllPositions();

    for (pair<int, int> pos : allMoves) {
        if (board.getSymbolFromPos(pos) == ' ') {
            Board boardMove = board;
            boardMove.setFigOnPos(playerAtTurn.figures[0], pos);
            res.push_back(boardMove);
        }
    }
    return res;
}
