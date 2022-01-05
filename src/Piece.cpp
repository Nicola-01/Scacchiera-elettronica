//Riccardo Miele 2008594

#ifndef Piece_cpp
#define Piece_cpp

#include "Piece.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

//COSTRUTTORI

Piece::Piece() //costruttore di default
{
    white = false;
    ex_position_x = -1;
    ex_position_y = -1;
};

Piece::Piece(bool color, int y, int x) //costruttore
{
    white = color;
    ex_position_x = x;
    ex_position_y = y;
};

Piece::Piece(bool color, int y, int x, bool m) //costruttore con moved
{
    white = color;
    ex_position_x = x;
    ex_position_y = y;
    moved = m;
};

Re::Re(bool color, int y, int x) : Piece(color, y, x) //costruttore Re
{
    if (color)
        type = 'r';
    else
        type = 'R';
    moved = false;
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
    moved = false;
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
    moved = false;
};

Nullo::Nullo() : Piece() //costruttore (Pezzo) Nullo
{
    type = ' ';
};

//FUNZIONI DI PIECE

bool Piece::is_end_same_color(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) //ritorna true se la destinazione ha lo stesso colore
{
    if (Board[end_y][end_x].print() == ' ')
        return false;
    return (Board[str_y][str_x].is_white() == Board[end_y][end_x].is_white());
};

bool Piece::move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    if (is_valid_move(Board, str_y, str_x, end_y, end_x))
    {
        ex_position_x = str_x;
        ex_position_y = str_y;
        char in = toupper(Board[end_y][end_x].print());
        if (in == 'P' && ((Pedone)Board[end_y][end_x]).check_promotion(end_y))
        {
            throw PromotionException(end_y, end_x); //bisogna distruggere il pedone
        }
        if (in == 'R' && std::abs(end_x - str_x) == 2)
        {
            throw ArroccoException(end_y, end_x);
        }
        return true;
    }
    return false;
};

