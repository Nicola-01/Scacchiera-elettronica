//Riccardo Miele 2008594

#ifndef Piece_cpp
#define Piece_cpp

#include "Piece.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

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

Re::Re(bool color, int y, int x, bool m) : Piece(color, y, x, m)
{
    if (color)
        type = 'r';
    else
        type = 'R';
    moved = m;
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

Torre::Torre(bool color, int y, int x, bool m) : Piece(color, y, x, m)
{
    if (color)
        type = 't';
    else
        type = 'T';
    moved = m;
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

Pedone::Pedone(bool color, int y, int x, bool m) : Piece(color, y, x, m)
{
    if (color)
        type = 'p';
    else
        type = 'P';
    moved = m;
}

Nullo::Nullo(bool color, int y, int x) : Piece(color, y, x) //costruttore (Pezzo) Nullo
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
    char in = toupper(Board[str_y][str_x].type);
    bool control = false; //control == vero is_valid_move ritorna == vero
                          // cout << "-- Tipo Pezzo: " << in << endl;
    //cout << "Spostamento [y][x] (str), (end) [" << str_y << "][" << str_x << "] [" << end_y << "][" << end_x << "]\n";
    switch (in)
    {
    case 'R':
    {
        Re r = Re(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x(), Board[str_y][str_x].is_moved());
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
        Torre t = Torre(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x(), Board[str_y][str_x].is_moved());
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
        Pedone p = Pedone(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x(), Board[str_y][str_x].is_moved());
        control = p.is_valid_move(Board, str_y, str_x, end_y, end_x);
        set_move(p.is_moved());
        break;
    }
    }
    if (control)
    {
        ex_position_x = str_x;
        ex_position_y = str_y;
        return true;
    }
    return false;
};

//ARROCCO

bool Piece::check_arrocco_re(Piece (&Board)[8][8], int end_y, int end_x)
{
    if (end_x < 4)
    {
        Torre t = Torre(Board[end_y][end_x - 1].is_white(), Board[end_y][end_x - 1].get_ex_position_y(), Board[end_y][end_x - 1].get_ex_position_y());
        if (!t.is_moved() && Board[end_y][end_x].print() != ' ' && Board[end_y][end_x + 1].print() != ' ' && Board[end_y][end_x - 1].print() != ' ')
        {
            Board[end_y][end_x - 2] = Nullo(false, end_y, end_x - 1);
            Board[end_y][end_x + 1] = Torre(is_white(), end_y, end_x + 1);
            return true;
        }
        return false;
    }
    else //end_x > 4
    {
        Torre t = Torre(Board[end_y][end_x + 1].is_white(), Board[end_y][end_x + 1].get_ex_position_y(), Board[end_y][end_x + 1].get_ex_position_y());
        if (!t.is_moved() && Board[end_y][end_x].print() != ' ' && Board[end_y][end_x - 1].print() != ' ')
        {
            Board[end_y][end_x + 1] = Nullo(false, end_y, end_x - 1);
            Board[end_y][end_x - 1] = Torre(is_white(), end_y, end_x + 1);
            return true;
        }
        return false;
    }
}

bool Piece::check_arrocco_torre(Piece (&Board)[8][8], int end_y, int end_x)
{
    if (end_x < 4)
    {
        Re r = Re(Board[end_y][end_x - 1].is_white(), Board[end_y][end_x - 1].get_ex_position_y(), Board[end_y][end_x - 1].get_ex_position_y());
        if (!r.is_moved() && Board[end_y][end_x].print() != ' ' && Board[end_y][end_x - 1].print() != ' ' && Board[end_y][end_x - 2].print() != ' ')
        {
            Board[end_y][end_x - 1] = Re(is_white(), end_y, end_x + 1);
            Board[end_y][end_x + 1] = Nullo(false, end_y, end_x - 1);
            return true;
        }
        return false;
    }
    else //end_x > 4
    {
        Re r = Re(Board[end_y][end_x + 1].is_white(), Board[end_y][end_x + 1].get_ex_position_y(), Board[end_y][end_x + 1].get_ex_position_y());
        if (!r.is_moved() && Board[end_y][end_x].print() != ' ' && Board[end_y][end_x + 1].print() != ' ')
        {
            Board[end_y][end_x - 1] = Nullo(false, end_y, end_x + 1);
            Board[end_y][end_x + 1] = Re(is_white(), end_y, end_x - 1);
            return true;
        }
        return false;
    }
};

//FUNZIONE IS_VALID_MOVE

bool Re::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false; //destinazione stesso colore;
    if (delta_x != 1 || delta_y != 1)
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
    return true;
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false;
    if (str_x != end_x && str_y != end_y)
        return false;              //destinazione diverso colore;
    bool control_condition = true; //true se si può fare la mossa
    if (delta_x == delta_y)        //controllo come se fosse un alfiere
    {
        for (int i = 1; i < delta_x; i++)
        {
            if (end_y > str_y)
            {
                if (Board[str_y + i][str_x - i].print() != ' ')
                {
                    control_condition = false;
                    break;
                }
            }
            else
            {
                if (Board[str_y - i][str_x + i].print() != ' ')
                {
                    control_condition = false;
                    break;
                }
            }
        }
    }
    else
    {
        for (int i = 1; i < delta_x; i++) //controllo come se fosse una torre
        {
            if (end_x > str_x)
            {
                if (Board[end_y][str_x + i].print() != ' ')
                {
                    control_condition = false;
                    break;
                }
            }
            else
            {
                if (Board[end_y][str_x - i].print() != ' ')
                {
                    control_condition = false;
                    break;
                }
            }
        }
        for (int i = 1; i < delta_y; i++)
        {
            if (end_y > str_y)
            {
                if (Board[str_y + i][end_x].print() != ' ')
                {
                    control_condition = false;
                    break;
                }
            }
            else
            {
                if (Board[str_y - i][end_x].print() != ' ')
                {
                    control_condition = false;
                    break;
                }
            }
        }
    }
    return control_condition;
};

