//Riccardo Miele 2008594

#ifndef Piece_cpp
#define Piece_cpp

#include "Piece.h"
//#include <string>
#include <iostream>
#include <time.h>
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
bool Piece::is_end_same_color(Piece (&Board)[Y][X], int end_y, int end_x) //ritorna true se la destinazione ha lo stesso colore
{
    if (Board[end_y][end_x].print() == ' ')
        return false;
    return (is_white() == Board[end_y][end_x].is_white());
}

template <int Y, int X>
bool Piece::move(Piece (&Board)[Y][X], int str_y, int str_x, int end_y, int end_x)
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
bool Piece::check_arrocco(Piece (&Board)[Y][X], int end_y, int end_x) //ARROCCO
{
    if (end_x < 4)
    {
        if (!Board[end_y][end_x - 1].is_moved() && (Board[end_y][end_x].print() != ' ' && Board[end_y][end_x + 1].print() != ' ' && Board[end_y][end_x + 2].print() != ' ')
        {
            Board[end_y][end_x - 1] = Nullo(false, end_y, end_x - 1);
            Board[end_y][end_x + 1] = Torre(is_white(), end_y, end_x + 1);
            return true;
        }
        return false;
    }
    else //end_x > 4
    {
        if (Board[end_y][end_x + 1].is_moved() && Board[end_y][end_x].print() != ' ' && Board[end_y][end_x - 1].print() != ' ')
        {
            Board[end_y][end_x + 1] = Nullo(false, end_y, end_x - 1);
            Board[end_y][end_x - 1] = Torre(is_white(), end_y, end_x + 1);
            return true;
        }
        return false;
    }
};

//FUNZIONE IS_VALID_MOVE

template <int Y, int X> //manca arrocco
bool Re::is_valid_move(Piece (&Board)[Y][X], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = abs(str_x - end_x);
    int delta_y = abs(str_y - end_y);
    if (is_end_same_color(end_y, end_x))
        return false; //destinazione stesso colore;
    if (delta_x != 1 || delta_y != 1)
    {
        if (!is_moved())
        {
            if (check_arrocco(Board, end_y, end_x))
            {
                moved = true;
                return true;
            }
        }
        return false; //percorso > 1
    }
    moved = true;
    return true;
};

template <int Y, int X>
bool Donna::is_valid_move(Piece (&Board)[Y][X], int str_y, int str_x, int end_y, int end_x)
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
bool Torre::is_valid_move(Piece (&Board)[Y][X], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = abs(str_x - end_x);
    int delta_y = abs(str_y - end_y);
    if (str_x != end_x && str_y != end_y)
        return false;                    //non si muove verticalmente o orizzontalmente
    if (is_end_same_color(end_y, end_x)) //posso crearlo nella classe padre is_friend
        return false;                    //destinazione diverso colore;
    /*          
    if (arrocco_torre)
    {   
        return;     NON SO COME GESTIRE
    }
    */
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
    moved = true;
    return true;
}

template <int Y, int X>
bool Cavallo::is_valid_move(Piece (&Board)[Y][X], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = abs(str_x - end_x);
    int delta_y = abs(str_y - end_y);
    if (is_end_same_color(end_y, end_x)) //posso crearlo nella classe padre is_friend
        return false;                    //destinazione diverso colore;
    return (delta_x <= 2 && delta_y <= 1) || (delta_x <= 1 && delta_y <= 2);
};

template <int Y, int X>
bool Alfiere::is_valid_move(Piece (&Board)[Y][X], int str_y, int str_x, int end_y, int end_x)
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
bool Pedone::is_valid_move(Piece (&Board)[Y][X], int str_y, int str_x, int end_y, int end_x) //promozione probabilmente sbagliata
{
    int delta_x = abs(str_x - end_x);
    int delta_y = abs(str_y - end_y);
    if (is_end_same_color(end_y, end_x)) //destinazione diverso colore;
        return false;
    if ((Board[str_y][end_x].get_ex_position_y() == 6 || Board[str_y][end_x].get_ex_position_y() == 1) && toupper(Board[str_y][end_x].print()) == 'P') //en passant
    {
        Board[str_y][end_x] = Nullo(false, str_y, str_x); //en passant in teoria giusto
        return true;
    }
    if (delta_x > 1 || delta_x < 0) //non si può muovere in diagonale
        return false;
    if (delta_y != 1 && moved) //non si può muovere piu' di 2 caselle
        return false;
    if (Board[end_y][end_x].print() != ' ' && str_x == end_x)
        return false;
    moved = true;
    if (check_promotion(end_y))
    {
        cout << "Inserisci il carattere del pezzo che vuoi";
        string input;
        char in;
        while (input.length() != 1 || (in != 'D' && in != 'T' && in != 'A' && in != 'C')) //funziona
        {
            cout << "Inserisci il carattere del pezzo che vuoi";
            cin >> input;
            in = input[0];
            in = toupper(in);
        }
        switch (in)
        {
        case 'D':
            Board[end_y][end_x] = Donna(is_white, end_y, end_x);
        case 'T':
            Board[end_y][end_x] = Torre(is_white, end_y, end_x);
        case 'C':
            Board[end_y][end_x] = Torre(is_white, end_y, end_x);
        case 'A':
            Board[end_y][end_x] = Torre(is_white, end_y, end_x);
        }
        Board[str_y][str_x] = Nullo (false, str_y, str_x);
        throw PromotionException();
    }
    return true;
};

//RANDOM MOVE

template <int Y, int X>
string Piece::random_position(Piece (&Board)[Y][X], int str_y, int str_x) //ritorna le coordinate sotto forma di stringa
{
    char in = toupper(type);
    srand(time(NULL));
    switch (in)
    {
        string output;
        int end_x;
        int end_y;
        int i = 0;
    case 'R': //funziona
    {
        do
        {
            end_x = rand() % (3) + (str_x - 1); //3 possibili numeri a partire da quello a sinistra
            end_y = rand() % (3) + (str_y - 1);
            output = end_y + end_x;
            if (i == 20)
                return "XX";
            i++;
        } while (end_y < 0 || end_x < 0 || !Board[end_y][end_x].is_valid_move(Piece (&Board)[end_y][end_x], str_y, str_x, end_y, end_x);
        return output;
    };
    case 'D': //poco efficiente
    {
        do
        {
            end_x = rand() % 8; //7 possibili numeri a partire da 0
            end_y = rand() % 8;
            if (i == 60)
                return "XX";
            i++;
        } while (!Board[end_y][end_x].is_valid_move(Piece(&Board)[end_y][end_x], str_y, str_x, end_y, end_x); 
        return output;
    }
    case 'T':
    {
        do
        {
            int random = rand() % 2;
            if (random)
            {
                end_x = str_x;
                end_y = rand() % 8;
            }
            else
            {
                end_y = str_y;
                end_x = rand() % 8;
            }
            if (i == 40)
                return "XX";
            i++;
        } while (!Board[end_y][end_x].is_valid_move(Piece(&Board)[end_y][end_x], str_y, str_x, end_y, end_x); 
        return output;
    }
    case 'C': //o cosi' o con uno switch -> riga 414
    {
        do
        {
            int random_1 = rand() % 2;
            int random_2 = rand() % 2;
            int random_3 = rand() % 2;
            if (random_1)
            {
                if (random_2)
                    end_y = str_y + 1;
                else
                {
                    end_y = str_y - 1;
                }
                if (random_3)
                {
                    end_x = str_x + 2;
                }
                else
                {
                    end_x = str_x - 2;
                }
            }
            else
            {
                if (random_2)
                    end_y = str_y + 2;
                else
                {
                    end_y = str_y - 2;
                }
                if (random_3)
                    end_x = str_x + 1;
                else
                {
                    end_x = str_x - 1;
                }
            }
            if (i == 20)
                return "XX";
            i++;
        } while (!Board[end_y][end_x].is_valid_move(Piece(&Board)[end_y][end_x], str_y, str_x, end_y, end_x); 
        return output;
    }
    case 'A': //poco efficiente
    {
        do
        {
            int i = rand() % 8;
            if (end_y > str_y)
            {
                end_y = str_y + i;
                end_x = str_x - i;
            }
            else
            {
                end_y = str_y - i;
                end_x = str_x + i;
            }
            if (i == 40)
                return "XX";
            i++;
        } while (end_y < 0 || end_x < 0 || !Board[end_y][end_x].is_valid_move(Piece(&Board)[end_y][end_x], str_y, str_x, end_y, end_x); 
        return output;
    }
    case 'P':
    {
        do
        {
            if (!is_moved())
            {
                end_x = rand() % (3) + (str_x - 1); //3 possibili numeri a partire da quello a sinistra
                end_y = rand() % (2) + (str_y + 1);
            }
            else
            {
                end_x = rand() % (3) + (str_x - 1); //3 possibili numeri a partire da quello a sinistra
                end_y = (str_y + 1);
            }
            if (i == 20)
                return "XX";
            i++;
        } while (end_x < 0 || !Board[end_y][end_x].is_valid_move(Piece(&Board)[end_y][end_x], str_y, str_x, end_y, end_x); 
        return output;
    }
    }
};
#endif

/*
//RANDOM MOVE CAVALLO
int random = rand() % 8
switch(random){
    case '0':
    {
        end_y = str_y + 1;
        end_x = str_x + 2;
    }
    case '1':
    {
        end_y = str_y + 1;
        end_x = str_x - 2;
    }
    case '2':
    {
        end_y = str_y - 1;
        end_x = str_x + 2;
    }
    case '3':
    {
        end_y = str_y - 1;
        end_x = str_x - 2;
    }
    case '4':
    {
        end_y = str_y + 2;
        end_x = str_x + 1;
    }
    case '5':
    {
        end_y = str_y + 2;
        end_x = str_x - 1;
    }
    case '6':
    {
        end_y = str_y - 2;
        end_x = str_x + 1;
    }
    case '7':
    {
        end_y = str_y - 2;
        end_x = str_x - 1;
    }

}



*/