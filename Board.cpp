#include "Board.h"

Board::Board() {
    constructHelper(3, 3);
}


Board::Board(int width, int height) {
    constructHelper(width, height);
}

void Board::constructHelper(int width, int height) {
    map<pair<int, int>, Figure> figurePosis;
    Player player0 = Player();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pair<int, int> currentPos(i, j);
            //figurePosis[currentPos].first  = player0;
            //figurePosis[currentPos].second = figure0;
        }
    }
    this->figurePosis = figurePosis;
    this->height = height;
    this->width = width;
}

void Board::drawBoard()
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pair<int, int> currentPos(i, j);
            //string colorModToRed = "\033[" << 32 << "m";
            int playerID = figurePosis[currentPos].playerID;
            char figChar = figurePosis[currentPos].getSymbol();
            if (playerID != 2) cout << figChar << ' ';
            else             cout << "\033[" << 33 << "m" << figChar << ' ';
            cout << "\33[" << 32 << "m"; // setze Farbe auf Standardt siehe GEHT NICHT? https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
        }
        cout << '\n';
    }
    cout << "\33[" << 34 << "m";
    cout << '\n' << "------" << '\n';
}

int Board::getWidth() {
    return width;
}
int Board::getHeight() {
    return height;
}

char Board::getSymbolFromPos(pair<int, int> pos)
{
    return figurePosis[pos].getSymbol();
}

void Board::setFigOnPos(Figure figure, pair<int, int> pos)
{
    figurePosis[pos] = figure;
}

string Board::getString()
{
    string res;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pair<int, int> currentPos(i, j);
            int playerID = figurePosis[currentPos].playerID;
            char figChar = figurePosis[currentPos].getSymbol();
            res += to_string(playerID);
            res += figChar;
        }
        res += ':';
    }
    res += '\n';
    cout << res;
    return res;
}

void Board::getBoardFromString(string input)
{
    int count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pair<int, int> currentPos(i, j);
            int playerID = input.at(count++) - '0';//(i + j * width) * 2) + j;
            char figChar = input.at(count++);//((i + j * width) * 2) + 1) + j;
            Figure fig = Figure(figChar, "Joe", playerID);
            figurePosis[currentPos] = fig;
        }
        count++; //input += '\n';
    }
    cout << input;
    return;
}