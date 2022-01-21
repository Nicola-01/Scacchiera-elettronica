//Riccardo Miele 2008594

#ifndef Piece_h
#define Piece_h
#include <string>

extern int n_moves;

class Piece
{
public:
    bool move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x);
    virtual std::pair<int, int> random_xy(Piece *(&Board)[8][8], int str_y, int str_x) = 0; //ritorna le coordinate sotto forma di stringa
    virtual bool is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x) = 0;
    virtual bool has_valid_move(Piece *(&Board)[8][8], int str_y, int str_x) = 0; //Definito in "Has_valid_move.cpp"

    bool is_white() { return white; }; // = true se e' un pezzo bianco
    bool is_moved() { return moved; };  // = true se il pezzo si e' mosso
    bool is_end_same_color(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x);  // = true se destinazione stesso colore
    bool check_arrocco_re(Piece *(&Board)[8][8], int end_y, int end_x);

    int get_ex_position_y() { return ex_position_y; };
    int get_ex_position_x() { return ex_position_x; };
    int get_number_move() { return number_move; };
    void set_move(bool m) { moved = m; };

    Piece(const Piece &) = delete;
    Piece &operator=(const Piece &) = delete;

    char print() { return type; };

protected:
    Piece() : white{false}, ex_position_y{-1}, ex_position_x{-1} {};
    Piece(bool color, int y, int x) : white{color}, ex_position_y{y}, ex_position_x{x} {};
    void set_number_move(int n) { number_move = n; }; 
    char type;
    int ex_position_x;
    int ex_position_y;
    bool white;
    bool moved;
    int number_move = 0;    //numero mossa, serve per en passant
};

class Re : public Piece
{
public:
    Re(bool color, int y, int x);
    bool is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x);
    std::pair<int, int> random_xy(Piece *(&Board)[8][8], int str_y, int str_x);
    bool has_valid_move(Piece *(&Board)[8][8], int str_y, int str_x);
};

class Donna : public Piece
{
public:
    Donna(bool color, int y, int x);
    bool is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x);
    std::pair<int, int> random_xy(Piece *(&Board)[8][8], int str_y, int str_x);
    bool has_valid_move(Piece *(&Board)[8][8], int str_y, int str_x);
};

class Torre : public Piece
{
public:
    Torre(bool color, int y, int x);
    bool is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x);
    std::pair<int, int> random_xy(Piece *(&Board)[8][8], int str_y, int str_x);
    bool has_valid_move(Piece *(&Board)[8][8], int str_y, int str_x);
};

class Alfiere : public Piece
{
public:
    Alfiere(bool color, int y, int x);
    bool is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x);
    std::pair<int, int> random_xy(Piece *(&Board)[8][8], int str_y, int str_x);
    bool has_valid_move(Piece *(&Board)[8][8], int str_y, int str_x);
};

class Cavallo : public Piece
{
public:
    Cavallo(bool color, int y, int x);
    bool is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x);
    std::pair<int, int> random_xy(Piece *(&Board)[8][8], int str_y, int str_x);
    bool has_valid_move(Piece *(&Board)[8][8], int str_y, int str_x);
};

class Pedone : public Piece
{
public:
    Pedone(bool color, int y, int x);
    bool is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x);
    std::pair<int, int> random_xy(Piece *(&Board)[8][8], int str_y, int str_x);
    bool has_valid_move(Piece *(&Board)[8][8], int str_y, int str_x);
};

class Nullo : public Piece
{
public:
    Nullo();
    bool is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x) { return false; };
    std::pair<int, int> random_xy(Piece *(&Board)[8][8], int str_y, int str_x);
    bool has_valid_move(Piece *(&Board)[8][8], int str_y, int str_x);
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