/*
    AUTORE: Martino Scagnet 2000134

    file: Rules.h
*/
#ifndef RULES_H
#define RULES_H

#include "Chessboard.h"


struct Rules
{
    bool is_check(const Chessboard& board, bool in_black);
    bool is_checkmate(const Chessboard& board, bool in_black);
    bool is_draw(const Chessboard& board);
};


#endif //RULES_H