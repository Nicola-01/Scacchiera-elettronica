
#include "Piece.h"
#include <cctype>   /* toupper */
#include <stdlib.h> /* abs */

bool Piece::is_valid_move(char letter, int str_x, int str_y, int end_x, int end_y)
{
    int delta_x = end_x - str_x;
    int delta_y = end_y - str_y;

    if (delta_x == 0 && delta_y == 0)
        return false;

    char up_lett = toupper(letter);
    switch (up_lett)
    {
    case 'R':
        return (abs(delta_x) <= 1 && abs(delta_y) <= 1);
    case 'D':
        return (abs(delta_x) == abs(delta_y)) || (abs(delta_x) == 0 || abs(delta_y) == 0);
    case 'A':
        return (abs(delta_x) == abs(delta_y));
    case 'C':
        return (abs(delta_x) <= 2 && abs(delta_y) <= 1) || (abs(delta_x) <= 1 && abs(delta_y) <= 2);
    case 'T':
        return (abs(delta_x) == 0 || abs(delta_y) == 0);
    case 'P':
        if (letter == 'p')
            return (delta_x == 0 && delta_y == -1);
        else // letter = 'P'
            return (delta_x == 0 && delta_y == 1);
    default:
            return false;
    }
}

