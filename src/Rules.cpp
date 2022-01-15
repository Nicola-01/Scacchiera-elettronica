/*
   AUTORE: Martino Scagnet 2000134

   file: Rules.cpp
*/
#include "Chessboard.h"
#include "Piece.h"

#include <utility>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream> //per test
//HELPER FUNCTIONS
bool is_valid_traj(int p_x, int p_y, int k_x, int k_y);
void past_positions(std::vector<char> mat, bool empty);
bool are_equals(std::vector<char> a, std::vector<char> b);
bool in_bounds(int n);
std::vector<std::pair<int,int>> cavallo_moves(int d_y, int d_x);
std::string string_move(int s_y, int s_x, int e_y, int e_x);
//Eccezioni
class three_time_repeated
{
};

//if(in_black) -> controllo scacco del re nero tra i pezzi bianchi -> pezzo.is_white()
//Ritorna 1 se il re indicato da in_black e' sotto scacco
// 2 se e' anche scacco matto
// 0 se non e' nulla
int Chessboard::is_check(bool in_black, int st_y, int st_x, int end_y, int end_x)
{
    //Piece threat = Piece();
    std::pair<int, int> threat_pos;
    bool mate = (board[end_y][end_x]->is_white() == in_black); //Se ho mosso bianco e cerco scacco nel nero e viceversa devo verificare lo scacco matto
    int k_x = king_white[1];
    int k_y = king_white[0];
    if (in_black)
    {
        k_x = king_black[1];
        k_y = king_black[0];
    }
    bool king_moved = (toupper(board[end_y][end_x]->print()) == 'R');
    //std::cout << "Mate = " << mate << " Pos Re da controllare: " << k_y << "," << k_x << "\n";
    if (mate) //La mossa e' d'attacco
    {
        bool found = false;
        bool second = false;
        if (board[end_y][end_x]->is_valid_move(board, end_y, end_x, k_y, k_x)) //Il pezzo mosso minaccia il re
        {
            found = true;
            threat_pos.first = end_y;
            threat_pos.second = end_x;
        }
        //controllo se il pezzo scoperto da moved minaccia
        if (is_valid_traj(st_y, st_x, k_y, k_x))
        {
            int diff_y = st_y - k_y;
            if (diff_y != 0){diff_y = diff_y / std::abs(diff_y);}
            int diff_x = st_x - k_x;
            if (diff_x != 0){diff_x = diff_x / std::abs(diff_x);}
            //std::cout << "Direzione della minaccia possibile rispetto a:(" << k_y << "," << k_x << ") :  (" << diff_y << "," << diff_x << ")\n";
            std::pair<int, int> second_t_pos = direction_threat(k_y, k_x, in_black, diff_y, diff_x);
            if (in_bounds(second_t_pos.first) && (second_t_pos.first != end_y || second_t_pos.second != end_x))//controllo che il pezzo trovato non sia quello mosso
            {
                //controllo che il pezzo trovato non sia quello mosso
                if (found)
                    second = true;
                else
                {
                    found = true;
                    threat_pos = second_t_pos;
                }
            }
        }
        //due pezzi minacciano
        if (found && second)
        {
            //std::cout << "\n\nDoppia minaccia\n\n";
            if (is_checkmate_d(k_y, k_x, in_black))
                return 2;
            return 1;
        }
        //un pezzo minaccia
        else if (found)
        {
            //std::cout << "\n\n singola minaccia \n\n";
            if (is_checkmate_s(k_y, k_x, threat_pos, in_black))
                return 2;
            return 1;
        }
        //Possibile arrocco:
        if (toupper(board[end_y][end_x]->print()) == 'R')
            all_directions_threat(k_y, k_x, in_black);
        return 0;
    }
    else if (!mate)//Controllo se ho fatto una mossa valida
    {
        if (all_directions_threat(k_y, k_x, in_black))
        {
            return 1;
        }
        //Controllo se qualche cavallo puo attaccare (k_y, k_x)
        std::vector<std::pair<int, int>> possible_cavallo = cavallo_moves(k_y, k_x);
        char c;
        (in_black) ? c = 'c' : c = 'C';
        for(int i = 0; i < possible_cavallo.size(); i++)
        {
            if(board[possible_cavallo[i].first][possible_cavallo[i].second]->print() == c)
                return 1;
        }
    }
    return 0;
}
//Se due pezzi attaccano il re questo puo' salvarsi solo muovendosi
bool Chessboard::is_checkmate_d(int k_y, int k_x, bool in_black)
{
    for (int x_off = -1; x_off <= 1; x_off++)
    {
        for (int y_off = -1; y_off <= 1; y_off++)
        {
            if ((x_off != 0 || y_off != 0) && in_bounds(k_y + y_off) && in_bounds(k_x + x_off))
            {
                if (!invalid_or_implies_check(k_y, k_x, k_y + y_off, k_x + x_off))
                {
                   //std::cout << "\n\n Il re puo muoversi in: (y= " << k_y + y_off << " , x= " << k_x + x_off << "\n\n";
                    return false;
                }
                //else
                    //std::cout << "\n\n Il re NON puo muoversi in: (y= " << k_y + y_off << " , x= " << k_x + x_off << "\n\n";
            }
        }
    }
    //std::cout << "\n\nscacco matto\n\n";
    return true;
}
//Se un solo pezzo attacca o il re puo' muoversi o un pezzo alleato
//Puo' mettersi nella traiettoria
bool Chessboard::is_checkmate_s(int k_y, int k_x, std::pair<int, int> t_pos, bool in_black)
{
    //controllo se il re si puo' muovere
    if (!is_checkmate_d(k_y, k_x, in_black))
        return false;
    //controllo se puo' essere difeso
    //1)Catturando la minaccia:
    if(can_be_eaten(t_pos.first, t_pos.second))
        return false;
    int dir_x = (t_pos.second - k_x);
    //2)Mettendosi in mezzo
    if (dir_x != 0){ dir_x = dir_x / std::abs(t_pos.second - k_x); }
    int dir_y = (t_pos.first - k_y);
    if (dir_y != 0){ dir_y = dir_y / std::abs(t_pos.first - k_y); }
    //scansione di tutti i pezzi alleati
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if ( (board[y][x]->print() != ' ') && ((board[y][x]->is_white()) == (board[k_y][k_x]->is_white())))
            {
                int i_x = k_x + dir_x;
                int i_y = k_y + dir_y;
                while (i_x != t_pos.second && i_y != t_pos.first)
                {
                    if (!invalid_or_implies_check(y, x, i_y, i_x)) //se si puo' mettere in mezzo senza generare scacco
                    {
                        //std::cout << "\n\n Si puo muovere: (y= " << y << " , x= " << x << ") --> (y= " << t_y << " , x= " << t_x << ")\n\n";
                        return false;
                    }
                    i_x = i_x + dir_x;
                    i_y = i_y + dir_y;
                }
            }
        }
    }
    //std::cout << "\n\nscacco matto\n\n";
    return true;
}