bool Torre::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (str_x != end_x && str_y != end_y)
        return false; //non si muove verticalmente o orizzontalmente
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false; //destinazione diverso colore;
    if (!is_moved() && check_arrocco_torre(Board, end_y, end_x))
    {
        moved = true;
        return true;
    }
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
        //cout << "ciclo for " << i << " " << delta_y << endl;
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
        //cout << str_y-i << " " << end_x << " " << Board[str_y - i][end_x].print()<<endl;
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
        if (end_y > str_y)
        {
            if (Board[str_y + i][str_x - i].print() != ' ')
                return false;
        }
        else
        {
            if (Board[str_y - i][str_x + i].print() != ' ')
                return false;
        }
    }
    return true;
};

bool Pedone::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) //promozione probabilmente sbagliata
{
    //cout << is_white() << " " << Board[end_y][end_x].is_white() << endl;
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x)) //destinazione diverso colore;
        return false;
    if (delta_y > 2) //non si può muovere piu' di 2 caselle
        return false;
    if (delta_x > 1) //non si può muovere in diagonale
        return false;
    if (is_white()) //tornare indietro, si puo' fare sicuramente meglio
    {
        if(end_y > str_y)  
            return false;
    }
    else{
        if(end_y < str_y)
            return false;
    }
    if (delta_x == delta_y)
    {
        if (Board[end_y][end_x].print() == ' ')
        {
            return false;
        }
        if ((Board[str_y][end_x].get_ex_position_y() == 6 || Board[str_y][end_x].get_ex_position_y() == 1) && toupper(Board[str_y][end_x].print()) == 'P' && Board[str_y][end_x].is_moved()) //en passant
        {
            Board[str_y][end_x] = Nullo(false, str_y, str_x); //en passant in teoria giusto
            return true;
        }
        
    }
    if (end_x == 0 && Board[end_y][end_x].print() != ' ') //non può mangiare in avanti
    {
        return false;
    }
    //delta_y == 2 && (Board[str_y][str_x].get_ex_position_y() == 6 || Board[str_y][str_x].get_ex_position_y() == 1)
    if (delta_y == 2 && moved)
    {
        return false;
    }

    if (check_promotion(end_y))
    {
        string input;
        char in;
        while (input.length() != 1 || (in != 'D' && in != 'T' && in != 'A' && in != 'C')) //funziona
        {
            cout << "Inserisci il carattere del pezzo che vuoi (D, T, C, A)" << endl;
            getline(cin, input);
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
            Board[end_y][end_x] = Cavallo(is_white(), end_y, end_x);
            break;
        }
        case 'A':
        {
            Board[end_y][end_x] = Alfiere(is_white(), end_y, end_x);
            break;
        }
        }
        Board[str_y][str_x] = Nullo(false, str_y, str_x);
        //bisogna distruggere il pedone
        throw PromotionException();
    }
    moved = true;
    return true;
};

