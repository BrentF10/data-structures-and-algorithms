#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

const int MIN_PLAYERS = 3;
const int MAX_PLAYERS = 8;
const int MIN_ROWS = 4;
const int MAX_ROWS = 11;
const int MIN_COLS = 4;
const int MAX_COLS = 14;
const int MAX_GAMES_DISPLAY = 1000;

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


    //------------------------------------------------------------------------------------
    //Sets the player's first name
    //------------------------------------------------------------------------------------

    void setFirstName(string f)
    {
        firstName = f;
    }


    //------------------------------------------------------------------------------------
    //Sets the player's last name
    //------------------------------------------------------------------------------------

    void setLastName(string l)
    {
        lastName = l;
    }


    //------------------------------------------------------------------------------------
    //Sets the player's game piece
    //------------------------------------------------------------------------------------

    void setPiece(char p)
    {
        piece = p;
    }


    //------------------------------------------------------------------------------------
    //Returns the player's first name
    //------------------------------------------------------------------------------------

    string getFirstName() const
    {
        return firstName;
    }


    //------------------------------------------------------------------------------------
    //Returns the player's last name
    //------------------------------------------------------------------------------------

    string getLastName() const
    {
        return lastName;
    }


    //------------------------------------------------------------------------------------
    //Returns the player's full name
    //------------------------------------------------------------------------------------

    string getFullName() const
    {
        return firstName + " " + lastName;
    }


    //------------------------------------------------------------------------------------
    //Returns the player's game piece
    //------------------------------------------------------------------------------------

    char getPiece() const
    {
        return piece;
    }


    //------------------------------------------------------------------------------------
    //Returns the player's number of wins
    //------------------------------------------------------------------------------------

    int getWins() const
    {
        return wins;
    }


    //------------------------------------------------------------------------------------
    //Returns the player's number of losses
    //------------------------------------------------------------------------------------

    int getLosses() const
    {
        return losses;
    }


    //------------------------------------------------------------------------------------
    //Returns the player's number of draws
    //------------------------------------------------------------------------------------

    int getDraws() const
    {
        return draws;
    }


    //------------------------------------------------------------------------------------
    //Adds one win to the player's record
    //------------------------------------------------------------------------------------

    void addWin()
    {
        wins++;
    }


    //------------------------------------------------------------------------------------
    //Adds one loss to the player's record
    //------------------------------------------------------------------------------------

    void addLoss()
    {
        losses++;
    }


    //------------------------------------------------------------------------------------
    //Adds one draw to the player's record
    //------------------------------------------------------------------------------------

    void addDraw()
    {
        draws++;
    }
};

class Board
{
private:
    char cells[MAX_ROWS * MAX_COLS];
    int rows;
    int cols;

public:
    Board()
    {
        rows = 0;
        cols = 0;
        clear();
    }


    //------------------------------------------------------------------------------------
    //Sets the board size and clears the board
    //------------------------------------------------------------------------------------

    void setSize(int r, int c)
    {
        rows = r;
        cols = c;
        clear();
    }


    //------------------------------------------------------------------------------------
    //Clears all cells on the board
    //------------------------------------------------------------------------------------

    void clear()
    {
        for (int i = 0; i < MAX_ROWS * MAX_COLS; i++)
        {
            cells[i] = ' ';
        }
    }


    //------------------------------------------------------------------------------------
    //Returns the number of rows on the board
    //------------------------------------------------------------------------------------

    int getRows() const
    {
        return rows;
    }


    //------------------------------------------------------------------------------------
    //Returns the number of columns on the board
    //------------------------------------------------------------------------------------

    int getCols() const
    {
        return cols;
    }


    //------------------------------------------------------------------------------------
    //Converts a row and column into the array index
    //------------------------------------------------------------------------------------

    int index(int row, int col) const
    {
        return row * cols + col;
    }


    //------------------------------------------------------------------------------------
    //Returns the character stored in a board cell
    //------------------------------------------------------------------------------------

    char getCell(int row, int col) const
    {
        return cells[index(row, col)];
    }


