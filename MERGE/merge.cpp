// Nicola Busato 2009663

#include <string>
#include <utility>
#include <vector>
#include <string>
#include <cctype> /* tolower toupper */
#include <iostream>
#include <iostream>
#include <cctype>
#include <fstream>
#include <iostream>
#include <time.h>
#include <stdlib.h>

#include <time.h> /* time */


using namespace std;

#define on_Linux 0

class InvalidMoveException
{
};
class InvalidMoveStringException
{
};

class Piece
{
public:
    Piece(bool color, int y, int x);
    Piece(bool color, int y, int x, bool m);
    Piece();

    bool move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x);
    std::pair<int, int> random_position(Piece (&Board)[8][8], int str_y, int str_x); //ritorna le coordinate sotto forma di stringa
    virtual bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x);

    bool is_white() { return white; }; // = true se e' un pezzo bianco
    virtual bool is_moved() { return moved; }

    bool is_end_same_color(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x);
    int get_ex_position_y() { return ex_position_y; };
    int get_ex_position_x() { return ex_position_x; };

    void set_number_move(int n) { number_move = n; };          //numero mossa
    int get_number_move() { return number_move; };

    bool check_boundary(int end_y, int end_x) { return end_y > -1 && end_x > -1 && end_y < 8 && end_x < 8; };
    bool check_arrocco_re(Piece (&Board)[8][8], int end_y, int end_x);
    void set_move(bool m) { moved = m; };
    char print() { return type; };
    // void undo_move();
protected:
    char type;
    int ex_position_x;
    int ex_position_y;
    bool white;
    bool moved = false;
    int number_move;
};

class Chessboard
{
private:
    //--- variables
    Piece board[8][8]; //[y][x]
    //Rules rul;
    const std::string pos{"TCADRACT"};
    int king_white[2]{7, 4}; //y x
    int king_black[2]{0, 4};
    int str[2];
    int end[2];
    int last_capture;

    //--- methods
    Piece inizializer_piece(char p, int y, int x);
    bool is_valid_string(std::string move);

    // std::pair<int, int> direction_threat(int king_y, int king_x, bool black_king, int dir_y, int dir_x);
    // bool is_checkmate_d(int k_y, int k_x);
    // bool is_checkmate_s(int k_y, int k_x, std::pair<int,int> t_pos);
    // std::vector<char> to_char_vector();

public:
    Chessboard();
    int move(std::string& move, bool white_turne);
    bool is_right_piece(int y, int x, bool white_turne) { return (board[y][x].print() != ' ' && board[y][x].is_white() == white_turne); };
    std::string random_move(int y, int x);
    char pices_type(int y, int x) { return board[y][x].print(); }

    bool is_checkmate(bool in_black, int st_y, int st_x, int end_y, int end_x) { return false; }
    int is_check(bool in_black, int st_y, int st_x, int end_y, int end_x) { return false; }
    bool is_draw(int end_y, int end_x) { return false; }
    
    bool is_checkmate(bool in_black) { return false; }
    int is_check(bool in_black) { return false; }
    bool is_draw() { return false; }
};

//Riccardo Miele 2008594



//MANCANO I DISTRUTTORI
//CONTROLLO DELLA REGOLA 4 DELL'ARROCCO

extern int n_moves;



class Re : public Piece
{
public:
    Re(bool color, int y, int x);
    Re(bool color, int y, int x, bool m);
    Re(Piece){};

    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
    bool is_moved() { return moved; };
    std::pair<int, int> random_xy(Piece (&Board)[8][8], int str_y, int str_x);
private:
    bool moved = false; //dopo la prima mossa diventa true
};

