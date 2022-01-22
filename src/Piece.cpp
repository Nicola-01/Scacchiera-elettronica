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

Cavallo::Cavallo(bool color, int y, int x) : Piece(color, y, x) //costruttore Cavallo
{
    type = ((color) ? 'c' : 'C');
};

Alfiere::Alfiere(bool color, int y, int x) : Piece(color, y, x) //costruttore Alfiere
{
    type = ((color) ? 'a' : 'A');
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

bool Piece::move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x) //controlla la validita' e aggiorna le ex posizioni
{
    if (is_valid_move(Board, str_y, str_x, end_y, end_x))
    {
        ex_position_x = str_x;
        ex_position_y = str_y;
        moved = true;
        char in = toupper(Board[str_y][str_x]->print());
        if (in == 'P' && check_promotion(end_y)) //se e' stata fatta una promozione viene ritornata un eccezione con le ex coordinate per ripristinare in caso di scacco
        {
            throw PromotionException(end_y, end_x);
        }
        if (in == 'R' && std::abs(end_x - str_x) == 2) //stessa cosa della promozione ma per l'arrocco
        {
            throw ArroccoException(end_y, end_x);
        }
        return true;
    }
    return false;
};

//ARROCCO
//controlla l'arrocco e gestisce lo spostamento del secondo pezzo

bool Piece::check_arrocco_re(Piece *(&Board)[8][8], int end_y, int end_x)
{
    if (end_x < 4) //controllo arrocco corto o lungo
    {
        if (!Board[end_y][end_x - 2]->is_moved() //controllo se la torre si e' mossa
            && Board[end_y][end_x]->print() == ' ' && Board[end_y][end_x + 1]->print() == ' ' &&
            Board[end_y][end_x - 1]->print() == ' ') //controllo le caselle in mezzo
        {
            delete Board[end_y][end_x - 2];
            delete Board[end_y][end_x + 1];
            Board[end_y][end_x - 2] = new Nullo(); //creo i pezzi nuovi lasciando lo spostamento del re alla scacchiera
            Board[end_y][end_x + 1] = new Torre(is_white(), end_y, end_x + 1);
            Board[end_y][end_x + 1]->moved = true;
            return true;
        }
    }
    else //arrocco corto
    {
        if (!Board[end_y][end_x + 1]->is_moved()                                               //controllo se la torre si e' gia' mossa
            && Board[end_y][end_x]->print() == ' ' && Board[end_y][end_x - 1]->print() == ' ') //controllo pezzi in mezzo
        {
            delete Board[end_y][end_x + 1];
            delete Board[end_y][end_x - 1];
            Board[end_y][end_x + 1] = new Nullo(); //creo i nuovi pezzi
            Board[end_y][end_x - 1] = new Torre(is_white(), end_y, end_x + 1);
            Board[end_y][end_x - 1]->moved = true;
            return true;
        }
    }
    return false;
}

//FUNZIONE IS_VALID_MOVE
//ritorna true se lo spostamento e' valido

bool Re::is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false; //destinazione stesso colore;
    if (delta_y > 1 || delta_x > 2)
        return false;
    if (delta_x == 2 && (Board[str_y][str_x]->is_moved() || !check_arrocco_re(Board, end_y, end_x)))
    {
        return false; //percorso > 1
    }
    return true;
};

bool Donna::is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    Torre *t = new Torre(is_white(), str_y, str_x); //controllo come se fosse una torre ed un alfiere e invoco le rispettive funzioni
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
        return false;                 //destinazione stesso colore
    for (int i = 1; i < delta_x; i++) //controllo che non ci siano pezzi in mezzo sulle x
    {
        if (end_x > str_x)
        {
            if (Board[end_y][str_x + i]->print() != ' ') //non puo' scavalcare
                return false;
        }
        else
        {
            if (Board[end_y][str_x - i]->print() != ' ') //non puo' scavalcare
                return false;
        }
    }
    for (int i = 1; i < delta_y; i++) //controllo che non ci siano pezzi in mezzo sulle y
    {
        if (end_y > str_y)
        {
            if (Board[str_y + i][end_x]->print() != ' ') //non puo' scavalcare
                return false;
        }
        else
        {
            if (Board[str_y - i][end_x]->print() != ' ') //non puo' scavalcare
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
        return false; //destinazione stesso colore
    return (delta_x == 2 && delta_y == 1) || (delta_x == 1 && delta_y == 2);
};

bool Alfiere::is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false; //destinazione stesso colore
    if (delta_x != delta_y)
        return false;                 //non si muove in diagonale
    for (int i = 1; i < delta_x; i++) //controllo la diagonale
    {
        if (end_x > str_x)
        {
            if (end_y > str_y)
            {
                if (Board[str_y + i][str_x + i]->print() != ' ') //non puo' scavalcare
                    return false;
            }
            else
            {
                if (Board[str_y - i][str_x + i]->print() != ' ') //non puo' scavalcare
                    return false;
            }
        }
        else
        {
            if (end_y > str_y)
            {
                if (Board[str_y + i][str_x - i]->print() != ' ') //non puo' scavalcare
                    return false;
            }
            else
            {
                if (Board[str_y - i][str_x - i]->print() != ' ') //non puo' scavalcare
                    return false;
            }
        }
    }
    return true;
};

