#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <array>
#include <algorithm>

#define HEX_LENTH 192
#define HEX_POSITION std::array<char, HEX_LENTH>

class Position
{
public:
    Position();
    Position(std::string encodedPosition);

    HEX_POSITION const encode();
    bool const isValidPosition();
    bool const isPeiceAt(uint8_t x, uint8_t y);
    char const getPeiceCharAt(uint8_t x, uint8_t y);
    uint8_t const getPeiceAt(uint8_t x, uint8_t y);
    bool const isPeiceAtIndex(uint8_t i);
    char const getPeiceCharAtIndex(uint8_t i);
    uint8_t const getPeiceAtIndex(uint8_t i);
    bool makeMove(std::string move);

    bool getTurn() { return this->turn; }
    std::string getTurnString() { return this->turn == turnValues.WHITE ? "white" : "black"; }

    // TODO get rid of test
    void showMovesFromPawn(uint8_t i);
private:
    std::array<uint64_t, 12> peices;
    // TODO add this to constructor
    bool turn = true;

    uint8_t castleRights = 0x0F;
    uint8_t const cordinateToIndex(uint8_t x, uint8_t y);
    bool const isOponentsPeiceAtIndex(uint8_t i);
    uint64_t const movesFromPawn(uint8_t i);
    /* uint64_t const movesFromKnight(uint8_t i);
    uint64_t const movesFromBishop(uint8_t i);
    uint64_t const movesFromRook(uint8_t i);
    uint64_t const movesFromBishop(uint8_t i);
    uint64_t const movesFromKing(uint8_t i); */
    
    struct {             
        const uint8_t WHITE     = 0;
        const uint8_t BLACK     = 6;
        const uint8_t PAWN      = 0;
        const uint8_t KNIGHT    = 1;
        const uint8_t BISHOP    = 2;
        const uint8_t ROOK      = 3;
        const uint8_t QUEEN     = 4;
        const uint8_t KING      = 5;
    } peicesOffset; 

    struct {             
        const uint8_t WHITE     = 0;
        const uint8_t BLACK     = 2;
        const uint8_t SHORT     = 0;
        const uint8_t LONG      = 1;
    } castleOffset;

    struct {
        const uint8_t UP            = 8;
        const uint8_t RIGHT         = 1;
        const uint8_t DOWN          = -1 * UP;
        const uint8_t LEFT          = -1 * RIGHT;
        const uint8_t DIAG_UR       = UP + RIGHT;
        const uint8_t DIAG_UL       = UP + LEFT;
        const uint8_t DIAG_DR       = DOWN + RIGHT;
        const uint8_t DIAG_DL       = DOWN + LEFT;
    } moveIndexOffset;

    struct{
        const bool WHITE = true;
        const bool BLACK = false;
    } turnValues;

    struct move {
        uint8_t to;
        uint8_t from;
    };
    
};