class Donna : public Piece
{
public:
    Donna(bool color, int y, int x);
    Donna(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
};

class Torre : public Piece
{
public:
    Torre(bool color, int y, int x);
    Torre(bool color, int y, int x, bool m);
    Torre(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
    bool is_moved() { return moved; };
    std::pair<int, int> random_xy(Piece (&Board)[8][8], int str_y, int str_x);
private:
    bool moved = false;
    //bool arrocco_torre = false;
};

class Alfiere : public Piece
{
public:
    Alfiere(bool color, int y, int x);
    Alfiere(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
    std::pair<int, int> random_xy(Piece (&Board)[8][8], int str_y, int str_x);
};

class Cavallo : public Piece
{
public:
    Cavallo(bool color, int y, int x);
    Cavallo(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
    std::pair<int, int> random_xy(Piece (&Board)[8][8], int str_y, int str_x);
};

class Pedone : public Piece
{
public:
    Pedone(bool color, int y, int x);
    Pedone(Piece){};
    Pedone(bool color, int y, int x, bool m);
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override;
    bool is_moved() { return moved; };
    bool check_promotion(int y) { return y == 0 || y == 7; }; //se arrivato alla fine e' true
    std::pair<int, int> random_xy(Piece (&Board)[8][8], int str_y, int str_x);
private:
    bool moved = false;
    int number_move;
};

class Nullo : public Piece
{
public:
    Nullo();
    Nullo(Piece){};
    bool is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) override { return false; };
};

//Eccezioni
class PromotionException
{
};
class ArroccoException
{
};

Chessboard::Chessboard()
{
    for (int x = 0; x < 8; x++)
    {
        board[0][x] = inizializer_piece(pos[x], 0, x);
        board[1][x] = inizializer_piece('P', 1, x); // P
        for (int y = 2; y <= 5; y++)
            board[y][x] = inizializer_piece(' ', y, x);
        board[6][x] = inizializer_piece('p', 6, x); // p
        board[7][x] = inizializer_piece(tolower(pos[x]), 7, x);
    }
}

int Chessboard::move(string& move, bool white_turne)
{
    bool promotion{false}, arrocco{false};
    for (int i = 0; i < move.size(); i++)
        move[i] = toupper(move[i]);
    if(move == "CLEAR")
        return -2;

    if (move == "XX XX")
        return -1;

    if (!is_valid_string(move))
        return 1; // formato string non valido   // throw InvalidMoveStringException();

    int str_x = (move[0] - 'A'),
        str_y = abs(move[1] - '0' - 8),
        end_x = (move[3] - 'A'),
        end_y = abs(move[4] - '0' - 8);

    //cout << str_y << " " << str_x << "   " << end_y << " "  << end_x << endl;

    if (board[str_y][str_x].print() == ' ')
        return 2; // nessun pezzo nella posizione indicata  // throw InvalidMoveException();

    if (!is_right_piece(str_y, str_x, white_turne))
        return 3; // Muove pezzo avverstaio

    try
    {
        //cout << "da qui " << end_y;
        //cin.get();
        if (!board[str_y][str_x].move(board, str_y, str_x, end_y, end_x))
            return 4; // Mossa non possibil
    }
    catch (PromotionException &e)
    {
        promotion = true; // se c'è stata una promozione ma dopo mi faccio un auto scacco allora quel pezzo deve tornare un pedone
    }
    catch (ArroccoException &e)
    {
        arrocco = true;
    }

        Piece gonna_die = board[end_y][end_x];
        board[end_y][end_x] = board[str_y][str_x];
        board[str_y][str_x] = Nullo();

    if (board[end_y][end_x].print() == 'R') // Re nero
    {
        king_black[0] = end_y;
        king_black[1] = end_x;
    }
    else if (board[end_y][end_x].print() == 'r')
    {
        king_white[0] = end_y;
        king_white[1] = end_x;
    }

    if (is_check(!white_turne, str_y, str_x, end_y, end_x) > 0)
    {

        board[str_y][str_x] = board[end_y][end_x];
        board[end_y][end_x] = gonna_die;

        if (promotion)
            board[str_y][str_x] = Pedone(white_turne, str_y, str_x);
        else if (arrocco) // se è stato fatto un auto scacco perchè si ha fatto un arrocco allora il re viene spostato "in automatico" ma la torre no 
        {
            int x_torre = (end_x<str_y) ? 3 : 5; // arrocco lungo : arrocco corto
            board[str_y][x_torre] = board[str_y][x_torre];
            board[str_y][x_torre] = Nullo();
        }
        else if (board[str_y][str_x].print() == 'R') // Re nero
        {
            king_black[0] = str_y;
            king_black[1] = str_x;
        }
        else if (board[str_y][str_x].print() == 'r')
        {
            king_white[0] = str_y;
            king_white[1] = str_x;
        }

        return 4; // scacco, mossa annullata
    }
    str[0] = str_y;
    str[1] = str_x;
    end[0] = end_y;
    end[1] = end_x;

    if (gonna_die.print() != ' ')
        last_capture = n_moves;
    return 0; // mossa valida
}

bool Chessboard::is_valid_string(string move) // Ln Ln    L->Lettera n->Numero
{
    return move.size() == 5 && move[2] == ' ' &&
           65 <= move[0] && move[0] <= 72 &&
           65 <= move[3] && move[3] <= 72 &&
           0 < move[1] - '0' && move[1] - '0' <= 8 &&
           0 < move[4] - '0' && move[4] - '0' <= 8;
}

string Chessboard::random_move(int y, int x)
{
    pair<int, int> a{-1,-1};
    bool promotion{false}, arrocco{false};
    try {
        a = board[y][x].random_position(board, y, x); // restituisce le cordinate di arrivo
    }
    catch (PromotionException &e) {
        promotion = true;
    }
    catch (ArroccoException &e) {
        arrocco = true;
    }
    
    cout << " --------------------- random " << y << " " << x << " " << a.first << " " << a.second << endl;
    if (a.first >= 0)
        return (char)('A' + x) + to_string(abs(y - 8)) + " " + (char)('A' + a.second) + to_string((abs(a.first - 8)));
    return "NV NV";
    // restituisce un array di 2, se è lo spostamento possibile da la posizione [y][x] altrimenti -1, -1
}

Piece Chessboard::inizializer_piece(char p, int y, int x)
{
    switch (toupper(p))
    {
    case 'R':
        return Re(p == 'r', y, x);
    case 'D':
        return Donna(p == 'd', y, x);
    case 'C':
        return Cavallo(p == 'c', y, x);
    case 'A':
        return Alfiere(p == 'a', y, x);
    case 'T':
        return Torre(p == 't', y, x);
    case 'P':
        return Pedone(p == 'p', y, x);
    default:
        return Nullo();
    }
}

ostream& operator<<(ostream& os, Chessboard& cb)
{
    os << "\n\n";
    for (int y = 0; y < 8; y++)
    {
        os << 8 - y << "   ";
        for (int x = 0; x < 8; x++)
            os << cb.pices_type(y, x) << " ";
        os << "\n";
    }
    os << "\n    A B C D E F G H\n\n";
    return os;
}
// Nicola Busato 2009663




int n_moves;

class ArgumentsException
{
};

constexpr int moves_max = 100;

string result_type(int t, string move_line);
void player_turne(Chessboard &scacchiera, bool white_turne, ofstream &log_file);
void computer_turne(Chessboard &scacchiera, bool white_turne, ofstream &log_file);

// stampa colorata (Solo su linux)  https://www.tutorialspoint.com/how-to-output-colored-text-to-a-linux-terminal
void print_red(string s) { cout << ((on_Linux) ? "\033[;31m" + s + "\033[0m" : s) << endl; }
void print_green(string s) { cout << ((on_Linux) ? "\033[;32m" + s + "\033[0m" : s) << endl; }
ostream &operator<<(ostream &os, Chessboard &cb);

int main(int argc, char *argv[])
{
    if (system("CLS"))
        system("clear");
    string game_type = argv[1];
    for (int i = 0; i < game_type.size(); i++)
        game_type[i] = tolower(game_type[i]);

    if (argc != 2 || (game_type != "pc" && game_type != "cc" && game_type != "pp"))
    {
        cout << "Argomenti non validi, aggiungere: pp (Player vs Player), pc (Player vs Computer) o cc (Computer vs Computer);\n";
        throw ArgumentsException();
    }

    ofstream log_file;
    log_file.open("../log.txt"); //svuoto il file se è già stato scritto
    //log_file.close();

    srand(time(NULL));
    int player = (game_type == "pc") ? rand() % 2 + 1 : 0; // 0, se non è un giocatore ,1 se è bianco, 2 se è nero
    if (player != 0)
        print_green((player == 1) ? "Giochi con il bianco" : "Giochi con il nero");

    Chessboard scacchiera{};
    n_moves;
    bool white_turne{true};
    while (n_moves < moves_max)
    {
        //outfile.open("../log.txt", ios_base::app); //riapro il file (faccio una sorta di autosave)
        //if (system("CLS")) system("clear");
        cout << scacchiera; //.move("XX XX", white_turne);

        if (game_type == "pp")
        { // forse provvisorio
            print_green(((white_turne) ? "-= Tocca al bianco =-" : "-= Tocca al nero =-"));
            player_turne(scacchiera, white_turne, log_file);
        }
        else if (player == 1 && white_turne || player == 2 && !white_turne)
        {
            print_green("--- Tocca a te");
            player_turne(scacchiera, white_turne, log_file);
        }
        else
        {
            print_red("--- Tocca al computer");
            computer_turne(scacchiera, white_turne, log_file);
        }

        white_turne = !white_turne;

        if (int check = scacchiera.is_check(!white_turne) > 0)
        {
            if (check == 2)
            { // è scacco matto
                (white_turne) ? print_green("Ha vinto il bianco") : print_green("Ha vinto il Nero");
                break;
            }
            // else è scacco
            (white_turne) ? print_green("Il Bianco ha fatto scacco al Nero") : print_green("Il Nero ha fatto scacco al Bianco");
            // log_file.close();
        }
        else if (false) //scacchiera.is_draw())
        {
            print_green("Partita finita in patta");
            break; // non mi piace molto, valuto
            // log_file.close();
            // return 0;
        }

        n_moves++;
    }
    log_file.close();
    return 0;
}

string result_type(int t, string move_line)
{
    switch (t)
    {
    case 1:
        return "Formato stringa non valido, inserirne una valida; \"A0 H8\", \"XX XX\", \"clear\"; :";
    case 2:
        return "Non puoi spostare l'aria, inserirne una valida:";
    case 3:
        return "Non puoi muovere il pezzi del avversario, fai una altra mossa:";
    case 4:
        return "La mossa " + move_line + " non e' valida, inserire una mossa valida:";
    case 5:
        return "Ti stai facendo scacco da solo, forse è meglio cambiarla:";
    default:
        return "";
    }
}

void player_turne(Chessboard &scacchiera, bool white_turne, ofstream &log_file)
{
    int output_type;
    string line;
    print_green("Inserire la mossa: ");
    getline(cin, line);
    while ((output_type = scacchiera.move(line, white_turne)) != 0)
    {
        if (output_type == -2)
        {
            if (system("CLS"))
                system("clear");
            cout << scacchiera;
            print_green("Inserire la mossa: ");
        }
        else
            cout << scacchiera;
        if (output_type == -1)
            cout << scacchiera;
        print_red(result_type(output_type, line));
        getline(cin, line);
    }
    log_file << line + "\n";
}

void computer_turne(Chessboard &scacchiera, bool white_turne, ofstream &log_file)
{
    string line;
    int y, x;
    do
    {
        do
        {
            y = rand() % 8;
            x = rand() % 8;
            cout << y << " " << x;
            cin.get();
        } while (!scacchiera.is_right_piece(y, x, white_turne));
        line = scacchiera.random_move(y, x);
        cout << "-- Prova dello spostamento: " << line << endl;
    } while (scacchiera.move(line, white_turne) != 0); //Not Valid
    cout << line;
    log_file << line + "\n";
}
//Riccardo Miele 2008594

//COSTRUTTORI

Piece::Piece() //costruttore di default
{
    white = false;
    ex_position_x = -1;
    ex_position_y = -1;
};

Piece::Piece(bool color, int y, int x) //costruttore
{
    white = color;
    ex_position_x = x;
    ex_position_y = y;
};

Piece::Piece(bool color, int y, int x, bool m) //costruttore con moved
{
    white = color;
    ex_position_x = x;
    ex_position_y = y;
    moved = m;
};

Re::Re(bool color, int y, int x) : Piece(color, y, x) //costruttore Re
{
    if (color)
        type = 'r';
    else
        type = 'R';
    moved = false;
};

Re::Re(bool color, int y, int x, bool m) : Piece(color, y, x, m)
{
    if (color)
        type = 'r';
    else
        type = 'R';
    moved = m;
};

Donna::Donna(bool color, int y, int x) : Piece(color, y, x) //costruttore Donna
{
    if (color)
        type = 'd';
    else
        type = 'D';
};

Torre::Torre(bool color, int y, int x) : Piece(color, y, x) //costruttore Torre
{
    if (color)
        type = 't';
    else
        type = 'T';
    moved = false;
};

Torre::Torre(bool color, int y, int x, bool m) : Piece(color, y, x, m)
{
    if (color)
        type = 't';
    else
        type = 'T';
    moved = m;
};

Alfiere::Alfiere(bool color, int y, int x) : Piece(color, y, x) //costruttore Alfiere
{
    if (color)
        type = 'a';
    else
        type = 'A';
};

Cavallo::Cavallo(bool color, int y, int x) : Piece(color, y, x) //costruttore Cavallo
{
    if (color)
        type = 'c';
    else
        type = 'C';
};

Pedone::Pedone(bool color, int y, int x) : Piece(color, y, x) //costruttore Pedone
{
    if (color)
        type = 'p';
    else
        type = 'P';
    moved = false;
};

Pedone::Pedone(bool color, int y, int x, bool m) : Piece(color, y, x, m)
{
    if (color)
        type = 'p';
    else
        type = 'P';
    moved = m;
}

Nullo::Nullo() : Piece() //costruttore (Pezzo) Nullo
{
    type = ' ';
};

//FUNZIONI DI PIECE

bool Piece::is_end_same_color(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) //ritorna true se la destinazione ha lo stesso colore
{
    if (Board[end_y][end_x].print() == ' ')
        return false;
    return (Board[str_y][str_x].is_white() == Board[end_y][end_x].is_white());
};

bool Piece::move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    if (is_valid_move(Board, str_y, str_x, end_y, end_x))
    {
        ex_position_x = str_x;
        ex_position_y = str_y;
        return true;
    }
    return false;
};

bool Piece::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    char in = toupper(Board[str_y][str_x].type);
    bool control = false; //control == vero is_valid_move ritorna == vero
    // cout << "-- Tipo Pezzo: " << in << endl;
    //cout << "Spostamento [y][x] (str), (end) [" << str_y << "][" << str_x << "] [" << end_y << "][" << end_x << "]\n";
    switch (in)
    {
    case 'R':
    {
        Re r = Re(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x(), Board[str_y][str_x].is_moved());
        control = r.is_valid_move(Board, str_y, str_x, end_y, end_x);
        set_move(r.is_moved());
        break;
    }
    case 'D':
    {
        Donna d = Donna(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
        control = d.is_valid_move(Board, str_y, str_x, end_y, end_x);
        break;
    }
    case 'T':
    {
        Torre t = Torre(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x(), Board[str_y][str_x].is_moved());
        control = t.is_valid_move(Board, str_y, str_x, end_y, end_x);
        set_move(t.is_moved());
        break;
    }
    case 'A':
    {
        Alfiere a = Alfiere(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
        control = a.is_valid_move(Board, str_y, str_x, end_y, end_x);
        break;
    }
    case 'C':
    {
        Cavallo c = Cavallo(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x());
        control = c.is_valid_move(Board, str_y, str_x, end_y, end_x);
        break;
    }
    case 'P':
    {
        Pedone p = Pedone(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x(), Board[str_y][str_x].is_moved());
        control = p.is_valid_move(Board, str_y, str_x, end_y, end_x);
        set_move(p.is_moved());
        break;
    }
    }
    return control;
}

//ARROCCO

bool Piece::check_arrocco_re(Piece (&Board)[8][8], int end_y, int end_x)
{
    if (end_x < 4)
    {
        Torre t = Torre(Board[end_y][end_x - 1].is_white(), Board[end_y][end_x - 1].get_ex_position_y(), Board[end_y][end_x - 1].get_ex_position_y());
        if (!t.is_moved() && Board[end_y][end_x].print() != ' ' && Board[end_y][end_x + 1].print() != ' ' && Board[end_y][end_x - 1].print() != ' ')
        {
            Board[end_y][end_x - 2] = Nullo(); //(false, end_y, end_x - 1);
            Board[end_y][end_x + 1] = Torre(is_white(), end_y, end_x + 1);
            throw ArroccoException(); //return true;
        }
    }
    else //end_x > 4
    {
        Torre t = Torre(Board[end_y][end_x + 1].is_white(), Board[end_y][end_x + 1].get_ex_position_y(), Board[end_y][end_x + 1].get_ex_position_y());
        if (!t.is_moved() && Board[end_y][end_x].print() != ' ' && Board[end_y][end_x - 1].print() != ' ')
        {
            Board[end_y][end_x + 1] = Nullo(); //(false, end_y, end_x - 1);
            Board[end_y][end_x - 1] = Torre(is_white(), end_y, end_x + 1);
            throw ArroccoException(); //return true;
        }
    }
    return false;
}

//FUNZIONE IS_VALID_MOVE

bool Re::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false; //destinazione stesso colore;
    if (delta_x != 1 || delta_y != 1)
    {
        if (!is_moved() && check_arrocco_re(Board, end_y, end_x))
        {
            moved = true;
            return true;
        }
        return false; //percorso > 1
    }
    moved = true;
    return true;
};

bool Donna::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    Piece p = Piece();
    bool control_condition = ((Torre)p).is_valid_move(Board, str_y, str_x, end_y, end_x) ||
                             ((Alfiere)p).is_valid_move(Board, str_y, str_x, end_y, end_x);
    return control_condition;
};

bool Torre::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (str_x != end_x && str_y != end_y)
        return false; //non si muove verticalmente o orizzontalmente
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false; //destinazione diverso colore;
    for (int i = 1; i < delta_x; i++)
    {
        if (end_x > str_x)
        {
            if (Board[end_y][str_x + i].print() != ' ')
                return false;
        }
        else
        {
            if (Board[end_y][str_x - i].print() != ' ')
                return false;
        }
    }
    for (int i = 1; i < delta_y; i++) //delta_y = 2
    {
        //cout << "ciclo for " << i << " " << delta_y << endl;
        if (end_y > str_y)
        {
            if (Board[str_y + i][end_x].print() != ' ')
                return false;
        }
        else // str_y = 6  end_y = 4
        {
            if (Board[str_y - i][end_x].print() != ' ')
                return false;
        }
        //cout << str_y-i << " " << end_x << " " << Board[str_y - i][end_x].print()<<endl;
    }
    moved = true;
    return true;
};

