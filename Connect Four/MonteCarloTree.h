#pragma once
#include <vector>
#include "Game.h"

using namespace std;

#define WIN_SCORE 2
#define DRAW_SROCE 1 
#define LOSE_SCORE 0

class MonteCarloTree
{
public:
	MonteCarloTree(MonteCarloTree *parent, int lastPlayer, int aiPlayer);
	~MonteCarloTree();

public:
	MonteCarloTree *parent;
	vector<MonteCarloTree*> child;

public:
	int aiPlayer;
	int lastPlayer;
	int visitCount;
	double winScore;
	double UCB;
	Game game;

public:
	static MonteCarloTree* humanPlay(MonteCarloTree* pTree, Game *pGame);
	static MonteCarloTree* aiPlay(MonteCarloTree* pTree, Game *pGame);

public:
	void simulateWithTime(int ms);
	void simulateWithCount(int count);

public:
	void expandNode();
	int getMaxChildUCB();
	int getMaxChildCount();

private:
	//随机博弈，返回结果
	void simulateGame();
	void updateChildUCB();
};

