// Nicola Busato 2009663

#include "Chessboard.h"
#include "Piece.h"

#include <string>
#include <cctype> /* tolower toupper */
#include <iostream>

using namespace std;

Chessboard::Chessboard()
{
    for (int x = 0; x < 8; x++)
    {
        board[0][x] = inizializer_piece(pos[x], 0, x);
        board[1][x] = inizializer_piece('P', 1, x); // P
        for (int y = 2; y <= 5; y++)
            board[y][x] = inizializer_piece(' ', y, x);
        board[6][x] = inizializer_piece('p', 6, x); // p
        board[7][x] = inizializer_piece(tolower(pos[x]), 7, x);
    }
    //board[1][0] = inizializer_piece('p', 1, 0); // p
}

int Chessboard::move(string& s_move, bool white_turne, bool replay)
{
    char prom;
    if (replay && s_move.size() == 7)
    {
        prom = s_move[6];
        s_move.resize(5);
        if ((white_turne && prom != 'd' && prom != 't' && prom != 'a' && prom != 'c') ||
            (!white_turne && prom != 'D' && prom != 'T' && prom != 'A' && prom != 'C'))   //se il pezzo è bianco la lettera deve essere minuscola se il pezzo è nero la lettera deve essere maiuscola
            return -10; // il replay se move restituisce una int != 0 da errore

    }

    bool promotion{ false }, arrocco{ false };

    for (int i = 0; i < s_move.size(); i++)
        s_move[i] = toupper(s_move[i]);

    if (!is_valid_string(s_move))
        return 1; // formato string non valido   // throw InvalidMoveStringException();

    int str_x = (s_move[0] - 'A'),
        str_y = abs(s_move[1] - '0' - 8),
        end_x = (s_move[3] - 'A'),
        end_y = abs(s_move[4] - '0' - 8);

    //cout << str_y << " " << str_x << "   " << end_y << " "  << end_x << endl;

    if (board[str_y][str_x].print() == ' ')
        return 2; // nessun pezzo nella posizione indicata  // throw InvalidMoveException();

    if (!is_right_piece(str_y, str_x, white_turne))
        return 3; // Muove pezzo avverstaio

    try
    {
        //cout << "da qui " << end_y;
        //cin.get();
        if (!board[str_y][str_x].move(board, str_y, str_x, end_y, end_x))
            return 4; // Mossa non possibil
    }
    catch (PromotionException& e)
    {
        promotion = true; // se c'è stata una promozione ma dopo mi faccio un auto scacco allora quel pezzo deve tornare un pedone
        if (!replay)
        {
            string line;
            do
            {
                cout << "Inserire il carattere per la promozione (D, T, A, C): ";
                getline(cin, line);

            } while (!(line.size() == 1 && ((prom = toupper(line[0])) == 'D' || line[0] == 'T' || line[0] == 'A' || line[0] == 'C')));
        }
        if (white_turne)
            prom = tolower(prom);
        s_move += " "; // move += " " + board[end_y][end_x].print();  // dava problemi su windows
        s_move += prom;
        board[str_y][str_x] = inizializer_piece(prom, str_y, str_x);
    }
    catch (ArroccoException& e)
    {
        arrocco = true;
    }

    Piece gonna_die = board[end_y][end_x];
    board[end_y][end_x] = board[str_y][str_x];
    board[str_y][str_x] = Nullo();

    if (board[end_y][end_x].print() == 'R') // Re nero
    {
        king_black[0] = end_y;
        king_black[1] = end_x;
    }
    else if (board[end_y][end_x].print() == 'r')
    {
        king_white[0] = end_y;
        king_white[1] = end_x;
    }

    if (is_check(!white_turne, str_y, str_x, end_y, end_x) > 0)
    {

        board[str_y][str_x] = board[end_y][end_x];
        board[end_y][end_x] = gonna_die;

        if (promotion)
        {
            board[str_y][str_x] = Pedone(white_turne, str_y, str_x);
            s_move.resize(5);
        }
        else if (arrocco) // se è stato fatto un auto scacco perchè si ha fatto un arrocco allora il re viene spostato "in automatico" ma la torre no 
        {
            int x_torre = (end_x < str_y) ? 3 : 5; // arrocco lungo : arrocco corto
            board[str_y][x_torre] = board[str_y][x_torre];
            board[str_y][x_torre] = Nullo();
        }
        else if (board[str_y][str_x].print() == 'R') // Re nero
        {
            king_black[0] = str_y;
            king_black[1] = str_x;
        }
        else if (board[str_y][str_x].print() == 'r')
        {
            king_white[0] = str_y;
            king_white[1] = str_x;
        }

        return 4; // scacco, mossa annullata
    }
    str[0] = str_y;
    str[1] = str_x;
    end[0] = end_y;
    end[1] = end_x;

    if (gonna_die.print() != ' ')
        last_capture = n_moves;

    return 0; // mossa valida
}

bool Chessboard::is_valid_string(string move) // Ln Ln    L->Lettera n->Numero
{
    return move.size() == 5 && move[2] == ' ' &&
        65 <= move[0] && move[0] <= 72 &&
        65 <= move[3] && move[3] <= 72 &&
        0 < move[1] - '0' && move[1] - '0' <= 8 &&
        0 < move[4] - '0' && move[4] - '0' <= 8;
}

string Chessboard::random_move(int y, int x)
{
    pair<int, int> a{ -1,-1 };
    string prom = "";
    bool promotion{ false }, arrocco{ false };
    try {
        a = board[y][x].random_position(board, y, x); // restituisce le cordinate di arrivo
        if (a.first < 0)
            return "NV NV";
    }
    catch (PromotionException& e) {
        promotion = true;
        string prom = " " + board[a.first][a.first].print();
    }
    catch (ArroccoException& e) {
        arrocco = true;
    }
    return (char)('A' + x) + to_string(abs(y - 8)) + " " + (char)('A' + a.second) + to_string((abs(a.first - 8))) + prom;
    // restituisce un array di 2, se è lo spostamento possibile da la posizione [y][x] altrimenti -1, -1
}

Piece Chessboard::inizializer_piece(char p, int y, int x)
{
    switch (toupper(p))
    {
    case 'R':
        return Re(p == 'r', y, x);
    case 'D':
        return Donna(p == 'd', y, x);
    case 'C':
        return Cavallo(p == 'c', y, x);
    case 'A':
        return Alfiere(p == 'a', y, x);
    case 'T':
        return Torre(p == 't', y, x);
    case 'P':
        return Pedone(p == 'p', y, x);
    default:
        return Nullo();
    }
}

ostream& operator<<(ostream& os, Chessboard& cb)
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
