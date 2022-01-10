// Nicola Busato 2009663

#include <iostream>
#include <cctype>
#include <fstream>
#include <string>

#include <chrono>
#include <thread>

#include "Chessboard.h"

// ON_LINUX mi dice se il programma viene eseguito su windows o linux, per attivare o meno la stampa colorata utilizzata a soli fili estetici
#ifdef __unix__
#define ON_LINUX 1
#else
#define ON_LINUX 0
#endif

using namespace std;

class ArgumentsException{}; // Errore se gli argomenti passati su riga di comando sono sbagliati
class FileNotFoundException{}; // Errore se il file non esiste
class ReplayException{}; // Errore se il file di log contiene mosse non valide

// stampa colorata (Solo su linux)  https://www.tutorialspoint.com/how-to-output-colored-text-to-a-linux-terminal
string print_red(string s, bool console) { return ((ON_LINUX && console) ? "\033[;31m" + s + "\033[0m" : s) + "\n"; }
string print_green(string s, bool console) { return ((ON_LINUX && console) ? "\033[;32m" + s + "\033[0m" : s) + "\n"; }
ostream &operator<<(ostream &os, Chessboard &cb);

int n_moves; // variabile globale tra i file per il numero di mosse

int main(int argc, char *argv[]) {
    if (system("CLS"))
        system("clear"); // cancello la console
    string arg;
    char replay_type;

    arg = argv[1];                                                                                                        // recupero il secondo parametro, il primo e' il nome del eseguibile
    if (arg.size() != 1 || !(((replay_type = tolower(arg[0])) == 'v' && argc == 3) || (replay_type == 'f' && argc == 4))) // controllo che siano esatti numero e tipo di argomento
    {
        cout << "Argomenti non validi, aggiungere: \"v [nome_file_log]\" o \"f [nome_file_log] [nome_file_output_replay]\";\n";
        throw ArgumentsException();
    }

    string line;
    ifstream in_file(argv[2]); // "apro" il file passato come parametro
    ofstream out_file;
    ostream *os = &cout;

    bool check{false}, white_turne{true};
    if (!in_file.is_open()) // controllo se il file esiste
        throw FileNotFoundException();

    if (replay_type == 'f') {
        out_file.open(argv[3]);  // "apro" il file passato come parametro
        if (!out_file.is_open()) // controllo se il file esiste
            throw FileNotFoundException();
        os = &out_file;
    }

    Chessboard scacchiera;
    *os << scacchiera;
    int num = 0;
    bool console{replay_type == 'v'}; // true se le stampe vanno su console
    while (!check && getline(in_file, line)) {
        // if (num == 4)   // da eliminare
        //     cout << "";
        if (scacchiera.move(line, white_turne, true) != 0)
        {
            cout << print_red("Il replay contiene mosse non valide, usare un replay valido\n", true);
            cout << line << endl; // da eliminare
            throw ReplayException();
        }
        *os << "--" << num << "   Mossa: " << line << "\n"
            << scacchiera << endl;
        if (console)
            this_thread::sleep_for(chrono::milliseconds(10)); // pausa tra una stampa e l'altra

        if (check = (scacchiera.is_check(!white_turne) == 2)) // scacco matto, la partita finisce
        {
            string s = (white_turne) ? "Il Bianco ha fatto scacco matto al Nero" : "Il Nero ha fatto scacco matto al Bianco";
            *os << print_green(s, console);
        }
        white_turne = !white_turne;
        num++;
    }
    if (!check) {
        string s = "La partita e' finita in patta";
        *os << print_green(s, console);
    }

    cout << print_green("\nIl replay e' stato concluso con successo\n", true);
    in_file.close();
    if (replay_type == 'f')
        out_file.close();
    return 0;
}