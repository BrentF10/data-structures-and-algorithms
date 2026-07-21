#include <iostream>
#include <string>
#include <cctype>

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
        Player()
        {
            firstName = "";
            lastName = "";
            piece = ' ';
            wins = 0;
            losses = 0;
            draws = 0;
        }
        
        Player(string first, string last, char p)
        {
            firstName = first;
            lastName = last;
            piece = p;
        }

        string getFirstName()
        {
            return firstName;
        }

        string getlastName()
        {
            return lastName;
        }

        string getFullName()
        {
            return firstName + " " + lastName;
        }

        char getPiece()
        {
            return piece;
        }

        int getWins()
        {
            return wins;
        }

        int getLoses()
        {
            return losses;
        }

        int getDraws()
        {
            return draws;
        }

        void setPiece(char p)
        {
            piece = p;
        }

        void setNames(string first, string last)
        {
            firstName = first;
            lastName = last;
        }

        void incrementWins()
        {
            wins = wins + 1;
        }

        void incrementLosses()
        {
            losses = losses + 1;
        }

        void incrementDraws()
        {
            draws = draws + 1;
        }

        int getFirstNameLength()
        {
            return firstName.size();
        }


};

class Board
{
    private:
        char cells[9];
        int moveCount;
        bool winningPositions[9];

        int mapPositionToIndex (int pos)
        {
            switch (pos)
            {
                case 1:
                return 0;

                case 2:
                return 2;

                case 3:
                return 6;

                case 4:
                return 8;

                case 5:
                return 4;

                case 6:
                return 1;

                case 7:
                return 3;

                case 8:
                return 5;

                case 9:
                return 7;

                default:
                return -1;
            }
        }

        int mapIndexToPosition(int idx)
        {
            switch (idx)
            {
                case 0:
                return 1;

                case 1:
                return 6;

                case 2:
                return 2;
                
                case 3:
                return 7;

                case 4:
                return 5;

                case 5:
                return 8;

                case 6:
                return 3;

                case 7:
                return 9;

                case 8:
                return 4;

                default:
                return -1;
            }
        }
        public:
            Board()
            {
                for (int i = 0; i < 9; i++)
                {
                    cells[i] = ' ';
                    winningPositions[i] = false;
                }
                moveCount = 0;
            }

            void reset()
            {
                for (int i=0; i < 9; i++)
                {
                    cells[i] = ' ';
                    winningPositions[i] = false;

                }
                moveCount = 0;
            }
            
            bool makeMove(int position, char piece)
            {
                int index = mapPositionToIndex(position);
                if (cells[index]==' ')
                {
                    cells[index] = piece;
                    moveCount = moveCount + 1;
                    return true;
                }
                return false;
            }

            bool isCellEmpty(int position)
            {
                if (cells[position]==' ')
                {
                    return true;
                }
                return false;
            }
            
            char getCellVLaue(int position)
            {
                return cells[position];
            }

            void display()
            {
                cout << endl;
                cout << "+---+---+---+" << endl;
                cout << "| " << (cells[0] == ' ' ? '1' : cells[0]) << " | " 
                    << (cells[1] == ' ' ? '6' : cells[1]) << " | " 
                    << (cells[2] == ' ' ? '2' : cells[2]) << " |" << endl;
                cout << "+---+---+---+" << endl;
                cout << "| " << (cells[3] == ' ' ? '7' : cells[3]) << " | " 
                    << (cells[4] == ' ' ? '5' : cells[4]) << " | " 
                    << (cells[5] == ' ' ? '8' : cells[5]) << " |" << endl;
                cout << "+---+---+---+" << endl;
                cout << "| " << (cells[6] == ' ' ? '3' : cells[6]) << " | " 
                    << (cells[7] == ' ' ? '9' : cells[7]) << " | " 
                    << (cells[8] == ' ' ? '4' : cells[8]) << " |" << endl;
                cout << "+---+---+---+" << endl << endl;
            }

            bool checkWin(char piece)
            {
                if (cells[0] == piece && cells[1] == piece && cells[2] == piece) 
                {
                    return true;
                }

                if (cells[3] == piece && cells[4] == piece && cells[5] == piece) 
                {
                    return true;
                }

                if (cells[6] == piece && cells[7] == piece && cells[8] == piece) 
                {
                    return true;
                }

                if (cells[0] == piece && cells[3] == piece && cells[6] == piece) 
                {
                    return true;
                }

                if (cells[1] == piece && cells[4] == piece && cells[7] == piece) 
                {
                    return true;
                }

                if (cells[2] == piece && cells[5] == piece && cells[8] == piece) 
                {
                    return true;
                }

                if (cells[0] == piece && cells[4] == piece && cells[8] == piece) 
                {
                    return true;
                }

                if (cells[2] == piece && cells[4] == piece && cells[6] == piece) 
                {
                    return true;
                }
                return false;
            }

