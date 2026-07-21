#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

class Player 
{
    private:
        string firstName;
        string lastName;
        char piece;
        int wins;
        int losses;
        int draws;

    public:
        Player();
        
        Player(string first, string last, char p);

        string getFirstName();

        string getlastName();

        string getFullName();

        char getPiece();

        int getWins();

        int getLoses();

        int getDraws();

        void setPiece(char p);

        void setNames(string first, string last);

        void incrementWins();

        void incrementLosses();

        void incrementDraws();

        int getFirstNameLength();
};

#endif