bool Cavallo::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    //cout << delta_x << " " << delta_y << endl;
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false; //destinazione diverso colore;
    return (delta_x == 2 && delta_y == 1) || (delta_x == 1 && delta_y == 2);
};

bool Alfiere::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x)
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x))
        return false; //destinazione diverso colore;
    if (delta_x != delta_y)
        return false; //non si muove in diagonale
    for (int i = 1; i < delta_x; i++)
    {
        if (end_y > str_y)
        {
            if (Board[str_y + i][str_x - i].print() != ' ')
                return false;
        }
        else
        {
            if (Board[str_y - i][str_x + i].print() != ' ')
                return false;
        }
    }
    return true;
};

bool Pedone::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) //promozione probabilmente sbagliata
{
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x)) //destinazione diverso colore;
        return false;
    if (delta_y > 2) //non si può muovere piu' di 2 caselle
        return false;
    if (delta_x > 1) //non si può muovere in diagonale
        return false;
    if (Board[str_y][str_x].print() == 'p') //tornare indietro, si puo' fare sicuramente meglio
    {
        if (end_y > str_y)
            return false;
    }
    else
    {
        if (end_y < str_y)
            return false;
    }

    if (delta_x == delta_y)
    {
        if (Board[end_y][end_x].print() != ' ')
        {
            return false;
        }
        std::cout << "en passant, n_moves: " << n_moves << " , pednone " << str_y << "; " << end_x << " ; number_move: " << Board[str_y][end_x].get_number_move() << std::endl;
        if ((Board[str_y][end_x].get_ex_position_y() == 6 || Board[str_y][end_x].get_ex_position_y() == 1) && toupper(Board[str_y][end_x].print()) == 'P' && Board[str_y][end_x].is_moved() && (n_moves - 1) == Board[str_y][end_x].get_number_move()) //en passant
        {
            Board[str_y][end_x] = Nullo(); //(false, str_y, str_x); //en passant in teoria giusto
            return true;
        }
    }
    if (delta_x == 0 && Board[end_y][end_x].print() != ' ') //non può mangiare in avanti
    {
        return false;
    }
    //delta_y == 2 && (Board[str_y][str_x].get_ex_position_y() == 6 || Board[str_y][str_x].get_ex_position_y() == 1)
    if (delta_y == 2 && moved)
    {
        return false;
    }
    if (delta_y == 2)
    {
        set_number_move(n_moves);
    }
    if (check_promotion(end_y))
    {
        std::string input;
        char in;
        while (input.length() != 1 || (in != 'D' && in != 'T' && in != 'A' && in != 'C')) //funziona
        {
            std::cout << "Inserisci il carattere del pezzo che vuoi (D, T, C, A)" << std::endl;
            std::getline(std::cin, input);
            in = input[0];
            in = toupper(in);
        }
        switch (in)
        {
        case 'D':
        {
            Board[str_y][str_x] = Donna(is_white(), end_y, end_x);
            break;
        }
        case 'T':
        {
            Board[str_y][str_x] = Torre(is_white(), end_y, end_x);
            break;
        }
        case 'C':
        {
            Board[str_y][str_x] = Cavallo(is_white(), end_y, end_x);
            break;
        }
        case 'A':
        {
            Board[str_y][str_x] = Alfiere(is_white(), end_y, end_x);
            break;
        }
        }
        //Board[str_y][str_x] = Nullo(false, str_y, str_x);
        //bisogna distruggere il pedone
        throw PromotionException();
    }
    moved = true;
    return true;
};

