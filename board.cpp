#include "board.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#define GetRowCol(__row, __col, __id) \
    int __row = _s[__id]._row;\
    int __col = _s[__id]._col

Board::Board(QWidget *parent) : QWidget(parent),_selectid(-1)
{
    for(int i=0;i<32;i++){
        _s[i].init(i);
    }
}

void Board::paintEvent(QPaintEvent *){
    QPainter painter(this);
    int d=40;
    _r = d/2;

    //画10条横线
    for(int i=1;i<=10;++i){
        painter.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    }

    //画9条竖线
    for(int i=1;i<=9;++i){
        if(i==1 || i==9)
              painter.drawLine(QPoint(i*d,d),QPoint(i*d,10*d));
        else{
             painter.drawLine(QPoint(i*d,d),QPoint(i*d,5*d));
              painter.drawLine(QPoint(i*d,6*d),QPoint(i*d,10*d));
        }
    }

    //九宫格
    painter.drawLine(QPoint(4*d,d),QPoint(6*d,3*d));
    painter.drawLine(QPoint(4*d,3*d),QPoint(6*d,d));

    painter.drawLine(QPoint(4*d,8*d),QPoint(6*d,10*d));
    painter.drawLine(QPoint(4*d,10*d),QPoint(6*d,8*d));
    //绘制32个棋子
    for(int i=0;i<32;++i){
        drawStone(painter,i);
    }
}

QPoint Board::center(int row,int col){
    QPoint ret;
    ret.rx()=2*_r*(col+1);
    ret.ry()=2*_r*(row+1);
    return ret;
}

QPoint Board::center(int id){
    return center(_s[id]._row,_s[id]._col);
}

bool Board::isDead(int id)
{
    if(id == -1)return true;
    return _s[id]._dead;
}

void Board::drawStone(QPainter& painter,int id){
    if(_s[id]._dead)
        return;
    QPoint c = center(id);
    QRect rect = QRect(c.x()-_r,c.y()-_r,_r*2,_r*2);

    if(id==_selectid){
        painter.setBrush(QBrush(Qt::gray));
    }else{
        painter.setBrush(QBrush(Qt::yellow));
    }
     painter.setPen(Qt::black);
     if(_s[id]._red)
         painter.setPen(Qt::red);
    painter.drawEllipse(c,_r,_r);

    painter.setFont(QFont("system",_r,700));

    painter.drawText(rect,_s[id].getText(),QTextOption(Qt::AlignCenter));
}

bool Board::getRowCol(QPoint pt,int &row,int &col){
    for(row=0;row<=9;row++){
        for(col=0;col<=8;col++){
            QPoint c=center(row,col);
            int dx=abs(c.x()-pt.x());
            int dy=abs(c.y()-pt.y());
            int dist = dx*dx+dy*dy;
            if(dist<_r*_r){
                return true;
            }
        }
    }
    return false;
}
//根据行列值获取棋子id
int Board::getStoneId(int row, int col)
{
    for(int i=0; i<32; ++i)
    {
        if(_s[i]._row == row && _s[i]._col == col && !isDead(i))
            return i;
    }
    return -1;
}

int Board::relation(int row1, int col1, int row, int col)
{
    return qAbs(row1-row)*10+qAbs(col1-col);
}

//将的走棋规则
bool Board::canMoveJiang(int moveid,int row,int col,int killid){
    /*
     * 1.位置在九宫格之内
     * 2.移动步长是一个格子
     */
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    //只能走一格
    if(r != 1 && r != 10){
        return false;
    }
    //列不分红黑棋子
    if(col < 3 || col > 5) return false;
    //行分红黑
    if(_s[moveid]._red){
        if(row>2)return false;
    }else{
        if(row<7)return false;
    }
    return true;
}

//士的走棋规则
bool Board::canMoveShi(int moveid,int row,int col,int killid){
    /*
     * 1.位置在九宫格之内
     * 2.移动步长是一个格子
     */
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 11) return false;

    if(col < 3 || col > 5) return false;
    if(_s[moveid]._red){
        if(row>2)return false;
    }else{
        if(row<7)return false;
    }
    return true;
}

bool Board::canMoveXiang(int moveid,int row,int col,int killid){

    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 22) return false;

    int rEye = (row+row1)/2;
    int cEye = (col+col1)/2;
    if(getStoneId(rEye, cEye) != -1)//象眼位置不能有棋子
        return false;
    if(_s[moveid]._red)
    {
        if(row > 5) return false;
    }
    else
    {
        if(row < 4) return false;
    }
    return true;
}

bool Board::canMoveMa(int moveid,int row,int col,int)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 12 && r != 21)
        return false;

    if(r == 12)
    {
        if(getStoneId(row1, (col+col1)/2) != -1)
            return false;
    }
    else
    {
        if(getStoneId((row+row1)/2, col1) != -1)
            return false;
    }
    return true;
}

bool Board::canMoveBing(int moveid, int row, int col, int)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 1 && r != 10) return false;

    if(_s[moveid]._red)
    {
        if(row < row1) return false;
        if(row1 <= 4 && row == row1) return false;
    }
    else
    {
        if(row > row1) return false;
        if(row1 >= 5 && row == row1) return false;
    }
    return true;
}

bool Board::canMove(int moveid,int row,int col,int killid){
     //moveid和killid颜色相同
    if(_s[moveid]._red==_s[killid]._red){
        //换选择
        _selectid = killid;
        update();
        return false;
    }
    switch(_s[moveid]._type){
        case Stone::JIANG:
            return canMoveJiang(moveid,row,col,killid);
            break;
        case Stone::SHI:
            return canMoveShi(moveid,row,col,killid);
            break;
        case Stone::XIANG:
            return canMoveXiang(moveid,row,col,killid);
            break;
        case Stone::CHE:
            break;
        case Stone::MA:
            return canMoveMa(moveid,row,col,killid);
            break;
        case Stone::PAO:
            break;
        case Stone::BING:
            return canMoveBing(moveid,row,col,killid);
            break;
    }
}

void Board::mouseReleaseEvent(QMouseEvent *ev){
    QPoint pt=ev->pos();
    int row,col;
    bool bRet = getRowCol(pt,row,col);
    if(bRet == false)
        return;
    int i,clickid=-1;
    for(i=0;i<32;++i){
        if(_s[i]._row==row&&_s[i]._col==col&&_s[i]._dead==false){
            break;
        }
    }
    if(i<32){
        clickid=i;
    }
    if(_selectid==-1){//可以选择棋子了
        if(clickid!=-1){//能选中棋子
            if(bRedTurn==_s[clickid]._red){//是红棋走
                _selectid = clickid;
                 update();
            }
        }
    }else{//走棋
        if(canMove(_selectid,row,col,clickid)){
            _s[_selectid]._row=row;
            _s[_selectid]._col=col;
            if(clickid!=-1){
                _s[clickid]._dead=true;
            }
            _selectid = -1;
            bRedTurn = !bRedTurn;
            update();
        }
    }
}