bool Piece::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    char in = toupper(Board[str_y][str_x].type);
    bool control = false; //control == vero is_valid_move ritorna == vero
    switch (in)
    {
    case 'R':
    {
        Re r = Re(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
        r.set_move(Board[str_y][str_x].is_moved());
        control = r.is_valid_move(Board, str_y, str_x, end_y, end_x);
        set_move(r.is_moved());
        break;
    }
    case 'D':
    {
        Donna d = Donna(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
        control = d.is_valid_move(Board, str_y, str_x, end_y, end_x);
        break;
    }
    case 'T':
    {
        Torre t = Torre(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
        t.set_move(Board[str_y][str_x].is_moved());
        control = t.is_valid_move(Board, str_y, str_x, end_y, end_x);
        set_move(t.is_moved());
        break;
    }
    case 'A':
    {
        Alfiere a = Alfiere(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
        control = a.is_valid_move(Board, str_y, str_x, end_y, end_x);
        break;
    }
    case 'C':
    {
        Cavallo c = Cavallo(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
        control = c.is_valid_move(Board, str_y, str_x, end_y, end_x);
        break;
    }
    case 'P':
    {
        Pedone p = Pedone(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
        p.set_move(Board[str_y][str_x].is_moved());
        control = p.is_valid_move(Board, str_y, str_x, end_y, end_x);
        set_move(p.is_moved());
        set_number_move(p.get_number_move());
        break;
    }
    }
    return control;
}

//ARROCCO

bool Piece::check_arrocco_re(Piece (&Board)[8][8], int end_y, int end_x)
{
    if (end_x < 4) //end_x == 2
    {
        //Torre t = Torre(Board[end_y][end_x - 2].is_white(), Board[end_y][end_x - 2].get_ex_position_y(), Board[end_y][end_x - 2].get_ex_position_y(), Board[end_y][end_x - 2].is_moved());
        Torre t = Torre(Board[end_y][end_x - 2].is_white(), Board[end_y][end_x - 2].get_ex_position_y(), Board[end_y][end_x - 2].get_ex_position_y());
        t.set_move(Board[end_y][end_x - 2].is_moved());
        if (!t.is_moved() && Board[end_y][end_x].print() == ' ' && Board[end_y][end_x + 1].print() == ' ' && Board[end_y][end_x - 1].print() == ' ')
        {
            Board[end_y][end_x - 2] = Nullo(); //(false, end_y, end_x - 1);
            //Board[end_y][end_x + 1] = Torre(is_white(), end_y, end_x + 1, true);
            Board[end_y][end_x + 1] = Torre(is_white(), end_y, end_x + 1);
            Board[end_y][end_x + 1].set_move(true);
            return true;
        }
    }
    else //end_x > 4 //end_x == 6
    {
        // Torre t = Torre(Board[end_y][end_x + 1].is_white(), Board[end_y][end_x + 1].get_ex_position_y(), Board[end_y][end_x + 1].get_ex_position_y(), Board[end_y][end_x + 1].is_moved());
        Torre t = Torre(Board[end_y][end_x + 1].is_white(), Board[end_y][end_x + 1].get_ex_position_y(), Board[end_y][end_x + 1].get_ex_position_y());
        t.set_move(Board[end_y][end_x + 1].is_moved());
        if (!t.is_moved() && Board[end_y][end_x].print() == ' ' && Board[end_y][end_x - 1].print() == ' ')
        {
            Board[end_y][end_x + 1] = Nullo(); //(false, end_y, end_x - 1);
            //Board[end_y][end_x - 1] = Torre(is_white(), end_y, end_x + 1, true);
            Board[end_y][end_x - 1] = Torre(is_white(), end_y, end_x + 1);
            Board[end_y][end_x - 1].set_move(true);
            return true;
        }
    }
    return false;
}

//FUNZIONE IS_VALID_MOVE

bool Re::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false; //destinazione stesso colore;
    if (delta_y > 1)
        return false;
    if (delta_x > 1)
    {
        if (!is_moved() && check_arrocco_re(Board, end_y, end_x))
        {
            moved = true;
            return true;
        }
        return false; //percorso > 1
    }
    moved = true;
    return true;
};

bool Donna::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    Piece p = Piece();
    bool control_condition = ((Torre)p).is_valid_move(Board, str_y, str_x, end_y, end_x) ||
                             ((Alfiere)p).is_valid_move(Board, str_y, str_x, end_y, end_x);
    return control_condition;
};

bool Torre::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (str_x != end_x && str_y != end_y)
        return false; //non si sta muovendo verticalmente o orizzontalmente
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false; //destinazione diverso colore;
    for (int i = 1; i < delta_x; i++)
    {
        if (end_x > str_x)
        {
            if (Board[end_y][str_x + i].print() != ' ')
                return false;
        }
        else
        {
            if (Board[end_y][str_x - i].print() != ' ')
                return false;
        }
    }
    for (int i = 1; i < delta_y; i++) //delta_y = 2
    {
        if (end_y > str_y)
        {
            if (Board[str_y + i][end_x].print() != ' ')
                return false;
        }
        else // str_y = 6  end_y = 4
        {
            if (Board[str_y - i][end_x].print() != ' ')
                return false;
        }
    }
    moved = true;
    return true;
};

bool Cavallo::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    //cout << delta_x << " " << delta_y << endl;
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false; //destinazione diverso colore;
    return (delta_x == 2 && delta_y == 1) || (delta_x == 1 && delta_y == 2);
};

bool Alfiere::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false; //destinazione diverso colore;
    if (delta_x != delta_y)
        return false; //non si muove in diagonale
    for (int i = 1; i < delta_x; i++)
    {
        if (end_x > str_x)
        {
            if (end_y > str_y)
            {
                if (Board[str_y + i][str_x + i].print() != ' ')
                    return false;
            }
            else
            {
                if (Board[str_y - i][str_x + i].print() != ' ')
                    return false;
            }
        }
        else
        {
            if (end_y > str_y)
            {
                if (Board[str_y + i][str_x - i].print() != ' ')
                    return false;
            }
            else
            {
                if (Board[str_y - i][str_x - i].print() != ' ')
                    return false;
            }
        }
    }
    return true;
};

