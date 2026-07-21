#include "Game.h"

using namespace std;

// ----------------------------------------------------------------------------------
// Prompts both players for first and last names and validates the input format.
// ----------------------------------------------------------------------------------
void Game::initializePlayers()
{
    string fullName;
    string first, last;
    
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

// ----------------------------------------------------------------------------------
// Returns the length of a string.
// ----------------------------------------------------------------------------------
int Game::stringSize(string s)
{
    return s.length();
}

// ----------------------------------------------------------------------------------
// Parses a line into exactly two alphabetic names (first and last); returns true if valid.
// ----------------------------------------------------------------------------------
bool Game::parseTwoNames(string line, string &firstOut, string &lastOut)
{
    int n = stringSize(line);
    int i = 0;

    while (i < n && line[i] == ' ')
    {
        i++;
    }
    if (i >= n) return false;

    firstOut = "";
    while (i < n && line[i] != ' ')
    {
        if (!isalpha(line[i]))
        {
            return false;
        }
        firstOut += line[i];
        i++;
    }
    
    if (firstOut.empty()) return false;

    while (i < n && line[i] == ' ')
    {
        i++;
    }
    if (i >= n) return false;

    lastOut = "";
    while (i < n && line[i] != ' ')
    {
        if (!isalpha(line[i]))
        {
            return false;
        }
        lastOut += line[i];
        i++;
    }
    
    if (lastOut.empty()) return false;

    while (i < n && line[i] == ' ')
    {
        i++;
    }

    if (i < n) return false;

    return true;
}

// ----------------------------------------------------------------------------------
// Prompts player 1 to choose 'x' or 'o' and assigns the opposite piece to player 2.
// ----------------------------------------------------------------------------------
void Game::choosePieces()
{
    char piece;
    string input;
    
    do
    {
        cout << player1.getFirstName() << ", please enter your piece (x or o): ";
        getline(cin, input);
        
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

// ----------------------------------------------------------------------------------
// Determines who starts the first game based on first name length and other comparisons.
// ----------------------------------------------------------------------------------
void Game::determineFirstStarter()
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

// ----------------------------------------------------------------------------------
// Determines who starts the next game based on the last game result.
// ----------------------------------------------------------------------------------
void Game::determineNextStarter()
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

// ----------------------------------------------------------------------------------
// Parses a line into a single integer position; returns true if the input is valid.
// ----------------------------------------------------------------------------------
bool Game::parsePositionInput(string line, int &posOut)
{
    int n = stringSize(line);
    int i = 0;
    
    while (i < n && line[i] == ' ')
    {
        i++;
    }
    if (i >= n) return false;
    
    string numStr = "";
    while (i < n && line[i] != ' ')
    {
        if (!isdigit(line[i]))
        {
            return false;
        }
        numStr += line[i];
        i++;
    }
    
    if (numStr.empty()) return false;
    
    while (i < n && line[i] == ' ')
    {
        i++;
    }
    
    if (i < n) return false;
    
    posOut = 0;
    for (int j = 0; j < numStr.length(); j++)
    {
        posOut = posOut * 10 + (numStr[j] - '0');
    }
    
    return true;
}

// ----------------------------------------------------------------------------------
// Runs one player's turn: prompts, validates, makes the move, and displays the board.
// ----------------------------------------------------------------------------------
void Game::playTurn()
{
    Player& currentPlayer = (currentPlayerIndex == 0) ? player1 : player2;
    string input;
    int position;
    bool validMove = false;
    
    do
    {
        cout << currentPlayer.getFirstName() << ", please select your position: ";
        getline(cin, input);
        
        if (!parsePositionInput(input, position))
        {
            cout << "Invalid input! Please enter a single number between 1 and 9." << endl << endl;
            continue;
        }
        
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

// ----------------------------------------------------------------------------------
// Checks for a win/draw/continue and returns a result code.
// ----------------------------------------------------------------------------------
int Game::checkGameOver()
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

// ----------------------------------------------------------------------------------
// Updates player win/loss/draw statistics based on the result code.
// ----------------------------------------------------------------------------------
void Game::updateStatistics(int result)
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

// ----------------------------------------------------------------------------------
// Displays total games played and each player's win/loss/draw stats.
// ----------------------------------------------------------------------------------
void Game::displayStatistics()
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

// ----------------------------------------------------------------------------------
// Displays the welcome message for the game.
// ----------------------------------------------------------------------------------
void Game::displayWelcome()
{
    cout << "---- Welcome to TicTacToe, please follow each prompt to play ----" << endl << endl;
}

// ----------------------------------------------------------------------------------
// Displays the current game number.
// ----------------------------------------------------------------------------------
void Game::displayGameNumber(){
    cout << "This is game number " << totalGamesPlayed;
}

// ----------------------------------------------------------------------------------
// Switches the current player index from 0 to 1 or 1 to 0.
// ----------------------------------------------------------------------------------
void Game::switchPlayer()
{
    currentPlayerIndex = (currentPlayerIndex == 0) ? 1 : 0;
}

// ----------------------------------------------------------------------------------
// Returns true if the piece is either 'x' or 'o'.
// ----------------------------------------------------------------------------------
bool Game::isValidPiece(char piece)
{
    return (piece == 'x' || piece == 'o');
}

// ----------------------------------------------------------------------------------
// Returns true if the response is Y/y or N/n.
// ----------------------------------------------------------------------------------
bool Game::isValidContinueResponse(char response)
{
    return (response == 'Y' || response == 'y' || response == 'N' || response == 'n');
}

// ----------------------------------------------------------------------------------
// Default constructor: initializes game tracking variables.
// ----------------------------------------------------------------------------------
Game::Game()
{
    currentPlayerIndex = 0;
    totalGamesPlayed = 0;
    firstGameStarterIndex = 0;
    lastGameResult = 0;
}

// ----------------------------------------------------------------------------------
// Runs initial setup: player names, piece selection, and first starter selection.
// ----------------------------------------------------------------------------------
void Game::setup()
{
    initializePlayers();
    choosePieces();
    determineFirstStarter();
}

// ----------------------------------------------------------------------------------
// Plays a single game round until win or draw, then updates stats and starter.
// ----------------------------------------------------------------------------------
void Game::playGame()
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

// ----------------------------------------------------------------------------------
// Runs the full program loop: plays games until the user chooses to stop.
// ----------------------------------------------------------------------------------
void Game::run()
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