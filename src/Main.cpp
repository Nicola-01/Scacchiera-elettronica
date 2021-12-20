
#include <iostream>
#include "Chessboard.h"
#include <cctype>
#include <fstream>

#include <time.h> /* time */

using namespace std;

class ArgumentsException
{
};

constexpr int moves_max = 100;

int main(int argc, char *argv[])
{
    if (argc != 2 || argv[0] != "pc" || argv[0] != "cc")
    {
        cout << "Argomenti non validi";
        throw ArgumentsException();
    }

    ofstream myfile;
    myfile.open("example.txt");

    int player = 0;
    srand(time(NULL));
    if (argv[0] == "pc")
        int player = rand() % 2 + 1; // 0, se non è un giocatore ,1 se è bianco, 2 se è nero

    Chess c{};
    //Rules rul{c};
    int n = 0;
    bool white_turne = true;

    while (n < moves_max)
    {
        // if (system("CLS")) system("clear");
        c.move("XX XX", white_turne);

        if (player == 1 && white_turne)
            player_turne(c, white_turne, myfile);
        else if (player == 2 && !white_turne)
            player_turne(c, white_turne, myfile);
        else
            computer_turne(c, white_turne, myfile);

        white_turne = !white_turne;

        if (is_check(white_turne))
        {
            if (is_checkmate(white_turne))
            {
                (white_turne) ? send_green("Ha vinto il bianco") : send_green("Ha vinto il Nero");
                myfile.close();
                return 0;
            }
            else
                (white_turne) ? send_green("Il Bianco ha fatto scacco al Nero") : send_green("Il Nero ha fatto scacco al Bianco");
        }
        n++;
    }
    myfile.close();
    return 0;
}

string result_type(int t)
{
    switch (t)
    {
    case 1:
        return "Formato stringa non valido, inserirne una valida:\n";
    case 2:
        return "Non puoi spostare l'aria, inserirne una valida:\n";
    case 3:
        return "Mossa non e' valida, inserirne una valida:\n";
    case 4:
        return "Scacco, mossa non valida, forse è meglio cambiarla:\n";
        // case 5:  return "Scacco matto:\n";

    default:
        return "";
    }
}

void player_turne(Chess &c, bool white_turne, ofstream &myfile)
{
    int output_type;
    string line;
    cout << "Inserire la mossa:\n";
    getline(cin, line);
    while ((output_type = c.move(line, white_turne)) != 0)
    {
        // if (system("CLS")) system("clear");
        // c.move("XX XX");

        send_error(result_type(output_type));
        getline(cin, line);
        
    }
    myfile << line + "\n";
}

void computer_turne(Chess &c, bool white_turne, ofstream &myfile)
{
    string line;
    int y, x, end_y, end_x;
    do
    {
        y = rand() % 8;
        x = rand() % 8;
    } while (!c.is_right_piece(y, x, white_turne));

    do
    {
        end_y = rand() % 8;
        end_x = rand() % 8;
        line = (char)('A' + x) + (y+1) + " " + (char)('A' + end_x) + (end_y+1);
    } while (c.move(line, white_turne) != 0);

    myfile << line + "\n";
}

// area di funzioni in test
#ifdef __unix__ /* __unix__ is usually defined by compilers targeting Unix systems */

#define OS_Windows 0

#elif defined(_WIN32) || defined(WIN32) /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#define OS_Windows 1
#include <windows.h>
HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE); // -- probabilmente funziona solo per windows

#endif

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