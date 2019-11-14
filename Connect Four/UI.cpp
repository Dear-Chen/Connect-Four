#include "UI.h"
#include <QMessageBox>

UI::UI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	pAiThread = new MyThread();

	pChooseButton[0][0] = ui.pushButton_1;
	pChooseButton[0][1] = ui.pushButton_2;
	pChooseButton[0][2] = ui.pushButton_3;
	pChooseButton[0][3] = ui.pushButton_4;
	pChooseButton[0][4] = ui.pushButton_5;
	pChooseButton[0][5] = ui.pushButton_6;
	pChooseButton[0][6] = ui.pushButton_7;
	pChooseButton[0][7] = ui.pushButton_8;

	pChooseButton[1][0] = ui.pushButton_9;
	pChooseButton[1][1] = ui.pushButton_10;
	pChooseButton[1][2] = ui.pushButton_11;
	pChooseButton[1][3] = ui.pushButton_12;
	pChooseButton[1][4] = ui.pushButton_13;
	pChooseButton[1][5] = ui.pushButton_14;
	pChooseButton[1][6] = ui.pushButton_15;
	pChooseButton[1][7] = ui.pushButton_16;

	pChooseButton[2][0] = ui.pushButton_17;
	pChooseButton[2][1] = ui.pushButton_18;
	pChooseButton[2][2] = ui.pushButton_19;
	pChooseButton[2][3] = ui.pushButton_20;
	pChooseButton[2][4] = ui.pushButton_21;
	pChooseButton[2][5] = ui.pushButton_22;
	pChooseButton[2][6] = ui.pushButton_23;
	pChooseButton[2][7] = ui.pushButton_24;

	pChooseButton[3][0] = ui.pushButton_25;
	pChooseButton[3][1] = ui.pushButton_26;
	pChooseButton[3][2] = ui.pushButton_27;
	pChooseButton[3][3] = ui.pushButton_28;
	pChooseButton[3][4] = ui.pushButton_29;
	pChooseButton[3][5] = ui.pushButton_30;
	pChooseButton[3][6] = ui.pushButton_31;
	pChooseButton[3][7] = ui.pushButton_32;

	pChooseButton[4][0] = ui.pushButton_33;
	pChooseButton[4][1] = ui.pushButton_34;
	pChooseButton[4][2] = ui.pushButton_35;
	pChooseButton[4][3] = ui.pushButton_36;
	pChooseButton[4][4] = ui.pushButton_37;
	pChooseButton[4][5] = ui.pushButton_38;
	pChooseButton[4][6] = ui.pushButton_39;
	pChooseButton[4][7] = ui.pushButton_40;

	pChooseButton[5][0] = ui.pushButton_41;
	pChooseButton[5][1] = ui.pushButton_42;
	pChooseButton[5][2] = ui.pushButton_43;
	pChooseButton[5][3] = ui.pushButton_44;
	pChooseButton[5][4] = ui.pushButton_45;
	pChooseButton[5][5] = ui.pushButton_46;
	pChooseButton[5][6] = ui.pushButton_47;
	pChooseButton[5][7] = ui.pushButton_48;

	pChooseButton[6][0] = ui.pushButton_49;
	pChooseButton[6][1] = ui.pushButton_50;
	pChooseButton[6][2] = ui.pushButton_51;
	pChooseButton[6][3] = ui.pushButton_52;
	pChooseButton[6][4] = ui.pushButton_53;
	pChooseButton[6][5] = ui.pushButton_54;
	pChooseButton[6][6] = ui.pushButton_55;
	pChooseButton[6][7] = ui.pushButton_56;

	pChooseButton[7][0] = ui.pushButton_57;
	pChooseButton[7][1] = ui.pushButton_58;
	pChooseButton[7][2] = ui.pushButton_59;
	pChooseButton[7][3] = ui.pushButton_60;
	pChooseButton[7][4] = ui.pushButton_61;
	pChooseButton[7][5] = ui.pushButton_62;
	pChooseButton[7][6] = ui.pushButton_63;
	pChooseButton[7][7] = ui.pushButton_64;

	map<QString, int>::iterator it = buttonMap.begin();
	buttonMap.insert(it, pair<QString, int>("pushButton_1", 0));
	buttonMap.insert(it, pair<QString, int>("pushButton_2", 0));
	buttonMap.insert(it, pair<QString, int>("pushButton_3", 0));
	buttonMap.insert(it, pair<QString, int>("pushButton_4", 0));
	buttonMap.insert(it, pair<QString, int>("pushButton_5", 0));
	buttonMap.insert(it, pair<QString, int>("pushButton_6", 0));
	buttonMap.insert(it, pair<QString, int>("pushButton_7", 0));
	buttonMap.insert(it, pair<QString, int>("pushButton_8", 0));

	buttonMap.insert(it, pair<QString, int>("pushButton_9", 1));
	buttonMap.insert(it, pair<QString, int>("pushButton_10", 1));
	buttonMap.insert(it, pair<QString, int>("pushButton_11", 1));
	buttonMap.insert(it, pair<QString, int>("pushButton_12", 1));
	buttonMap.insert(it, pair<QString, int>("pushButton_13", 1));
	buttonMap.insert(it, pair<QString, int>("pushButton_14", 1));
	buttonMap.insert(it, pair<QString, int>("pushButton_15", 1));
	buttonMap.insert(it, pair<QString, int>("pushButton_16", 1));

	buttonMap.insert(it, pair<QString, int>("pushButton_17", 2));
	buttonMap.insert(it, pair<QString, int>("pushButton_18", 2));
	buttonMap.insert(it, pair<QString, int>("pushButton_19", 2));
	buttonMap.insert(it, pair<QString, int>("pushButton_20", 2));
	buttonMap.insert(it, pair<QString, int>("pushButton_21", 2));
	buttonMap.insert(it, pair<QString, int>("pushButton_22", 2));
	buttonMap.insert(it, pair<QString, int>("pushButton_23", 2));
	buttonMap.insert(it, pair<QString, int>("pushButton_24", 2));

	buttonMap.insert(it, pair<QString, int>("pushButton_25", 3));
	buttonMap.insert(it, pair<QString, int>("pushButton_26", 3));
	buttonMap.insert(it, pair<QString, int>("pushButton_27", 3));
	buttonMap.insert(it, pair<QString, int>("pushButton_28", 3));
	buttonMap.insert(it, pair<QString, int>("pushButton_29", 3));
	buttonMap.insert(it, pair<QString, int>("pushButton_30", 3));
	buttonMap.insert(it, pair<QString, int>("pushButton_31", 3));
	buttonMap.insert(it, pair<QString, int>("pushButton_32", 3));

	buttonMap.insert(it, pair<QString, int>("pushButton_33", 4));
	buttonMap.insert(it, pair<QString, int>("pushButton_34", 4));
	buttonMap.insert(it, pair<QString, int>("pushButton_35", 4));
	buttonMap.insert(it, pair<QString, int>("pushButton_36", 4));
	buttonMap.insert(it, pair<QString, int>("pushButton_37", 4));
	buttonMap.insert(it, pair<QString, int>("pushButton_38", 4));
	buttonMap.insert(it, pair<QString, int>("pushButton_39", 4));
	buttonMap.insert(it, pair<QString, int>("pushButton_40", 4));

	buttonMap.insert(it, pair<QString, int>("pushButton_41", 5));
	buttonMap.insert(it, pair<QString, int>("pushButton_42", 5));
	buttonMap.insert(it, pair<QString, int>("pushButton_43", 5));
	buttonMap.insert(it, pair<QString, int>("pushButton_44", 5));
	buttonMap.insert(it, pair<QString, int>("pushButton_45", 5));
	buttonMap.insert(it, pair<QString, int>("pushButton_46", 5));
	buttonMap.insert(it, pair<QString, int>("pushButton_47", 5));
	buttonMap.insert(it, pair<QString, int>("pushButton_48", 5));

	buttonMap.insert(it, pair<QString, int>("pushButton_49", 6));
	buttonMap.insert(it, pair<QString, int>("pushButton_50", 6));
	buttonMap.insert(it, pair<QString, int>("pushButton_51", 6));
	buttonMap.insert(it, pair<QString, int>("pushButton_52", 6));
	buttonMap.insert(it, pair<QString, int>("pushButton_53", 6));
	buttonMap.insert(it, pair<QString, int>("pushButton_54", 6));
	buttonMap.insert(it, pair<QString, int>("pushButton_55", 6));
	buttonMap.insert(it, pair<QString, int>("pushButton_56", 6));

	buttonMap.insert(it, pair<QString, int>("pushButton_57", 7));
	buttonMap.insert(it, pair<QString, int>("pushButton_58", 7));
	buttonMap.insert(it, pair<QString, int>("pushButton_59", 7));
	buttonMap.insert(it, pair<QString, int>("pushButton_60", 7));
	buttonMap.insert(it, pair<QString, int>("pushButton_61", 7));
	buttonMap.insert(it, pair<QString, int>("pushButton_62", 7));
	buttonMap.insert(it, pair<QString, int>("pushButton_63", 7));
	buttonMap.insert(it, pair<QString, int>("pushButton_64", 7));

	connect(pAiThread, SIGNAL(closeButton()), this, SLOT(closeChessButton()), Qt::QueuedConnection);
	connect(pAiThread, SIGNAL(openButton()), this, SLOT(openChessButton()), Qt::QueuedConnection);
	connect(pAiThread, SIGNAL(sendResult(MonteCarloTree *)), this, SLOT(aiPlayResult(MonteCarloTree *)), Qt::QueuedConnection);

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			connect(pChooseButton[j][i], SIGNAL(clicked()), this, SLOT(chessMove()));
		}
	}

	connect(ui.pushButton_start, SIGNAL(clicked()), this, SLOT(startGame()));
	connect(ui.pushButton_reset, SIGNAL(clicked()), this, SLOT(resetGame()));

	closeChessButton();

	ui.pushButton_reset->setDisabled(true);

	chessState.clearBoard();
	updateBoard();
	pTree = NULL;
	playCount = 0;
}

