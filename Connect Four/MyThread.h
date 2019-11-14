#pragma once
#include <QThread>
#include "MonteCarloTree.h"

class MyThread :
	public QThread
{
	Q_OBJECT
public:
	explicit MyThread();
	~MyThread();
signals:
	void closeButton();
	void openButton();
	void sendResult(MonteCarloTree *);

public:
	void start(MonteCarloTree* pTree, Game *pGame);
private:
	void run();

private:
	MonteCarloTree *pTree;
	Game *pGame;
};

