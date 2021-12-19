// Nicola Busato 2009663

#ifndef Chessboard_h
#define Chessboard_h

#include <string>
#include "Piece.h"

class Chess
{
private:
    //--- variables
    Piece board[8][8]; //[y][x]
    const std::string pos{"TCADRACT"};
    int[] king_white{7,4};
    int[] king_black{0,4};

    //--- methods
    bool is_valid_move(std::string move);
    Piece inizializer_piece(char p);
public:
    Chess();
    void print();
    bool move(std::string move);
};

#endif