// Nicola Busato 2009663

#ifndef Chessboard_h
#define Chessboard_h

#include <string>
include <utility>
#include "Piece.h"
#include "Rules.h"
#include "Piece.h"

class InvalidMoveException
{
};
class InvalidMoveStringException
{
};

class Chessboard
{
private:
    //--- variables
    Piece board[8][8]; //[y][x]
    //Rules rul;
    const std::string pos{"TCADRACT"};
    int king_white[2]{7, 4}; //y x
    int king_black[2]{0, 4};

    //--- methods
    Piece inizializer_piece(char p, int y, int x);
    bool is_valid_string(std::string move);
    void print();

    std::pair<int, int> Chessboard::direction_treat(int king_y, int king_x, int dir_y, int dir_x);

public:
    Chessboard();
    int move(std::string move, bool white_turne);
    bool is_right_piece(int y, int x, bool white_turne);
    string random_move(int y, int x);

    bool is_check(bool in_black);
    bool is_checkmate(bool in_black);
    bool is_draw();
};

#endif