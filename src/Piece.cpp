//Riccardo Miele 2008594

#include "Piece.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

//helper function
bool check_promotion(int y) { return y == 0 || y == 7; }; //se arrivato alla fine e' true
bool check_boundary(int end_y, int end_x) { return end_y > -1 && end_x > -1 && end_y < 8 && end_x < 8; };

//COSTRUTTORI

Re::Re(bool color, int y, int x) : Piece(color, y, x) //costruttore Re
{
    type = ((color) ? 'r' : 'R');
    moved = false;
};

Donna::Donna(bool color, int y, int x) : Piece(color, y, x) //costruttore Donna
{
    type = ((color) ? 'd' : 'D');
};

Torre::Torre(bool color, int y, int x) : Piece(color, y, x) //costruttore Torre
{
    type = ((color) ? 't' : 'T');
    moved = false;
};

Alfiere::Alfiere(bool color, int y, int x) : Piece(color, y, x) //costruttore Alfiere
{
    type = ((color) ? 'a' : 'A');
};

Cavallo::Cavallo(bool color, int y, int x) : Piece(color, y, x) //costruttore Cavallo
{
    type = ((color) ? 'c' : 'C');
};

Pedone::Pedone(bool color, int y, int x) : Piece(color, y, x) //costruttore Pedone
{
    type = ((color) ? 'p' : 'P');
    moved = false;
};

Nullo::Nullo() : Piece() //costruttore (Pezzo) Nullo
{
    type = ' ';
};

//FUNZIONI DI PIECE

bool Piece::is_end_same_color(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x) //ritorna true se la destinazione ha lo stesso colore
{
    if (Board[end_y][end_x]->print() == ' ')
        return false;
    return (Board[str_y][str_x]->is_white() == Board[end_y][end_x]->is_white());
};

bool Piece::move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    if (is_valid_move(Board, str_y, str_x, end_y, end_x))
    {
        ex_position_x = str_x;
        ex_position_y = str_y;
        moved = true;
        char in = toupper(Board[str_y][str_x]->print());
        if (in == 'P' && check_promotion(end_y))
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

//ARROCCO

bool Piece::check_arrocco_re(Piece *(&Board)[8][8], int end_y, int end_x)
{
   // std::cout << "arrocco";
    if (end_x < 4) //end_x == 2
    {
        //Torre t = Torre(Board[end_y][end_x - 2].is_white(), Board[end_y][end_x - 2].get_ex_position_y(), Board[end_y][end_x - 2].get_ex_position_y());
        //t.moved = Board[end_y][end_x - 2].is_moved(); //non so se serva
        if (!Board[end_y][end_x - 2]->is_moved() && Board[end_y][end_x]->print() == ' ' && Board[end_y][end_x + 1]->print() == ' ' && Board[end_y][end_x - 1]->print() == ' ')
        {
            delete Board[end_y][end_x - 2];
            delete Board[end_y][end_x + 1];
            Board[end_y][end_x - 2] = new Nullo();
            Board[end_y][end_x + 1] = new Torre(is_white(), end_y, end_x + 1);
            Board[end_y][end_x + 1]->moved = true;
            return true;
        }
    }
    else //end_x > 4 //end_x == 6
    {
        //Torre t = Torre(Board[end_y][end_x + 1].is_white(), Board[end_y][end_x + 1].get_ex_position_y(), Board[end_y][end_x + 1].get_ex_position_y());
        //t.moved = Board[end_y][end_x + 1].is_moved(); //non so se serva
        if (!Board[end_y][end_x + 1]->is_moved() && Board[end_y][end_x]->print() == ' ' && Board[end_y][end_x - 1]->print() == ' ')
        {
            delete Board[end_y][end_x + 1];
            delete Board[end_y][end_x - 1];
            Board[end_y][end_x + 1] = new Nullo();
            Board[end_y][end_x - 1] = new Torre(is_white(), end_y, end_x + 1);
            Board[end_y][end_x - 1]->moved = true;
            return true;
        }
    }
    return false;
}

//FUNZIONE IS_VALID_MOVE

bool Re::is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false; //destinazione stesso colore;
    if (delta_y > 1)
        return false;
    if (delta_x > 1 && (Board[str_y][str_x]->is_moved() || !check_arrocco_re(Board, end_y, end_x)))
    {
       // std::cout << is_moved() << check_arrocco_re(Board, end_y, end_x);
        return false; //percorso > 1
    }
    return true;
};