    //------------------------------------------------------------------------------------
    //Determines whether a position is inside the board
    //------------------------------------------------------------------------------------

    bool isInside(int row, int col) const
    {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    }


    //------------------------------------------------------------------------------------
    //Determines whether a board cell is empty
    //------------------------------------------------------------------------------------

    bool isEmpty(int row, int col) const
    {
        return getCell(row, col) == ' ';
    }


    //------------------------------------------------------------------------------------
    //Places a piece in the specified board cell
    //------------------------------------------------------------------------------------

    void placePiece(int row, int col, char piece)
    {
        cells[index(row, col)] = piece;
    }


    //------------------------------------------------------------------------------------
    //Determines whether the board is completely full
    //------------------------------------------------------------------------------------

    bool isFull() const
    {
        for (int i = 0; i < rows * cols; i++)
        {
            if (cells[i] == ' ')
            {
                return false;
            }
        }
        return true;
    }


    //------------------------------------------------------------------------------------
    //Displays the current board
    //------------------------------------------------------------------------------------

    void display() const
    {
        cout << "\n";
        cout << "   ";
        for (int c = 1; c <= cols; c++)
        {
            if (c < 10)
            {
                cout << " " << c << "  ";
            }
            else
            {
                cout << " " << c << " ";
            }
        }
        cout << "\n";

        cout << "   ";
        for (int c = 0; c < cols; c++)
        {
            cout << "--- ";
        }
        cout << "\n";

        for (int r = 0; r < rows; r++)
        {
            char rowLabel = 'A' + r;
            cout << rowLabel << " |";
            for (int c = 0; c < cols; c++)
            {
                cout << setw(2) << getCell(r, c) << " |";
            }
            cout << " " << rowLabel << "\n";

            cout << "   ";
            for (int c = 0; c < cols; c++)
            {
                cout << "--- ";
            }
            cout << "\n";
        }

        cout << "   ";
        for (int c = 1; c <= cols; c++)
        {
            if (c < 10)
            {
                cout << " " << c << "  ";
            }
            else
            {
                cout << " " << c << " ";
            }
        }
        cout << "\n";
    }


    //------------------------------------------------------------------------------------
    //Checks for three matching pieces in a given direction
    //------------------------------------------------------------------------------------

    bool hasThreeInDirection(int row, int col, int dr, int dc, char piece) const
    {
        for (int step = 0; step < 3; step++)
        {
            int nr = row + dr * step;
            int nc = col + dc * step;
            if (!isInside(nr, nc) || tolower(getCell(nr, nc)) != tolower(piece))
            {
                return false;
            }
        }
        return true;
    }


    //------------------------------------------------------------------------------------
    //Determines whether the given piece has a winning configuration
    //------------------------------------------------------------------------------------

    bool hasWinningConfiguration(char piece) const
    {
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                if (tolower(getCell(r, c)) == tolower(piece))
                {
                    if (hasThreeInDirection(r, c, 0, 1, piece) ||
                        hasThreeInDirection(r, c, 1, 0, piece) ||
                        hasThreeInDirection(r, c, 1, 1, piece) ||
                        hasThreeInDirection(r, c, 1, -1, piece))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }


    //------------------------------------------------------------------------------------
    //Marks all winning pieces in uppercase
    //------------------------------------------------------------------------------------

    void markWinningConfigurations(char piece)
    {
        bool winningMarks[MAX_ROWS * MAX_COLS];
        for (int i = 0; i < MAX_ROWS * MAX_COLS; i++)
        {
            winningMarks[i] = false;
        }

        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                if (tolower(getCell(r, c)) == tolower(piece))
                {
                    int dirs[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
                    for (int d = 0; d < 4; d++)
                    {
                        int dr = dirs[d][0];
                        int dc = dirs[d][1];
                        if (hasThreeInDirection(r, c, dr, dc, piece))
                        {
                            for (int step = 0; step < 3; step++)
                            {
                                int nr = r + dr * step;
                                int nc = c + dc * step;
                                winningMarks[index(nr, nc)] = true;
                            }
                        }
                    }
                }
            }
        }

        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                int i = index(r, c);
                if (winningMarks[i])
                {
                    cells[i] = toupper(cells[i]);
                }
            }
        }
    }
};

