#include "MonteCarloTree.h"
#include <float.h>
#include <algorithm>
#include <functional>
#include <ctime>
#include "log.h"


MonteCarloTree::MonteCarloTree(MonteCarloTree * parent, int lastPlayer, int aiPlayer):parent(parent), lastPlayer(lastPlayer), aiPlayer(aiPlayer)
{
	this->visitCount = 0;
	this->winScore = 0;
}

MonteCarloTree::~MonteCarloTree()
{
	//释放内存
	for (auto i : this->child)
	{
		delete i;
	}
}

/*
 * 人类玩家下棋
 */
MonteCarloTree* MonteCarloTree::humanPlay(MonteCarloTree * pTree, Game * pGame)
{
	//1.寻找人类玩家的落子位置和子指针
	//2.删除父与子之间的联系
	//3.释放父级指针
	//4.将子指针赋值给父类
	MonteCarloTree *pChild;
	int childPos = 0;
	for (auto i : pTree->child)
	{
		if (i->game.board == pGame->board)
		{
			pChild = i;
			break;
		}
		childPos++;
	}

	pTree->child.at(childPos) = NULL;
	pChild->parent = NULL;

	delete pTree;

	return pChild;
}

/*
 * AI 落子
 */
MonteCarloTree*  MonteCarloTree::aiPlay(MonteCarloTree * pTree, Game * pGame)
{
	//1.模拟棋局
	//2.寻找到最有落子点，并完成落子
	//3.记录下最优解的位置
	//4.删除父与子之间的联系
	//5.释放父级指针
	//6.将子指针赋值给父指针

	LOG4CPLUS_TRACE_METHOD(logger, L"MonteCarloTree::aiPlay()");
	//LOG4CPLUS_INFO(logger, "Start simulation!");

	pTree->simulateWithCount(150000);
	pTree->simulateWithTime(1000);

	//LOG4CPLUS_INFO(logger, "End simulation!");

	int pos = pTree->getMaxChildCount();
	wstring msg;

	vector<int> action = pTree->game.getAvailableActionSet();
	msg = L"Action set ------- :";
	for (auto ac : action)
	{
		msg += to_wstring(ac) + L" ";
	}
	LOG4CPLUS_INFO(logger, msg);

	msg = L"Player " + to_wstring(3 - pTree->lastPlayer) + L" choose action " + to_wstring(pos + 1);
	LOG4CPLUS_INFO(logger, msg);

	for (auto ch : pTree->child)
	{
		msg = L"UCB = " + to_wstring(ch->UCB);
		LOG4CPLUS_INFO(logger, msg);
		msg = L"visit count = " + to_wstring(ch->visitCount);
		LOG4CPLUS_INFO(logger, msg);
		msg = L"win score = " + to_wstring(ch->winScore);
		LOG4CPLUS_INFO(logger, msg);
	}

	pGame->board = pTree->child.at(pos)->game.board;

	MonteCarloTree *pChild = pTree->child.at(pos);

	pChild->parent = nullptr;
	pTree->child.at(pos) = nullptr;

	msg = L"Player " + to_wstring(pChild->lastPlayer) + L" UCB is :" + to_wstring(pChild->UCB);
	LOG4CPLUS_FATAL(logger, msg);

	delete pTree;
	return pChild;
}

/*
 * 按时间搜索
 */
void MonteCarloTree::simulateWithTime(int ms)
{
	clock_t start, end;
	start = clock();
	do
	{
		simulateWithCount(1000);
		end = clock();
	} while (start + ms > end);
}

/*
 * 按次数搜索
 */
void MonteCarloTree::simulateWithCount(int count)
{
	do
	{
		count--;
		simulateGame();
	}
	while (count > 0);
}

/*
 * 展开子节点
 */
void MonteCarloTree::expandNode()
{
	//已经展开过了
	if (this->child.size() != 0)
		return;

	if (this->game.winner() >= 0)
		return;
	
	MonteCarloTree *p;
	vector<int> ActionSet = game.getAvailableActionSet();
	int player = 3 - this->lastPlayer;
	for (auto ac : ActionSet)
	{
		//设置子类 设置父类
		p = new MonteCarloTree(this, player, this->aiPlayer);
		p->game.setBoard(&this->game.board);
		p->game.chessMove(&p->game.board, player, ac);
		this->child.push_back(p);
	}
}

/*
 * 寻找child中UCB值最大的一个的引索号
 * == -1 不存在child
 * >= 0 返回的数字代表引索
 */
int MonteCarloTree::getMaxChildUCB()
{
	if (this->child.size() == 0)
		return -1;

	updateChildUCB();
	auto biggest = max_element(this->child.begin(), this->child.end(), [](const MonteCarloTree *a, const MonteCarloTree *b)->bool {return !(a->UCB >= b->UCB); });
	auto pos = distance(this->child.begin(), biggest);
	return pos;
}

/*
 * 寻找child中访问次数最多的一个的引索号
 * == -1 不存在child
 * >= 0 返回的数字代表引索
 */
int MonteCarloTree::getMaxChildCount()
{
	if (this->child.size() == 0)
		return -1;
	auto biggest = max_element(this->child.begin(), this->child.end(), [](const MonteCarloTree *a, const MonteCarloTree *b)->bool {return !(a->visitCount >= b->visitCount); });
	auto pos = distance(this->child.begin(), biggest);
	return pos;
}

/*
 * 模拟游戏过程
 */
void MonteCarloTree::simulateGame()
{
	std::function<MonteCarloTree*(MonteCarloTree*)> findStartState = [&findStartState](MonteCarloTree* pTree)->MonteCarloTree*
	{
		if (pTree->child.size() == 0)
			return pTree;
		return findStartState(pTree->child.at(pTree->getMaxChildUCB()));
	};

	MonteCarloTree *pStart = findStartState(this);
	if (pStart->visitCount > 0)
	{
		pStart->expandNode();
		if (pStart->child.size() > 0)
			pStart = pStart->child.at(0);
	}
	double result = pStart->game.randomPlayGame(pStart->lastPlayer);

	//定义反向传播函数
	std::function<void(MonteCarloTree*, int)> BP = [&BP](MonteCarloTree *pTree, int result)
	{
		if(result == 0)
			pTree->winScore += DRAW_SROCE;
		else
		{
			if (result == pTree->lastPlayer)
				pTree->winScore += WIN_SCORE;
			else
				pTree->winScore += LOSE_SCORE;
		}
		pTree->visitCount++;
		if (pTree->parent == NULL)
			return;
		else
			BP(pTree->parent, result);
	};

	//根据结果反向传播
	BP(pStart, result);
	return;
}

/*
 * 使用UCB公式，更新子节点的分数
 */
void MonteCarloTree::updateChildUCB()
{
	double c = 1.414;
	for (auto i : this->child)
	{
		if (i->visitCount == 0)
		{
			i->UCB = std::numeric_limits<double>::max();
			continue;
		}

		if (this->visitCount == 0)
		{
			i->UCB = std::numeric_limits<double>::max();
			continue;
		}

		i->UCB = i->winScore / i->visitCount + c * sqrt(log(this->visitCount) / i->visitCount);
	}
}
