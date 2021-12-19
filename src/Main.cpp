
#include <iostream>
#include "Chessboard.h"
#include <cctype>
#include <fstream>

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
    
    bool player = (argv[0] == "pc");

    Chess c{};
    string line;
    int n = 0;
    bool white_turne = true;
    int output_type;

    while (moves_max < n)
    {
        // if (system("CLS")) system("clear");
        c.move("XX XX", white_turne);

        cout << "Inserire la mossa:\n";
        getline(cin, line);
        while ((output_type = c.move(line, white_turne)) != 0)
        {
            // if (system("CLS")) system("clear");
            // c.move("XX XX");

            send_error(result_type(output_type));
        }
        myfile << line+"\n";
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
        cout << "\032[;31m" << s << "\033[0m" << endl; // https://www.tutorialspoint.com/how-to-output-colored-text-to-a-linux-terminal
    }
}