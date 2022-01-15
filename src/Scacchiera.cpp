// Nicola Busato 2009663

#include <iostream>
#include <cctype>
#include <fstream>

#include <time.h> /* time */

#include "Chessboard.h"

// ON_LINUX mi dice se il programma viene eseguito su windows o linux, per attivare o meno la stampa colorata utilizzata a soli fili estetici
#ifdef __unix__
#define ON_LINUX 1
#else
#define ON_LINUX 0
#endif

using namespace std;
int n_moves; // variabile globale tra i file per il numero di mosse

class ArgumentsException{}; // Errore se gli argomenti passati su riga di comando sono sbagliati

constexpr int moves_max = 100;
// Le patte si dividono in 4 tipologie
const string draw_type[] = {"",                                                            // 0
                            "Patta, numero di pezzi insufficente",                         // 1
                            "Patta, ripetizioni di mosse",                                 // 2
                            "patta, 50 mosse senza cattura o senza spostamenti di pedoni", // 3
                            "Stallo, non ci sono più mosse valide"};                       // 4

// dichiarazione helper function
string result_type(int t, string move_line);
void player_turne(Chessboard &scacchiera, bool white_turne, ofstream &log_file, bool &patta);
void computer_turne(Chessboard &scacchiera, bool white_turne, ofstream &log_file);

ostream &operator<<(ostream &os, Chessboard &cb);

// dichiarazione e definizione helper function
void print_red(string s) { cout << ((ON_LINUX) ? "\033[;31m" + s + "\033[0m" : s) << endl; }
void print_green(string s) { cout << ((ON_LINUX) ? "\033[;32m" + s + "\033[0m" : s) << endl; }
// stampa colorata (Solo su linux)  https://www.tutorialspoint.com/how-to-output-colored-text-to-a-linux-terminal

int main(int argc, char *argv[])
{
    string game_type = argv[1];                // recupero il secondo parametro, il primo e' il nome del eseguibile
    for (int i = 0; i < game_type.size(); i++) // rendo minuscolo l'argomento
        game_type[i] = tolower(game_type[i]);

    if (argc != 2 || (game_type != "pc" && game_type != "cc" && game_type != "pp")) // controllo che siano esatti numero e tipo di argomento
    {
        cout << "Argomenti non validi, aggiungere: pp (Player vs Player), pc (Player vs Computer) o cc (Computer vs Computer);\n";
        throw ArgumentsException();
    }

    ofstream log_file("../log.txt"); // svuoto il file per i log se e' già stato scritto

    if (system("CLS")) system("clear"); // cancello la console
    Chessboard scacchiera;
    cout << scacchiera; // stampo la scacchiera
    bool white_turne{ true }, patta{ false };

    srand(time(NULL));                                     // metto un seed al ranodm, se non lo facessi darebbe semopre lo stesso ordine di numeri
    int player = (game_type == "pc") ? rand() % 2 + 1 : 0; // 0, se non e' un giocatore, 1 se e' bianco, 2 se e' nero
    if (player != 0)
        print_green((player == 1) ? "Giochi con il bianco" : "Giochi con il nero");

    while (game_type != "cc" || game_type == "cc" && n_moves < moves_max) // se la partita e' player vs computer o player vs player va avanti finche' il giocatore non scrive "patta", altrimenti si ferma a moves_max
    {
        // if (system("CLS")) system("clear"); // suoto la console

        if (game_type == "pp")
        {
            cout << "mossa n: " << n_moves << "\n";
            print_green(((white_turne) ? "-= Tocca al bianco =-" : "-= Tocca al nero =-")); // se la partita e' tra due giocatori scrivo di chi e' il turono
            player_turne(scacchiera, white_turne, log_file, patta);
        }
        else if (player == 1 && white_turne || player == 2 && !white_turne) // controllo di chi e' il turno
        {
            print_green("--- Tocca a te"); // turno giocatore
            player_turne(scacchiera, white_turne, log_file, patta);
        }
        else
        {
            //print_red("--- Tocca al computer"); // turno computer
            computer_turne(scacchiera, white_turne, log_file);
        }
        //cout << scacchiera;         // ristampo la scacchiera
        white_turne = !white_turne;   // passo il turno

        int check, draw;
        if (!patta && (check = scacchiera.is_check(!white_turne)) > 0) // controllo se e' scacco e che il player non abbia chiamato la patta
        {
            if (check == 2) { // e' scacco matto
                (white_turne) ? print_green("Il Nero ha fatto scacco matto al Bianco") : print_green("Il Bianco ha fatto scacco matto al Nero");
                break;
            }
            (white_turne) ? print_green("Il Nero ha fatto scacco al Bianco") : print_green("Il Bianco ha fatto scacco al Nero");
        }
        else if (patta || (draw = scacchiera.is_draw()) > 0) { // patta e' true quando un player scrive "patta"
            (patta) ? print_green("Partita finita in patta, chiamata dal giocatore") :  print_green(draw_type[draw]);
            break;
        }
        n_moves++;
    }
    if (game_type == "cc" && n_moves == moves_max)
        print_red("Partita finita in patta, raggiunto il numero massimo di mosse");
    cout << scacchiera;
    log_file.close();
    return 0;
}

