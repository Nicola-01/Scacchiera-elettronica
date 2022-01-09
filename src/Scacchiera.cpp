// Nicola Busato 2009663

#include <iostream>
#include <cctype>
#include <fstream>

#include <time.h> /* time */

#include "Chessboard.h"


#ifdef __unix__
#define ON_LINUX 1
#else
#define ON_LINUX 0
#endif


using namespace std;
int n_moves;

class ArgumentsException
{
};

constexpr int moves_max = 100;

string result_type(int t, string move_line);
void player_turne(Chessboard& scacchiera, bool white_turne, ofstream& log_file, bool& patta);
void computer_turne(Chessboard &scacchiera, bool white_turne, ofstream &log_file);

// stampa colorata (Solo su linux)  https://www.tutorialspoint.com/how-to-output-colored-text-to-a-linux-terminal
void print_red(string s) { cout << ((ON_LINUX) ? "\033[;31m" + s + "\033[0m" : s) << endl; }
void print_green(string s) { cout << ((ON_LINUX) ? "\033[;32m" + s + "\033[0m" : s) << endl; }
ostream& operator<<(ostream& os, Chessboard& cb);

int main(int argc, char *argv[])
{
    string game_type = argv[1];
    for (int i = 0; i < game_type.size(); i++)
        game_type[i] = tolower(game_type[i]);

    if (argc != 2 || (game_type != "pc" && game_type != "cc" && game_type != "pp"))
    {
        cout << "Argomenti non validi, aggiungere: pp (Player vs Player), pc (Player vs Computer) o cc (Computer vs Computer);\n";
        throw ArgumentsException();
    }

    ofstream log_file ("../log.txt"); //svuoto il file se è già stato scritto

    if (system("CLS"))
        system("clear");
    Chessboard scacchiera{};
    cout << scacchiera;
    bool white_turne{ true }, patta{ false };

    srand(time(NULL));
    int player = (game_type == "pc") ? rand() % 2 + 1 : 0; // 0, se non è un giocatore ,1 se è bianco, 2 se è nero
    if (player != 0)
        print_green((player == 1) ? "Giochi con il bianco" : "Giochi con il nero");

    while (game_type != "cc" || game_type == "cc" && n_moves < moves_max)
    {
        //outfile.open("../log.txt", ios_base::app); //riapro il file (faccio una sorta di autosave)
        //if (system("CLS")) system("clear");
        
        if (game_type == "pp")
        { // forse provvisorio
            print_green(((white_turne) ? "-= Tocca al bianco =-" : "-= Tocca al nero =-"));
            player_turne(scacchiera, white_turne, log_file, patta);
        }
        else if (player == 1 && white_turne || player == 2 && !white_turne)
        {
            print_green("--- Tocca a te");
            player_turne(scacchiera, white_turne, log_file, patta);
        }
        else
        {
            print_red("--- Tocca al computer");
            computer_turne(scacchiera, white_turne, log_file);
        }
        cout << scacchiera;
        /*cout << "..";
        cin.get();*/
        white_turne = !white_turne;

        if (int check = scacchiera.is_check(!white_turne) > 0)
        {
            if (check == 2)
            { // e' scacco matto
                (white_turne) ? print_green("Il Bianco ha fatto scacco matto al Nero") : print_green("Il Nero ha fatto scacco matto al Bianco");
                break;
            }
            // else e' scacco
            (white_turne) ? print_green("Il Bianco ha fatto scacco al Nero") : print_green("Il Nero ha fatto scacco al Bianco");
            // log_file.close();
        }
        else if (patta || scacchiera.is_draw())
        {
            print_green("Partita finita in patta");
            break; // non mi piace molto, valuto
            // log_file.close();
            // return 0;
        }
        n_moves++;
    }
    if (game_type == "cc" && n_moves == moves_max)
        print_red("Partita finita in patta, raggiunto il numero massimo di mosse");
    log_file.close();
    return 0;
}

void player_turne(Chessboard &scacchiera, bool white_turne, ofstream &log_file, bool &patta)
{
    int output_type;
    string line;
    print_green("Inserire la mossa: ");
    getline(cin, line);
    while ((output_type = scacchiera.move(line, white_turne)) != 0) // il metodo move fa rende line maiuscolo
    {
        // da eliminare per la consegna 
        cout << scacchiera;
        if (line == "CLEAR")
        {
            if (system("CLS"))
                system("clear");
            cout << scacchiera;
            print_green("Inserire la mossa: ");
        }
        else if (line == "XX XX")
        {
            cout << scacchiera;
            print_green("Inserire la mossa: ");
        }
        else if (line == "PATTA")
        {
            patta = true;
            return;
        }
        else
            print_red(result_type(output_type, line));

        getline(cin, line);
    }
    log_file << line + "\n";
}

void computer_turne(Chessboard &scacchiera, bool white_turne, ofstream &log_file)
{
    string line;
    int y, x, out;
    do
    {
        do
        {
            y = rand() % 8;
            x = rand() % 8;
            //cout << "--y x " << y << " " << x << endl;
            if (y == 0 && x == 4 && !white_turne || y == 7 && x == 4 && white_turne)
                ;

        } while (!scacchiera.is_right_piece(y, x, white_turne));
        cout << "pezzo selezionato (y,x): " << y << ", " << x << endl;
        line = scacchiera.random_move(y, x, white_turne);
        cout << "-- Prova dello spostamento: " << line << endl;
        //cin.get();
    } while (line == "NV NV" || (out = scacchiera.move(line, white_turne)) != 0); //Not Valid
    // cout << out;
    // if (out == 4)
    //     cout << "waa";
    cout << n_moves + 1 << " Mossa computer: " << line << endl;
    log_file << line + "\n";
}

string result_type(int t, string move_line)
{
    switch (t)
    {
    case 1:
        return "Formato stringa non valido, inserirne una valida; \"A0 H8\", \"XX XX\", \"clear\" o \"patta\"; :";
    case 2:
        return "Non puoi spostare l'aria, inserirne una valida:";
    case 3:
        return "Non puoi muovere il pezzi del avversario, fai una altra mossa:";
    case 4:
        return "La mossa " + move_line + " non e' valida, inserire una mossa valida:";
    case 5:
        return "Se fai quella finisci sotto scacco, forse e' meglio cambiarla:";
    case 6:
        return "Non puoi arroccare, il re e' sotto scacco o passa in una casella in cui sarebbe sotto scacco";
    default:
        return "";
    }
}