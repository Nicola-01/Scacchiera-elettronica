/*
    AUTORE: Martino Scagnet 2000134

    file: Rules.cpp
*/
#include "Rules.h"
#include "Chessboard.h"
#include "Piece.h"

#include <memory>

//HELPER FUNCTIONS
//controlla se in una direzione indicata da x_dir y_dir ci sono minacce
//bool direction_treat(const Chessboard& board, int king_x, int king_y, int x_dir, int y_dir);

//if(in_black) -> controllo scacco del re nero tra i pezzi bianchi -> pezzo.is_white() 

bool Rules::is_check(bool in_black)
{
    int* king_pos = board.get_white_king();
    if(in_black)
        king_pos = board.get_black_king();
    int k_x = king_pos[1];
    int k_y = king_pos[0];
    delete king_pos;
    //______Ricerca del pezzo che minaccia_______
    Piece threat = Piece();//*****DA IMPLEMENTARE COSTRUTTORE DEFAULT NULLO
    //Controllando tutti i possibili attaccanti
    //Nel caso sia stato il re minacciato a muoversi
    //Ricerca nelle vicinanze (per comprendere possibili cavalli)
    for(int s_x = k_x-2; (s_x <= 7) && (s_x <= k_x+2); s_x++)
    {
        //controllo che la casella in esame sia nella scacchiera
        if(s_x > 0)
        {        
            for(int s_y = k_y-2; (s_y <= 7) && (s_y <= k_y+2); s_y++)
            {
                //controllo che la casella in esame sia nella scacchiera e non sia il re stesso
                if(s_y < 0 || (s_x == k_x && s_y == k_y))
                    continue;
                //controllo anche la verticale
                if(s_x == k_x)
                    s_y = 0;
                Piece in_exam = board.get_piece(s_y, s_x);//****DA IMPLEMENTARE
                if( (in_exam.print() != ' ') && 
                    (in_exam.is_white() == in_black) && 
                    (board.is_piece_valid_move(s_y, s_x, in_exam.is_white(), k_y, k_x)) )
                {
                    //in_exam puo' catturare il re minacciato
                    threat = in_exam;
                    return true;
                    /*if(!mate)
                        return true;
                    */
                }
            }
        }
    }
    
    //controllo a sinistra delle vicinanze
    for(int s_x = k_x - 3; s_x >= 0; s_x--)
    {
        int off = k_x - s_x; //off > 0
        for(int s_y = k_y - off; s_y < 7; s_y + off)//Controllo diagonale alta, riga e diagonale bassa
        {
            if(s_y >= 0)
            {
                Piece in_exam = board.get_piece(s_y, s_x);//DA IMPLEMENTARE
                if( (in_exam.print() != ' ') && 
                    (in_exam.is_white() == in_black) && 
                    (board.is_piece_valid_move(s_y, s_x, in_exam.is_white(), k_y, k_x)) )
                {
                    //in_exam puo' catturare il re minacciato
                    threat = in_exam;
                    return true;
                    /*if(!mate)
                        return true;
                    */
                }
            }
        }
    }
    
    //controllo a destra delle vicinanze
    for(int s_x = k_x + 3; s_x <= 7; s_x++)
    {
        int off = s_x - k_x ; //off > 0
        for(int s_y = k_y - off; s_y < 7; s_y + off)//Controllo diagonale alta, riga e diagonale bassa
        {
            if(s_y >= 0)
            {
                Piece in_exam = board.get_piece(s_y, s_x);//DA IMPLEMENTARE
                if( (in_exam.print() != ' ') && 
                    (in_exam.is_white() == in_black) && 
                    (board.is_piece_valid_move(s_y, s_x, in_exam.is_white(), k_y, k_x)) )
                {
                    //in_exam puo' catturare il re minacciato
                    threat = in_exam;
                    return true;
                    /*if(!mate)
                        return true;
                    */
                }
            }
        }
    }
    return false;
}
bool Rules::is_checkmate(bool in_black)
{
    return false;
}
bool Rules::is_draw()
{
    return false;
}

/*
//SECONDA VERSIONE OTTIMIZZATA
//Ritorna 1 se il re indicato da in_black e' sotto scacco
// 2 se e' anche scacco matto
// 0 se non è nulla
//Lancia CheckmateException nel caso lo scacco sia matto 
int Rules::is_check(bool in_black, int st_x, int st_y, int end_x, int end_y)
{
    Piece moved = board.get_piece(end_y, end_x);
    Piece threat = Piece();
    //Se ho mosso bianco e cerco scacco nel nero e viceversa devo verificare lo scacco matto
    bool mate = (moved.is_white() == in_black);
    int* king_pos;
    king_pos = board.get_white_king();
    if(in_black)
        king_pos = board.get_black_king();
    int k_x = king_pos[1];
    int k_y = king_pos[0];
    delete king_pos;
    if(mate)//La mossa e' d'attacco
    {
        bool found = false;
        //controllo se il pezzo mosso minaccia
        if (board.is_piece_valid_move(end_y, end_x, moved.is_white(), k_y, k_x))
        {
            found = true;
            threat = moved;
        }
        //controllo se il pezzo scoperto da moved minaccia


    }
    return 0;
}
bool Rules::is_checkmate(int k_x, int k_y, Piece threat, Piece s_thr)
{

}
//*/


// DEFINIZIONE HELPER FUNCTIONS
///*
bool direction_treat(const Chessboard& board, int king_x, int king_y, int x_dir, int y_dir)
{
    
    return false;
}


//*/