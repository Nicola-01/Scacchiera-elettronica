//Riccardo Miele 2008594

#ifndef Piece_cpp
#define Piece_cpp

#include "Piece.h"
//#include <string>
#include <iostream>
using namespace std;

//COSTRUTTORI

Piece::Piece() //costruttore di default
{
    white = false;
    ex_position_x = -1;
    ex_position_y = -1;
}

Piece::Piece(bool color, int y, int x) //costruttore
{
    white = color;
    ex_position_x = x;
    ex_position_y = y;
};

Re::Re(bool color, int y, int x) : Piece(color, y, x) //costruttore Re
{
    if (color)
        type = 'r';
    else
        type = 'R';
};

Donna::Donna(bool color, int y, int x) : Piece(color, y, x) //costruttore Donna
{
    if (color)
        type = 'd';
    else
        type = 'D';
};

Torre::Torre(bool color, int y, int x) : Piece(color, y, x) //costruttore Torre
{
    if (color)
        type = 't';
    else
        type = 'T';
};

Alfiere::Alfiere(bool color, int y, int x) : Piece(color, y, x) //costruttore Alfiere
{
    if (color)
        type = 'a';
    else
        type = 'A';
};

Cavallo::Cavallo(bool color, int y, int x) : Piece(color, y, x) //costruttore Cavallo
{
    if (color)
        type = 'c';
    else
        type = 'C';
};

Pedone::Pedone(bool color, int y, int x) : Piece(color, y, x) //costruttore Pedone
{
    if (color)
        type = 'p';
    else
        type = 'P';
};

Nullo::Nullo(bool color, int y, int x) : Piece(color, y, x) //costruttore (Pezzo) Nullo
{
    type = ' ';
};

//FUNZIONI DI PIECE

template <int Y, int X>
bool Piece::is_end_same_color(int end_y, int end_x) //ritorna true se la destinazione
{
    if (Board[end_y][end_x].print() == ' ')
        return false;
    return (is_white == Board[end_y][end_x].is_white); //posso crearlo nella classe padre is_friend
}

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

//FUNZIONE IS_VALID_MOVE

template <int Y, int X> //manca arrocco
bool Re::is_valid_move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y)
{
    int delta_x = abs(str_x - end_x);
    int delta_y = abs(str_y - end_y);
    if ((delta_x != 1 && arrocco) || delta_y != 1)
        return false; //percorso > 1
    if (is_end_same_color(end_y, end_x))
        return false; //destinazione diverso colore;
    return true;
};

template <int Y, int X>
bool Donna::is_valid_move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y)
{
    int delta_x = abs(str_x - end_x);
    int delta_y = abs(str_y - end_y);
    if (is_end_same_color(end_y, end_x)) //posso crearlo nella classe padre is_friend
        return false;
    if (str_x != end_x && str_y != end_y)
        return false;              //destinazione diverso colore;
    bool control_condition = true; //true se si può fare la mossa
    if (delta_x == delta_y)        //controllo come se fosse un alfiere
    {
        for (int i = 1; i < delta_x; i++)
        {
            if (end_y > str_y)
                if (Board[str_y + i][str_x - i].print() != ' ')
                {
                    control_condition = false;
                    break;
                }
                else if (Board[str_y - i][str_x + i].print() != ' ')
                {
                    control_condition = false;
                    break;
                }
        }
    }
    else
    {
        for (int i = 1; i < delta_x; i++) //controllo come se fosse una torre
        {
            if (end_x > str_x)
                if (Board[end_y][str_x + i].print() != ' ')
                {
                    control_condition = false;
                    break;
                }
                else if (Board[end_y][str_x - i].print() != ' ')
                {
                    control_condition = false;
                    break;
                }
        }
        for (int i = 1; i < delta_y; i++)
        {
            if (end_y > str_y)
                if (Board[str_y + i][end_y].print() != ' ')
                {
                    control_condition = false;
                    break;
                }
                else if (Board[str_y - i][end_y].print() != ' ')
                {
                    control_condition = false;
                    break;
                }
        }
    }
    return control_condition;
}

template <int Y, int X> //manca arrocco
bool Torre::is_valid_move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y)
{
    int delta_x = abs(str_x - end_x);
    int delta_y = abs(str_y - end_y);
    if (str_x != end_x && str_y != end_y)
        return false;                    //non si muove verticalmente o orizzontalmente
    if (is_end_same_color(end_y, end_x)) //posso crearlo nella classe padre is_friend
        return false;                    //destinazione diverso colore;
    for (int i = 1; i < delta_x; i++)
    {
        if (end_x > str_x)
            if (Board[end_y][str_x + i].print() != ' ')
                return false;
            else if (Board[end_y][str_x - i].print() != ' ')
                return false;
    }
    for (int i = 1; i < delta_y; i++)
    {
        if (end_y > str_y)
            if (Board[str_y + i][end_y].print() != ' ')
                return false;
            else if (Board[str_y - i][end_y].print() != ' ')
                return false;
    }
}

// return (abs(delta_x) <= 2 && abs(delta_y) <= 1) || (abs(delta_x) <= 1 && abs(delta_y) <= 2)
template <int Y, int X>
bool Cavallo::is_valid_move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y)
{
    int delta_x = abs(str_x - end_x);
    int delta_y = abs(str_y - end_y);
    if (is_end_same_color(end_y, end_x)) //posso crearlo nella classe padre is_friend
        return false;                    //destinazione diverso colore;
    return (delta_x <= 2 && delta_y <= 1) || (delta_x <= 1 && delta_y <= 2);
};

template <int Y, int X>
bool Alfiere::is_valid_move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y)
{
    int delta_x = abs(str_x - end_x);
    int delta_y = abs(str_y - end_y);
    if (is_end_same_color(end_y, end_x) //posso crearlo nella classe padre is_friend
        return false;        //destinazione diverso colore;
    if (delta_x != delta_y)
        return false; //non si muove in diagonale
    for (int i = 1; i < delta_x; i++)
    {
        if (end_y > str_y)
            if (Board[str_y + i][str_x - i].print() != ' ')
                return false;
            else if (Board[str_y - i][str_x + i].print() != ' ')
                return false;
    }
    return true;
};

template <int Y, int X>
bool Pedone::is_valid_move(Piece (&Board)[Y][X], int str_x, int str_y, int end_x, int end_y) //manca promozione
{
    int delta_x = abs(str_x - end_x);
    int delta_y = abs(str_y - end_y);
    if (delta_x > 1 || delta_x < 0)
        return false; //non si può muovere in diagonale
    if (delta_y != 1 && is_moved)
        return false; //non si può muovere piu' di 2 caselle
    if (is_end_same_color(end_y, end_x))
        return false; //destinazione diverso colore;
    if (Board[end_y][end_x].print() != ' ' && str_x == end_x)
        return false;
    is_moved = true;
    if (check_promotion(end_y))
    {
        cout << "Inserisci il carattere del pezzo che vuoi";
        char in;
        while (in.length() != 1 && in != 'D' && in != 'T' && in != 'A' && in != 'C')
        {
            cout << "Inserisci il carattere del pezzo che vuoi";
            cin >> in;
            in = toupper(in);
        }
        switch (in)
        {
        case 'D':
            &Board[end_y][end_x] = Donna(is_white; end_y; end_x);
        case 'T':
            &Board[end_y][end_x] = Torre(is_white; end_y; end_x);
        case 'C':
            &Board[end_y][end_x] = Torre(is_white; end_y; end_x);
        case 'A':
            &Board[end_y][end_x] = Torre(is_white; end_y; end_x);
        }
    }
    return true;
};

#endif