class Game
{
private:
    Player players[MAX_PLAYERS];
    int playerCount;
    Board board;
    int totalGamesPlayed;
    int starterIndex;

public:
    Game()
    {
        playerCount = 0;
        totalGamesPlayed = 0;
        starterIndex = 0;
    }


    //------------------------------------------------------------------------------------
    //Runs the full game program
    //------------------------------------------------------------------------------------

    void run()
    {
        initializePlayers();
        starterIndex = findFirstGameStarter();

        bool keepPlaying = true;
        while (keepPlaying)
        {
            int rows;
            int cols;
            getBoardDimensions(rows, cols);
            board.setSize(rows, cols);
            board.display();

            int winnerIndex = -1;
            bool draw = false;
            playOneGame(winnerIndex, draw);
            totalGamesPlayed++;
            updateStatistics(winnerIndex, draw);
            displayStatistics();
            starterIndex = determineNextStarter(winnerIndex, draw);
            keepPlaying = askPlayAgain();
        }

        cout << "\nThank you for playing.\n";
    }

private:


    //------------------------------------------------------------------------------------
    //Determines whether a string contains letters only
    //------------------------------------------------------------------------------------

    bool isLettersOnly(const string &text) const
    {
        if (text.length() == 0)
        {
            return false;
        }

        for (unsigned int i = 0; i < text.length(); i++)
        {
            if (!isalpha(text[i]))
            {
                return false;
            }
        }
        return true;
    }


    //------------------------------------------------------------------------------------
    //Formats a name with proper capitalization
    //------------------------------------------------------------------------------------

    string formatName(string name) const
    {
        for (unsigned int i = 0; i < name.length(); i++)
        {
            if (i == 0)
            {
                name[i] = toupper(name[i]);
            }
            else
            {
                name[i] = tolower(name[i]);
            }
        }
        return name;
    }


    //------------------------------------------------------------------------------------
    //Parses a full name into first and last name
    //------------------------------------------------------------------------------------

    bool parseFullName(const string &line, string &first, string &last) const
    {
        first = "";
        last = "";
        int i = 0;
        int n = static_cast<int>(line.length());

        while (i < n && line[i] == ' ')
        {
            i++;
        }

        while (i < n && line[i] != ' ')
        {
            first += line[i];
            i++;
        }

        while (i < n && line[i] == ' ')
        {
            i++;
        }

        while (i < n && line[i] != ' ')
        {
            last += line[i];
            i++;
        }

        while (i < n)
        {
            if (line[i] != ' ')
            {
                return false;
            }
            i++;
        }

        if (!isLettersOnly(first) || !isLettersOnly(last))
        {
            return false;
        }

        return true;
    }


    //------------------------------------------------------------------------------------
    //Reads and validates an integer line of input
    //------------------------------------------------------------------------------------

    int readIntegerLine(const string &prompt, int minValue, int maxValue)
    {
        string line;
        int value = 0;
        bool valid = false;

        while (!valid)
        {
            cout << prompt;
            getline(cin, line);

            if (parseInteger(line, value) && value >= minValue && value <= maxValue)
            {
                valid = true;
            }
            else
            {
                cout << "Invalid input. Please try again.\n\n";
            }
        }

        return value;
    }


    //------------------------------------------------------------------------------------
    //Parses a string as an integer
    //------------------------------------------------------------------------------------

    bool parseInteger(const string &line, int &value) const
    {
        value = 0;
        int i = 0;
        int n = static_cast<int>(line.length());

        while (i < n && line[i] == ' ')
        {
            i++;
        }

        if (i >= n)
        {
            return false;
        }

        int sign = 1;
        if (line[i] == '+')
        {
            i++;
        }
        else if (line[i] == '-')
        {
            sign = -1;
            i++;
        }

        if (i >= n || !isdigit(line[i]))
        {
            return false;
        }

        while (i < n && isdigit(line[i]))
        {
            value = value * 10 + (line[i] - '0');
            i++;
        }

        while (i < n && line[i] == ' ')
        {
            i++;
        }

        if (i != n)
        {
            return false;
        }

        value *= sign;
        return true;
    }