bool Pedone::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) //promozione probabilmente sbagliata
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x)) //destinazione diverso colore;
        return false;
    if (delta_y > 2) //non si può muovere piu' di 2 caselle
        return false;
    if (delta_x > 1) //non si può muovere in diagonale
        return false;
    if (Board[str_y][str_x].print() == 'p') //tornare indietro, si puo' fare sicuramente meglio
    {
        if (end_y > str_y)
            return false;
    }
    else
    {
        if (end_y < str_y)
            return false;
    }

    if (delta_x == delta_y && Board[end_y][end_x].print() == ' ')
    {
        if ((Board[str_y][end_x].get_ex_position_y() == 6 || Board[str_y][end_x].get_ex_position_y() == 1) && toupper(Board[str_y][end_x].print()) == 'P' && Board[str_y][end_x].is_moved() && (n_moves - 1) == Board[str_y][end_x].get_number_move()) //en passant
        {
            {
                Board[str_y][end_x] = Nullo(); //en passant in teoria giusto
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    if (delta_x == 0 && Board[end_y][end_x].print() != ' ') //non può mangiare in avanti
    {
        return false;
    }
    if (delta_y == 2)
    {
        if (moved)
            return false;
        else
        {
            if (delta_x != 0)
                return false;
        }
        set_number_move(n_moves);
    }
    moved = true;
    return true;
};

//RANDOM MOVE

std::pair<int, int> Piece::random_position(Piece (&Board)[8][8], int str_y, int str_x) //ritorna le coordinate sotto forma di stringa
{
    char in = toupper(type);
    srand(time(NULL));
    std::pair<int, int> output;
    Piece tmp = Piece(false, 0, 0); //serve solo per invocare il metodo giusto
    switch (in)
    {
    case 'R': //funziona
    {
        output = ((Re)tmp).random_xy(Board, str_y, str_x);
        break;
    };
    case 'D': //poco efficiente
    {
        int i = 0;
        do
        {
            if (i >= 40)
            {
                output.first = -1; //non so se serva
                output.second = -1;
                break;
            }
            int torre_alfiere = rand() % 2;
            if (torre_alfiere)
            {
                output = ((Torre)tmp).random_xy(Board, str_y, str_x);
            }
            else
            {
                output = ((Alfiere)tmp).random_xy(Board, str_y, str_x);
            }
            i++;
        } while (output.first == -1);
        break;
    }
    case 'T':
    {
        output = ((Torre)tmp).random_xy(Board, str_y, str_x);
        break;
    }
    case 'C': //o cosi' o con uno switch -> riga 414
    {
        output = ((Cavallo)tmp).random_xy(Board, str_y, str_x);
        break;
    }
    case 'A':
    {
        output = ((Alfiere)tmp).random_xy(Board, str_y, str_x);
        break;
    }
    case 'P':
    {
        output = ((Pedone)tmp).random_xy(Board, str_y, str_x);
        break;
    }
    }
    return output;
};

//RANDOM PER OGNI PEZZO

std::pair<int, int> Re::random_xy(Piece (&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x;
    int i = 0;
    std::pair<int, int> output{-1, -1};
    do
    {
        end_x = rand() % (3) + (str_x - 1); //3 possibili numeri a partire da quello a sinistra
        end_y = rand() % (3) + (str_y - 1); //3 possibili numeri a partire da quello a sotto
        if (i >= 20)
        {
            end_y = -1;
            end_x = -1;
            break;
        }
        i++;
    } while (!(check_boundary(end_y, end_x) && is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    return output; //se non trova niente ritorna -1-1
};

std::pair<int, int> Torre::random_xy(Piece (&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x;
    int i = 0;
    std::pair<int, int> output{-1, -1};
    do
    {
        int random = rand() % 2;
        if (random)
        {
            end_x = str_x; //se random == 1 si muove in verticale
            end_y = rand() % 8;
        }
        else
        {
            end_y = str_y; //si muove in orizzontale
            end_x = rand() % 8;
        }
        if (i >= 40)
        {
            end_y = -1;
            end_x = -1;
            break; //se non trova niente ritorna -1-1
        }
        i++;
    } while (!(check_boundary(end_y, end_x) && is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    return output;
};

std::pair<int, int> Cavallo::random_xy(Piece (&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x;
    int i = 0;
    std::pair<int, int> output{-1, -1};
    do
    {
        int random_1 = rand() % 2;
        int random_2 = rand() % 2;
        int random_3 = rand() % 2;
        if (random_1) //se random_1 == 1 delta_y = 1
        {
            if (random_2) //se random_2 == 1 end_y > str_y
                end_y = str_y + 1;
            else
            {
                end_y = str_y - 1;
            }
            if (random_3) //se random_3 == 1 end_x > str_x
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
            if (random_2) //se random_2 == 1 end_y > str_y
                end_y = str_y + 2;
            else
            {
                end_y = str_y - 2;
            }
            if (random_3) //se random_3 == 1 end_x > str_x
                end_x = str_x + 1;
            else
            {
                end_x = str_x - 1;
            }
        }
        if (i >= 20)
        {
            end_y = -1;
            end_x = -1;
            break; //se non trova niente ritorna -1-1
        }
        i++;
    } while (!(check_boundary(end_y, end_x) && is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    return output;
};

std::pair<int, int> Alfiere::random_xy(Piece (&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x, i;
    std::pair<int, int> output{-1, -1};
    int cont = 0;
    do
    {
        i = 1 + rand() % 7; //7 possibili numeri a partire da 0
        int up_down = rand() % 2;
        int right_left = rand() % 2;
        if (up_down) //se up_down == 1 si muove verso l'alto
            end_y = str_y - i;
        else
        {
            end_y = str_y + i;
        }
        if (right_left) // rigth_left == 1 si muove verso destra
            end_x = str_x + i;
        else
        {
            end_x = str_x - i;
        }
        if (cont >= 40)
        {
            end_y = -1;
            end_x = -1;
            break; //se non trova niente ritorna -1-1
        }
        cont++;
    } while (!(check_boundary(end_y, end_x) && is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    return output;
};

std::pair<int, int> Pedone::random_xy(Piece (&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x;
    int i = 0;
    std::pair<int, int> output{-1, -1};
    //Pedone p = Pedone(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x(), Board[str_y][str_x].is_moved());
    Pedone p = Pedone(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
    p.set_move(Board[str_y][str_x].is_moved());
    do
    {
        int d_y;
        end_x = rand() % (3) + (str_x - 1); //3 possibili numeri a partire da quello a sinistra
        if (!p.is_moved())                  //si può muovere di due
        {
            d_y = 1 + rand() % 2;
        }
        else
        {

            d_y = 1;
        }
        if (p.is_white())
        {
            end_y = str_y - d_y;
        }
        else
        {
            end_y = str_y + d_y;
        }
        if (p.check_promotion(end_y) && check_boundary(end_y, end_x) && !is_end_same_color(Board, str_y, str_x, end_y, end_x))
        {
            int random = rand() % 4; //4 possibili numeri a partire da 0
            switch (random)
            {
            case 0: //donna
            {
                Board[end_y][end_x] = Donna(is_white(), end_y, end_x);
                break;
            }
            case 1: //torre
            {
                Board[end_y][end_x] = Torre(is_white(), end_y, end_x);
                break;
            }
            case 2: //cavallo
            {
                Board[end_y][end_x] = Cavallo(is_white(), end_y, end_x);
                break;
            }
            case 3: //alfiere
            {
                Board[end_y][end_x] = Alfiere(is_white(), end_y, end_x);
                break;
            }
            }
            Board[str_y][str_x] = Nullo(); //(false, str_y, str_x);
            //bisogna distruggere il pedone
            throw PromotionException(end_y, end_x);
        }
        if (i >= 20)
        {
            end_y = -1;
            end_x = -1;
            return output; //se non trova niente ritorna -1-1
        }
        i++;
    } while (!(check_boundary(end_y, end_x) && is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    return output;
};

#endif

/*
is_valid_move pedone
if (delta_y == 2 && moved)
    {
        return false;
    }
    if (delta_y == 2 && !moved)
    {
        if (delta_x != 0)
            return false;
    }
    if (delta_y == 2)
    {
        set_number_move(n_moves);
    }
    //&& delta_x == 0
    //if (delta_y == 2 && delta_x != 0)
    // {
    //   return false;
    //}


*/

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

//IS_VALID_MOVE PEDONE FUNZIONANTE PARZIALMENTE

bool Pedone::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) //promozione probabilmente sbagliata
{
    //cout << is_white() << " " << Board[end_y][end_x].is_white() << endl;
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x)) //destinazione diverso colore;
        return false;
    //cout << "DP";
    // if ((Board[str_y][end_x].get_ex_position_y() == 6 || Board[str_y][end_x].get_ex_position_y() == 1) && toupper(Board[str_y][end_x].print()) == 'P') //en passant
    // {
    //     Board[str_y][end_x] = Nullo(false, str_y, str_x); //en passant in teoria giusto
    //     return true;
    // }
    if (delta_y > 2) //non si può muovere piu' di 2 caselle
        return false;
    if (delta_y == delta_x && delta_y == 1 && Board[end_y][end_x].print() != ' ')
        return true;
    if (delta_x > 0) //non si può muovere in diagonale
        return false;
    if (delta_y == 2 && !moved)
    {
        moved = true;
        return true;
    }

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
        {
            Board[end_y][end_x] = Donna(is_white(), end_y, end_x);
            break;
        }
        case 'T':
        {
            Board[end_y][end_x] = Torre(is_white(), end_y, end_x);
            break;
        }
        case 'C':
        {
            Board[end_y][end_x] = Torre(is_white(), end_y, end_x);
            break;
        }
        case 'A':
        {
            Board[end_y][end_x] = Torre(is_white(), end_y, end_x);
            break;
        }
        }
        Board[str_y][str_x] = Nullo(false, str_y, str_x);
        //bisogna distruggere il pedone
        throw PromotionException();
    }
    return true;
};

*/