//RANDOM MOVE
//risolvere promozione pedone
pair<int, int> Piece::random_position(Piece (&Board)[8][8], int str_y, int str_x) //ritorna le coordinate sotto forma di stringa
{
    char in = toupper(type);
    srand(time(NULL));
    pair<int, int> output{-1, -1};
    int end_x;
    int end_y;
    int i = 0;
    switch (in)
    {
    case 'R': //funziona
    {
        do
        {
            end_x = rand() % (3) + (str_x - 1); //3 possibili numeri a partire da quello a sinistra
            end_y = rand() % (3) + (str_y - 1); //3 possibili numeri a partire da quello a sotto
            if (i >= 20)
                return output; //se non trova niente ritorna XX
            i++;
        } while (check_boundary(end_y, end_x) || !move(Board, str_y, str_x, end_y, end_x));
        break;
    };
    case 'D': //poco efficiente
    {
        do
        {
            end_x = rand() % 8; //7 possibili numeri a partire da 0
            end_y = rand() % 8; //7 possibili numeri a partire da 0
            if (i >= 60)
                return output; //se non trova niente ritorna XX
            i++;
        } while (check_boundary(end_y, end_x) || !move(Board, str_y, str_x, end_y, end_x));
        break;
    }
    case 'T':
    {
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
                return output; //se non trova niente ritorna XX
            i++;
        } while (check_boundary(end_y, end_x) || !move(Board, str_y, str_x, end_y, end_x));
        break;
    }
    case 'C': //o cosi' o con uno switch -> riga 414
    {
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
                return output; //se non trova niente ritorna XX
            i++;
        } while (check_boundary(end_y, end_x) || !move(Board, str_y, str_x, end_y, end_x));
        break;
    }
    case 'A':
    {

        do
        {
            int cont = 0;
            int i = 1 + rand() % 7; //7 possibili numeri a partire da 0
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
                return output; //se non trova niente ritorna XX
            cont++;
        } while (check_boundary(end_y, end_x) || !move(Board, str_y, str_x, end_y, end_x));
        break;
    }
    case 'P':
    {
        Pedone p = Pedone(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x(), Board[str_y][str_x].is_moved());
        do
        {

            if (!p.is_moved()) //si può muovere di due
            {
                end_x = rand() % (3) + (str_x - 1); //3 possibili numeri a partire da quello a sinistra
                end_y = rand() % (2) + (str_y + 1); //2 possibili numeri a partire da quello str_y + 1
            }
            else
            {
                end_x = rand() % (3) + (str_x - 1); //3 possibili numeri a partire da quello a sinistra
                end_y = (str_y + 1);
            }
            if (p.check_promotion(end_y))
            {
                int random = rand() % 4; //4 possibili numeri a partire da 0
                switch (random)
                {
                case '0': //donna
                {
                    Board[end_y][end_x] = Donna(is_white(), end_y, end_x);
                    break;
                }
                case '1': //torre
                {
                    Board[end_y][end_x] = Torre(is_white(), end_y, end_x);
                    break;
                }
                case '2': //cavallo
                {
                    Board[end_y][end_x] = Cavallo(is_white(), end_y, end_x);
                    break;
                }
                case '3': //alfiere
                {
                    Board[end_y][end_x] = Alfiere(is_white(), end_y, end_x);
                    break;
                }
                }
                Board[str_y][str_x] = Nullo(false, str_y, str_x);
                //bisogna distruggere il pedone
                throw PromotionException();
            }
            if (i >= 20)
                return output; //se non trova niente ritorna XX
            i++;
        } while (check_boundary(end_y, end_x) || !move(Board, str_y, str_x, end_y, end_x));
        break;
    }
    }
    output.first = end_y;
    output.second = end_x;
    return output;
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