#ifndef Piece_h
#define Piece_h
//Pezzo (variabili colore, tipo) (funzioni move, isValidMove(?), cout)

class Piece
{
public:
    Piece(bool color, int y, int x){
        is_white = color;
        ex_position_x = x;
        ex_position_y = y;

    };
    template <int Y, int X>
    bool move(Piece (&Board)[Y][X] , int str_x, int str_y, int end_x, int end_y){
        if (is_valid_move(Piece (&Board)[Y][X] , int str_x, int str_y, int end_x, int end_y)){
            ex_position_x = str_x;
            ex_position_y = str_y;
            return true;}
        return false;
    };
    virtual bool is_valid_move() = 0;
    bool is_white() { return is_white; }; // = true se e' un pezzo bianco
    char print() { return type; };
   // void undo_move();
protected:
    char type;
    int ex_position_x = -1;
    int ex_position_y = -1;
    bool is_white;
}
// bool white_turne(); // = true se e' turno del bianco
class Re : public Piece
{
public:
    Re(bool color, int y, int x):Piece(color, y, x)
    {
        if (color)
            type = 'r';
        else
            type = 'R';
        
    };
    template <int Y, int X>
    bool is_valid_move(Piece (&Board)[Y][X] , int str_x, int str_y, int end_x, int end_y)
    {
        int delta_x = abs(str_x - end_x);
        int delta_y = abs(str_y - end_y);
        if ((delta_x != 1 && arrocco) || delta_y != 1)
            return false; //percorso > 1
        if (is_white == Board[end_y][end_x].is_white)
            return false; //destinazione diverso colore; 
        return true;
    }

private:
    bool arrocco = false; //se e' stato fatto l'arrocco -> true
}

class Donna : public Piece
{
    Donna(bool color, int y, int x):Piece(color, y, x)
    {
        if (color)
            type = 'd';
        else
            type = 'D';
        
    };
    template <int Y, int X>
    bool move(Piece (&Board)[Y][X] , int str_x, int str_y, int end_x, int end_y)
    {
        if (is_valid_move(Piece (&Board)[Y][X] , int str_x, int str_y, int end_x, int end_y)){
            ex_position_x = str_x;
            ex_position_y = str_y;
            return true;}
        return false;
    }
    bool is_valid_move(Piece (&Board)[Y][X] , int str_x, int str_y, int end_x, int end_y)
    {
        int delta_x = abs(str_x - end_x);
        int delta_y = abs(str_y - end_y);
        
    }


}

class Torre : public Piece
{
    public:
    Torre(bool color, int y, int x):Piece(color, y, x)
    {
        if (color)
            type = 't';
        else
            type = 'T';
        
    };
}

class Alfiere : public Piece
{   
    public:
    Alfiere(bool color, int y, int x):Piece(color, y, x)
    {
        if (color)
            type = 'a';
        else
            type = 'A';
        
    };

} class Cavallo : public Piece
{
    public:
    Cavallo(bool color, int y, int x):Piece(color, y, x)
    {
        if (color)
            type = 'c';
        else
            type = 'C';
        
    };
} class Pedone : public Piece
{
    public:
    Pedone(bool color, int y, int x):Piece(color, y, x)
    {
        if (color)
            type = 'p';
        else
            type = 'P';
        
    };

} class Nullo : public Piece
{
    public:
    Nullo(bool color, int y, int x):Piece(color, y, x)
    {
        if (color)
            type = ' ';
        else
            type = ' ';
        
    };
}
#endif