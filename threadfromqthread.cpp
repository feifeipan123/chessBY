#include "threadfromqthread.h"

ThreadFromQThread::ThreadFromQThread(QObject* par):QThread(par)
{

}
ThreadFromQThread::~ThreadFromQThread(){
    qDebug()<<"ThreadFromQThread::~ThreadFromQThread";
}

void ThreadFromQThread::run(){

}
