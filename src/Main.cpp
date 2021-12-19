
#include <iostream>
#include "Chessboard.h"
#include <cctype>

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

    bool player = (argv[0] == "pc");

    Chess c{};
    string line;
    int n = 0;
    while (moves_max < n)
    {
        c.print();
        getline(cin, line);
        try
        {
            c.move(line);
        }
        catch (const InvalidMoveStringException e)
        {
            cout << "" << endl;
        }
    }

    return 0;
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
        cout << "\033[;31m" << s << "\033[0m" << endl;
    }
}