bool Chessboard::is_checkmate(bool in_black, int st_y, int st_x, int end_y, int end_x)
{
    int flag = is_check(in_black, st_y, st_x, end_y, end_x);
    switch (flag)
    {
    case 0:
    case 1:
        return false;
    case 2:
        return true;
    }
    return false;
}
//is_draw: 0 = Non patta, 1 = MATERIALE INSUFF, 2 = RIPETIZIONE DI POSIZIONE, 3 = 50 MOSSE SENZA PEDONI O CATTURE, 4 = STALLO
int Chessboard::is_draw(int end_y, int end_x)
{
    std::vector<char> p_l;
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if (board[y][x]->print() != ' ')
                p_l.push_back(board[y][x]->print());
        }
    }
    //_____PER MATERIALE INSUFFICIENTE______
    //Si suppone che ci debbano essere per forza due re
    //a) Re contro Re
    if (p_l.size() < 3)
        return 1;
    if (p_l.size() == 3)
    {
        //b)due re e (un alfiere o un cavallo)
        for (char c : p_l)
            if (toupper(c) == 'A' || toupper(c) == 'C')
            {
                //std::cout << "\n\nPATTA PER MANCANZA DI MATERIALE\n";
                return 1;
            }
    }
    if (p_l.size() == 4)
    {
        //c) due re e alfieri avversari sulle stesse caselle
        if ((std::find(p_l.begin(), p_l.end(), 'a') != p_l.end()) && (std::find(p_l.begin(), p_l.end(), 'A') != p_l.end()))
        {
            bool first = false;
            bool odd;
            for (int x = 0; x < 8; x++)
            {
                for (int y = 0; y < 8; y++)
                {
                    if (toupper(board[y][x]->print()) == 'A')
                    {
                        if (!first)
                        {
                            odd = (x + y) % 2;
                            first = true;
                        }
                        if (first && (((x + y) % 2) == odd))
                        {
                            //std::cout << "\n\nPATTA PER MANCANZA DI MATERIALE\n";
                            return 1;
                        }
                    }
                }
            }
        }
    }
    static int piece_number = p_l.size();
    static int move_counter = 0;
    //_________PER RIPETIZIONE DI POSIZIONE________
    if (piece_number != p_l.size())
    {
        past_positions(to_char_vector(), true); //Azzero le posizioni passate
        //(REGOLA 50 MOSSE)
        move_counter = 0; //Azzero il contatore di mosse senza catture o mosse di pedone
        piece_number = p_l.size();
    }
    else
    {
        try
        {
            past_positions(to_char_vector(), false);
        }
        catch (const three_time_repeated &e)
        {
            //std::cout << "\n\nPATTA PER RIPETIZIONE DI POSIZIONE\n";
            return 2;
        }
        piece_number = p_l.size();
    }
    //_________REGOLA DELLE 50 MOSSE_________
    if (toupper(board[end_y][end_x]->print()) == 'P')
    {
        move_counter = 0;
    }
    move_counter++;
    //std::cout<<"Mosse senza catture o mosse di pedone = "<<move_counter<<"\n";
    if (move_counter >= 50)
        return 3;
    //________PER STALLO________
    bool in_white = !(board[end_y][end_x]->is_white()); //Se ha mosso bianco controllo stallo nero
    int k_y = king_white[0];
    int k_x = king_white[1];
    if (!in_white)
    {
        k_y = king_black[0];
        k_x = king_black[1];
    }
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            
            if ((board[y][x]->print() != ' ') && (board[y][x]->is_white() == in_white) && (board[y][x]->has_valid_move(board, y, x)))
            {
                //std::cout << "Analisi del pezzo ( " << y << ", "<<x << ")\n";
                if (toupper(board[y][x]->print()) == 'C') //Cavallo
                {
                    std::vector<std::pair<int,int>> c_mov = cavallo_moves(y, x);
                    for(int i = 0; i < c_mov.size(); i++)
                    {
                        if (!invalid_or_implies_check(y, x, c_mov[i].first, c_mov[i].second))
                        {
                            return 0;
                        }
                    }
                }
                else //Altri pezzi mosse lineari
                {
                    for (int dir_y = -1; dir_y <= 1; dir_y++)
                    {
                        for (int dir_x = -1; dir_x <= 1; dir_x++)
                        {
                            if (dir_x == 0 && dir_y == 0) { continue; }
                            int i_y = y + dir_y;
                            int i_x = x + dir_x;
                            while (in_bounds(i_y) && in_bounds(i_x))
                            {
                                if (!invalid_or_implies_check(y, x, i_y, i_x))
                                {
                                    return 0;
                                }
                                i_y += dir_y;
                                i_x += dir_x;
                            }
                        }
                    }
                }
                //std::cout << "Finito pezzo ( " << y << ", "<<x << ")\n";
            }
        }
    }
    //std::cout << "Uscito dal ciclo di is_draw \n";
    return 4;
}

