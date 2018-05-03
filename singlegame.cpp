#include "singlegame.h"

void SingleGame::click(int id, int row, int col){

    Board::click(id,row,col);
    if(!_bRedTurn){
        computerMove();
    }
}
