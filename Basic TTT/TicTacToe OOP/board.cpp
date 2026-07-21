#include "Board.h"

using namespace std;

// ----------------------------------------------------------------------------------
// Converts a 1-9 user position into the internal array index mapping.
// ----------------------------------------------------------------------------------
int Board::mapPositionToIndex (int pos)
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

// ----------------------------------------------------------------------------------
// Converts an internal array index back into the displayed 1-9 position mapping.
// ----------------------------------------------------------------------------------
int Board::mapIndexToPosition(int idx)
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

// ----------------------------------------------------------------------------------
// Default constructor: clears the board, resets winning markers, and sets move count to 0.
// ----------------------------------------------------------------------------------
Board::Board()
{
    for (int i = 0; i < 9; i++)
    {
        cells[i] = ' ';
        winningPositions[i] = false;
    }
    moveCount = 0;
}

// ----------------------------------------------------------------------------------
// Resets the board state to empty and clears winning markers.
// ----------------------------------------------------------------------------------
void Board::reset()
{
    for (int i=0; i < 9; i++)
    {
        cells[i] = ' ';
        winningPositions[i] = false;

    }
    moveCount = 0;
}

// ----------------------------------------------------------------------------------
// Attempts to place a piece at a given position; returns true if successful.
// ----------------------------------------------------------------------------------
bool Board::makeMove(int position, char piece)
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

// ----------------------------------------------------------------------------------
// Returns true if the given cell (by index) is empty.
// ----------------------------------------------------------------------------------
bool Board::isCellEmpty(int position)
{
    if (cells[position]==' ')
    {
        return true;
    }
    return false;
}

// ----------------------------------------------------------------------------------
// Returns the character stored in the given cell (by index).
// ----------------------------------------------------------------------------------
char Board::getCellVLaue(int position)
{
    return cells[position];
}

// ----------------------------------------------------------------------------------
// Prints the board to the console using the custom display mapping.
// ----------------------------------------------------------------------------------
void Board::display()
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

// ----------------------------------------------------------------------------------
// Checks whether the given piece currently has a winning 3-in-a-row pattern.
// ----------------------------------------------------------------------------------
bool Board::checkWin(char piece)
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

// ----------------------------------------------------------------------------------
// Uppercases the cells that form any winning pattern for the given piece.
// ----------------------------------------------------------------------------------
void Board::markAllWinningPatterns(char piece)
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

// ----------------------------------------------------------------------------------
// Returns true if the board has no empty cells.
// ----------------------------------------------------------------------------------
bool Board::isFull()
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

// ----------------------------------------------------------------------------------
// Returns the number of moves that have been made.
// ----------------------------------------------------------------------------------
int Board::getMoveCount()
{
    return moveCount;
}

// ----------------------------------------------------------------------------------
// Returns true if the position is 1-9 and the mapped cell is empty.
// ----------------------------------------------------------------------------------
bool Board::isValidPosition(int position)
{
    if (position < 1 || position > 9)
    {
        return false;
    }
    
    int index = mapPositionToIndex(position);
    return (cells[index] == ' ');
}