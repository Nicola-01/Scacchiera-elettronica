//Riccardo Miele 2008594

#ifndef Piece_h
#define Piece_h
#include <string>

#include <vector>

//MANCANO I DISTRUTTORI
//CONTROLLO DELLA REGOLA 4 DELL'ARROCCO

extern int n_moves;

class Piece
{
public:
    Piece() : white{false}, ex_position_y{-1}, ex_position_x{-1} {};
    Piece(bool color, int y, int x, bool m) : white{color}, ex_position_y{y}, ex_position_x{-x}, moved{m} {};
    Piece(bool color, int y, int x) : white{color}, ex_position_y{y}, ex_position_x{-x} {};

    bool move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x);
    std::pair<int, int> random_position(Piece (&Board)[8][8], int str_y, int str_x); //ritorna le coordinate sotto forma di stringa
    virtual bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x);

    bool has_valid_move(Piece (&Board)[8][8], int str_y, int str_x); //Definito in "Has_valid_move.cpp"

    bool is_white() { return white; }; // = true se e' un pezzo bianco
    bool is_moved() { return moved; }
    void set_move(bool m) { moved = m; };
    void set_type(char c) { type = c; };

    bool is_end_same_color(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x);
    int get_ex_position_y() { return ex_position_y; };
    int get_ex_position_x() { return ex_position_x; };

    void set_number_move(int n) { number_move = n; }; //numero mossa
    int get_number_move() { return number_move; };

    bool check_boundary(int end_y, int end_x) { return end_y > -1 && end_x > -1 && end_y < 8 && end_x < 8; };
    bool check_arrocco_re(Piece (&Board)[8][8], int end_y, int end_x);

    char print() { return type; };

private:
    char type;
    int ex_position_x;
    int ex_position_y;
    bool white;
    bool moved;
    int number_move = 0;
};

class Re : public Piece
{
public:
    Re(bool color, int y, int x);
    Re(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
    std::pair<int, int> random_xy(Piece (&Board)[8][8], int str_y, int str_x);
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
    std::pair<int, int> random_xy(Piece (&Board)[8][8], int str_y, int str_x);
};

class Alfiere : public Piece
{
public:
    Alfiere(bool color, int y, int x);
    Alfiere(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
    std::pair<int, int> random_xy(Piece (&Board)[8][8], int str_y, int str_x);
};

class Cavallo : public Piece
{
public:
    Cavallo(bool color, int y, int x);
    Cavallo(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
    std::pair<int, int> random_xy(Piece (&Board)[8][8], int str_y, int str_x);
};

class Pedone : public Piece
{
public:
    Pedone(bool color, int y, int x);
    Pedone(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
    bool check_promotion(int y) { return y == 0 || y == 7; }; //se arrivato alla fine e' true
    std::pair<int, int> random_xy(Piece (&Board)[8][8], int str_y, int str_x);
};

class Nullo : public Piece
{
public:
    Nullo();
    Nullo(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override { return false; };
};

//Eccezioni
class PromotionException
{
public:
    std::pair<int, int> t;
    PromotionException(int y, int x)
    {
        t.first = y;
        t.second = x;
    }
};
class ArroccoException
{
public:
    std::pair<int, int> t;
    ArroccoException(int y, int x)
    {
        t.first = y;
        t.second = x;
    }
};

#endif