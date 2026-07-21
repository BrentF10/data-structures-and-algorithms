#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <cctype>
#include "Player.h"
#include "Board.h"

using namespace std;

class Game
{
    private:
        Player player1;
        Player player2;
        Board board;
        int currentPlayerIndex;
        int totalGamesPlayed;
        int firstGameStarterIndex;
        int lastGameResult;


        void initializePlayers();

        int stringSize(string s);

        bool parseTwoNames(string line, string &firstOut, string &lastOut);

        void choosePieces();

        void determineFirstStarter();

        void determineNextStarter();

        bool parsePositionInput(string line, int &posOut);

        void playTurn();

        int checkGameOver();

        void updateStatistics(int result);

        void displayStatistics();

        void displayWelcome();

        void displayGameNumber();

        void switchPlayer();

        bool isValidPiece(char piece);
        
        bool isValidContinueResponse(char response);

    public:
        Game();

        void setup();

        void playGame();

        void run();
};

#endif