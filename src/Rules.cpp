/*
    AUTORE: Martino Scagnet 2000134

    file: Rules.cpp
*/
#include "Rules.h"
#include "Chessboard.h"
//#include "Piece.h"

#include <utility>
#include <memory>
#include <cstdlib>

//HELPER FUNCTIONS
bool is_valid_traj(int p_x, int p_y, int k_x, int k_y);

//if(in_black) -> controllo scacco del re nero tra i pezzi bianchi -> pezzo.is_white() 

///*
//SECONDA VERSIONE OTTIMIZZATA
//Ritorna 1 se il re indicato da in_black e' sotto scacco
// 2 se e' anche scacco matto
// 0 se non e' nulla
int Chessboard::is_check(bool in_black, int st_y, int st_x, int end_y, int end_x)
{
    Piece moved = board[end_y][end_x];
    //Piece threat = Piece();
    std::pair<int,int> threat_pos;
    //Se ho mosso bianco e cerco scacco nel nero e viceversa devo verificare lo scacco matto
    bool mate = (moved.is_white() == in_black);
    int k_x = king_white[1];
    int k_y = king_white[0];
    if(in_black)
    {
        k_x = king_black[1];
        k_y = king_black[0];
    }

    if(mate)//La mossa e' d'attacco
    {
        bool found = false;
        bool second = false;
        //controllo se il pezzo mosso minaccia
        if (moved.is_valid_move(board, end_y, end_x, k_y, k_x))
        {
            found = true;
            threat_pos.first = end_y;
            threat_pos.second = end_x;
        }
        //controllo se il pezzo scoperto da moved minaccia
        if(is_valid_traj(st_y, st_x, k_y, k_x))
        {
            std::pair<int, int> second_t_pos = direction_threat(k_y, k_x, in_black ,((st_y-k_y)/std::abs(st_y-k_y)), ((st_x-k_x)/std::abs(st_x-k_x));
            if( second_t_pos.first >= 0)
            {
                if(found)
                    second = true;
                else
                {
                    found = true;
                    threat_pos = second_t_pos;
                }
            }
        }
        //due pezzi minacciano
        if(found && second)
        {
            if(is_checkmate_d(k_y, k_x))
                return 2;
            return 1;
        }
        //un pezzo minaccia
        if(found)
        {
            if(is_checkmate(k_y, k_x, threat_pos))
                return 2;
            return 1;
        }
    }
    else if(k_x == end_x && k_y == end_y) //se e' stato mosso un re
    {
        for(int dir_x = -1; dir_x <= 1; dir_x++)
        {
            for(int dir_y = -1; dir_y <= 1; dir_y++)
            {
                threat_pos = direction_threat(k_y, k_x, in_black, dir_y, dir_x);
                if(threat_pos.first >= 0 && threat_pos.second >= 0)
                    return 1;
            }
        }
    }
    else //verifica che la mossa sia valida
    {
        //controllo se il pezzo scoperto da moved minaccia
        if(is_valid_traj(st_y, st_x, k_y, k_x))
        {
            std::pair<int, int> threat_pos = direction_threat(k_y, k_x, in_black ,((st_y-k_y)/std::abs(st_y-k_y)), ((st_x-k_x)/std::abs(st_x-k_x));
            if(threat_pos.first > 0)
                return 1;
        }
    }
    return 0;
}
//Se due pezzi attaccano il re questo puo' salvarsi solo muovendosi
bool Chessboard::is_checkmate_d(int k_y, int k_x)
{
    for(int x_off = -1; x_off <= 1 && ((x_off+k_x)<8); x_off++)
    {
        if((x_off+k_x) >= 0)
        {
            for(int y_off = -1; y_off <= 1 && ((y_off+k_y)<8); y_off++)
            {
                if((y_off+k_y) >= 0)
                {
                    if(board[k_y][k_x].is_valid_move(board, k_y, k_x, k_y+y_off, k_x+x_off))
                        return false;
                }
            }
        }
    }
    return true;
}
//Se un pezzo attacca o questo puo' muoversi o un pezzo alleato 
//Puo' mettersi nella traiettoria
bool Chessboard::is_checkmate(int k_y, int k_x, std::pair<int,int> t_pos)
{
    //controllo se il re si puo' muovere
    if(!is_checkmate_d(k_y, k_x))
        return false;
    //controllo se puo' essere difeso
    int dir_x = 
    return true;
}

//Ritorna la posizione della minaccia nella direzione indicata, (-1,-1) altrimenti
std::pair<int, int> Chessboard::direction_threat(int king_y, int king_x, bool black_king, int dir_y, int dir_x)
{
    int i_x = king_x + dir_x;
    int i_y = king_y + dir_y;
    while(i_x >= 0 && i_x < 8 && i_y >= 0 && i_y < 8)
    {
        if(board[i_y][i_x].is_valid_move(board, i_y, i_x, king_x, king_y))
            return make_pair(i_y, i_x);
        i_x = i_x + dir_x;
        i_y = i_y + dir_y;
    }
    return std::pair<int,int>(-1,-1);
}

//*/


// DEFINIZIONE HELPER FUNCTIONS
///*
//Ritorna una direzione come schema sotto, -1 se non fa parte della croce di possibile attacco
/*
(7)(0)(1)
(6)(K)(2)
(5)(4)(3)
*/
bool is_valid_traj(int p_y, int p_x, int k_y, int k_x)
{
    int x_diff = k_x - p_x;
    int y_diff = k_y - p_y;
    if((x_diff == 0) != (y_diff==0))
        return true;
    x_diff = std::abs(x_diff);
    y_diff = std::abs(y_diff);
    if(std::abs(x_diff) == std::abs(y_diff))
        return true;
    return false;
}




//*/