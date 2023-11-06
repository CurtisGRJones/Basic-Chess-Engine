#include "position.h"

// TODO add more error checking

template <class T>
bool isBitSet(T value, uint64_t index)
{
    return (bool)(((T)1 << index) & value);
}

template <class T>
T setBit(T value, uint64_t index)
{
    return (((T)1 << index) | value);
}

Position::Position()
{
    this->peices = {
        0x000000000000ff00, // [0]  White Pawns
        0x0000000000000042, // [1]  White Knights
        0x0000000000000024, // [2]  White Bishops
        0x0000000000000081, // [3]  White Rooks
        0x0000000000000008, // [4]  White Queen
        0x0000000000000010, // [5]  White King
        0x00ff000000000000, // [6]  Black Pawns
        0x4200000000000000, // [7]  Black Knights
        0x2400000000000000, // [8]  Black Bishops
        0x8100000000000000, // [9]  Black Rooks
        0x0800000000000000, // [10] Black Queen
        0x1000000000000000  // [11] Black King
    };
}

Position::Position(std::string encodedPosition)
{
    if (encodedPosition.length() != HEX_LENTH)
    {
        // TODO change this to preoper exception
        throw "Invalid length of hex string";
    }
    throw "Not Impl";
}

HEX_POSITION const Position::encode()
{
    HEX_POSITION result = {};
    for (int i = 0; i < this->peices.size(); i++)
    {
        char hex[17];
        sprintf(hex, "%016lX", static_cast<int64_t>(this->peices[i]));
        for (int j = 0; j < 16; j++)
        {
            result[16 * i + j] = hex[j];
        }
    }

    return result;
}

bool const Position::isValidPosition()
{

    uint64_t occupiedSpaces = 0;

    for (int i = 0; i < 12; i++)
    {
        if (occupiedSpaces & this->peices[i])
        {
            printf(
                "Colision at %i\nOccupied:\t%016lX\nPeices:\t\t%016lX\nBitAnd:\t\t%016lX",
                i,
                occupiedSpaces,
                this->peices[i],
                this->peices[i] & occupiedSpaces);
            return false;
        }
        occupiedSpaces = occupiedSpaces | this->peices[i];
    }

    const bool pawnPositionValid =
        (0xff000000000000ff &
         (this->peices[this->peicesOffset.WHITE + this->peicesOffset.PAWN] |
          this->peices[this->peicesOffset.BLACK + this->peicesOffset.PAWN])) == 0;

    const bool hasOneKing =
        (
            // Both sides dont have more than 1 king
            (
                this->peices[this->peicesOffset.WHITE + this->peicesOffset.KING] &
                (this->peices[this->peicesOffset.WHITE + this->peicesOffset.KING] - 1)) |
            (this->peices[this->peicesOffset.BLACK + this->peicesOffset.KING] &
             (this->peices[this->peicesOffset.BLACK + this->peicesOffset.KING] - 1))) == 0 &&
        // Both sides have at least 1 king
        this->peices[this->peicesOffset.WHITE + this->peicesOffset.KING] &&
        this->peices[this->peicesOffset.BLACK + this->peicesOffset.KING];

    return pawnPositionValid && hasOneKing;
}

bool const Position::isPeiceAt(uint8_t x, uint8_t y)
{
    return this->getPeiceAt(x, y) != UINT8_MAX;
}

uint8_t const Position::getPeiceAt(uint8_t x, uint8_t y)
{
    if (x < 0 || x > 7 || y < 0 || y > 7)
    {
        throw "X and Y cneed to be beteween 0 and 7 inclusivly";
    }

    return this->getPeiceAtIndex(this->cordinateToIndex(x, y));
}

char const Position::getPeiceCharAt(uint8_t x, uint8_t y)
{
    return this->getPeiceCharAtIndex(this->cordinateToIndex(x, y));
}

bool const Position::isPeiceAtIndex(uint8_t i)
{
    return this->getPeiceAtIndex(i) != UINT8_MAX;
}

uint8_t const Position::getPeiceAtIndex(uint8_t i)
{
    for (int j = 0; j < 12; j++)
    {
        if (isBitSet(this->peices[j], i))
        {
            return j;
        }
    }

    return UINT8_MAX;
}

char const Position::getPeiceCharAtIndex(uint8_t i)
{
    const auto x = this->getPeiceAtIndex(i);
    if (x == UINT8_MAX)
    {
        return 'X';
    }
    const char peiceChars[] = {'p', 'n', 'b', 'r', 'q', 'k'};
    return peiceChars[x % 6] - ((int)(x < 6) * 32);
}

uint8_t const Position::cordinateToIndex(uint8_t x, uint8_t y)
{
    return x * 8 + y;
}

bool const Position::isOponentsPeiceAtIndex(uint8_t i)
{
    uint8_t offset = this->turn == turnValues.WHITE ? peicesOffset.BLACK : peicesOffset.WHITE;

    const auto map = setBit((int64_t)0, i);

    for (int i = 0; i < 6; i++)
    {
        if (this->peices[offset + i] & map)
        {
            return true;
        }
    }

    return false;
}

bool Position::makeMove(std::string move)
{
    std::transform(move.begin(), move.end(), move.begin(), ::toupper);
    uint8_t moveFrom = UINT8_MAX;
    switch (move[0])
    {
    case 'N':

        break;
    case 'B':
        if (move[1] >= 'A' && move[1] <= 'H')
        {
        }
        else
        {
        }
        break;
    case 'R':

        break;
    case 'Q':

        break;
    case 'K':

        break;
    case 'O':

        break;
    default:
        if (move[0] >= 'A' && move[0] <= 'H')
        {
        }
        else
        {
            throw "Invalid Move";
        }
    }

    this->turn = !this->turn;

    return true;
}

uint64_t const Position::movesFromPawn(uint8_t i)
{
    // TODO handle promotion
    uint64_t result = 0;
    const int8_t defaultMove = turn == this->turnValues.WHITE ? moveIndexOffset.UP : moveIndexOffset.DOWN;
    const int8_t defaultDestination = i + defaultMove;
    if (defaultDestination < 64 && !this->isPeiceAtIndex(defaultDestination))
    {
        result = setBit(result, defaultDestination);
        const int8_t startingRow = turn == this->turnValues.WHITE ? 1 : 6;
        const int8_t firstMoveDestination = i + defaultMove * 2;
        if ((int8_t)(i / 8) == startingRow && !this->isPeiceAtIndex(firstMoveDestination))
        {
            result = setBit(result, firstMoveDestination);
        }
    }
    // ensure diagonals are on the same row
    // TODO maybe have movement in a function that returns a code if no working
    const int8_t leftTakesDestination = defaultDestination + moveIndexOffset.LEFT;
    const int8_t rightTakesDestination = defaultDestination + moveIndexOffset.RIGHT;
    if (leftTakesDestination < 64 && this->isOponentsPeiceAtIndex(leftTakesDestination))
    {
        result = setBit(result, leftTakesDestination);
    }

    if (rightTakesDestination < 64 && this->isOponentsPeiceAtIndex(rightTakesDestination))
    {
        result = setBit(result, rightTakesDestination);
    }

    return result;
}

// TODO remove

void Position::showMovesFromPawn(uint8_t i)
{
    const auto value = this->movesFromPawn(i);
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            std::cout << isBitSet(value, this->cordinateToIndex(i, j));
        }
        std::cout << '\n';
    }
}