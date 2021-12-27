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
        board[1][x] = inizializer_piece('P', 1, x);
        for (int y = 2; y <= 5; y++)
            board[y][x] = inizializer_piece(' ', y, x);
        board[6][x] = inizializer_piece('p', 6, x);
        board[7][x] = inizializer_piece(tolower(pos[x]), 7, x);
    }
}

void Chessboard::print()
{
    cout << "\n\n";
    for (int y = 0; y < 8; y++)
    {
        cout << 8 - y << "   ";
        for (int x = 0; x < 8; x++)
            cout << board[y][x].print() << " ";
        cout << "\n";
    }
    cout << "\n\n    A B C D E F G H\n\n";
}

int Chessboard::move(string move, bool white_turne)
{
    for (int i = 0; i < move.size(); i++)
        move[i] = toupper(move[i]);

    if (move == "XX XX")
    {
        print();
        return -1;
    }

    if (!is_valid_string(move))
        return 1; // formato string non valido   // throw InvalidMoveStringException();

    int str_x = (move[0] - 'A'),
        str_y = abs(move[1] - '0' - 8),
        end_x = (move[3] - 'A'),
        end_y = abs(move[4] - '0' - 8);

    if (board[str_y][str_x].print() == ' ')
        return 2; // nessun pezzo nella posizione indicata  // throw InvalidMoveException();

    if (!is_right_piece(str_y, str_x, white_turne))
        return 3; // Muove pezzo avverstaio

    if (!board[str_y][str_x].move(board, str_x, str_y, end_x, end_y))
        return 4; // Mossa non possibil

    board[end_y][end_x] = board[str_y][str_x];
    board[str_y][str_x] = Nullo(false, str_y, str_y);

    if (board[end_y][end_x].print() == 'R') // Re nero
    {
        king_black[0] = end_y;
        king_black[1] = end_y;
    }
    else if (board[end_y][end_x].print() == 'r')
    {
        king_white[0] = end_y;
        king_white[1] = end_y;
    }

    if (is_check(!white_turne, str_y, str_x, end_y, end_x))
    {

        board[str_y][str_x] = board[end_y][end_x];
        board[str_y][str_x] = Nullo(false, str_y, str_y);

        if (board[str_y][str_x].print() == 'R') // Re nero
        {
            king_black[0] = end_y;
            king_black[1] = end_y;
        }
        else if (board[str_y][str_x].print() == 'r')
        {
            king_white[0] = end_y;
            king_white[1] = end_y;
        }

        return 4; // scacco, mossa annullata
    }

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

bool Chessboard::is_right_piece(int y, int x, bool white_turne)
{
    return (board[y][x].print() != ' ' && board[y][x].is_white() == white_turne);
}

string Chessboard::random_move(int y, int x)
{
    string a = board[y][x].random_position(board,y,x); // restituisce le cordinate di arrivo
    if (a != "XX")
    {
        return ('A' + x) + (abs(y - 8)) + " " + ('A' + (int)a[1]) + (abs((int)a[0] - 8));
    }
    return "NV NV";
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
        return Nullo(false, y, x);
    }
}