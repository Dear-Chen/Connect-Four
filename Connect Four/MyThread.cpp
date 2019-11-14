#include "MyThread.h"



MyThread::MyThread()
{
}


MyThread::~MyThread()
{
}

void MyThread::start(MonteCarloTree * pTree, Game * pGame)
{
	this->pTree = pTree;
	this->pGame = pGame;
	QThread::start();
}

void MyThread::run()
{
	emit closeButton();
	this->pTree = MonteCarloTree::aiPlay(pTree, pGame);
	emit sendResult(this->pTree);
	emit openButton();
}
