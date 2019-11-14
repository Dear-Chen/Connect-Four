#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UI.h"
#include "MonteCarloTree.h"
#include "MyThread.h"
#include <map>

class UI : public QMainWindow
{
	Q_OBJECT

public:
	UI(QWidget *parent = Q_NULLPTR);
public slots:
	void chessMove();
	void startGame();
	void resetGame();
	void closeChessButton();
	void openChessButton();
	void aiPlayResult(MonteCarloTree *pTree);

private:
	Ui::UIClass ui;
	MyThread *pAiThread;
	QPushButton *pChooseButton[BOARD_SIZE][BOARD_SIZE];
	map<QString, int> buttonMap;

private:
	Game chessState;
	MonteCarloTree* pTree;
	int humanNO;
	int playCount;

private:
	void updateBoard();
	bool isEnd();
};