bool Donna::is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    //Torre t = Board[str_y][str_x];
    Torre *t = new Torre(is_white(), str_y, str_x);
    Alfiere *a = new Alfiere(is_white(), str_y, str_x);
    bool control_condition = (a->is_valid_move(Board, str_y, str_x, end_y, end_x) || t->is_valid_move(Board, str_y, str_x, end_y, end_x));
    delete t;
    delete a;
    return control_condition;
};

bool Torre::is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
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
            if (Board[end_y][str_x + i]->print() != ' ')
                return false;
        }
        else
        {
            if (Board[end_y][str_x - i]->print() != ' ')
                return false;
        }
    }
    for (int i = 1; i < delta_y; i++) //delta_y = 2
    {
        if (end_y > str_y)
        {
            if (Board[str_y + i][end_x]->print() != ' ')
                return false;
        }
        else // str_y = 6  end_y = 4
        {
            if (Board[str_y - i][end_x]->print() != ' ')
                return false;
        }
    }
    return true;
};

bool Cavallo::is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false; //destinazione diverso colore;
    return (delta_x == 2 && delta_y == 1) || (delta_x == 1 && delta_y == 2);
};

bool Alfiere::is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
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
                if (Board[str_y + i][str_x + i]->print() != ' ')
                    return false;
            }
            else
            {
                if (Board[str_y - i][str_x + i]->print() != ' ')
                    return false;
            }
        }
        else
        {
            if (end_y > str_y)
            {
                if (Board[str_y + i][str_x - i]->print() != ' ')
                    return false;
            }
            else
            {
                if (Board[str_y - i][str_x - i]->print() != ' ')
                    return false;
            }
        }
    }
    return true;
};

