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
	//�ͷ��ڴ�
	for (auto i : this->child)
	{
		delete i;
	}
}

/*
 * �����������
 */
MonteCarloTree* MonteCarloTree::humanPlay(MonteCarloTree * pTree, Game * pGame)
{
	//1.Ѱ��������ҵ�����λ�ú���ָ��
	//2.ɾ��������֮�����ϵ
	//3.�ͷŸ���ָ��
	//4.����ָ�븳ֵ������
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
 * AI ����
 */
MonteCarloTree*  MonteCarloTree::aiPlay(MonteCarloTree * pTree, Game * pGame)
{
	//1.ģ�����
	//2.Ѱ�ҵ��������ӵ㣬���������
	//3.��¼�����Ž��λ��
	//4.ɾ��������֮�����ϵ
	//5.�ͷŸ���ָ��
	//6.����ָ�븳ֵ����ָ��

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
 * ��ʱ������
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
 * ����������
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
 * չ���ӽڵ�
 */
void MonteCarloTree::expandNode()
{
	//�Ѿ�չ������
	if (this->child.size() != 0)
		return;

	if (this->game.winner() >= 0)
		return;
	
	MonteCarloTree *p;
	vector<int> ActionSet = game.getAvailableActionSet();
	int player = 3 - this->lastPlayer;
	for (auto ac : ActionSet)
	{
		//�������� ���ø���
		p = new MonteCarloTree(this, player, this->aiPlayer);
		p->game.setBoard(&this->game.board);
		p->game.chessMove(&p->game.board, player, ac);
		this->child.push_back(p);
	}
}

/*
 * Ѱ��child��UCBֵ����һ����������
 * == -1 ������child
 * >= 0 ���ص����ִ�������
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
 * Ѱ��child�з��ʴ�������һ����������
 * == -1 ������child
 * >= 0 ���ص����ִ�������
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
 * ģ����Ϸ����
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

	//���巴�򴫲�����
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

	//���ݽ�����򴫲�
	BP(pStart, result);
	return;
}

/*
 * ʹ��UCB��ʽ�������ӽڵ�ķ���
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
