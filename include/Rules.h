/*
    AUTORE: Martino Scagnet 2000134

    file: Rules.h
*/
#ifndef RULES_H
#define RULES_H

#include "Chessboard.h"

class CheckmateException{};

class Rules
{
private:
    Chessboard board;
public:
    Rules(Chessboard& b): board{b}{}
    bool is_check(bool in_black);
    //Seconda versione in via di sviluppo
    //bool is_check(bool in_black, int st_x, int st_y, int end_x, int end_y);
    bool is_checkmate(bool in_black);
    //bool is_checkmate(int k_x, int k_y, Piece threat, Piece s_thr);
    bool is_draw();
};


#endif //RULES_H