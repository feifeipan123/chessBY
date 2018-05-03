#include "board.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#define GetRowCol(__row, __col, __id) \
    int __row = _s[__id]._row;\
    int __col = _s[__id]._col

Board::Board(QWidget *parent) : QWidget(parent),_selectid(-1)
{
    this->_r = 20;
    setMinimumSize(_r*18+1, _r*20+1);
    init(true);
}

bool Board::isBottomSide(int id)
{
    return _bSide == _s[id]._red;
}

int Board::getStoneCountAtLine(int row1, int col1, int row2, int col2)
{
    int ret = 0;
    if(row1 != row2 && col1 != col2)
        return -1;
    if(row1 == row2 && col1 == col2)
        return -1;

    if(row1 == row2)
    {
        int min = col1 < col2 ? col1 : col2;
        int max = col1 < col2 ? col2 : col1;
        for(int col = min+1; col<max; ++col)
        {
            if(getStoneId(row1, col) != -1) ++ret;
        }
    }
    else
    {
        int min = row1 < row2 ? row1 : row2;
        int max = row1 < row2 ? row2 : row1;
        for(int row = min+1; row<max; ++row)
        {
            if(getStoneId(row, col1) != -1) ++ret;
        }
    }

    return ret;
}
void Board::init(bool bRedSide)
{
    for(int i=0; i<32; ++i)
    {
        _s[i].init(i);
    }
    if(bRedSide)
    {
        for(int i=0; i<32; ++i)
        {
            _s[i].rotate();
        }
    }

    _selectid = -1;
    _bRedTurn = true;
    _bSide = bRedSide;
    update();
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
    if(isDead(id))return;

    QPoint c = center(id);
    QRect rect = QRect(c.x()-_r,c.y()-_r,_r*2,_r*2);

    QColor color;
    if(red(id))color=Qt::red;
    else color=Qt::black;
    painter.setPen(QPen(QBrush(color),2));

    if(id==_selectid){
        painter.setBrush(QBrush(Qt::gray));
    }else{
        painter.setBrush(QBrush(Qt::yellow));
    }

    painter.drawEllipse(c,_r,_r);

    painter.setFont(QFont("system",_r*1.2,700));

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
bool Board::canMoveJiang(int moveid,int row,int col,int){
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
    if(isBottomSide(moveid))
    {
        if(row < 7) return false;
    }
    else
    {
        if(row > 2) return false;
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
    if(isBottomSide(moveid))
    {
        if(row < 7) return false;
    }
    else
    {
        if(row > 2) return false;
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
    if(isBottomSide(moveid))
    {
        if(row < 4) return false;
    }
    else
    {
        if(row > 5) return false;
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

    if(isBottomSide(moveid))
    {
        if(row > row1) return false;
        if(row1 >= 5 && row == row1) return false;
    }
    else
    {
        if(row < row1) return false;
        if(row1 <= 4 && row == row1) return false;
    }
    return true;
}

bool Board::canMoveChe(int moveid,int row, int col,int)
{
    GetRowCol(row1, col1, moveid);
    int ret = getStoneCountAtLine(row1, col1, row, col);
    if(ret == 0)
        return true;
    return false;
}

bool Board::canMovePao(int moveid,int row, int col,int killid)
{
    GetRowCol(row1, col1, moveid);
    int ret = getStoneCountAtLine(row, col, row1, col1);
    if(killid != -1)
    {
        if(ret == 1) return true;
    }
    else
    {
        if(ret == 0) return true;
    }
    return false;
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
            return canMoveChe(moveid,row,col,killid);
            break;
        case Stone::MA:
            return canMoveMa(moveid,row,col,killid);
            break;
        case Stone::PAO:
            return canMovePao(moveid,row,col,killid);
            break;
        case Stone::BING:
            return canMoveBing(moveid,row,col,killid);
            break;
    }
}

void Board::killStone(int id)
{
    if(id==-1) return;
    _s[id]._dead = true;
}

bool Board::canSelect(int id)
{
    return _bRedTurn == _s[id]._red;
}

void Board::moveStone(int moveid, int row, int col)
{
    _s[moveid]._row = row;
    _s[moveid]._col = col;

    _bRedTurn = !_bRedTurn;
}

void Board::moveStone(int moveid, int row, int col,int killid)
{
    killStone(killid);
    moveStone(moveid, row, col);
}

void Board::trySelectStone(int id)
{
    if(id == -1)
        return;

    if(!canSelect(id)) return;

    _selectid = id;
    update();
}

bool Board::red(int id)
{
    return _s[id]._red;
}

bool Board::sameColor(int id1, int id2)
{
    if(id1 == -1 || id2 == -1) return false;

    return red(id1) == red(id2);
}

void Board::tryMoveStone(int killid, int row, int col)
{
    if(killid != -1 && sameColor(killid, _selectid))
    {
        trySelectStone(killid);
        return;
    }

    bool ret = canMove(_selectid, row, col,killid);
    if(ret)
    {
        moveStone(_selectid, row, col,killid);
        _selectid = -1;
        update();
    }
}

void Board::click(int id, int row, int col)
{
    if(this->_selectid == -1)
    {
        trySelectStone(id);
    }
    else
    {
        tryMoveStone(id, row, col);
    }
}

bool Board::getClickRowCol(QPoint pt, int &row, int &col)
{
    for(row=0; row<=9; ++row)
    {
        for(col=0; col<=8; ++col)
        {
            QPoint distance = center(row, col) - pt;
            if(distance.x() * distance.x() + distance.y() * distance.y() < _r* _r)
                return true;
        }
    }
    return false;
}

void Board::click(QPoint pt)
{
    int row, col;
    bool bClicked = getClickRowCol(pt, row, col);
    if(!bClicked) return;

    int id = getStoneId(row, col);
    click(id, row, col);
}
void Board::mouseReleaseEvent(QMouseEvent *ev){
    if(ev->button() != Qt::LeftButton)
    {
        return;
    }
    click(ev->pos());
//    QPoint pt=ev->pos();
//    int row,col;
//    bool bRet = getRowCol(pt,row,col);
//    if(bRet == false)
//        return;
//    int i,clickid=-1;
//    for(i=0;i<32;++i){
//        if(_s[i]._row==row&&_s[i]._col==col&&_s[i]._dead==false){
//            break;
//        }
//    }
//    if(i<32){
//        clickid=i;
//    }
//    if(_selectid==-1){//可以选择棋子了
//        if(clickid!=-1){//能选中棋子
//            if(_bRedTurn==_s[clickid]._red){//是红棋走
//                _selectid = clickid;
//                 update();
//            }
//        }
//    }else{//走棋
//        if(canMove(_selectid,row,col,clickid)){
//            _s[_selectid]._row=row;
//            _s[_selectid]._col=col;
//            if(clickid!=-1){
//                _s[clickid]._dead=true;
//            }
//            _selectid = -1;
//            _bRedTurn = !_bRedTurn;
//            update();
//        }
//    }
}
