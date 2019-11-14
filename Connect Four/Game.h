#pragma once
#include <vector>

using namespace std;

#define BOARD_SIZE 8

struct ChessBoard
{
	char state[BOARD_SIZE][BOARD_SIZE];
	bool operator == (const ChessBoard& rhs)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (this->state[j][0] == 0 && rhs.state[j][0] == 0)
				continue;
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				if (this->state[j][i] == 0 && rhs.state[j][i] == 0)
				{
					//为了跳出当前的循环
					i += BOARD_SIZE;
				}
				else
				{
					if (this->state[j][i] != rhs.state[j][i])
						return false;
				}
			}
		}
		return true;
	};
};

class Game
{
public:
	Game();
	Game(ChessBoard board);
	~Game();

//唯一的数据就是棋盘信息
public:
	ChessBoard board;

public:
	void clearBoard();
	void setBoard(const ChessBoard *pBoard);
	double randomPlayGame(int player);

public:
	int winner()
	{
		return winner(&this->board);
	};
	static int winner(ChessBoard *pBoard);

	bool chessMove(int player, int action)
	{
		return chessMove(&this->board, player, action);
	};
	static bool chessMove(ChessBoard *pBoard, int player, int action);

	vector<int> getAvailableActionSet()
	{
		return getAvailableActionSet(&this->board);
	};
	static vector<int> getAvailableActionSet(const ChessBoard *pBoard);
};

