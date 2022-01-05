// Nicola Busato 2009663

#include <iostream>
#include <cctype>
#include <fstream>
#include <string>

#include <chrono>
#include <thread>

#include "Chessboard.h"

#ifdef __unix__
#define ON_LINUX 1
#else
#define ON_LINUX 0
#endif

using namespace std;
int n_moves;

class ArgumentsException{};

class FileNotFoundException{};

class ReplayException {};

constexpr int moves_max = 100;

string result_type(int t, string move_line);

// stampa colorata (Solo su linux)  https://www.tutorialspoint.com/how-to-output-colored-text-to-a-linux-terminal
void print_red(string s) { cout << ((ON_LINUX) ? "\033[;31m" + s + "\033[0m" : s) << endl; }
void print_green(string s) { cout << ((ON_LINUX) ? "\033[;32m" + s + "\033[0m" : s) << endl; }
ostream &operator<<(ostream &os, Chessboard &cb);

int main(int argc, char* argv[])
{
    // if (system("CLS"))
    //     system("clear");
    string arg;
    char replay_type;
    try
    {
        arg = argv[1];
        replay_type = tolower(arg[0]);
        if (arg.size() != 1 || !((replay_type == 'v' && argc == 3) || (replay_type == 'f' && argc == 4)))
            throw ArgumentsException();
    }
    catch (...)
    {
        cout << "Argomenti non validi, aggiungere: \"v [nome_file_log]\" o \"f [nome_file_log] [nome_file_output_replay]\";\n";
        throw ArgumentsException();
    }

    string line;
    ifstream in_file(argv[2]);
    ofstream out_file;

    bool check{ false },white_turne{ true };
    if (in_file.is_open())
    {
        if (replay_type == 'f')
        {
            out_file.open(argv[3]);
            if (!out_file.is_open())
                throw FileNotFoundException();
        }
        Chessboard scacchiera{};
        if (replay_type == 'v')
            cout << scacchiera;
        else
            out_file << scacchiera;
        int num = 0;
        while (!check && getline(in_file, line))
        {
            if (num == 94)
                cout <<"";
            if (scacchiera.move(line, white_turne, true) != 0)
            {
                print_red("Il replay contiene mosse non valide, usare un replay valido\n");
                cout << line << endl;
                throw ReplayException();
            }
            if (replay_type == 'v') {
                cout << num << "   Mossa: " << line << scacchiera << endl;
                this_thread::sleep_for(chrono::milliseconds(10));
            }
            else
                out_file << "Mossa: " << line << scacchiera << endl;
            if (check = (scacchiera.is_check(!white_turne) == 2)) // scacco matto, la partita finisce
            {
                string s = (white_turne) ? "Il Bianco ha fatto scacco matto al Nero" : "Il Nero ha fatto scacco matto al Bianco";
                if (replay_type == 'v')     //(replay_type == 'v') ? print_green(s) : out_file << s;
                    print_green(s);
                else
                    out_file << s;
            }
            white_turne = !white_turne;
            num++;
        }
        if (!check)
        {
            string s = "La partita e' finita in patta";
            if (replay_type == 'v')
                print_green(s);
            else
                out_file << s;
        }

        print_green("\nIl replay e' stato concluso con successo\n");
        in_file.close();
        if (replay_type == 'v')
            out_file.close();
    }
    else
        throw FileNotFoundException();
    
    return 0;
}
