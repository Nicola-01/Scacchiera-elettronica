/*
   AUTORE: Martino Scagnet 2000134

   file: Valid_moves.cpp
*/
#include "Piece.h"

#include <vector>

std::vector< std::pair<int, int> > Piece::valid_moves(Piece (&Board)[8][8], int str_y, int str_x)
{
    char in = toupper(Board[str_y][str_x].type);
    switch (in)
    {
        case 'R':
        {
            Re p = Re(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
            return p.valid_moves(Piece (&Board)[8][8], int str_y, int str_x);
        }
        case 'D':
        {
            Donna p = Donna(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
            return p.valid_moves(Piece (&Board)[8][8], int str_y, int str_x);
        }
        case 'T':
        {
            Torre p = Torre(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
            return p.valid_moves(Piece (&Board)[8][8], int str_y, int str_x);
        }
        case 'A':
        {
            Alfiere p = Alfiere(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
            return p.valid_moves(Piece (&Board)[8][8], int str_y, int str_x);
        }
        case 'C':
        {
            Cavallo p = Cavallo(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
            return p.valid_moves(Piece (&Board)[8][8], int str_y, int str_x);
        }
        case 'P':
        {
            Pedone p = Pedone(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
            return p.valid_moves(Piece (&Board)[8][8], int str_y, int str_x);
        }
    }
    return std::vector<pair<int,int>>;
}

std::vector< std::pair<int, int> > Re::valid_moves(Piece (&Board)[8][8], int str_y, int str_x)
{
    std::vector<pair<int,int>> moves;
    return moves;
}
std::vector< std::pair<int, int> > Donna::valid_moves(Piece (&Board)[8][8], int str_y, int str_x)
{
    std::vector<pair<int,int>> moves;
    return moves;
}
std::vector< std::pair<int, int> > Torre::valid_moves(Piece (&Board)[8][8], int str_y, int str_x)
{
    std::vector<pair<int,int>> moves;
    return moves;
}
std::vector< std::pair<int, int> > Alfiere::valid_moves(Piece (&Board)[8][8], int str_y, int str_x)
{
    std::vector<pair<int,int>> moves;
    return moves;
}
std::vector< std::pair<int, int> > Cavallo::valid_moves(Piece (&Board)[8][8], int str_y, int str_x)
{
    std::vector<pair<int,int>> moves;
    return moves;
}
std::vector< std::pair<int, int> > Pedone::valid_moves(Piece (&Board)[8][8], int str_y, int str_x)
{
    std::vector<pair<int,int>> moves;
    return moves;
}