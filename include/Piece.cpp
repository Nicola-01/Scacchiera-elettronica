#ifndef Piece_hpp
#define Piece_hpp

#include "Piece.h" 

//Pezzo (variabili colore, tipo) (funzioni move, isValidMove(?), cout)
Re::Re(bool color, int y, int x) 
    {
        if (color)
            type = 'r';
        else
            type = 'R';
    };
Piece::Piece(bool color, int y, int x)
    {
        is_white = color;
        ex_position_x = x;
        ex_position_y = y;
    };

    template <int Y, int X>
bool Piece::move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y)
    {
        if (is_valid_move(Piece(&Board)[Y][X], int str_x, int str_y, int end_x, int end_y))
        {
            ex_position_x = str_x;
            ex_position_y = str_y;
            return true;
        }
        return false;
    };
    
    


    
    template <int Y, int X>
    bool Re::is_valid_move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y)
    {
        int delta_x = abs(str_x - end_x);
        int delta_y = abs(str_y - end_y);
        if ((delta_x != 1 && arrocco) || delta_y != 1)
            return false; //percorso > 1
        if (is_white == Board[end_y][end_x].is_white)
            return false; //destinazione diverso colore;
        return true;
    }


    Donna::Donna(bool color, int y, int x) : Piece(color, y, x)
    {
        if (color)
            type = 'd';
        else
            type = 'D';
    };
    template <int Y, int X>
    bool Donna::move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y)
    {
        if (is_valid_move(Piece(&Board)[Y][X], int str_x, int str_y, int end_x, int end_y))
        {
            ex_position_x = str_x;
            ex_position_y = str_y;
            return true;
        }
        return false;
    }
     template <int Y, int X>
    bool Donna::is_valid_move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y)
    {
        int delta_x = abs(str_x - end_x);
        int delta_y = abs(str_y - end_y);
    }

    Torre::Torre(bool color, int y, int x) : Piece(color, y, x)
    {
        if (color)
            type = 't';
        else
            type = 'T';
    };
    Alfiere::Alfiere(bool color, int y, int x) : Piece(color, y, x)
    {
        if (color)
            type = 'a';
        else
            type = 'A';
    };
    Cavallo::Cavallo(bool color, int y, int x) : Piece(color, y, x)
    {
        if (color)
            type = 'c';
        else
            type = 'C';
    };

Pedone::Pedone(bool color, int y, int x) : Piece(color, y, x)
    {
        if (color)
            type = 'p';
        else
            type = 'P';
    };
    Nullo::Nullo(bool color, int y, int x) : Piece(color, y, x)
    {
        if (color)
            type = ' ';
        else
            type = ' ';
    };

#endif