//RANDOM MOVE

std::pair<int, int> Piece::random_position(Piece (&Board)[8][8], int str_y, int str_x) //ritorna le coordinate sotto forma di stringa
{
    char in = toupper(type);
    srand(time(NULL));
    std::pair<int, int> output;
    Piece tmp = Piece(false, 0, 0); //serve solo per invocare il metodo giusto
    switch (in)
    {
    case 'R': //funziona
    {
        output = ((Re)tmp).random_xy(Board, str_y, str_x);
        break;
    };
    case 'D': //poco efficiente
    {
        do
        {
            int torre_alfiere = rand() % 2;
            if (torre_alfiere)
            {
                output = ((Torre)tmp).random_xy(Board, str_y, str_x);
            }
            else
            {
                output = ((Alfiere)tmp).random_xy(Board, str_y, str_x);
            }
        } while (output.first == -1);
        break;
    }
    case 'T':
    {
        output = ((Torre)tmp).random_xy(Board, str_y, str_x);
        break;
    }
    case 'C': //o cosi' o con uno switch -> riga 414
    {
        output = ((Cavallo)tmp).random_xy(Board, str_y, str_x);
        break;
    }
    case 'A':
    {
        output = ((Alfiere)tmp).random_xy(Board, str_y, str_x);
        break;
    }
    case 'P':
    {
        output = ((Pedone)tmp).random_xy(Board, str_y, str_x);
        break;
    }
    }
    return output;
};