bool Pedone::is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x) //promozione probabilmente sbagliata
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x)) //destinazione diverso colore;
        return false;
    if (delta_y > 2 || delta_x > 1 || delta_y == 0) //non si può muovere piu' di 2 caselle o non si può muovere in diagonale
        return false;
    if (Board[str_y][str_x]->print() == 'p') //tornare indietro, si puo' fare sicuramente meglio
    {
        if (end_y > str_y)
            return false;
    }
    else
    {
        if (end_y < str_y)
            return false;
    }
    if (delta_x == delta_y && Board[end_y][end_x]->print() == ' ')
    {
        //std::cout << Board[str_y][end_x]->get_number_move() << n_moves - 1 << std::endl;
        if ((Board[str_y][end_x]->get_ex_position_y() == 6 || Board[str_y][end_x]->get_ex_position_y() == 1) && toupper(Board[str_y][end_x]->print()) == 'P' && Board[str_y][end_x]->is_moved() && (n_moves - 1) == Board[str_y][end_x]->get_number_move()) //en passant
        {
            {
                delete Board[str_y][end_x];
                Board[str_y][end_x] = new Nullo(); //en passant in teoria giusto
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    if (delta_x == 0 && Board[end_y][end_x]->print() != ' ') //non può mangiare in avanti
        return false;
    if (delta_y == 2)
    {
        if (delta_x == 0)
        {
            if (Board[str_y][str_x]->print() == 'p') //tornare indietro, si puo' fare sicuramente meglio
            {
                //str_y > end_y
                if (Board[end_y + 1][end_x]->print() != ' ')
                    return false;
            }
            else
            {
                if (Board[end_y - 1][end_x]->print() != ' ')
                    return false;
            }
        }
        if (is_moved()) //moved
            return false;
        else
        {
            if (delta_x != 0)
                return false;
        }
        set_number_move(n_moves);
    }
    return true;
};

//RANDOM PER OGNI PEZZO

std::pair<int, int> Re::random_xy(Piece *(&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x;
    int cont{0};
    std::pair<int, int> output{-1, -1};
    if (!has_valid_move(Board, str_y, str_x))
        return output;
    do
    {
        end_x = rand() % (3) + (str_x - 1); //3 possibili numeri a partire da quello a sinistra
        end_y = rand() % (3) + (str_y - 1); //3 possibili numeri a partire da quello a sotto
        if (cont == 20)
        {
            end_y = -1;
            end_x = -1;
            break;
        }
        cont++;
    } while (!(check_boundary(end_y, end_x) && is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    return output; //se non trova niente ritorna -1-1
};

std::pair<int, int> Torre::random_xy(Piece *(&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x;
    int cont{0};
    std::pair<int, int> output{-1, -1};
    if (!has_valid_move(Board, str_y, str_x))
        return output;
    do
    {
        int up_rigth = rand() % 2;
        if (up_rigth)
        {
            end_x = str_x; //se random == 1 si muove in verticale
            end_y = rand() % 8;
        }
        else
        {
            end_y = str_y; //si muove in orizzontale
            end_x = rand() % 8;
        }
        if (cont == 40)
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

std::pair<int, int> Cavallo::random_xy(Piece *(&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x;
    int cont{0};
    std::pair<int, int> output{-1, -1};
    if (!has_valid_move(Board, str_y, str_x))
        return output;
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
        if (cont == 20)
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

std::pair<int, int> Alfiere::random_xy(Piece *(&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x, i;
    std::pair<int, int> output{-1, -1};
    if (!has_valid_move(Board, str_y, str_x))
        return output;
    int cont{0};
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
        if (cont == 40)
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

std::pair<int, int> Pedone::random_xy(Piece *(&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x, d_y;
    int cont{0};
    std::pair<int, int> output{-1, -1};
    if (!has_valid_move(Board, str_y, str_x))
        return output;
    Pedone *p = new Pedone(Board[str_y][str_x]->is_white(), Board[str_y][str_x]->get_ex_position_y(), Board[str_y][str_x]->get_ex_position_x());
    p->moved = Board[str_y][str_x]->is_moved(); //non so se serva
    do
    {
        int d_y{1};
        end_x = str_x;
        if (!p->is_moved())
            d_y = 1 + rand() % 2;

        if (d_y == 1)
            end_x = rand() % (3) + (str_x - 1); // 3 possibili numeri a partire da quello a sinistra

        end_y = (p->is_white()) ? str_y - d_y : str_y + d_y;
        // std::cout << "cp" << check_promotion(end_y) << " " << end_y << " == 0, cb" << check_boundary(end_y, end_x) << " == 1, iesc" << !is_end_same_color(Board, str_y, str_x, end_y, end_x) << "== 1" << std::endl;
        if (check_promotion(end_y) && check_boundary(end_y, end_x) && !is_end_same_color(Board, str_y, str_x, end_y, end_x))
        {
            int random = rand() % 4; //4 possibili numeri a partire da 0
          //  std::cout << "random == " << random;
            delete Board[end_y][end_x];
            switch (random)
            {
            case 0: //donna
            {
                Board[end_y][end_x] = new Donna(is_white(), end_y, end_x);
                break;
            }
            case 1: //torre
            {
                Board[end_y][end_x] = new Torre(is_white(), end_y, end_x);
                break;
            }
            case 2: //cavallo
            {
                Board[end_y][end_x] = new Cavallo(is_white(), end_y, end_x);
                break;
            }
            case 3: //alfiere
            {
                Board[end_y][end_x] = new Alfiere(is_white(), end_y, end_x);
                break;
            }
            }
            delete Board[str_y][str_x];
            Board[str_y][str_x] = new Nullo();
            throw PromotionException(end_y, end_x);
        }
        if (cont == 20)
        {
            end_y = -1;
            end_x = -1;
            return output; //se non trova niente ritorna -1-1
        }
        cont++;
    } while (!(check_boundary(end_y, end_x) && p->is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    delete p;
    return output;
};

std::pair<int, int> Donna::random_xy(Piece *(&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x, d_y;
    std::pair<int, int> output{-1, -1};
    if (!has_valid_move(Board, str_y, str_x))
        return output;
    int torre_alfiere = rand() % 2;
    Piece *t = new Torre(Board[str_y][str_x]->is_white(), Board[str_y][str_x]->get_ex_position_y(), Board[str_y][str_x]->get_ex_position_x());
    Alfiere *a = new Alfiere(Board[str_y][str_x]->is_white(), Board[str_y][str_x]->get_ex_position_y(), Board[str_y][str_x]->get_ex_position_x());
    for (int i = 0; i < 2 && output.first == -1; i++)
    {
        if (torre_alfiere)
        {
            output = t->random_xy(Board, str_y, str_x);
            torre_alfiere--;
        }
        else
        {
            output = a->random_xy(Board, str_y, str_x);
            torre_alfiere++;
        }
    }
    delete t;
    delete a;
    return output;
};

std::pair<int, int> Nullo::random_xy(Piece *(&Board)[8][8], int str_y, int str_x)
{
    std::pair<int, int> output{-1, -1};
    return output;
};
