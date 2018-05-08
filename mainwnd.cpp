#include "mainwnd.h"
#include <QHBoxLayout>
#include "singlegame.h"
#include "multigame.h"
#include "netgame.h"

MainWnd::MainWnd(int gameType,QWidget *parent):QWidget(parent)
{
    _gameType = gameType;
    switch(_gameType){
        case 0:
    {
            SingleGame* game0 = new SingleGame;
            CtrlPanel* panel0 = new CtrlPanel;

            QHBoxLayout* hLay0 = new QHBoxLayout(this);
            hLay0->addWidget(game0, 1);
            hLay0->addWidget(panel0);
            connect(panel0, SIGNAL(sigBack()), game0, SLOT(slotBack()));
           break;
    }
        case 1:
    {
            MultiGame* game1 = new MultiGame;
            CtrlPanel* panel1 = new CtrlPanel;

            QHBoxLayout* hLay1 = new QHBoxLayout(this);
            hLay1->addWidget(game1, 1);
            hLay1->addWidget(panel1);
            connect(panel1, SIGNAL(sigBack()), game1, SLOT(slotBack()));
            break;
    }
        case 2:
    {
            NetGame* game2 = new NetGame(true);
            CtrlPanel* panel2 = new CtrlPanel;

            QHBoxLayout* hLay2 = new QHBoxLayout(this);
            hLay2->addWidget(game2, 1);
            hLay2->addWidget(panel2);
            connect(panel2, SIGNAL(sigBack()), game2, SLOT(slotBack()));
            break;
    }
        case 3:
    {
            NetGame* game3 = new NetGame(false);
            CtrlPanel* panel3 = new CtrlPanel;

            QHBoxLayout* hLay3 = new QHBoxLayout(this);
            hLay3->addWidget(game3, 1);
            hLay3->addWidget(panel3);
            connect(panel3, SIGNAL(sigBack()), game3, SLOT(slotBack()));
            break;
    }
    }

}

MainWnd::~MainWnd()
{

}
