#include "board.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

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

bool Board::canMove(int moveid,int row,int col,int killid){
     //moveid和killid颜色相同
    if(_s[moveid]._red==_s[killid]._red){
        //换选择
        _selectid = killid;
        update();
        return false;
    }
    return true;
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
    if(_selectid==-1){//选中棋子
        if(clickid!=-1){
            _selectid = clickid;
             update();
        }
    }else{//走棋
        if(canMove(_selectid,row,col,clickid)){
            _s[_selectid]._row=row;
            _s[_selectid]._col=col;
            if(clickid!=-1){
                _s[clickid]._dead=true;
            }
            _selectid = -1;
            update();
        }
    }

}