/*
 * 落子函数处理
 */
void UI::chessMove()
{
	QString get = this->sender()->objectName();

	//寻找落子位置
	int index;
	index = buttonMap.at(get);

	//处理落子
	if (humanNO == 2)
	{
		chessState.chessMove(humanNO, index);
		pTree = MonteCarloTree::humanPlay(pTree, &chessState);
	}
	else if (humanNO == 1)
	{
		if (playCount == 0)
		{
			playCount++;
			pTree = new MonteCarloTree(NULL, humanNO, 3 - humanNO);
			pTree->game.clearBoard();
			chessState.chessMove(humanNO, index);
			pTree->game.setBoard(&this->chessState.board);
		}
		else
		{
			chessState.chessMove(humanNO, index);
			pTree = MonteCarloTree::humanPlay(pTree, &chessState);
		}
	}
	updateBoard();
	if (isEnd() == true)
		return;
	//AI 落子过程
	pAiThread->start(pTree, &chessState);
	return;
}

void UI::startGame()
{
	humanNO = ui.comboBox->currentIndex() + 1;

	ui.comboBox->setDisabled(true);
	ui.pushButton_start->setDisabled(true);

	ui.pushButton_reset->setEnabled(true);
	openChessButton();

	//电脑先手
	if (humanNO == 2)
	{
		pTree = new MonteCarloTree(NULL, humanNO, 3 - humanNO);
		pTree->game.clearBoard();
		pAiThread->start(pTree, &chessState);
	}
	else if(humanNO == 3)
	{
		pTree = new MonteCarloTree(NULL, humanNO - 1, 4 - humanNO);
		pTree->game.clearBoard();
		pAiThread->start(pTree, &chessState);
	}
	updateBoard();
}

