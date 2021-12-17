#ifndef Chess_h
#define Chess_h

#include <string>

class Chess
{
private:
    char scacchiera[8][8]; //[y][x]
    const std::string pos{"TCADRACT"};
    bool is_valid_move(std::string move);
public:
    Chess();
    void print();
    bool move(std::string move);
};

#endif