//RANDOM PER OGNI PEZZO

std::pair<int, int> Re::random_xy(Piece (&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x;
    int i = 0;
    std::pair<int, int> output{-1, -1};
    do
    {
        end_x = rand() % (3) + (str_x - 1); //3 possibili numeri a partire da quello a sinistra
        end_y = rand() % (3) + (str_y - 1); //3 possibili numeri a partire da quello a sotto
        if (i >= 20)
        {
            end_y = -1;
            end_x = -1;
            break;
        }
        i++;
    } while (!(check_boundary(end_y, end_x) && is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    return output; //se non trova niente ritorna -1-1
};

std::pair<int, int> Torre::random_xy(Piece (&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x;
    int i = 0;
    std::pair<int, int> output{-1, -1};
    do
    {
        int random = rand() % 2;
        if (random)
        {
            end_x = str_x; //se random == 1 si muove in verticale
            end_y = rand() % 8;
        }
        else
        {
            end_y = str_y; //si muove in orizzontale
            end_x = rand() % 8;
        }
        if (i >= 40)
        {
            end_y = -1;
            end_x = -1;
            break; //se non trova niente ritorna -1-1
        }
        i++;
    } while (!(check_boundary(end_y, end_x) && is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    return output;
};

std::pair<int, int> Cavallo::random_xy(Piece (&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x;
    int i = 0;
    std::pair<int, int> output{-1, -1};
    do
    {
        int random_1 = rand() % 2;
        int random_2 = rand() % 2;
        int random_3 = rand() % 2;
        if (random_1) //se random_1 == 1 delta_y = 1
        {
            if (random_2) //se random_2 == 1 end_y > str_y
                end_y = str_y + 1;
            else
            {
                end_y = str_y - 1;
            }
            if (random_3) //se random_3 == 1 end_x > str_x
            {
                end_x = str_x + 2;
            }
            else
            {
                end_x = str_x - 2;
            }
        }
        else
        {
            if (random_2) //se random_2 == 1 end_y > str_y
                end_y = str_y + 2;
            else
            {
                end_y = str_y - 2;
            }
            if (random_3) //se random_3 == 1 end_x > str_x
                end_x = str_x + 1;
            else
            {
                end_x = str_x - 1;
            }
        }
        if (i >= 20)
        {
            end_y = -1;
            end_x = -1;
            break; //se non trova niente ritorna -1-1
        }
        i++;
    } while (!(check_boundary(end_y, end_x) && is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    return output;
};

std::pair<int, int> Alfiere::random_xy(Piece (&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x, i;
    std::pair<int, int> output{-1, -1};
    int cont = 0;
    do
    {
        i = 1 + rand() % 7; //7 possibili numeri a partire da 0
        int up_down = rand() % 2;
        int right_left = rand() % 2;
        if (up_down) //se up_down == 1 si muove verso l'alto
            end_y = str_y - i;
        else
        {
            end_y = str_y + i;
        }
        if (right_left) // rigth_left == 1 si muove verso destra
            end_x = str_x + i;
        else
        {
            end_x = str_x - i;
        }
        if (cont >= 40)
        {
            end_y = -1;
            end_x = -1;
            break; //se non trova niente ritorna -1-1
        }
        cont++;
    } while (!(check_boundary(end_y, end_x) && is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    return output;
};

std::pair<int, int> Pedone::random_xy(Piece (&Board)[8][8], int str_y, int str_x)
{
    srand(time(NULL));
    int end_y, end_x;
    int i = 0;
    std::pair<int, int> output{-1, -1};
    Pedone p = Pedone(Board[str_y][str_x].is_white(), Board[str_y][str_x].get_ex_position_y(), Board[str_y][str_x].get_ex_position_x(), Board[str_y][str_x].is_moved());
    do
    {
        int d_y;
        end_x = rand() % (3) + (str_x - 1); //3 possibili numeri a partire da quello a sinistra
        if (!p.is_moved())                  //si può muovere di due
        {
            d_y = 1 + rand() % 2;
        }
        else
        {

            d_y = 1;
        }
        if (p.is_white())
        {
            end_y = str_y - d_y;
        }
        else
        {
            end_y = str_y + d_y;
        }
        end_y = rand() % (2) + (str_y + 1); //2 possibili numeri a partire da quello str_y + 1
        end_y = (str_y + 1);
        if (p.check_promotion(end_y) && check_boundary(end_y, end_x) && !is_end_same_color(Board, str_y, str_x, end_y, end_x))
        {
            int random = rand() % 4; //4 possibili numeri a partire da 0
            switch (random)
            {
            case '0': //donna
            {
                Board[end_y][end_x] = Donna(is_white(), end_y, end_x);
                break;
            }
            case '1': //torre
            {
                Board[end_y][end_x] = Torre(is_white(), end_y, end_x);
                break;
            }
            case '2': //cavallo
            {
                Board[end_y][end_x] = Cavallo(is_white(), end_y, end_x);
                break;
            }
            case '3': //alfiere
            {
                Board[end_y][end_x] = Alfiere(is_white(), end_y, end_x);
                break;
            }
            }
            Board[str_y][str_x] = Nullo(); //(false, str_y, str_x);
            //bisogna distruggere il pedone
            throw PromotionException();
        }
        if (i >= 20)
        {
            end_y = -1;
            end_x = -1;
            return output; //se non trova niente ritorna -1-1
        }
        i++;
    } while (!(check_boundary(end_y, end_x) && is_valid_move(Board, str_y, str_x, end_y, end_x)));
    output.first = end_y;
    output.second = end_x;
    return output;
};


/*
//RANDOM MOVE CAVALLO
int random = rand() % 8
switch(random){
    case '0':
    {
        end_y = str_y + 1;
        end_x = str_x + 2;
    }
    case '1':
    {
        end_y = str_y + 1;
        end_x = str_x - 2;
    }
    case '2':
    {
        end_y = str_y - 1;
        end_x = str_x + 2;
    }
    case '3':
    {
        end_y = str_y - 1;
        end_x = str_x - 2;
    }
    case '4':
    {
        end_y = str_y + 2;
        end_x = str_x + 1;
    }
    case '5':
    {
        end_y = str_y + 2;
        end_x = str_x - 1;
    }
    case '6':
    {
        end_y = str_y - 2;
        end_x = str_x + 1;
    }
    case '7':
    {
        end_y = str_y - 2;
        end_x = str_x - 1;
    }

}

//IS_VALID_MOVE PEDONE FUNZIONANTE PARZIALMENTE

bool Pedone::is_valid_move(Piece (&Board)[8][8], int str_y, int str_x, int end_y, int end_x) //promozione probabilmente sbagliata
{
    //cout << is_white() << " " << Board[end_y][end_x].is_white() << endl;
    int delta_x = std::abs(str_x - end_x);
    int delta_y = std::abs(str_y - end_y);
    if (is_end_same_color(Board, str_y, str_x, end_y, end_x)) //destinazione diverso colore;
        return false;
    //cout << "DP";
    // if ((Board[str_y][end_x].get_ex_position_y() == 6 || Board[str_y][end_x].get_ex_position_y() == 1) && toupper(Board[str_y][end_x].print()) == 'P') //en passant
    // {
    //     Board[str_y][end_x] = Nullo(false, str_y, str_x); //en passant in teoria giusto
    //     return true;
    // }
    if (delta_y > 2) //non si può muovere piu' di 2 caselle
        return false;
    if (delta_y == delta_x && delta_y == 1 && Board[end_y][end_x].print() != ' ')
        return true;
    if (delta_x > 0) //non si può muovere in diagonale
        return false;
    if (delta_y == 2 && !moved)
    {
        moved = true;
        return true;
    }

    moved = true;
    if (check_promotion(end_y))
    {
        cout << "Inserisci il carattere del pezzo che vuoi";
        string input;
        char in;
        while (input.length() != 1 || (in != 'D' && in != 'T' && in != 'A' && in != 'C')) //funziona
        {
            cout << "Inserisci il carattere del pezzo che vuoi";
            cin >> input;
            in = input[0];
            in = toupper(in);
        }
        switch (in)
        {
        case 'D':
        {
            Board[end_y][end_x] = Donna(is_white(), end_y, end_x);
            break;
        }
        case 'T':
        {
            Board[end_y][end_x] = Torre(is_white(), end_y, end_x);
            break;
        }
        case 'C':
        {
            Board[end_y][end_x] = Torre(is_white(), end_y, end_x);
            break;
        }
        case 'A':
        {
            Board[end_y][end_x] = Torre(is_white(), end_y, end_x);
            break;
        }
        }
        Board[str_y][str_x] = Nullo(false, str_y, str_x);
        //bisogna distruggere il pedone
        throw PromotionException();
    }
    return true;
};

*//*
    AUTORE: Martino Scagnet 2000134

    file: Rules.cpp
*/

/*
#include "Chessboard.h"
#include "Piece.h"

#include <utility>
#include <memory>
#include <vector>
#include <algorithm>

//HELPER FUNCTIONS
bool is_valid_traj(int p_x, int p_y, int k_x, int k_y);
std::vector<std::pair<std::vector<char>, int>> past_positions(std::vector<char>);
bool are_equals(std::vector<char> a, std::vector<char> b);
//Eccezioni
class three_time_repeated{};
//if(in_black) -> controllo scacco del re nero tra i pezzi bianchi -> pezzo.is_white() 

///*
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
    bool king_moved = (toupper(moved.print())=='R');
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
            std::pair<int, int> second_t_pos = direction_threat(k_y, k_x, in_black ,((st_y-k_y)/std::abs(st_y-k_y)), ((st_x-k_x)/std::abs(st_x-k_x)));
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
            if(is_checkmate_s(k_y, k_x, threat_pos))
                return 2;
            return 1;
        }
        return 0;
    }
    if(king_moved) //se e' stato mosso un re
    {
        for(int dir_x = -1; dir_x <= 1; dir_x++)
        {
            for(int dir_y = -1; dir_y <= 1; dir_y++)
            {
                if((dir_x!=0)||(dir_y!=0))
                {
                    threat_pos = direction_threat(k_y, k_x, in_black, dir_y, dir_x);
                    if(threat_pos.first >= 0 && threat_pos.second >= 0)
                        return 1;
                }
            }
        }
        return 0;
    }
    if(!mate && !king_moved) //verifica che la mossa sia valida
    {
        //controllo se il pezzo scoperto da moved minaccia
        if(is_valid_traj(st_y, st_x, k_y, k_x))
        {
            int d_y = st_y - k_y;
            int d_x = st_x - k_x;
            if(d_y!=0)
                d_y = d_y / (std::abs(d_y));
            if(d_x!=0)
                d_x = d_x / (std::abs(d_x));
            std::pair<int, int> threat_pos = direction_threat(k_y, k_x, in_black ,d_y, d_x);
            if(threat_pos.first > 0)
                return 1;
        }
        return 0;
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
bool Chessboard::is_checkmate_s(int k_y, int k_x, std::pair<int,int> t_pos)
{
    //controllo se il re si puo' muovere
    if(!is_checkmate_d(k_y, k_x))
        return false;
    //controllo se puo' essere difeso
    int dir_x = (t_pos.second - k_x)/std::abs(t_pos.second - k_x);
    int dir_y = (t_pos.first - k_y)/std::abs(t_pos.first - k_y);
    //scansione di tutti i pezzi alleati
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if( ((board[y][x].is_white()) != (board[k_y][k_x].is_white())) )
            {
                for(int t_x = k_x + dir_x; (t_x + dir_x)!=(t_pos.second) ; t_x = t_x + dir_x)
                {
                    for(int t_y = k_y + dir_y; (t_y + dir_y)!=(t_pos.first); t_y = t_y + dir_y)
                    {
                        if(board[y][x].is_valid_move(board, y, x, t_y, t_x))//se si puo' mettere in mezzo
                            return false;
                    }
                }
            }

        }
    }
    return true;
}

bool Chessboard::is_checkmate(bool in_black, int st_y, int st_x, int end_y, int end_x)
{
    int flag = is_check(in_black, st_y, st_x, end_y, end_x);
    switch(flag)
    {
        case 0: case 1:
            return false;
        case 2:
            return true;
    }
    return false;
}

//Ritorna la posizione (y,x) della minaccia nella direzione indicata, (-1,-1) altrimenti
std::pair<int, int> Chessboard::direction_threat(int king_y, int king_x, bool black_king, int dir_y, int dir_x)
{
    int i_x = king_x + dir_x;
    int i_y = king_y + dir_y;
    while(i_x >= 0 && i_x < 8 && i_y >= 0 && i_y < 8)
    {
        if((board[i_y][i_x].is_white())== black_king)
        {
            if(board[i_y][i_x].is_valid_move(board, i_y, i_x, king_y, king_x))
             return std::pair<int,int>(i_y, i_x);
        }
        i_x = i_x + dir_x;
        i_y = i_y + dir_y;
    }
    return std::pair<int,int>(-1,-1);
}

bool Chessboard::is_draw(int end_y, int end_x )
{
    std::vector<char> p_l;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(board[y][x].print() != ' ')
                p_l.push_back(board[y][x].print());
        }
    }
    //_____PER MATERIALE INSUFFICIENTE______
    //Si suppone che ci debbano essere per forza due re
    //a) Re contro Re
    if(p_l.size() < 3)
        return true;
    if(p_l.size() == 3)
    {
        //b)due re e (un alfiere o un cavallo)
        for(char c : p_l)
            if(toupper(c) == 'A' || toupper(c) == 'C')
                return true;
    }
    if(p_l.size() == 4)
    {
        //c) due re e alfieri avversari sulle stesse caselle
        if((std::find(p_l.begin(),p_l.end(), 'a') != p_l.end())&&(std::find(p_l.begin(),p_l.end(), 'A')!= p_l.end()))
        {
            bool first = false;
            bool odd;
            for(int x = 0; x < 8; x++)
            {
                for(int y = 0; y < 8; y++)
                {
                    if(toupper(board[y][x].print()) == 'A')
                    {
                        if(!first)
                        {
                            odd = (x+y)%2;
                            first = true;
                        }
                        if(first && (((x+y)%2)==odd))
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    static int piece_number = -1;
    static int move_counter = 0;
    if(piece_number == -1)
        piece_number = p_l.size();
    //________PER RIPETIZIONE DI POSIZIONE________
    if(piece_number != p_l.size())
    {
        past_positions(to_char_vector(), true);//Azzero le posizioni passate 
        move_counter = 0;//Azzero il contatore di mosse senza catture o mosse di pedone
        piece_number = p_l.size();
    }
    else
    {
        try
        {
            past_positions(to_char_vector(), false);
        }
        catch(const three_time_repeated& e)
        {
            return true;
        }
        piece_number = p_l.size();
    }
    //________REGOLA DELLE 50 MOSSE_________
    if(toupper(board[end_y][end_x].print()) == 'P')
    {
        move_counter = 0;
    }
    move_counter++;
    if(move_counter >= 50)
        return true;
    //________PER STALLO________
    bool in_white = !(board[end_y][end_x].is_white());//Se ha mosso bianco controllo stallo nero
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8 && (board[y][x].is_white() == in_white); x++)
        {
            for(int p_y = 0; p_y < 8; p_y++)
            {
                for(int p_x = 0; p_x < 8; p_x++)
                {
                    if(board[y][x].is_valid_move(board, y,x, p_y, p_x))
                        return false;
                }
            }
        }
    }
    return true;
}

std::vector<char> Chessboard::to_char_vector()//Ritorno la matrice per righe
{
    std::vector<char> v;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            v.push_back(board[i][j].print());
        }
    }
    return v;
}

//


// DEFINIZIONE HELPER FUNCTIONS
//
//Ritorna una direzione come schema sotto, -1 se non fa parte della croce di possibile attacco

(7)(0)(1)
(6)(K)(2)
(5)(4)(3)

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
//empty per svuotare la "memoria"
void past_positions(std::vector<char> mat, bool empty)
{
    static std::vector<std::pair<std::vector<char>, int>> past_pos;
    if(empty)
    {
        past_pos = {std::pair<std::vector<char>, int> (mat, 0)};
        return;
    }
    for(int i = 0; i < past_pos.size(); i++)
    {
        std::vector<char> &m = past_pos[i].first;
        if(are_equals(mat, m))
        {
            if(past_pos[i].second == 2)
                throw three_time_repeated{};
            past_pos[i].second ++;
            return;
        }
    }
    past_pos.push_back(std::pair<std::vector<char>, int>(mat, 0));
    return;
}
bool are_equals(std::vector<char> a, std::vector<char> b)
{
    if(a.size() != b.size())
        return false;
    for(int i = 0; i < a.size(); i++)
    {
        if(a[i] != b[i])
            return false;
    }
    return true;
}

*/