void UI::resetGame()
{
	ui.comboBox->setEnabled(true);
	ui.pushButton_start->setEnabled(true);

	ui.pushButton_reset->setDisabled(true);
	closeChessButton();

	if (pAiThread->isRunning() == true)
	{
		pAiThread->terminate();
		pAiThread->quit();
		pAiThread->wait(100);
	}

	chessState.clearBoard();
	updateBoard();
	playCount = 0;
	delete pTree;
}

void UI::closeChessButton()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			pChooseButton[j][i]->setDisabled(true);
		}
	}
}

void UI::openChessButton()
{
	for (int i = 0; i < BOARD_SIZE - 1; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (i == 0)
			{
				if(chessState.board.state[j][0] == 0)
					pChooseButton[j][0]->setEnabled(true);
				else
					pChooseButton[j][0]->setDisabled(true);
			}
			if (chessState.board.state[j][i] != 0 && chessState.board.state[j][i + 1] == 0)
				pChooseButton[j][i + 1]->setEnabled(true);
			else
				pChooseButton[j][i + 1]->setDisabled(true);
		}
	}
}

void UI::aiPlayResult(MonteCarloTree * pTree)
{
	this->pTree = pTree;
	if (this->humanNO == 3)
	{
		if (isEnd() == true)
			return;
		//AI 落子过程
		pAiThread->start(pTree, &chessState);
	}
	isEnd();
	updateBoard();
}

void UI::updateBoard()
{
	auto setColor = [](QPushButton *p, int color) {
		//QSizePolicy policy = p->sizePolicy();
		switch (color)
		{
		case 0: p->setStyleSheet("background-color: rgb(240,240,240);"); break;			//灰色，背景色
		case 1: p->setStyleSheet("background-color: rgb(0,0,0);"); break;				//黑色
		case 2: p->setStyleSheet("background-color: rgb(255,0,0);"); break;				//红色
		default:
			break;
		}
	};

	char *p = &chessState.board.state[0][0];

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			setColor(pChooseButton[i][j], *p++);
		}
	}
}

bool UI::isEnd()
{
	int end = chessState.winner();
	if (end < 0)
		return false;

	updateBoard();
	QString strMsg;
	if (end == 0)
	{
		strMsg = QString::fromLocal8Bit("平局！");
	}
	if (humanNO == 1 || humanNO == 2)
	{
		if (end == humanNO)
		{
			strMsg = QString::fromLocal8Bit("你赢了！");
		}
		else if (end == 3 - humanNO)
		{
			strMsg = QString::fromLocal8Bit("你输了！");
		}
	}
	else if (humanNO == 3)
	{
		if (end == 1)
		{
			strMsg = QString::fromLocal8Bit("黑子获胜！");
		}
		else if (end == 2)
		{
			strMsg = QString::fromLocal8Bit("红子获胜！");
		}
	}

	QMessageBox::information(this, tr("Report"), strMsg);
	resetGame();
	return true;
}
