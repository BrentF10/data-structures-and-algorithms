#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Board
{
    private:
        char cells[9];
        int moveCount;
        bool winningPositions[9];

        
        int mapPositionToIndex (int pos);

        int mapIndexToPosition(int idx);

    public:
        Board();

        void reset();
        
        bool makeMove(int position, char piece);

        bool isCellEmpty(int position);
        
        char getCellVLaue(int position);

        void display();

        bool checkWin(char piece);

        void markAllWinningPatterns(char piece);

        bool isFull();
        
        int getMoveCount();

        bool isValidPosition(int position);
};

#endif