#include "Game.h"
#include <random>
#include <ctime>

Game::Game()
{
}

Game::Game(ChessBoard board):board(board)
{
}

Game::~Game()
{
}

/*
 * 返回当前棋局所有的可行集合
 */
vector<int> Game::getAvailableActionSet(const ChessBoard *pBoard)
{
	vector<int> rtn;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (pBoard->state[i][BOARD_SIZE - 1] == 0)
			rtn.push_back(i);
	}
	return rtn;
}

/*
 * 全都清零
 */
void Game::clearBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			this->board.state[j][i] = 0;
		}
	}
}

/*
 * 设置棋局的信息
 */
void Game::setBoard(const ChessBoard *pBoard)
{
	this->board = *pBoard;
}

/*
 * 随机开始博弈
 * 返回游戏结果
 */
double Game::randomPlayGame(int player)
{
	//随机数引擎
	static std::default_random_engine e((unsigned int)time(NULL));
	static std::uniform_real_distribution<double> u(0, 1);

	ChessBoard temp;
	temp = board;

	while(1)
	{
		int end = winner(&temp);
		if (end >= 0)
		{
			return end;
		}
		vector<int> ActionSet = getAvailableActionSet(&temp);

		player = 3 - player;
		int action = (int)floor(u(e)*ActionSet.size());
		chessMove(&temp, player, ActionSet.at(action));
	}
}

/*
 * 根据当前的棋局，判断胜负
 * 返回值int
 * == 2 玩家2获胜
 * == 1 玩家1获胜
 * == 0 平局
 * == -1 继续下
 */
int Game::winner(ChessBoard * pBoard)
{
	char pos0, pos1, pos2, pos3;

	//定义lambda function
	auto f = [&pos0, &pos1, &pos2, &pos3](int player)->int
	{
		if (pos0 == player && pos1 == player && pos2 == player && pos3 == player)
			return player;
		else
			return 0;
	};

	int zeroFlag = 0;

	int i, j;
	int player;
	char *p;
	//判断是否有胜负
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			p = &pBoard->state[j][i];
			player = *p;
			if (player != 0)
			{
				pos0 = *p;

				//分成四个方向
				//横向  斜向下  写向上
				if (i < BOARD_SIZE - 3)
				{
					//先判断横向
					pos1 = *(p + 1);
					pos2 = *(p + 2);
					pos3 = *(p + 3);
					if (f(player) != 0)
						return player;
					//再判断斜向下方向
					if (j < BOARD_SIZE - 3)
					{
						pos1 = *(p + 1 + 1 * BOARD_SIZE);
						pos2 = *(p + 2 + 2 * BOARD_SIZE);
						pos3 = *(p + 3 + 3 * BOARD_SIZE);
						if (f(player) != 0)
							return player;
					}
					//最后判断斜向上方向
					if (j > 2)
					{
						pos1 = *(p + 1 - 1 * BOARD_SIZE);
						pos2 = *(p + 2 - 2 * BOARD_SIZE);
						pos3 = *(p + 3 - 3 * BOARD_SIZE);
						if (f(player) != 0)
							return player;
					}
				}
				//纵向
				if (j < BOARD_SIZE - 3)
				{
					pos1 = *(p + 1 * BOARD_SIZE);
					pos2 = *(p + 2 * BOARD_SIZE);
					pos3 = *(p + 3 * BOARD_SIZE);
					if (f(player) != 0)
						return player;
				}

			}
			else
			{
				zeroFlag = 1;
				continue;			//加快检索速度
			}
		}
	}

	//判断时候还有落子的位置
	if (zeroFlag == 1)
		return -1;

	//平局
	return 0;
}

/*
 * 完成落子的工作
 */
bool Game::chessMove(ChessBoard * pBoard, int player, int action)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (pBoard->state[action][i] == 0)
		{
			pBoard->state[action][i] = player;
			return true;
		}
	}
	return false;
}
