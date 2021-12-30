// Nicola Busato 2009663

#include <iostream>
#include <cctype>
#include <fstream>

#include <time.h> /* time */

#include "Chessboard.h"

using namespace std;
int n_moves;

class ArgumentsException
{
};

constexpr int moves_max = 100;

string result_type(int t);
void player_turne(Chessboard &c, bool white_turne, ofstream &log_file);
void computer_turne(Chessboard &c, bool white_turne, ofstream &log_file);

void send_error(string s);
void send_green(string s);

int main(int argc, char *argv[])
{
    string inp = argv[1];
    if (argc != 2 || (inp != "pc" && inp != "cc"))
    {
        cout << "Argomenti non validi";
        throw ArgumentsException();
    }
    std::ofstream outfile;

    ofstream log_file;
    log_file.open("../log.txt"); //svuoto il file se è già stato scritto
    log_file.close();

    int player = 0;
    srand(time(NULL));
    if (inp == "pc")
        player = rand() % 2 + 1; // 0, se non è un giocatore ,1 se è bianco, 2 se è nero

    Chessboard c{};
    n_moves = 0;
    bool white_turne = true;
    while (n_moves < moves_max)
    {
        outfile.open("../log.txt", ios_base::app); //riapro il file (faccio una sorta di autosave)
        //if (system("CLS")) system("clear");
        c.move("XX XX", white_turne);
        cout << "Colore giocatore (1 bianco, 2 nero): " << player << "\nturno bianco (1=true): " << white_turne << endl;

        
        if(inp=="pp")
            player_turne(c, white_turne, log_file);    
        else if (player == 1 && white_turne || player == 2 && !white_turne)
        {
            send_green("--- Tocca a te");
            player_turne(c, white_turne, log_file);
        }
        else
        {
            send_error("--- Tocca al computer");
            computer_turne(c, white_turne, log_file);
        }

        white_turne = !white_turne;

        if (int check = c.is_check(!white_turne) > 0)
        {
            if (check == 2) // è scacco matto
            {
                (white_turne) ? send_green("Ha vinto il bianco") : send_green("Ha vinto il Nero");
                return 0;
            }
            // else è scacco

            (white_turne) ? send_green("Il Bianco ha fatto scacco al Nero") : send_green("Il Nero ha fatto scacco al Bianco");
            // log_file.close();
        }
        if (false) //c.is_draw())
        {
            send_green("Partita finita in patta");
            return 0;
        }

        n_moves++;
        log_file.close();
    }
    return 0;
}

string result_type(int t) // string line --- passa la mossa
{
    switch (t)
    {
    case 1:
        return "Formato stringa non valido, inserirne una valida:";
    case 2:
        return "Non puoi spostare l'aria, inserirne una valida:";
    case 3:
        return "Non puoi muovere il pezzi del avversario, fai una altra mossa:";
    case 4:
        return "Mossa non e' valida, inserirne una valida:";
    case 5:
        return "Scacco, mossa non valida, forse è meglio cambiarla:";
        // case 5:  return "Scacco matto:\n";

    default:
        return "";
    }
}

void player_turne(Chessboard &c, bool white_turne, ofstream &log_file)
{
    int output_type;
    string line;
    send_green("Inserire la mossa:");
    getline(cin, line);
    while ((output_type = c.move(line, white_turne)) != 0)
    {
        c.move("XX XX", white_turne);

        send_error(result_type(output_type));
        getline(cin, line);
    }
    log_file << line + "\n";
}

void computer_turne(Chessboard &c, bool white_turne, ofstream &log_file)
{
    string line;
    int y, x;
    do
    {
        do
        {
            y = rand() % 8;
            x = rand() % 8;
        } while (!c.is_right_piece(y, x, white_turne));
        line = c.random_move(y, x);
        cin.get();
        cout << "-- Prova dello spostamento: " << line << endl;
    } while (line == "NV NV"); //Not Valid
    c.move(line, white_turne);
    cout << line;
    log_file << line + "\n";
}

void send_error(string s)
{
    cout << s << endl;
    cout << "\033[;31m" << s << "\033[0m" << endl;
}

void send_green(string s)
{
    cout << s << endl;
    cout << "\033[;32m" << s << "\033[0m" << endl;
}
/* 
    // area di funzioni in test
#ifdef __unix__ /* __unix__ is usually defined by compilers targeting Unix systems */
// #define OS_Windows 0

// #elif defined(_WIN32) || defined(WIN32) /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

// #define OS_Windows 1
// #include <windows.h>
// HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE); // -- probabilmente funziona solo per windows

// #endif
/*

void send_error(string s)
{
    if (OS_Windows)
    {
        SetConsoleTextAttribute(color, 4);
        cout << s << endl;
        SetConsoleTextAttribute(color, 7);
    }
    else
    {
        cout << "\033[;31m" << s << "\033[0m" << endl; // https://www.tutorialspoint.com/how-to-output-colored-text-to-a-linux-terminal
    }
}

void send_green(string s)
{
    if (OS_Windows)
    {
        SetConsoleTextAttribute(color, 2);
        cout << s << endl;
        SetConsoleTextAttribute(color, 7);
    }
    else
    {
        cout << "\033[;32m" << s << "\033[0m" << endl; // https://www.tutorialspoint.com/how-to-output-colored-text-to-a-linux-terminal
    }
}
*/