#ifndef Piece_h
#define Piece_h

using namespace std;

class Piece
{
private:
public:
    Piece() {};
    bool is_valid_move(char letter, int str_x, int str_y, int end_x, int end_y);
};

#endif