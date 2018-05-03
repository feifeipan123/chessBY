#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "Board.h"

class SingleGame:public Board
{
public:
    virtual void click(int id, int row, int col);
};

#endif // SINGLEGAME_H
