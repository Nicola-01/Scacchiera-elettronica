/*
    AUTORE: Martino Scagnet 2000134

    file: Rules.h
*/
#ifndef RULES_H
#define RULES_H

#include "Chessboard.h"


struct Rules
{
    bool is_check(const Chess& board, bool white_turne);
    bool is_check_mate(const Chess& board, bool white_turne);
    bool is_draw(const Chess& board);
};


#endif //RULES_H