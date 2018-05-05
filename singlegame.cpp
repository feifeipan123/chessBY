﻿#include "singlegame.h"
#include <QDebug>

void SingleGame::click(int id, int row, int col){
    if(!this->_bRedTurn)
        return;
    Board::click(id,row,col);
    if(!this->_bRedTurn){
        Step* step=getBestMove();
        moveStone(step->_moveid,step->_rowTo,step->_colTo,step->_killid);
        delete step;
    }

}

void SingleGame::getAllPossibleMove(QVector<Step *> &steps){
    int min=16,max=32;
    if(_bRedTurn){
        min=0,max=16;
    }
    for(int i=min;i<max;++i){
        if(_s[i]._dead)continue;
        for(int row=0;row<=9;++row){
            for(int col=0;col<=8;++col){
                  int killid=getStoneId(row,col);
                  if(sameColor(killid,i))continue;
                  if(canMove(i,row,col,killid)){
                      saveStep(i,killid,row,col,steps);
                  }
            }
        }
    }
}

int SingleGame::getMinScore(){
    //1.看看有哪些不走可以走
      QVector<Step*> steps;
      getAllPossibleMove(steps);//红棋的PossibleMove
      int minScore=100000;//最低分
      while(steps.count()){
          Step *step=steps.back();
          steps.removeLast();
          fakeMove(step);
          int score=calcScore();
          unfakeMove(step);
          if(score<minScore){
              minScore=score;
          }
          delete step;
      }
      return minScore;
}

Step* SingleGame::getBestMove(){
    /*
      1.看看有哪些不走可以走
      2.试着走一下
      3.评估走的结果
      4.去最好的结果作为参考
    */
  //1.看看有哪些不走可以走
    QVector<Step*> steps;
    getAllPossibleMove(steps);
    //2.试着走一下
    int maxScore=-100000;//最高分
    Step *ret=NULL;//最高分对应的步骤
     while(steps.count()){
         Step *step=steps.back();
         steps.removeLast();
         fakeMove(step);
         int score=getMinScore();
         unfakeMove(step);
         if(score>maxScore){
             maxScore=score;
             if(ret) delete ret;
             ret=step;
         }else{
             delete step;
         }
     }
//    for(QVector<Step*>::iterator it=steps.begin();it!=steps.end();++it){
//        Step* step=*it;
//        fakeMove(step);
//        int score=getMinScore();
//        unfakeMove(step);
//        if(score>maxScore){
//            maxScore=score;
//            ret=step;
//        }
//    }
    return ret;
}

void SingleGame::fakeMove(Step *step){
      killStone(step->_killid);
      moveStone(step->_moveid,step->_rowTo,step->_colTo);
}
void SingleGame::unfakeMove(Step* step){
    reliveStone(step->_killid);
    moveStone(step->_moveid,step->_rowFrom,step->_colFrom);

}

/*评价局面分*/
int SingleGame::calcScore(){
    /*enum TYPE{
        JIANG,
        CHE,
        PAO,
        MA,
        BING,
        SHI,
        XIANG
    };*/
    int redTotalScore=0;
    int blackTotalSocre=0;
    static int chessScore[]={1500,100,50,50,20,10,10};
    //黑棋分的总数-红棋分的总数
    for(int i=0;i<16;++i){
        if(_s[i]._dead)continue;
        redTotalScore+=chessScore[_s[i]._type];
    }

    for(int i=16;i<32;++i){
        if(_s[i]._dead)continue;
        blackTotalSocre+=chessScore[_s[i]._type];
    }
    return blackTotalSocre-redTotalScore;
}