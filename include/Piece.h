//Riccardo Miele 2008594

#ifndef Piece_h
#define Piece_h
#include <string>
using namespace std;

class Piece
{
public:
    Piece(bool color, int y, int x);
    Piece();

    bool move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x);
    string random_position(Piece (&Board)[8][8], int str_y, int str_x); //ritorna le coordinate sotto forma di stringa

    bool check_arrocco_re(Piece (&Board)[8][8], int end_y, int end_x); 
    bool check_arrocco_torre(Piece (&Board)[8][8], int end_y, int end_x);
    bool is_white() { return white; }; // = true se e' un pezzo bianco
    char print() { return type; };

    bool is_end_same_color(Piece (&Board)[8][8], int end_y, int end_x);
    int get_ex_position_y() { return ex_position_y; };
    virtual bool is_moved() { return moved; }
    // void undo_move();
    virtual bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) { return false; };

protected:
    char type;
    int ex_position_x;
    int ex_position_y;
    bool white;
    bool moved;
};

class Re : public Piece
{
public:
    Re(bool color, int y, int x);
    Re get_type(Piece n);
    Re(Piece){};

    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
    bool is_moved() { return moved; };

private:
    bool moved = false; //dopo la prima mossa diventa true
};

class Donna : public Piece
{
public:
    Donna(bool color, int y, int x);
    Donna(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
};

class Torre : public Piece
{
public:
    Torre(bool color, int y, int x);
    Torre(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
    bool is_moved() { return moved; };

private:
    bool moved = false;
    bool arrocco_torre = false;
};

class Alfiere : public Piece
{
public:
    Alfiere(bool color, int y, int x);
    Alfiere(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
};

class Cavallo : public Piece
{
public:
    Cavallo(bool color, int y, int x);
    Cavallo(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
};

class Pedone : public Piece
{
public:
    Pedone(bool color, int y, int x);
    Pedone(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
    bool is_moved() { return moved; };
    class PromotionException
    {
    };

private:
    bool moved = false;
    bool check_promotion(int y) { return y == 0 || y == 7; }; //se arrivato alla fine e' true
};

class Nullo : public Piece
{
public:
    Nullo(bool color, int y, int x);
    Nullo(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override { return false; };
};

#endif