            void markAllWinningPatterns(char piece)
            {
                if (cells[0] == piece && cells[1] == piece && cells[2] == piece) 
                {
                    cells[0] = toupper(cells[0]);
                    cells[1] = toupper(cells[1]);
                    cells[2] = toupper(cells[2]);
                }

                if (cells[3] == piece && cells[4] == piece && cells[5] == piece) 
                {
                    cells[3] = toupper(cells[3]);
                    cells[4] = toupper(cells[4]);
                    cells[5] = toupper(cells[5]);
                }

                if (cells[6] == piece && cells[7] == piece && cells[8] == piece) 
                {
                    cells[6] = toupper(cells[6]);
                    cells[7] = toupper(cells[7]);
                    cells[8] = toupper(cells[8]);
                }

                if (cells[0] == piece && cells[3] == piece && cells[6] == piece) 
                {
                    cells[0] = toupper(cells[0]);
                    cells[3] = toupper(cells[3]);
                    cells[6] = toupper(cells[6]);
                }

                if (cells[1] == piece && cells[4] == piece && cells[7] == piece) 
                {
                    cells[1] = toupper(cells[1]);
                    cells[4] = toupper(cells[4]);
                    cells[7] = toupper(cells[7]);
                }

                if (cells[2] == piece && cells[5] == piece && cells[8] == piece) 
                {
                    cells[2] = toupper(cells[2]);
                    cells[5] = toupper(cells[5]);
                    cells[8] = toupper(cells[8]);
                }

                if (cells[0] == piece && cells[4] == piece && cells[8] == piece) 
                {
                    cells[0] = toupper(cells[0]);
                    cells[4] = toupper(cells[4]);
                    cells[8] = toupper(cells[8]);
                }

                if (cells[2] == piece && cells[4] == piece && cells[6] == piece) 
                {
                    cells[2] = toupper(cells[2]);
                    cells[4] = toupper(cells[4]);
                    cells[6] = toupper(cells[6]);
                }
            }

            bool isFull()
            {
                for (int i=0; i < 9; i++)
                {
                    if (cells[i]==' ')
                    {
                        return false;
                    }
                }
                return true;
            }
            
            int getMoveCount()
            {
                return moveCount;
            }

