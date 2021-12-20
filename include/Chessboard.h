// Nicola Busato 2009663

#ifndef Chessboard_h
#define Chessboard_h

#include <string>
#include "Piece.h"

class InvalidMoveException {};
class InvalidMoveStringException {};

class Chess
{
private:
    //--- variables
    Piece board[8][8]; //[y][x]
    const std::string pos{"TCADRACT"};
    int king_white[2] {7,4}; //y x
    int king_black[2] {0,4};

    //--- methods
    Piece inizializer_piece(char p);
    bool is_valid_move(std::string move, bool white_turne);
    void print();
public:
    Chess();
    int move(std::string move, bool white_turne);
    bool is_right_piece(int y, int x, bool white_turne);
    bool is_piece_valid_move(int y, int x, bool white_turne, int end_y, int end_x);
};

#endif