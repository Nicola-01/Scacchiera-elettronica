#include <iostream>
#include "Chess.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Chess c{};
    string line;
    while (true)
    {
        c.print();
        getline(cin, line);
        try
        {
            c.move(line);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

    return 0;
}