// definizione helper function

void player_turne(Chessboard &scacchiera, bool white_turne, ofstream &log_file, bool &patta) // mossa player
{
    int output_type;
    string line;
    print_green("Inserire la mossa: ");
    getline(cin, line);
    while ((output_type = scacchiera.move(line, white_turne)) != 0) // il metodo move rende line maiuscolo
    {
        if (line == "CLEAR") // pulisco e ristampo la scacchiera
        {
            if (system("CLS"))
                system("clear");
            cout << scacchiera;
            print_green("Inserire la mossa: ");
        }
        else if (line == "XX XX") // ristampo la scacchiera
        {
            cout << scacchiera;
            print_green("Inserire la mossa: ");
        }
        else if (line == "PATTA") // esco dal metodo e concludo la partita
        {
            patta = true;
            return;
        }
        else
            print_red(result_type(output_type, line)); // restituisco il tipo di errore
        getline(cin, line);
    }
    log_file << line + "\n"; // salvo la mossa sul file di log
}

void computer_turne(Chessboard &scacchiera, bool white_turne, ofstream &log_file) // mossa computer
{
    string line;
    int y, x, out;
    int nv_cout = 0;
    do {
        nv_cout++;
        do {
            y = rand() % 8;
            x = rand() % 8;
            /*y = (white_turne) ? 6 : 1;*/
            // cout << "--y x " << y << " " << x << endl;
            // if (y == 0 && x == 4 && !white_turne || y == 7 && x == 4 && white_turne)
            //     ;
        } while (!scacchiera.is_right_piece(y, x, white_turne)); // controllo se il pezzo e' giusto se no genero altre coordinate
        //cout << "pezzo selezionato (y,x): " << y << ", " << x << endl;
        line = scacchiera.random_move(y, x, white_turne); // genera la mossa nel formato "Ln Ln"
        //cout << "-- Prova dello spostamento: " << line << endl;
    } while (line == "NV NV" || (out = scacchiera.move(line, white_turne)) != 0); // il pezzo non ha mosse valide allora ne seleziono un altro, o la mossa genera uno scacco
    // cout << out;
    // if (out == 4)
    //     cout << "waa";
    //cout << n_moves + 1 << " ";
    //cout << " Mossa computer: " << line << endl; // stampo la mossa del pc
    cout << line << "\n";
    log_file << line + "\n";    // salvo la mossa sul file di log
}

string result_type(int err, string move_line) // in base al tipo di errore stampo una stringa, potevo usare anche un array di stringhe
{
    switch (err) {
    case 1:
        return "Formato stringa non valido, inserirne una valida; \"A0 H8\", \"XX XX\", \"clear\" o \"patta\"; :";
    case 2:
        return "Non puoi spostare l'aria, inserirne una valida:";
    case 3:
        return "Non puoi muovere il pezzi del avversario, fai una altra mossa:";
    case 4:
        return "La mossa " + move_line + " non e' valida, inserire una mossa valida:";
    case 5:
        return "Se fai quella finisci/resti sotto scacco, forse e' meglio cambiarla:";
    case 6:
        return "Non puoi arroccare, il re e' sotto scacco o passa in una casella in cui sarebbe sotto scacco";
    default:
        return "";
    }
}
