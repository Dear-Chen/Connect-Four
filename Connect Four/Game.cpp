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
 * ���ص�ǰ������еĿ��м���
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
 * ȫ������
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
 * ������ֵ���Ϣ
 */
void Game::setBoard(const ChessBoard *pBoard)
{
	this->board = *pBoard;
}

/*
 * �����ʼ����
 * ������Ϸ���
 */
double Game::randomPlayGame(int player)
{
	//���������
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
 * ���ݵ�ǰ����֣��ж�ʤ��
 * ����ֵint
 * == 2 ���2��ʤ
 * == 1 ���1��ʤ
 * == 0 ƽ��
 * == -1 ������
 */
int Game::winner(ChessBoard * pBoard)
{
	char pos0, pos1, pos2, pos3;

	//����lambda function
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
	//�ж��Ƿ���ʤ��
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			p = &pBoard->state[j][i];
			player = *p;
			if (player != 0)
			{
				pos0 = *p;

				//�ֳ��ĸ�����
				//����  б����  д����
				if (i < BOARD_SIZE - 3)
				{
					//���жϺ���
					pos1 = *(p + 1);
					pos2 = *(p + 2);
					pos3 = *(p + 3);
					if (f(player) != 0)
						return player;
					//���ж�б���·���
					if (j < BOARD_SIZE - 3)
					{
						pos1 = *(p + 1 + 1 * BOARD_SIZE);
						pos2 = *(p + 2 + 2 * BOARD_SIZE);
						pos3 = *(p + 3 + 3 * BOARD_SIZE);
						if (f(player) != 0)
							return player;
					}
					//����ж�б���Ϸ���
					if (j > 2)
					{
						pos1 = *(p + 1 - 1 * BOARD_SIZE);
						pos2 = *(p + 2 - 2 * BOARD_SIZE);
						pos3 = *(p + 3 - 3 * BOARD_SIZE);
						if (f(player) != 0)
							return player;
					}
				}
				//����
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
				continue;			//�ӿ�����ٶ�
			}
		}
	}

	//�ж�ʱ�������ӵ�λ��
	if (zeroFlag == 1)
		return -1;

	//ƽ��
	return 0;
}

/*
 * ������ӵĹ���
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
