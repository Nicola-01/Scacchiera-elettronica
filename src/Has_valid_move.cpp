/*
   AUTORE: Martino Scagnet 2000134

   file: Has_valid_move.cpp
*/
#include "Piece.h"
bool in_board(int n);
//
//bool Piece::has_valid_move(Piece* (&Board)[8][8], int str_y, int str_x)
//{
//    char in = toupper(Board[str_y][str_x]->type);
//    switch (in)
//    {
//        case 'R':
//        {
//            Re p = Re(Board[str_y][str_x]->is_white(), str_y, str_x);
//            return p.has_valid_move(Board, str_y, str_x);
//        }
//        case 'D':
//        {
//            Donna p = Donna(Board[str_y][str_x]->is_white(), str_y, str_x);
//            return p.has_valid_move(Board, str_y, str_x);
//        }
//        case 'T':
//        {
//            Torre p = Torre(Board[str_y][str_x]->is_white(), str_y, str_x);
//            return p.has_valid_move(Board, str_y, str_x);
//        }
//        case 'A':
//        {
//            Alfiere p = Alfiere(Board[str_y][str_x]->is_white(), str_y, str_x);
//            return p.has_valid_move(Board, str_y, str_x);
//        }
//        case 'C':
//        {
//            Cavallo p = Cavallo(Board[str_y][str_x]->is_white(), str_y, str_x);
//            return p.has_valid_move(Board, str_y, str_x);
//        }
//        case 'P':
//        {
//            Pedone p = Pedone(Board[str_y][str_x]->is_white(), str_y, str_x);
//            return p.has_valid_move(Board, str_y, str_x);
//        }
//    }
//
//    return false;
//}
bool Re::has_valid_move(Piece* (&Board)[8][8], int str_y, int str_x)
{
    for(int dir_y = -1; dir_y <= 1; dir_y++)
    {
        for(int dir_x = -1; dir_x <= 1; dir_x++)
        {
            if((dir_x != 0 || dir_y != 0) && in_board(str_y) && in_board(str_x))
            {
                if(is_valid_move(Board, str_y, str_x, str_y+dir_y, str_x+dir_x))
                    return true;
            }
        }
    }
    return false;
}
bool Donna::has_valid_move(Piece* (&Board)[8][8], int str_y, int str_x)
{
   for(int dir_y = -1; dir_y <= 1; dir_y++)
    {
        for(int dir_x = -1; dir_x <= 1; dir_x++)
        {
            if((dir_x != 0 || dir_y != 0) && in_board(str_y) && in_board(str_x))
            {
                if(is_valid_move(Board, str_y, str_x, str_y+dir_y, str_x+dir_x))
                    return true;
            }
        }
    }
    return false;
}
bool Torre::has_valid_move(Piece* (&Board)[8][8], int str_y, int str_x)
{
    if(in_board(str_y+1)&&is_valid_move(Board, str_y, str_x, str_y +1, str_x)){return true;}
    if(in_board(str_y-1)&&is_valid_move(Board, str_y, str_x, str_y -1, str_x)){return true;}
    if(in_board(str_x+1)&&is_valid_move(Board, str_y, str_x, str_y, str_x +1)){return true;}
    if(in_board(str_x-1)&&is_valid_move(Board, str_y, str_x, str_y, str_x -1)){return true;}
    return false;
}
bool Alfiere::has_valid_move(Piece* (&Board)[8][8], int str_y, int str_x)
{
    if(in_board(str_y-1)&&in_board(str_x-1)&&is_valid_move(Board, str_y, str_x, str_y -1, str_x -1)){return true;}
    if(in_board(str_y-1)&&in_board(str_x+1)&&is_valid_move(Board, str_y, str_x, str_y -1, str_x +1)){return true;}
    if(in_board(str_y+1)&&in_board(str_x-1)&&is_valid_move(Board, str_y, str_x, str_y +1, str_x -1)){return true;}
    if(in_board(str_y+1)&&in_board(str_x+1)&&is_valid_move(Board, str_y, str_x, str_y +1, str_x +1)){return true;}
    return false;
}
bool Cavallo::has_valid_move(Piece* (&Board)[8][8], int str_y, int str_x)
{
    for(int off_y = -2; off_y <= 2; off_y++)
    {
        if(off_y == 0){continue;}
        if(off_y%2 == 0)
        {
            for(int off_x = -1; off_x <= 1; off_x+2)
            {
                if(in_board(str_y+off_y)&&in_board(str_x+off_x)&&is_valid_move(Board, str_y, str_x, str_y +off_y, str_x +off_x))
                    return true;
            }
        }
        else
        {
            for(int off_x = -2; off_x <= 2; off_x +4)
            {
                if(in_board(str_y+off_y)&&in_board(str_x+off_x)&&is_valid_move(Board, str_y, str_x, str_y +off_y, str_x +off_x))
                    return true;
            }
        }
    }
    return false;
}
bool Pedone::has_valid_move(Piece* (&Board)[8][8], int str_y, int str_x)
{
    int off_y = 1;
    if(is_white()){off_y = -1;}
    for(int off_x = -1; off_x <= 1; off_x++)
    {
        if(in_board(str_y+off_y)&&in_board(str_x+off_x)&&is_valid_move(Board, str_y, str_x, str_y +off_y, str_x +off_x))
            return true;
    }
    return false;
}
bool Nullo::has_valid_move(Piece* (&Board)[8][8], int str_y, int str_x)
{
    return false;
}
//HELPER FUNCTIONS
bool in_board(int n)
{
    return (n>=0 && n<8);
}