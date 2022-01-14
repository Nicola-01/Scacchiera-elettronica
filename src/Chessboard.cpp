
// Nicola Busato 2009663

#include "Chessboard.h"
#include "Piece.h"

#include <string>
#include <cctype> // serve per toupper tolower, quindi per rendere il carattere maiuscolo o minuscolo
#include <iostream>

// dichiarazioen helper function
Piece* inizializer_piece(char p, int y, int x); // restituisce il pezzo corretto
bool is_valid_string(std::string move);

Chessboard::Chessboard() // inserisco nelle rispettive posizioioni i pezzi
{
    const std::string pos{"R       "}; // e' la "sequenza" in cui vengono posizionati i pezzi diversi dal pedone
    for (int x = 0; x < 8; x++)
    {
        board[0][x] = inizializer_piece(pos[x], 0, x);
        board[1][x] = inizializer_piece(' ', 1, x); // P
        for (int y = 3; y <= 6; y++)
            board[y][x] = inizializer_piece(' ', y, x);
        board[2][x] = inizializer_piece('p', 6, x); // p
        board[7][x] = inizializer_piece(tolower(pos[x]), 7, x);
    }
}

Chessboard::~Chessboard() {
    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++)
            delete board[y][x];     //libero le aree di memoria puntate dal array
}

int Chessboard::move(std::string &s_move, bool white_turne, bool replay) // metodo che gestitsce lo spostamento (validita e controlli)
{
    bool promotion{false},    // segna se e' avvenuta una promozione,
        arrocco{false},       // segna se e' avvenuto un arrocco,
        arrocco_check{false}; // segna se e' stato fatto scacco mentre il re si sposta

    char prom;              // carattere che rappresenta il tipo di promozione estrapolato dai log oppure e' una mossa del random
    if (s_move.size() == 7) // se la linea ha 7 carattieri allora contiene una promozione es. (H7 H8 b)
    {
        prom = s_move[6];
        s_move.resize(5); // riporto la strigna a 5 caratteri,
        if (s_move[5] != ' ' ||
            (white_turne && prom != 'd' && prom != 't' && prom != 'a' && prom != 'c') || // se il pezzo e' bianco la lettera deve essere minuscola
            (!white_turne && prom != 'D' && prom != 'T' && prom != 'A' && prom != 'C'))  // se il pezzo e' nero la lettera deve essere maiuscola
            return 1;                                                                    // il replay se move restituisce una int != 0 da errore
    }

    for (int i = 0; i < s_move.size(); i++) // rende tutta la stringa maiuscola
        s_move[i] = toupper(s_move[i]);

    if (!is_valid_string(s_move)) // controlla la validità della stringa
        return 1;                 // formato string non valido   // throw InvalidMoveStringException();

    int str_x = (s_move[0] - 'A'), // normalizzio le coordinate da lettere e numeri in numeri tra [0,8] che rappresentano le coordinate della matrice
        str_y = abs(s_move[1] - '0' - 8),
        end_x = (s_move[3] - 'A'),
        end_y = abs(s_move[4] - '0' - 8);

    if (board[str_y][str_x]->print() == ' ') // controllo se la posizione e' un pezzo
        return 2;                            // nessun pezzo nella posizione indicata  // throw InvalidMoveException();

    if (!is_right_piece(str_y, str_x, white_turne)) // controllo se la posizione e' un pezzo dello stesso colore
        return 3;                                   // Muove pezzo avverstaio

    try
    {
        if (!board[str_y][str_x]->move(board, str_y, str_x, end_y, end_x)) // richiamo move del pezzo, può restituire un errore se e' avvenuto un arrocco o una promozione
            return 4;                                                      // Mossa non possibil
    }
    catch (PromotionException &e) // e' avvenuta una promozione
    {
        promotion = true; // se c'e' stata una promozione ma dopo mi faccio un auto scacco allora quel pezzo deve tornare un pedone
        if (!replay)      // se sta giocando il player allora devo chiedergli il pezzo
        {
            std::string line;
            do
            {
                std::cout << "Inserire il carattere per la promozione (D, T, A, C): ";
                std::getline(std::cin, line);
            } while (!(line.size() == 1 && ((prom = toupper(line[0])) == 'D' || prom == 'T' || prom == 'A' || prom == 'C')));
        }
        if (white_turne)
            prom = tolower(prom);

        s_move += " "; // move += " " + prom;  // dava problemi su windows
        s_move += prom;
        board[str_y][str_x] = inizializer_piece(prom, str_y, str_x);
    }
    catch (ArroccoException &e) // controllo se il re spostandosi passa in una posizione in cui sarebbe sotto scacco
    {
        arrocco_check = is_check(!white_turne, str_y, str_x, end_y, end_x);
        arrocco = true;                // devo controllare se non va sotto scacco spostandosi
        int d_x = (end_x - str_x) / 2; // se negativo il re si e' spostato a sx altrimenti a dx
        Piece *torre_tmp = board[str_y][str_x + d_x];
        board[end_y][str_x + d_x] = board[str_y][str_x]; // sposto il re nella casella intermedia

        // modifico la posizione del re per vedere se e' scacco
        if (white_turne)
        {
            king_white[0] = end_y;
            king_white[1] = str_x + d_x;
        }
        else
        {
            king_black[0] = end_y;
            king_black[1] = str_x + d_x;
        }
        if (!arrocco_check)
            arrocco_check = is_check(!white_turne, str_y, str_x, end_y, str_x + d_x);
        board[str_y][str_x] = board[end_y][str_x + d_x]; // riptistino lo spostamento
        board[str_y][str_x + d_x] = torre_tmp;                   // rimetto la torre al suo posto
        // non elimino torre_tmp perchè se no eliminerei l'aria di memoria di board[str_y][str_x + d_x]
    }

    Piece *gonna_die = board[end_y][end_x];    // salvo il pezzo che morirà
    board[end_y][end_x] = board[str_y][str_x]; // sposto effettivamente il pezzo
    board[str_y][str_x] = new Nullo();         // metto un pezzo nullo al posto del pezzo

    if (board[end_y][end_x]->print() == 'r') // controllo se e' stato spostato il re bianco e ne salvo le nuove coordinate
    {
        king_white[0] = end_y;
        king_white[1] = end_x;
    }
    else if (board[end_y][end_x]->print() == 'R') // stessa cosa del re bianco ma per il re nero
    {
        king_black[0] = end_y;
        king_black[1] = end_x;
    }

    str[0] = str_y; // mi salvo le ultime coordinate di muovimento
    str[1] = str_x;
    end[0] = end_y;
    end[1] = end_x;

    if (arrocco_check || is_check(!white_turne) > 0) // controllo se c'e' stato scacco
    {
        board[str_y][str_x] = board[end_y][end_x]; // se e' avenuto lo scacco riposiziono i pezi al loro posto
        board[end_y][end_x] = gonna_die;
        // non elimino gonna_die perchè se no eliminerei l'aria di memoria di board[end_y][end_x]

        if (promotion) // se e' avvenuta una promozione lo riporto come pedone
            board[str_y][str_x] = new Pedone(white_turne, str_y, str_x);

        else if (arrocco) // se e' stato fatto un auto scacco perchè si ha fatto un arrocco allora il re viene spostato "in automatico" ma la torre no
        {
            int new_x_torre = (end_x < str_x) ? 3 : 5; // arrocco lungo : arrocco corto
            int old_x_torre = (end_x < str_x) ? 0 : 7; // arrocco lungo : arrocco corto
            board[str_y][old_x_torre] = board[str_y][new_x_torre];
            board[str_y][new_x_torre] = new Nullo();
            return 6;
        }
        else if (board[str_y][str_x]->print() == 'r') // Re bianco
        {
            king_white[0] = str_y;
            king_white[1] = str_x;
        }
        else if (board[str_y][str_x]->print() == 'R') // Re nero
        {
            king_black[0] = str_y;
            king_black[1] = str_x;
        }
        

        return 5; // scacco, mossa annullata
    }

    if (gonna_die->print() != ' ')
        last_capture = n_moves;

    delete gonna_die; // libero la memoria
    return 0;         // mossa valida
}