    //------------------------------------------------------------------------------------
    //Initializes all players and their pieces
    //------------------------------------------------------------------------------------

    void initializePlayers()
    {
        cout << "Enter the number of players -> ";
        string line;
        int count = 0;
        bool validCount = false;

        while (!validCount)
        {
            getline(cin, line);
            if (parseInteger(line, count) && count >= MIN_PLAYERS && count <= MAX_PLAYERS)
            {
                playerCount = count;
                validCount = true;
            }
            else
            {
                cout << "Invalid input. Please enter a number from 3 to 8.\n";
                cout << "Enter the number of players -> ";
            }
        }

        cout << "\nPlease enter each player's first and last name.\n\n";

        for (int i = 0; i < playerCount; i++)
        {
            string fullLine;
            string first;
            string last;
            bool validName = false;

            while (!validName)
            {
                cout << "Player " << (i + 1) << " -> ";
                getline(cin, fullLine);
                if (parseFullName(fullLine, first, last))
                {
                    players[i].setFirstName(formatName(first));
                    players[i].setLastName(formatName(last));
                    players[i].setPiece('z' - i);
                    validName = true;
                    cout << "\n";
                }
                else
                {
                    cout << "Invalid input. Please enter a first and last name using letters only.\n";
                }
            }
        }
    }


    //------------------------------------------------------------------------------------
    //Finds the starting player for the first game (player with piece 'x')
    //------------------------------------------------------------------------------------

    int findFirstGameStarter() const
    {
        for (int i = 0; i < playerCount; i++)
        {
            if (players[i].getPiece() == 'x')
            {
                return i;
            }
        }
        return 0;
    }


    //------------------------------------------------------------------------------------
    //Gets the board dimensions from the user
    //------------------------------------------------------------------------------------

    void getBoardDimensions(int &rows, int &cols)
    {
        cout << "\nPlease enter the dimension of the board.\n\n";
        rows = readIntegerLine("Enter the number of rows    -> ", MIN_ROWS, MAX_ROWS);
        cout << "\n";
        cols = readIntegerLine("Enter the number of columns -> ", MIN_COLS, MAX_COLS);
        cout << "\n";
    }


    //------------------------------------------------------------------------------------
    //Parses a move entered by the user
    //------------------------------------------------------------------------------------

    bool parseMove(const string &line, int &row, int &col) const
    {
        string trimmed = trim(line);
        if (trimmed.length() < 2 || trimmed.length() > 3)
        {
            return false;
        }

        char rowChar = trimmed[0];
        if (!isalpha(rowChar))
        {
            return false;
        }

        rowChar = toupper(rowChar);
        row = rowChar - 'A';

        string numberPart = "";
        for (unsigned int i = 1; i < trimmed.length(); i++)
        {
            if (!isdigit(trimmed[i]))
            {
                return false;
            }
            numberPart += trimmed[i];
        }

        int number = 0;
        if (!parseInteger(numberPart, number))
        {
            return false;
        }

        col = number - 1;
        return true;
    }


    //------------------------------------------------------------------------------------
    //Removes leading and trailing spaces from a string
    //------------------------------------------------------------------------------------

    string trim(const string &line) const
    {
        int start = 0;
        int end = static_cast<int>(line.length()) - 1;

        while (start <= end && line[start] == ' ')
        {
            start++;
        }
        while (end >= start && line[end] == ' ')
        {
            end--;
        }

        if (start > end)
        {
            return "";
        }

        string result = "";
        for (int i = start; i <= end; i++)
        {
            result += line[i];
        }
        return result;
    }


    //------------------------------------------------------------------------------------
    //Plays one full game until there is a winner or a draw
    //------------------------------------------------------------------------------------