//Ritorna la posizione (y,x) della minaccia nella direzione indicata, (-1,-1) altrimenti
std::pair<int, int> Chessboard::direction_threat(int king_y, int king_x, bool black_king, int dir_y, int dir_x)
{
    if (dir_y == 0 && dir_x == 0){return std::pair<int, int>(-1, -1);}
    int i_x = king_x + dir_x;
    int i_y = king_y + dir_y;
    while (in_bounds(i_x)&&in_bounds(i_y))
    {
        //std::cout << "In: " << i_y << ", " << i_x << " ce un  (" << board[i_y][i_x]->print() << ")\n";
        if ((board[i_y][i_x]->print() != ' ') && in_bounds(king_y) && in_bounds(king_x) && board[i_y][i_x]->is_valid_move(board, i_y, i_x, king_y, king_x))
        {
            //std::cout << "Minaccia in: (" << i_y << "," << i_x << ")\n";
            return std::pair<int, int>(i_y, i_x);
        }
        else if ((board[i_y][i_x]->print() != ' ') && ((board[i_y][i_x]->is_white()) != black_king))//Se trovo un pezzo dello stesso colore di black_king
            break;
        i_x = i_x + dir_x;
        i_y = i_y + dir_y;
    }
    //std::cout << "Nessuna minaccia\n";
    return std::pair<int, int>(-1, -1);
}
//Se il pezzo in (k_y, k_x) e minacciato da qualche direzione ritorna true
bool Chessboard::all_directions_threat(int k_y, int k_x, bool black_king)
{
    for (int dir_x = -1; dir_x <= 1; dir_x++)
    {
        for (int dir_y = -1; dir_y <= 1; dir_y++)
        {
            if ((dir_x != 0) || (dir_y != 0))
            {
                std::pair<int, int> threat_pos = direction_threat(k_y, k_x, black_king, dir_y, dir_x);
                if (in_bounds(threat_pos.first) && in_bounds(threat_pos.second))
                {
                    //std::cout << "Minaccia in :"<< threat_pos.first<<","<<threat_pos.second<<" : "<<board[threat_pos.first][threat_pos.second]->print()<<"\n";
                    return true;
                }
            }
        }
    }
    return false;
}
bool Chessboard::can_be_eaten(int p_y, int p_x)
{
    for (int dir_x = -1; dir_x <= 1; dir_x++)
    {
        for (int dir_y = -1; dir_y <= 1; dir_y++)
        {
            if ((dir_x != 0) || (dir_y != 0))
            {
                std::pair<int, int> t_pos = direction_threat(p_y, p_x, !(board[p_y][p_x]->is_white()), dir_y, dir_x);
                if (in_bounds(t_pos.first) && in_bounds(t_pos.second))
                {
                    if(!invalid_or_implies_check(t_pos.first, t_pos.second, p_y, p_x))
                        return true;
                }
            }
        }
    }
    return false;
}
std::vector<char> Chessboard::to_char_vector() //Ritorno la matrice per righe
{
    std::vector<char> v;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            v.push_back(board[i][j]->print());
        }
    }
    return v;
}
//controllo se la mossa (st_y, st_x) -> (end_y, end_x) implica scacco proprio
bool Chessboard::invalid_or_implies_check(int st_y, int st_x, int end_y, int end_x)
{
    if (!in_bounds(end_y) || !in_bounds(end_x) || !board[st_y][st_x]->is_valid_move(board, st_y, st_x, end_y, end_x))
    {
        //std::cout << " (Mossa non valida) \n";
        return true;
    }
    Piece *p_ep = board[end_y][end_x];
    board[end_y][end_x] = board[st_y][st_x];
    board[st_y][st_x] = new Nullo(); //DO MOVE
    bool check = false;
    bool bk_moved =( board[end_y][end_x]->print() == 'R');
    bool wk_moved = (board[end_y][end_x]->print() == 'r');
    if (bk_moved)//Aggiorno le posizioni dei re, necessario ad is_check
    {
        king_black[0] = end_y;
        king_black[1] = end_x;
    } 
    if (wk_moved)
    {
        king_white[0] = end_y;
        king_white[1] = end_x;
    }
    if (is_check(!board[end_y][end_x]->is_white(), st_y, st_x, end_y, end_x))
        check = true;
    delete board[st_y][st_x]; //Elimino il pezzo nullo inserito per provare la mossa
    board[st_y][st_x] = board[end_y][end_x];
    board[end_y][end_x] = p_ep; //  UNDO MOVE
    if (bk_moved)//Resetto le posizioni dei re se testati
    {
        king_black[0] = st_y;
        king_black[1] = st_x;
    } 
    if (wk_moved)
    {
        king_white[0] = st_y;
        king_white[1] = st_x;
    }
    //if(check){//std::cout<<"La mossa implica scacco\n";}
    return check;
}