std::string Chessboard::random_move(int y, int x, bool white_turne) // crea una stringa per i movimenti dei pezzi
{
    std::pair<int, int> a{-1, -1};
    std::string prom = "";
    bool promotion{false}, arrocco{false};
    try
    {
        a = board[y][x]->random_xy(board, y, x); // restituisce le cordinate di arrivo invocando il random del pezzo, se non ha spostamenti disponibili da (-1, -1)
        if (a.first < 0)
            return "NV NV";
    }
    catch (PromotionException &e) // se il pedone viene promosso allora il pezzo viene modiificato nel metodo random_xy del pedone
    {
        promotion = true;
        a = e.t;
        std::string prom = " " + board[a.first][a.second]->print(); // recupero il tipo di promozione
        board[a.first][a.second] = new Pedone(white_turne, y, x);   // lo riporto a pedone
    }
    catch (ArroccoException &e)
    {
        arrocco = true;
        a = e.t;
    }
    return (char)('A' + x) + std::to_string(abs(y - 8)) + " " + (char)('A' + a.second) + std::to_string((abs(a.first - 8))) + prom;
}

// definizione helper function

bool is_valid_string(std::string move) // la stringa deve essere del tipo da "Ln Ln" dove L rappresenta una lettera tra [A, H] e n un numero tra [1,8]
{
    return move.size() == 5 && move[2] == ' ' &&
           'A' <= move[0] && move[0] <= 'H' &&
           'A' <= move[3] && move[3] <= 'H' && // 65, 72
           0 < move[1] - '0' && move[1] - '0' <= 8 &&
           0 < move[4] - '0' && move[4] - '0' <= 8;
}

Piece *inizializer_piece(char p, int y, int x) // restituisce il pezzo corretto
{
    switch (toupper(p))
    {
    case 'R':
        return new Re(p == 'r', y, x);
    case 'D':
        return new Donna(p == 'd', y, x);
    case 'C':
        return new Cavallo(p == 'c', y, x);
    case 'A':
        return new Alfiere(p == 'a', y, x);
    case 'T':
        return new Torre(p == 't', y, x);
    case 'P':
        return new Pedone(p == 'p', y, x);
    default:
        return new Nullo();
    }
}

std::ostream &operator<<(std::ostream &os, Chessboard &cb) // stampa su ostream, quindi utilizzabile sia per stampare sulla console che su file
{
    os << "\n";
    for (int y = 0; y < 8; y++)
    {
        os << 8 - y << "   ";
        for (int x = 0; x < 8; x++)
            os << cb.pices_type(y, x) << " ";
        os << "\n";
    }
    os << "\n    A B C D E F G H\n\n";
    return os;
}