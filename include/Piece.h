//Riccardo Miele 2008594

#ifndef Piece_h
#define Piece_h
#include <string>
using namespace std;
//#include "Piece.cpp"
class Piece
{
public:
    Piece(bool color, int y, int x);
    Piece();
    template <int Y, int X>
    bool move(Piece (&Board)[Y][X], int str_y, int str_x, int end_y, int end_x);

    virtual bool is_valid_move();

    template <int Y, int X>
    string random_position(Piece (&Board)[Y][X], int str_y, int str_x); //ritorna le coordinate sotto forma di stringa

    template <int Y, int X>
    bool check_arrocco(Piece (&Board)[Y][X], int end_y, int end_x); //non so come gestirlo

    bool is_white() { return white; }; // = true se e' un pezzo bianco
    char print() { return type; };
    template <int Y, int X>
    bool is_end_same_color(Piece (&Board)[Y][X], int end_y, int end_x);
    int get_ex_position_y() { return ex_position_y; };
    // void undo_move();
protected:
    char type;
    int ex_position_x;
    int ex_position_y;
    bool white;
};
// bool white_turne(); // = true se e' turno del bianco
//Pezzo (variabili colore, tipo) (funzioni move, isValidMove(?), cout)
class Re : public Piece
{
public:
    Re(bool color, int y, int x) : Piece(color, y, x){};

    template <int Y, int X>
    bool is_valid_move(Piece (&Board)[Y][X], int str_y, int str_x, int end_y, int end_x);
    bool is_moved() { return moved; };

private:
    //bool arrocco_re = false; //se l'arrocco non e' piu' possibile -> true
    bool moved = false; //dopo la prima mossa diventa true
};

class Donna : public Piece
{
public:
    Donna(bool color, int y, int x) : Piece(color, y, x){};
    template <int Y, int X>
    bool is_valid_move(Piece (&Board)[Y][X], int str_y, int str_x, int end_y, int end_x);
};

class Torre : public Piece
{
public:
    Torre(bool color, int y, int x) : Piece(color, y, x){};
    template <int Y, int X>
    bool is_valid_move(Piece (&Board)[Y][X], int str_y, int str_x, int end_y, int end_x);
    bool is_moved() { return moved; };

private:
    bool moved = false;
    bool arrocco_torre = false;
};

class Alfiere : public Piece
{
public:
    Alfiere(bool color, int y, int x) : Piece(color, y, x){};
    template <int Y, int X>
    bool is_valid_move(Piece (&Board)[Y][X], int str_y, int str_x, int end_y, int end_x);
};

class Cavallo : public Piece
{
public:
    Cavallo(bool color, int y, int x) : Piece(color, y, x){};
    template <int Y, int X>
    bool is_valid_move(Piece (&Board)[Y][X], int str_y, int str_x, int end_y, int end_x);
};

class Pedone : public Piece
{
public:
    Pedone(bool color, int y, int x) : Piece(color, y, x){};
    template <int Y, int X>
    bool is_valid_move(Piece (&Board)[Y][X], int str_y, int str_x, int end_y, int end_x);
    bool is_moved() { return moved; };
    class PromotionException{};
private:
    bool moved = false;
    bool check_promotion(int y) { return y == 0 || y == 7; }; //se arrivato alla fine e' true
};

class Nullo : public Piece
{
public:
    Nullo(bool color, int y, int x) : Piece(color, y, x){};
    template <int Y, int X>
    bool is_valid_move(Piece (&Board)[Y][X], int str_y, int str_x, int end_y, int end_x) { return false; };
};

#endif