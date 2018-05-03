#include "stone.h"

Stone::Stone()
{

}

Stone::~Stone(){

}
void Stone::init(int id){
    struct {
            int row, col;
            Stone::TYPE type;
        } pos[16] = {
        {0, 0, Stone::CHE},
        {0, 1, Stone::MA},
        {0, 2, Stone::XIANG},
        {0, 3, Stone::SHI},
        {0, 4, Stone::JIANG},
        {0, 5, Stone::SHI},
        {0, 6, Stone::XIANG},
        {0, 7, Stone::MA},
        {0, 8, Stone::CHE},

        {2, 1, Stone::PAO},
        {2, 7, Stone::PAO},
        {3, 0, Stone::BING},
        {3, 2, Stone::BING},
        {3, 4, Stone::BING},
        {3, 6, Stone::BING},
        {3, 8, Stone::BING},
        };
    _id = id;
    _dead = false;
    _red = id<16;

    if(_red){
        _row = pos[id].row;
        _col = pos[id].col;
        _type = pos[id].type;
    }else{
        _row = 9 - pos[id-16].row;
        _col = 8 - pos[id-16].col;
        _type = pos[id-16].type;
    }
}
QString Stone::getText(){
    switch (this->_type) {
    case CHE:
        return QString::fromLocal8Bit("车");
        break;
    case MA:
        return QString::fromLocal8Bit("马");
        break;
    case PAO:
        return QString::fromLocal8Bit("炮");
        break;
    case BING:
        return QString::fromLocal8Bit("兵");
        break;
    case JIANG:
        return QString::fromLocal8Bit("将");
        break;
    case SHI:
        return QString::fromLocal8Bit("士");
        break;
    case XIANG:
        return QString::fromLocal8Bit("相");
        break;
    }
    return QString::fromLocal8Bit("错误");
}

void Stone::rotate()
{
    this->_col = 8-this->_col;
    this->_row = 9-this->_row;
}
