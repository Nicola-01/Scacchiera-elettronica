// Nicola Busato 2009663

#ifndef Chessboard_h
#define Chessboard_h

#include <string>
#include <utility>
#include <vector>
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
    const std::string pos{"TCADRACT"}; // è la "sequenza" in cui vengono posizionati i pezzi diversi dal pedone
    int king_white[2]{7, 4}; //y x
    int king_black[2]{0, 4};
    int str[2];
    int end[2];
    int last_capture;

    //--- methods
    Piece inizializer_piece(char p, int y, int x);
    bool is_valid_string(std::string move);

    std::pair<int, int> direction_threat(int king_y, int king_x, bool black_king, int dir_y, int dir_x);
    bool is_checkmate_d(int k_y, int k_x);
    bool is_checkmate_s(int k_y, int k_x, std::pair<int,int> t_pos);
    std::vector<char> to_char_vector();

public:
    Chessboard();
    int move(std::string& s_move, bool white_turne) { return move(s_move, white_turne, false); }
    int move(std::string& s_move, bool white_turne, bool replay);
    bool is_right_piece(int y, int x, bool white_turne) { return (board[y][x].print() != ' ' && board[y][x].is_white() == white_turne); };
    std::string random_move(int y, int x);
    char pices_type(int y, int x) { return board[y][x].print(); }


     bool is_checkmate(bool in_black, int st_y, int st_x, int end_y, int end_x) { return false; };
     int is_check(bool in_black, int st_y, int st_x, int end_y, int end_x) { return false; };
     bool is_draw(int end_y, int end_x) { return false; };
    
   /* bool is_checkmate(bool in_black, int st_y, int st_x, int end_y, int end_x);
    int is_check(bool in_black, int st_y, int st_x, int end_y, int end_x);
    bool is_draw(int end_y, int end_x);*/
    
    bool is_checkmate(bool in_black) { return is_checkmate(in_black, str[0], str[1], end[0], end[1]); }
    int is_check(bool in_black) { return is_checkmate(in_black, str[0], str[1], end[0], end[1]); }
    bool is_draw() { return is_draw(end[0], end[1]); }
};

#endif