            bool isValidPosition(int position)
            {
                // Check if position is in range 1-9
                if (position < 1 || position > 9)
                {
                    return false;
                }
                
                // Check if the cell at that position is empty
                int index = mapPositionToIndex(position);
                return (cells[index] == ' ');
            }
};

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

        void initializePlayers()
        {
            string fullName;
            string first, last;
            
            // Player 1
            do
            {
                cout << "Player 1 please enter your first and last name: ";
                getline(cin, fullName);
                
                if (!parseTwoNames(fullName, first, last))
                {
                    cout << "Invalid name! Name must contain only letters with exactly one space between first and last name." << endl;
                    cout << "Please try again." << endl << endl;
                }
                
            } while (!parseTwoNames(fullName, first, last));
            
            player1.setNames(first, last);
            cout << endl;
            
            // Player 2
            do
            {
                cout << "Player 2 please enter your first and last name: ";
                getline(cin, fullName);
                
                if (!parseTwoNames(fullName, first, last))
                {
                    cout << "Invalid name! Name must contain only letters with exactly one space between first and last name." << endl;
                    cout << "Please try again." << endl << endl;
                }
                
            } while (!parseTwoNames(fullName, first, last));
            
            player2.setNames(first, last);
            cout << endl;
        }

    
    int stringSize(string s)
    {
        return s.length();
    }
    
    bool parseTwoNames(string line, string &firstOut, string &lastOut)
    {
        int n = stringSize(line);
        int i = 0;

        // Skip leading spaces
        while (i < n && line[i] == ' ')
        {
            i++;
        }
        if (i >= n) return false;  // Empty line

        // Extract first name
        firstOut = "";
        while (i < n && line[i] != ' ')
        {
            if (!isalpha(line[i]))  // Must be a letter
            {
                return false;
            }
            firstOut += line[i];
            i++;
        }
        
        if (firstOut.empty()) return false;  // No first name found

        // Skip spaces between first and last name
        while (i < n && line[i] == ' ')
        {
            i++;
        }
        if (i >= n) return false;  // No last name

        // Extract last name
        lastOut = "";
        while (i < n && line[i] != ' ')
        {
            if (!isalpha(line[i]))  // Must be a letter
            {
                return false;
            }
            lastOut += line[i];
            i++;
        }
        
        if (lastOut.empty()) return false;  // No last name found

        // Skip trailing spaces
        while (i < n && line[i] == ' ')
        {
            i++;
        }

        // If we haven't reached the end, there are extra tokens
        if (i < n) return false;

        return true;
    }

        void choosePieces()
        {
            char piece;
            string input;
            
            do
            {
                cout << player1.getFirstName() << ", please enter your piece (x or o): ";
                getline(cin, input);
                
                // Check if input is exactly one character
                if (input.length() != 1)
                {
                    cout << "Invalid piece! Please enter exactly one character ('x' or 'o')." << endl << endl;
                    continue;
                }
                
                piece = input[0];
                
                if (!isValidPiece(piece))
                {
                    cout << "Invalid piece! Please enter 'x' or 'o' only." << endl << endl;
                }
                
            } while (!isValidPiece(piece) || input.length() != 1);
            
            cout << endl;
            player1.setPiece(piece);
            
            if (piece == 'x')
            {
                player2.setPiece('o');
            }
            else
            {
                player2.setPiece('x');
            }
            
            cout << player1.getFirstName() << " will be: " << player1.getPiece() << endl;
            cout << player2.getFirstName() << " will be: " << player2.getPiece() << endl << endl;
        }

        void determineFirstStarter()
        {
            if (player1.getFirstNameLength() < player2.getFirstNameLength()||player1.getFirstNameLength() == player2.getFirstNameLength())
            {
                currentPlayerIndex = 0;
                firstGameStarterIndex = 0;
                cout << player1.getFirstName() << " will start" << endl;
            }
            else if (player2.getFirstName() < player1.getFirstName())
            {
                currentPlayerIndex = 1;
                firstGameStarterIndex = 1;
                cout << player2.getFirstName() << " will start" << endl;
            }
        }

        void determineNextStarter()
        {
            if (lastGameResult == 1)
            {
                currentPlayerIndex = 1;
                cout << player2.getFirstName() << " will start the next game" << endl;
            }
            else if (lastGameResult == 2)
            {
                currentPlayerIndex = 0;
                cout << player1.getFirstName() << " will start the next game" << endl;
            }
            else
            {
                currentPlayerIndex = (firstGameStarterIndex == 0) ? 1 : 0;
                firstGameStarterIndex = currentPlayerIndex;
                Player& nextStarter = (currentPlayerIndex == 0) ? player1 : player2;
                cout << nextStarter.getFirstName() << " will start the next game" << endl;
            }
        }

        bool parsePositionInput(string line, int &posOut)
        {
            int n = stringSize(line);
            int i = 0;
            
            // Skip leading spaces
            while (i < n && line[i] == ' ')
            {
                i++;
            }
            if (i >= n) return false;  // Empty input
            
            // Extract the number
            string numStr = "";
            while (i < n && line[i] != ' ')
            {
                if (!isdigit(line[i]))  // Must be a digit
                {
                    return false;
                }
                numStr += line[i];
                i++;
            }
            
            if (numStr.empty()) return false;
            
            // Skip trailing spaces
            while (i < n && line[i] == ' ')
            {
                i++;
            }
            
            // If we haven't reached the end, there are extra tokens
            if (i < n) return false;
            
            // Convert string to integer
            posOut = 0;
            for (int j = 0; j < numStr.length(); j++)
            {
                posOut = posOut * 10 + (numStr[j] - '0');
            }
            
            return true;
        }

        void playTurn()
        {
            Player& currentPlayer = (currentPlayerIndex == 0) ? player1 : player2;
            string input;
            int position;
            bool validMove = false;
            
            do
            {
                cout << currentPlayer.getFirstName() << ", please select your position: ";
                getline(cin, input);
                
                // Check if input can be converted to a single integer
                if (!parsePositionInput(input, position))
                {
                    cout << "Invalid input! Please enter a single number between 1 and 9." << endl << endl;
                    continue;
                }
                
                // Check if position is valid (1-9 and cell is empty)
                if (!board.isValidPosition(position))
                {
                    if (position < 1 || position > 9)
                    {
                        cout << "Invalid position! Please enter a number between 1 and 9." << endl << endl;
                    }
                    else
                    {
                        cout << "That position is already taken! Please choose another position." << endl << endl;
                    }
                }
                else
                {
                    validMove = true;
                }
                
            } while (!validMove);
            
            board.makeMove(position, currentPlayer.getPiece());
            board.display();
        }

        int checkGameOver()
        {
            if(board.checkWin(player1.getPiece()))
            {
                return 1;
            }
            else if (board.checkWin(player2.getPiece()))
            {
                return 2;
            }
            else if (board.isFull())
            {
                return 3;
            }
            else
            {
                return 0;
            }
        }

        void updateStatistics(int result)
        {
            if (result == 0)
            {
                return;
            }
            else if (result == 1)
            {
                player1.incrementWins();
                player2.incrementLosses();
            }
            else if (result == 2)
            {
                player2.incrementWins();
                player1.incrementLosses();
            }
            else
            {
                player1.incrementDraws();
                player2.incrementDraws();
            }
        }


        void displayStatistics()
        {
            cout << "Total Games Played: " << totalGamesPlayed << endl << endl;
           
            cout << player1.getFullName() << "'s stats: " << endl;
            cout << "Wins: " << player1.getWins() << endl;
            cout << "Losses: " << player1.getLoses() << endl;
            cout << "Draws: " << player1.getDraws() << endl << endl;
            
            cout << player2.getFullName() << "'s stats: " << endl;
            cout << "Wins: " << player2.getWins() << endl;
            cout << "Losses: " << player2.getLoses() << endl;
            cout << "Draws: " << player2.getDraws() << endl << endl;

        }

        void displayWelcome()
        {
            cout << "---- Welcome to TicTacToe, please follow each prompt to play ----" << endl << endl;
        }

        void displayGameNumber(){
            cout << "This is game number " << totalGamesPlayed;
        }

        void switchPlayer()
        {
            currentPlayerIndex = (currentPlayerIndex == 0) ? 1 : 0;
        }


        
        bool isValidPiece(char piece)
        {
            return (piece == 'x' || piece == 'o');
        }
        
        bool isValidContinueResponse(char response)
        {
            return (response == 'Y' || response == 'y' || response == 'N' || response == 'n');
        }

    public:
        Game()
        {
            currentPlayerIndex = 0;
            totalGamesPlayed = 0;
            firstGameStarterIndex = 0;
            lastGameResult = 0;
        }

        void setup()
        {
            initializePlayers();
            choosePieces();
            determineFirstStarter();
        }

        void playGame()
        {
            board.reset();
            totalGamesPlayed++;
            
            cout << "Total games played: " << totalGamesPlayed << endl;
            board.display();
            
            while (true)
            {
                playTurn();
                
                int result = checkGameOver();
                
                if (result != 0) 
                {
                    if (result == 1)
                    {
                        cout << endl << player1.getFullName() << " wins!" << endl;
                        board.markAllWinningPatterns(player1.getPiece());
                        board.display();
                    }
                    else if (result == 2)
                    {
                        cout << endl << player2.getFullName() << " wins!" << endl;
                        board.markAllWinningPatterns(player2.getPiece());
                        board.display();
                    }
                    else
                    {
                        cout << endl << "It's a draw!" << endl;
                    }
                    
                    updateStatistics(result);
                    lastGameResult = result;
                    break;
                }
                
                switchPlayer();
            }
            
            displayStatistics();
            determineNextStarter();
        }

        void run()
        {
            displayWelcome();
            char again;
            string input;
            
            do
            {
                playGame();
                
                do
                {
                    cout << endl << "Would you like to play another game? (Y/N): ";
                    getline(cin, input);
                    
                    // Check if input is exactly one character
                    if (input.length() != 1)
                    {
                        cout << "Invalid input! Please enter exactly one character ('Y' or 'N')." << endl;
                        continue;
                    }
                    
                    again = input[0];
                    
                    if (!isValidContinueResponse(again))
                    {
                        cout << "Invalid input! Please enter 'Y' for yes or 'N' for no." << endl;
                    }
                    
                } while (!isValidContinueResponse(again) || input.length() != 1);
                
                cout << endl;
                
            } while (again == 'Y' || again == 'y');
            
            cout << "Thanks for playing!" << endl;
        }



};

int main()
{
    Game game;           
    game.setup();        
    game.run();
    return 0;
}