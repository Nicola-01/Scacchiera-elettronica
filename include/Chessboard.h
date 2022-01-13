// Nicola Busato 2009663

#ifndef Chessboard_h
#define Chessboard_h

#include <string>
#include <utility>
#include <vector>
#include "Piece.h"

// class InvalidMoveException{};       // errore mossa non valida
// class InvalidMoveStringException{}; // errore stringa non valida
// alla fine ho deciso che move restituisce un intero che rappresenta il tipo di errore,
// in questo modo non ho creato un try catch a cascata per gestite il tipo di errore da restituire al utente

class Chessboard
{
private:
    //--- variables
    Piece *board[8][8];      // Matrice 8x8 che rappresenta la scacchiera, matrice di puntatori di pezzi, [y][x]
    int king_white[2]{7, 4}; // coordinate del re bianco, (y, x)
    int king_black[2]{0, 4}; // coordinate del re bianco, (y, x)
    int str[2];              // salva le (y, x) di inizo del ultimo move valido
    int end[2];              // salva le (y, x) di fine del ultimo move valido
    int last_capture;        // memorizza la mossa in cui e' avenuta l'ultima cattura, per la patta

    //--- methods
    //_______ Definiti in: src/Rules.cpp _________
    std::pair<int, int> direction_threat(int king_y, int king_x, bool black_king, int dir_y, int dir_x);
    bool all_directions_threat(int k_y, int k_x, bool black_king);
    bool can_be_eaten(int p_y, int p_x);
    bool is_checkmate_d(int k_y, int k_x, bool in_black);
    bool is_checkmate_s(int k_y, int k_x, std::pair<int, int> t_pos, bool in_black);
    std::vector<char> to_char_vector();
    bool invalid_or_implies_check(int st_y, int st_x, int end_y, int end_x);

public:
    Chessboard();  // costruttore, inserisce nella matrice i pezzi nelle rispettive posizioni
    ~Chessboard(); // distruttore, devo liverare board

    int move(std::string &s_move, bool white_turne) { return move(s_move, white_turne, false); } // controlla se lo spostamento e' valido, se e' così esegue lo spostamento
    int move(std::string &s_move, bool white_turne, bool replay);                                // come sopra ma con dei controlli aggiuntivi per il replay
    std::string random_move(int y, int x, bool white_turne);                                     // restituise la mossa (stile mossa player) che il computer esegue

    char pices_type(int y, int x) { return board[y][x]->print(); }                                                                           // restituisce il pezzo selezionato
    bool is_right_piece(int y, int x, bool white_turne) { return (board[y][x]->print() != ' ' && board[y][x]->is_white() == white_turne); }; // restituisce se il pezzo e' del player
    //_______ Definiti in: src/Rules.cpp _________
    bool is_checkmate(bool in_black, int st_y, int st_x, int end_y, int end_x);
    int is_check(bool in_black, int st_y, int st_x, int end_y, int end_x);
    bool is_draw(int end_y, int end_x);

    bool is_checkmate(bool in_black) { return is_checkmate(in_black, str[0], str[1], end[0], end[1]); } // richiama is_chckmate con l'ultimo spostamento valido
    int is_check(bool in_black) { return is_check(in_black, str[0], str[1], end[0], end[1]); }          // richiama is_check con l'ultimo spostamento valido
    bool is_draw() { return is_draw(end[0], end[1]); }                                                  // richiama is_draw con l'ultimo spostamento valido
};

#endif