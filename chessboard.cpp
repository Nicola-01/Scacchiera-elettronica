// Nicola Busato 2009663

#include "Chessboard.h"
#include "Piece.h"

#include <string>
#include <cctype> /* tolower toupper */
#include <iostream>

using namespace std;

Chess::Chess()
{
    for (int x = 0; x < 8; x++)
    {
        board[0][x] = inizializer_piece(pos[x]);
        board[1][x] = inizializer_piece('P');
        board[6][x] = inizializer_piece('p');
        board[7][x] = inizializer_piece(tolower(pos[x]));
    }

    for (int y = 2; y <= 5; y++)
        for (int x = 0; x < 8; x++)
            board[y][x] = inizializer_piece(' ');
}

void Chess::print()
{
    cout << "\n\n";
    for (int y = 0; y < 8; y++)
    {
        cout << 8 - y << "   ";
        for (int x = 0; x < 8; x++)
            cout << board[y][x] << " ";
        cout << "\n";
    }
    cout << "\n\n    A B C D E F G H\n\n";
}

class InvalidMoveException {};
class InvalidMoveStringException {};

bool Chess::move(const string move)
{
    if(toupper(move)=="XX XX")
        print();

    if (!is_valid_move(move))
        throw InvalidMoveStringException();
    
    

    int str_x = (toupper(move[0]) - 'A'),
        str_y = abs(move[1] - '0' - 8),
        end_x = (toupper(move[3]) - 'A'),
        end_y = abs(move[4] - '0' - 8);

    Piece tmp{};
    if (board[str_y][str_x] == ' ' || !tmp.is_valid_move(board[str_y][str_x], str_x, str_y, end_x, end_y))
        throw InvalidMoveException();

    board[end_y][end_x] = board[str_y][str_x];
    board[str_y][str_x] = ' ';

    return true;
}

bool Chess::is_valid_move(std::string move)     // Ln Ln    L->Lettera n->Numero
{
    return move.size() == 5 && move[2] == ' ' &&
           65 <= toupper(move[0]) && toupper(move[0]) <= 72 &&
           65 <= toupper(move[3]) && toupper(move[3]) <= 72 &&
           0 < move[1] - '0' && move[1] - '0' <= 8 &&
           0 < move[4] - '0' && move[4] - '0' <= 8;

Piece Chess::inizializer_piece(char p)
{
    switch (toupper(p))
    {
    case 'R': return piece_king((p == 'R') 'Black' :: 'White');
    case 'D': return piece_queen((p == 'D') 'Black' :: 'White');
    case 'C': return piece_knight((p == 'C') 'Black' :: 'White');
    case 'A': return piece_bishop((p == 'A') 'Black' :: 'White');
    case 'T': return piece_rook((p == 'T') 'Black' :: 'White');
    case 'P': return piece_pawn((p == 'P') 'Black' :: 'White');
    default : return piece_space();
    }
}
