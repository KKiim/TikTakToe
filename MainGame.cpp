#include "MainGame.h"
#include "TikTakToe.h"
#include "Chess.h"
#include "Utils.h"

Utils util;


int main()
{
    if (util.getCfgVal("gameName") == "TikTakToe") {
        TikTakToe tikTakToe = TikTakToe();
        cout << startGame(tikTakToe);
    }
    else if ((util.getCfgVal("gameName") == "Chess")) {
        //Chess chess = Chess();
        //cout << startGame(chess);
    }

    cout << cin.get();
}


string startGame(BoardGame& myBoardGame) {
    //string boardString = "2X1O2X:0 1O2X:1O0 0 :\n";
    //string boardString = "2X0 2X:0 1O0 :1O0 0 :\n";
    //string boardString = "0 0 0 :0 0 0 :0 0 0 :\n"; //2X0 0 :0 1O0 : 1O0 0 :
    //string boardString   = "2X0 2X:0 1O0 :1O0 0 :\n";
    //string boardString = "2X2X0 :0 0 0 :0 0 0 :\n";
    //string boardString = "2X2X0 :0 0 0 :1O1O2X:\n";
    //string boardString = "2X0 2X:0 1O0 :1O0 0 :\n";
    string boardString = util.getCfgVal("startBoardString");
    boardString += "\n";



    myBoardGame.board.getBoardFromString(boardString);
    myBoardGame.board.drawBoard();

    while (true) {
        if (myBoardGame.getRoundNo() % 2 == 0) {
            myBoardGame.doAiMove();
        }
        else {
            myBoardGame.doAiMove();
        }
        myBoardGame.board.drawBoard();
        myBoardGame.board.getString();

        if (myBoardGame.didWin(1)) return "Player 1 wins the game!";
        else if (myBoardGame.didWin(2)) return "Player 2 wins the game!";
        else if (myBoardGame.didWin(0)) return "Done!"; // if Player == 0 Wins the game ends in remi(unentschieden)

        myBoardGame.changePlayerAtMove();
        myBoardGame.nextRound();
    }
}