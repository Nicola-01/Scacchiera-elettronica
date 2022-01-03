///*
//    AUTORE: Martino Scagnet 2000134
//
//    file: Rules.cpp
//*/
//#include "Chessboard.h"
//#include "Piece.h"
//
//#include <utility>
//#include <memory>
//#include <vector>
//#include <algorithm>
//
////HELPER FUNCTIONS
//bool is_valid_traj(int p_x, int p_y, int k_x, int k_y);
//std::vector<std::pair<std::vector<char>, int>> past_positions(std::vector<char>);
//bool are_equals(std::vector<char> a, std::vector<char> b);
////Eccezioni
//class three_time_repeated{};
////if(in_black) -> controllo scacco del re nero tra i pezzi bianchi -> pezzo.is_white() 
//
/////*
////Ritorna 1 se il re indicato da in_black e' sotto scacco
//// 2 se e' anche scacco matto
//// 0 se non e' nulla
//int Chessboard::is_check(bool in_black, int st_y, int st_x, int end_y, int end_x)
//{
//    Piece moved = board[end_y][end_x];
//    //Piece threat = Piece();
//    std::pair<int,int> threat_pos;
//    //Se ho mosso bianco e cerco scacco nel nero e viceversa devo verificare lo scacco matto
//    bool mate = (moved.is_white() == in_black);
//    int k_x = king_white[1];
//    int k_y = king_white[0];
//    if(in_black)
//    {
//        k_x = king_black[1];
//        k_y = king_black[0];
//    }
//    bool king_moved = (toupper(moved.print())=='R');
//    if(mate)//La mossa e' d'attacco
//    {
//        bool found = false;
//        bool second = false;
//        //controllo se il pezzo mosso minaccia
//        if (moved.is_valid_move(board, end_y, end_x, k_y, k_x))
//        {
//            found = true;
//            threat_pos.first = end_y;
//            threat_pos.second = end_x;
//        }
//        //controllo se il pezzo scoperto da moved minaccia
//        if(is_valid_traj(st_y, st_x, k_y, k_x))
//        {
//            std::pair<int, int> second_t_pos = direction_threat(k_y, k_x, in_black ,((st_y-k_y)/std::abs(st_y-k_y)), ((st_x-k_x)/std::abs(st_x-k_x)));
//            if( second_t_pos.first >= 0)
//            {
//                if(found)
//                    second = true;
//                else
//                {
//                    found = true;
//                    threat_pos = second_t_pos;
//                }
//            }
//        }
//        //due pezzi minacciano
//        if(found && second)
//        {
//            if(is_checkmate_d(k_y, k_x))
//                return 2;
//            return 1;
//        }
//        //un pezzo minaccia
//        if(found)
//        {
//            if(is_checkmate_s(k_y, k_x, threat_pos))
//                return 2;
//            return 1;
//        }
//        return 0;
//    }
//    if(king_moved) //se e' stato mosso un re
//    {
//        for(int dir_x = -1; dir_x <= 1; dir_x++)
//        {
//            for(int dir_y = -1; dir_y <= 1; dir_y++)
//            {
//                if((dir_x!=0)||(dir_y!=0))
//                {
//                    threat_pos = direction_threat(k_y, k_x, in_black, dir_y, dir_x);
//                    if(threat_pos.first >= 0 && threat_pos.second >= 0)
//                        return 1;
//                }
//            }
//        }
//        return 0;
//    }
//    if(!mate && !king_moved) //verifica che la mossa sia valida
//    {
//        //controllo se il pezzo scoperto da moved minaccia
//        if(is_valid_traj(st_y, st_x, k_y, k_x))
//        {
//            int d_y = st_y - k_y;
//            int d_x = st_x - k_x;
//            if(d_y!=0)
//                d_y = d_y / (std::abs(d_y));
//            if(d_x!=0)
//                d_x = d_x / (std::abs(d_x));
//            std::pair<int, int> threat_pos = direction_threat(k_y, k_x, in_black ,d_y, d_x);
//            if(threat_pos.first > 0)
//                return 1;
//        }
//        return 0;
//    }
//    return 0;
//}
////Se due pezzi attaccano il re questo puo' salvarsi solo muovendosi
//bool Chessboard::is_checkmate_d(int k_y, int k_x)
//{
//    for(int x_off = -1; x_off <= 1 && ((x_off+k_x)<8); x_off++)
//    {
//        if((x_off+k_x) >= 0)
//        {
//            for(int y_off = -1; y_off <= 1 && ((y_off+k_y)<8); y_off++)
//            {
//                if((y_off+k_y) >= 0)
//                {
//                    if(board[k_y][k_x].is_valid_move(board, k_y, k_x, k_y+y_off, k_x+x_off))
//                        return false;
//                }
//            }
//        }
//    }
//    return true;
//}
//
////Se un pezzo attacca o questo puo' muoversi o un pezzo alleato 
////Puo' mettersi nella traiettoria
//bool Chessboard::is_checkmate_s(int k_y, int k_x, std::pair<int,int> t_pos)
//{
//    //controllo se il re si puo' muovere
//    if(!is_checkmate_d(k_y, k_x))
//        return false;
//    //controllo se puo' essere difeso
//    int dir_x = (t_pos.second - k_x)/std::abs(t_pos.second - k_x);
//    int dir_y = (t_pos.first - k_y)/std::abs(t_pos.first - k_y);
//    //scansione di tutti i pezzi alleati
//    for(int x = 0; x < 8; x++)
//    {
//        for(int y = 0; y < 8; y++)
//        {
//            if( ((board[y][x].is_white()) != (board[k_y][k_x].is_white())) )
//            {
//                for(int t_x = k_x + dir_x; (t_x + dir_x)!=(t_pos.second) ; t_x = t_x + dir_x)
//                {
//                    for(int t_y = k_y + dir_y; (t_y + dir_y)!=(t_pos.first); t_y = t_y + dir_y)
//                    {
//                        if(board[y][x].is_valid_move(board, y, x, t_y, t_x))//se si puo' mettere in mezzo
//                            return false;
//                    }
//                }
//            }
//
//        }
//    }
//    return true;
//}
//
//bool Chessboard::is_checkmate(bool in_black, int st_y, int st_x, int end_y, int end_x)
//{
//    int flag = is_check(in_black, st_y, st_x, end_y, end_x);
//    switch(flag)
//    {
//        case 0: case 1:
//            return false;
//        case 2:
//            return true;
//    }
//    return false;
//}
//
////Ritorna la posizione (y,x) della minaccia nella direzione indicata, (-1,-1) altrimenti
//std::pair<int, int> Chessboard::direction_threat(int king_y, int king_x, bool black_king, int dir_y, int dir_x)
//{
//    int i_x = king_x + dir_x;
//    int i_y = king_y + dir_y;
//    while(i_x >= 0 && i_x < 8 && i_y >= 0 && i_y < 8)
//    {
//        if((board[i_y][i_x].is_white())== black_king)
//        {
//            if(board[i_y][i_x].is_valid_move(board, i_y, i_x, king_y, king_x))
//             return std::pair<int,int>(i_y, i_x);
//        }
//        i_x = i_x + dir_x;
//        i_y = i_y + dir_y;
//    }
//    return std::pair<int,int>(-1,-1);
//}
//
//bool Chessboard::is_draw(int end_y, int end_x )
//{
//    std::vector<char> p_l;
//    for(int x = 0; x < 8; x++)
//    {
//        for(int y = 0; y < 8; y++)
//        {
//            if(board[y][x].print() != ' ')
//                p_l.push_back(board[y][x].print());
//        }
//    }
//    //_____PER MATERIALE INSUFFICIENTE______
//    //Si suppone che ci debbano essere per forza due re
//    //a) Re contro Re
//    if(p_l.size() < 3)
//        return true;
//    if(p_l.size() == 3)
//    {
//        //b)due re e (un alfiere o un cavallo)
//        for(char c : p_l)
//            if(toupper(c) == 'A' || toupper(c) == 'C')
//                return true;
//    }
//    if(p_l.size() == 4)
//    {
//        //c) due re e alfieri avversari sulle stesse caselle
//        if((std::find(p_l.begin(),p_l.end(), 'a') != p_l.end())&&(std::find(p_l.begin(),p_l.end(), 'A')!= p_l.end()))
//        {
//            bool first = false;
//            bool odd;
//            for(int x = 0; x < 8; x++)
//            {
//                for(int y = 0; y < 8; y++)
//                {
//                    if(toupper(board[y][x].print()) == 'A')
//                    {
//                        if(!first)
//                        {
//                            odd = (x+y)%2;
//                            first = true;
//                        }
//                        if(first && (((x+y)%2)==odd))
//                        {
//                            return true;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    static int piece_number = -1;
//    static int move_counter = 0;
//    if(piece_number == -1)
//        piece_number = p_l.size();
//    //________PER RIPETIZIONE DI POSIZIONE________
//    if(piece_number != p_l.size())
//    {
//        past_positions(to_char_vector(), true);//Azzero le posizioni passate 
//        move_counter = 0;//Azzero il contatore di mosse senza catture o mosse di pedone
//        piece_number = p_l.size();
//    }
//    else
//    {
//        try
//        {
//            past_positions(to_char_vector(), false);
//        }
//        catch(const three_time_repeated& e)
//        {
//            return true;
//        }
//        piece_number = p_l.size();
//    }
//    //________REGOLA DELLE 50 MOSSE_________
//    if(toupper(board[end_y][end_x].print()) == 'P')
//    {
//        move_counter = 0;
//    }
//    move_counter++;
//    if(move_counter >= 50)
//        return true;
//    //________PER STALLO________
//    bool in_white = !(board[end_y][end_x].is_white());//Se ha mosso bianco controllo stallo nero
//    for(int y = 0; y < 8; y++)
//    {
//        for(int x = 0; x < 8 && (board[y][x].is_white() == in_white); x++)
//        {
//            for(int p_y = 0; p_y < 8; p_y++)
//            {
//                for(int p_x = 0; p_x < 8; p_x++)
//                {
//                    if(board[y][x].is_valid_move(board, y,x, p_y, p_x))
//                        return false;
//                }
//            }
//        }
//    }
//    return true;
//}
//
//std::vector<char> Chessboard::to_char_vector()//Ritorno la matrice per righe
//{
//    std::vector<char> v;
//    for(int i = 0; i < 8; i++)
//    {
//        for(int j = 0; j < 8; j++)
//        {
//            v.push_back(board[i][j].print());
//        }
//    }
//    return v;
//}
//
////*/
//
//
//// DEFINIZIONE HELPER FUNCTIONS
/////*
////Ritorna una direzione come schema sotto, -1 se non fa parte della croce di possibile attacco
///*
//(7)(0)(1)
//(6)(K)(2)
//(5)(4)(3)
//*/
//bool is_valid_traj(int p_y, int p_x, int k_y, int k_x)
//{
//    int x_diff = k_x - p_x;
//    int y_diff = k_y - p_y;
//    if((x_diff == 0) != (y_diff==0))
//        return true;
//    x_diff = std::abs(x_diff);
//    y_diff = std::abs(y_diff);
//    if(std::abs(x_diff) == std::abs(y_diff))
//        return true;
//    return false;
//}
////empty per svuotare la "memoria"
//void past_positions(std::vector<char> mat, bool empty)
//{
//    static std::vector<std::pair<std::vector<char>, int>> past_pos;
//    if(empty)
//    {
//        past_pos = {std::pair<std::vector<char>, int> (mat, 0)};
//        return;
//    }
//    for(int i = 0; i < past_pos.size(); i++)
//    {
//        std::vector<char> &m = past_pos[i].first;
//        if(are_equals(mat, m))
//        {
//            if(past_pos[i].second == 2)
//                throw three_time_repeated{};
//            past_pos[i].second ++;
//            return;
//        }
//    }
//    past_pos.push_back(std::pair<std::vector<char>, int>(mat, 0));
//    return;
//}
//bool are_equals(std::vector<char> a, std::vector<char> b)
//{
//    if(a.size() != b.size())
//        return false;
//    for(int i = 0; i < a.size(); i++)
//    {
//        if(a[i] != b[i])
//            return false;
//    }
//    return true;
//}
//
////*/