    void playOneGame(int &winnerIndex, bool &draw)
    {
        winnerIndex = -1;
        draw = false;
        int current = starterIndex;
        bool gameOver = false;

        while (!gameOver)
        {
            int row;
            int col;
            getValidMove(current, row, col);
            board.placePiece(row, col, players[current].getPiece());

            if (board.hasWinningConfiguration(players[current].getPiece()))
            {
                board.markWinningConfigurations(players[current].getPiece());
                board.display();
                cout << "\n" << players[current].getFirstName() << " wins!\n";
                winnerIndex = current;
                gameOver = true;
            }
            else
            {
                board.display();

                if (board.isFull())
                {
                    cout << "\nThe game is a draw.\n";
                    draw = true;
                    gameOver = true;
                }
                else
                {
                    current = (current + 1) % playerCount;
                }
            }
        }
    }


    //------------------------------------------------------------------------------------
    //Gets a valid move from the current player
    //------------------------------------------------------------------------------------

    void getValidMove(int playerIndex, int &row, int &col)
    {
        string line;
        bool validMove = false;

        while (!validMove)
        {
            cout << players[playerIndex].getFirstName() << ", enter your move -> ";
            getline(cin, line);

            if (parseMove(line, row, col) &&
                board.isInside(row, col) &&
                board.isEmpty(row, col))
            {
                validMove = true;
            }
            else
            {
                cout << "Invalid input. Please try again.\n";
            }
        }
    }


    //------------------------------------------------------------------------------------
    //Updates the player statistics after a game
    //------------------------------------------------------------------------------------

    void updateStatistics(int winnerIndex, bool draw)
    {
        if (draw)
        {
            for (int i = 0; i < playerCount; i++)
            {
                players[i].addDraw();
            }
        }
        else
        {
            for (int i = 0; i < playerCount; i++)
            {
                if (i == winnerIndex)
                {
                    players[i].addWin();
                }
                else
                {
                    players[i].addLoss();
                }
            }
        }
    }


    //------------------------------------------------------------------------------------
    //Displays the game statistics table
    //------------------------------------------------------------------------------------

    void displayStatistics() const
    {
        int widestName = 0;
        for (int i = 0; i < playerCount; i++)
        {
            int len = static_cast<int>(players[i].getFullName().length());
            if (len > widestName)
            {
                widestName = len;
            }
        }

        string tableLine = "---------------------";

        cout << "\nTotal game played = " << totalGamesPlayed << "\n\n";

        cout << string(widestName + 2, ' ') << tableLine << "\n";
        cout << string(widestName + 2, ' ') << "| WIN | LOSS | DRAW |\n";
        cout << string(widestName + 2, ' ') << tableLine << "\n";

        for (int i = 0; i < playerCount; i++)
        {
            cout << left << setw(widestName + 1) << players[i].getFullName()
                 << " "
                 << "| "
                 << right << setw(3) << players[i].getWins() << " | "
                 << setw(4) << players[i].getLosses() << " | "
                 << setw(4) << players[i].getDraws() << " |\n";

            cout << string(widestName + 2, ' ') << tableLine << "\n";
        }
    }


    //------------------------------------------------------------------------------------
    //Determines the next starting player
    //------------------------------------------------------------------------------------

    int determineNextStarter(int winnerIndex, bool draw) const
    {
        if (draw)
        {
            return (starterIndex + 1) % playerCount;
        }
        return (winnerIndex + 1) % playerCount;
    }


    //------------------------------------------------------------------------------------
    //Asks the user whether to play another game
    //------------------------------------------------------------------------------------

    bool askPlayAgain() const
    {
        string line;
        char ch = '\0';
        bool validInput = false;

        while (!validInput)
        {
            cout << "\nDo you want to play another game? (Y/N) -> ";
            getline(cin, line);
            line = trim(line);
            if (line.length() == 1)
            {
                ch = toupper(line[0]);
                if (ch == 'Y' || ch == 'N')
                {
                    validInput = true;
                }
            }
            if (!validInput)
            {
                cout << "Invalid input. Please enter Y or N.\n";
            }
        }

        return ch == 'Y';
    }
};


//------------------------------------------------------------------------------------
//Starts the program
//------------------------------------------------------------------------------------

int main()
{
    Game game;
    game.run();
    return 0;
}