bool Pedone::is_valid_move(Piece *(&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false;                               //destinazione stesso colore
    if (delta_y > 2 || delta_x > 1 || delta_y == 0) //non si puo' muovere piu' di 2 caselle o non si puo' muovere in diagonale
        return false;
    if (Board[str_y][str_x]->print() == 'p') //non puo' tornare indietro
    {
        if (end_y > str_y)
            return false;
    }
    else
    {
        if (end_y < str_y)
            return false;
    }
    if (delta_x == delta_y && Board[end_y][end_x]->print() == ' ') //controllo lo spostamento in diagonale
    {
        if (toupper(Board[str_y][end_x]->print()) == 'P'                                                        //controllo se e' un pedone
            && (Board[str_y][end_x]->get_ex_position_y() == 6 || Board[str_y][end_x]->get_ex_position_y() == 1) //controllo ex posizioni del pedone da mangiare
            && Board[str_y][end_x]->is_moved()                                                                  //controllo se si e' gia' mosso
            && (n_moves - 1) == Board[str_y][end_x]->get_number_move())                                         //controllo il numero della mossa salvata
        {
            delete Board[str_y][end_x];
            Board[str_y][end_x] = new Nullo(); //creo un pezzo nullo dove c'era il pedone che viene mangiato con l'en passant
            return true;
        }
        else
        {
            return false;
        }
    }
    if (delta_x == 0 && Board[end_y][end_x]->print() != ' ') //non puo' mangiare in avanti
        return false;
    if (delta_y == 2)
    {
        if (delta_x == 0) //controllo che si muova in avanti
        {
            if (Board[str_y][str_x]->print() == 'p') //non puo' tornare indietro
            {
                if (Board[end_y + 1][end_x]->print() != ' ') //non puo' scavalcare
                    return false;
            }
            else
            {
                if (Board[end_y - 1][end_x]->print() != ' ') //non puo' scavalcare
                    return false;
            }
        }
        if (is_moved()) //se si e' gia' mosso non puo' fare un altro spostamento uguale a 2
            return false;
        else
        {
            if (delta_x != 0) //non puo' andare avanti di 2 e muoversi anche in diagonale
                return false;
        }
        set_number_move(n_moves); //mi salvo il numero della mossa per un eventuale en passant avversario
    }
    return true;
};

//FUNZIONE RANDOM PER OGNI PEZZO
//ritorna una coppia di coordinate valide oppure {-1, -1}

std::pair<int, int> Re::random_xy(Piece *(&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL)); //generatore random con seed
    int end_y, end_x;
    int cont{0};
    std::pair<int, int> output{-1, -1};
    if (!has_valid_move(Board, str_y, str_x)) //se non ha mosse possibile ritorno -1,-1
        return output;
    do
    {
        end_x = rand() % (3) + (str_x - 1); //3 possibili numeri a partire da quello a sx della attuale posizione
        end_y = rand() % (3) + (str_y - 1); //3 possibili numeri a partire da quello a sotto della attuale posizione
        if (cont == 20)
        {
            end_y = -1; //se non ho trovato un valore valido ripristino -1, -1 ed esco dal ciclo
            end_x = -1;
            break;
        }
        cont++;
    } while (!(check_boundary(end_y, end_x) && is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    return output; //se non trova niente ritorna -1-1
};

std::pair<int, int> Donna::random_xy(Piece *(&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL)); //generatore random con seed
    int end_y, end_x;
    std::pair<int, int> output{-1, -1};
    if (!has_valid_move(Board, str_y, str_x)) //se non ha mosse possibile ritorno -1,-1
        return output;
    int torre_alfiere = rand() % 2; //scelgo a caso se generare uno spostamento torre o uno alfiere
    Piece *t = new Torre(Board[str_y][str_x]->is_white(), Board[str_y][str_x]->get_ex_position_y(), Board[str_y][str_x]->get_ex_position_x());
    Alfiere *a = new Alfiere(Board[str_y][str_x]->is_white(), Board[str_y][str_x]->get_ex_position_y(), Board[str_y][str_x]->get_ex_position_x());
    for (int i = 0; i < 2 && output.first == -1; i++) //se e' stato generato un valore valido esco alla prima iterazione
    {
        if (torre_alfiere) //se torre_alfiere == 1 creo uno spostamento per la torre
        {
            output = t->random_xy(Board, str_y, str_x);
            torre_alfiere--;
        }
        else //creo uno spostamento per l'alfiere
        {
            output = a->random_xy(Board, str_y, str_x);
            torre_alfiere++;
        }
    }
    delete t;
    delete a;
    return output;
};

std::pair<int, int> Torre::random_xy(Piece *(&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL)); //generatore random con seed
    int end_y, end_x;
    int cont{0};
    std::pair<int, int> output{-1, -1};
    if (!has_valid_move(Board, str_y, str_x)) //se non ha mosse possibile ritorno -1,-1
        return output;
    do
    {
        int up_right = rand() % 2;
        if (up_right) //se up_right == 1 si muove in verticale
        {
            end_x = str_x;
            end_y = rand() % 8;
        }
        else //si muove in orizzontale
        {
            end_y = str_y;
            end_x = rand() % 8;
        }
        if (cont == 40)
        {
            end_y = -1; //se non ho trovato un valore valido ripristino -1, -1 ed esco dal ciclo
            end_x = -1;
            break;
        }
        cont++;
    } while (!(check_boundary(end_y, end_x) && is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    return output;
};

std::pair<int, int> Cavallo::random_xy(Piece *(&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL)); //generatore random con seed
    int end_y, end_x;
    int cont{0};
    std::pair<int, int> output{-1, -1};
    if (!has_valid_move(Board, str_y, str_x)) //se non ha mosse possibile ritorno -1,-1
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
            end_y = -1; //se non ho trovato un valore valido ripristino -1, -1 ed esco dal ciclo
            end_x = -1;
            break;
        }
        cont++;
    } while (!(check_boundary(end_y, end_x) && is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    return output;
};

std::pair<int, int> Alfiere::random_xy(Piece *(&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL)); //generatore random con seed
    int end_y, end_x, i;
    std::pair<int, int> output{-1, -1};
    if (!has_valid_move(Board, str_y, str_x)) //se non ha mosse possibile ritorno -1,-1
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
        if (right_left) // right_left == 1 si muove verso destra
            end_x = str_x + i;
        else
        {
            end_x = str_x - i;
        }
        if (cont == 40)
        {
            end_y = -1; //se non ho trovato un valore valido ripristino -1, -1 ed esco dal ciclo
            end_x = -1;
            break;
        }
        cont++;
    } while (!(check_boundary(end_y, end_x) && is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    return output;
};

std::pair<int, int> Pedone::random_xy(Piece *(&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL)); //generatore random con seed
    int end_y, end_x, d_y;
    int cont{0};
    std::pair<int, int> output{-1, -1};
    if (!has_valid_move(Board, str_y, str_x)) //se non ha mosse possibile ritorno -1,-1
        return output;
    Pedone *p = new Pedone(Board[str_y][str_x]->is_white(), Board[str_y][str_x]->get_ex_position_y(), Board[str_y][str_x]->get_ex_position_x());
    p->moved = Board[str_y][str_x]->is_moved();
    do
    {
        int d_y{1};
        end_x = str_x;
        if (!p->is_moved()) //se non si e' mosso puo' andare avanti anche di 2
            d_y = 1 + rand() % 2;

        if (d_y == 1)
            end_x = rand() % (3) + (str_x - 1); // 3 possibili numeri a partire da quello a sinistra

        end_y = (p->is_white()) ? str_y - d_y : str_y + d_y;          //faccio in modo che si muova nella giusta direzione
        if (check_promotion(end_y) && check_boundary(end_y, end_x)    //se e' arrivato alla fine viene fatta la promozione
            && !is_end_same_color(Board, str_y, str_x, end_y, end_x)) //controllo che non vada sopra un pezzo alleato
        {
            int random = rand() % 4; //4 possibili numeri a partire da 0
            delete Board[end_y][end_x];
            switch (random) //in base al valore di random viene fatta la promozione a quel pezzo deciso dal numero
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
            end_y = -1; //se non ho trovato un valore valido ripristino -1, -1 ed esco dal ciclo
            end_x = -1;
            return output;
        }
        cont++;
    } while (!(check_boundary(end_y, end_x) && p->is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    delete p;
    return output;
};

std::pair<int, int> Nullo::random_xy(Piece *(&Board)[8][8], int str_y, int str_x)
{
    std::pair<int, int> output{-1, -1};
    return output;
};
