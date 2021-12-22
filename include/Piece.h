//Riccardo Miele 2008594

#ifndef Piece_h
#define Piece_h

#include "Piece.cpp"
class Piece
{
public:
    Piece(bool color, int y, int x);
    Piece();
    template <int Y, int X>
    bool move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y);
    virtual bool is_valid_move();
    bool is_white() { return white; }; // = true se e' un pezzo bianco
    char print() { return type; };
    // void undo_move();
protected:
    char type;
    int ex_position_x;
    int ex_position_y;
    bool white;
};
// bool white_turne(); // = true se e' turno del bianco

class Re : public Piece
{
    public:
        Re(bool color, int y, int x) : Piece(color, y, x){};
        template <int Y, int X>
        bool is_valid_move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y);

    private:
    bool arrocco_re = false; //se e' stato fatto l'arrocco -> true
};


class Donna : public Piece
{
    public:
    Donna(bool color, int y, int x) : Piece(color, y, x){};
    template <int Y, int X>


    bool is_valid_move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y);
};


class Torre : public Piece
{
public:
    Torre(bool color, int y, int x) : Piece(color, y, x){};
    template <int Y, int X>
    bool is_valid_move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y);
private:
    bool arrocco_torre = false;
};


class Alfiere : public Piece
{
public:
    Alfiere(bool color, int y, int x) : Piece(color, y, x){};
    template <int Y, int X>
    bool is_valid_move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y);
};

class Cavallo : public Piece
{
public:
    Cavallo(bool color, int y, int x) : Piece(color, y, x){};
    template <int Y, int X>
    bool is_valid_move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y);
};

class Pedone : public Piece
{
public:
    Pedone(bool color, int y, int x) : Piece(color, y, x){};
    template <int Y, int X>
    bool is_valid_move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y);
private:
    bool is_moved = false; 
};

class Nullo : public Piece
{
public:
    Nullo(bool color, int y, int x) : Piece(color, y, x){};
    template <int Y, int X>
    bool is_valid_move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y){ return false; };
};

#endif