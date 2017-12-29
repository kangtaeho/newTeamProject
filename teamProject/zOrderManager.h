#pragma once
#include "singletonBase.h"
#include <vector>
struct tagZOrder{

};

class gameNode;
class zOrderManager : public singletonBase<zOrderManager>
{
	vector<gameNode*> _vGameNode;
	vector<gameNode*>::iterator _viGameNode;

	vector<int> _vY;
	vector<int>::iterator _viY;
public:
	zOrderManager();
	~zOrderManager();

	HRESULT init();
	void update();
	void release();
					//그릴 클래스		,현재 y축(쉽게 말해 렉트의 bottom)
	void addZOrder(gameNode* tempGameNode,int y);
	void sortY( int start, int num);	//정렬
	int partition(int start, int end);
	void allClear() { _vGameNode.clear(); _vY.clear(); }
	//void zOrderUpdate();
	//그려라
	void paintZOrder();
};