//_________________________________________________________________________________________________
// DEFINIZIONE HELPER FUNCTIONS
//Ritorna false se non fa parte della croce di possibile attacco
bool is_valid_traj(int p_y, int p_x, int k_y, int k_x)
{
    int x_diff = k_x - p_x;
    int y_diff = k_y - p_y;
    if ((x_diff == 0) != (y_diff == 0))//XOR
        return true;
    x_diff = std::abs(x_diff);
    y_diff = std::abs(y_diff);
    if (std::abs(x_diff) == std::abs(y_diff))
        return true;
    return false;
}
//empty per svuotare la "memoria"
void past_positions(std::vector<char> mat, bool empty)
{
    static std::vector<std::pair<std::vector<char>, int>> past_pos; //vettore di coppie: (matrice per righe, numero di ripetizioni della posizione)
    if (empty)
    {
        past_pos = {std::pair<std::vector<char>, int>(mat, 1)};
        return;
    }
    for (int i = 0; i < past_pos.size(); i++)
    {
        std::vector<char> &m = past_pos[i].first;
        if (are_equals(mat, m))
        {
            if (past_pos[i].second == 2)
                throw three_time_repeated{};
            past_pos[i].second++;
            return;
        }
    }
    past_pos.push_back(std::pair<std::vector<char>, int>(mat, 1));
    return;
}
bool are_equals(std::vector<char> a, std::vector<char> b)
{
    if (a.size() != b.size())
        return false;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
            return false;
    }
    return true;
}
bool in_bounds(int n)
{
    return (n >= 0 && n < 8);
}
//da coordinate della matrice a stringa come mossa
std::string string_move(int s_y, int s_x, int e_y, int e_x)
{
    std::string s_m;
    char c_s_x = s_x + 65; //'A' = 65
    s_m.push_back(c_s_x);
    s_m += std::to_string(8 - s_y);
    s_m.push_back(' ');
    char c_e_x = e_x + 65;
    s_m.push_back(c_e_x);
    s_m += std::to_string(8 - e_y);
    return s_m;
}
//ritorna le posizioni di un cavallo che possa partire (od arrivare) in d_y, d_x
std::vector<std::pair<int,int>> cavallo_moves(int d_y, int d_x)
{
    std::vector<std::pair<int,int>> moves;
    for (int off_y = -2; off_y <= 2; off_y++)
    {
        if (off_y == 0)
        {
            continue;
        }
        if (off_y % 2 == 0)
        {
            for (int off_x = -1; off_x <= 1; off_x += 2)
            {
                if (in_bounds(d_y + off_y) && in_bounds(d_x + off_x))
                {
                    moves.push_back(std::pair<int,int>(d_y + off_y, d_x + off_x));
                }
            }
        }
        else
        {
            for (int off_x = -2; off_x <= 2; off_x += 4)
            {
                if (in_bounds(d_y + off_y) && in_bounds(d_x + off_x))
                {
                    moves.push_back(std::pair<int,int>(d_y + off_y, d_x + off_x));
                }
            }
        }
    }
    return moves;
}