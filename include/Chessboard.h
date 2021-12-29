// Nicola Busato 2009663

#ifndef Chessboard_h
#define Chessboard_h

#include <string>
#include <utility>
#include "Piece.h"
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
    int str[2];
    int end[2];

    //--- methods
    Piece inizializer_piece(char p, int y, int x);
    bool is_valid_string(std::string move);
    void print();

    std::pair<int, int> direction_threat(int king_y, int king_x, bool black_king, int dir_y, int dir_x);
    bool is_checkmate_d(int k_y, int k_x);
    bool is_checkmate_s(int k_y, int k_x, std::pair<int,int> t_pos);

public:
    Chessboard();
    int move(std::string move, bool white_turne);
    bool is_right_piece(int y, int x,  bool white_turne);
    string random_move(int y, int x);

    bool is_checkmate(bool in_black, int st_y, int st_x, int end_y, int end_x);
    int is_check(bool in_black, int st_y, int st_x, int end_y, int end_x);
    bool is_checkmate(bool in_black) { return is_checkmate(in_black, str[0], str[1], end[0], end[1]); }
    int is_check(bool in_black) { return is_checkmate(in_black, str[0], str[1], end[0], end[1]); }
    bool is_draw();
};

#endif
