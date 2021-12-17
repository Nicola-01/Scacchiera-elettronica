using namespace std;

#include "Chess.h"
#include "Piece.h"

#include <string>
#include <cctype> /* tolower toupper */
#include <iostream>

Chess::Chess()
{
    for (int x = 0; x < 8; x++)
    {
        scacchiera[0][x] = pos[x];
        scacchiera[1][x] = 'P';
        scacchiera[6][x] = 'p';
        scacchiera[7][x] = tolower(pos[x]);
    }

    for (int y = 2; y <= 5; y++)
        for (int x = 0; x < 8; x++)
            scacchiera[y][x] = ' ';
}

void Chess::print()
{
    cout << "\n\n";
    for (int y = 0; y < 8; y++)
    {
        cout << 8 - y << "   ";
        for (int x = 0; x < 8; x++)
            cout << scacchiera[y][x] << " ";
        cout << "\n";
    }
    cout << "\n\n    A B C D E F G H\n\n";
}

class InvalidMoveException {};
class InvalidMoveStringException {};

bool Chess::move(const string move)
{
    if (!is_valid_move(move))
        throw InvalidMoveStringException();
    int str_x = (toupper(move[0]) - 'A'),
        str_y = abs(move[1] - '0' - 8),
        end_x = (toupper(move[3]) - 'A'),
        end_y = abs(move[4] - '0' - 8);

    Piece tmp{};
    if (scacchiera[str_y][str_x] == ' ' || !tmp.is_valid_move(scacchiera[str_y][str_x], str_x, str_y, end_x, end_y))
        throw InvalidMoveException();

    scacchiera[end_y][end_x] = scacchiera[str_y][str_x];
    scacchiera[str_y][str_x] = ' ';

    return true;
}

bool Chess::is_valid_move(std::string move)
{
    return move.size() == 5 && move[2] == ' ' &&
           65 <= toupper(move[0]) && toupper(move[0]) <= 72 &&
           65 <= toupper(move[3]) && toupper(move[3]) <= 72 &&
           0 < move[1] - '0' && move[1] - '0' <= 8 &&
           0 < move[4] - '0' && move[4] - '0' <= 8;
}
