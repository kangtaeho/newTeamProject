#include "stdafx.h"
#include "zOrderManager.h"
#include "gameNode.h"

zOrderManager::zOrderManager()
{
}


zOrderManager::~zOrderManager()
{
}
HRESULT zOrderManager::init()
{
	return S_OK;
}

void zOrderManager::release()
{

}

void zOrderManager::update()
{
	for (_viGameNode = _vGameNode.begin(); _viGameNode != _vGameNode.end(); ++_viGameNode)
	{
		(*_viGameNode)->update();
	}


}

//그릴 클래스		,현재 y축(쉽게 말해 렉트의 bottom)
void zOrderManager::addZOrder(gameNode* tempGameNode, int y)
{
	_vGameNode.push_back(tempGameNode);
	_vY.push_back(y);
}

void zOrderManager::sortY(int start, int num){
	//1개만 담겨있을경우 정렬 필요 없으니
	if (num < 1) return;

	int left = start;
		int right=num;

	int pivot = _vY[(left+right)/2];

	while (left <= right)
	{
		while (_vY[left] < pivot)
			left++;
		while (_vY[right] > pivot)
			right--;
		if (left <= right)
		{
			int tempY = _vY[left];
			_vY[left] = _vY[right];
			_vY[right] = tempY;
			gameNode* temp;
			temp = _vGameNode[left];
			_vGameNode[left] = _vGameNode[right];
			_vGameNode[right] = temp;

			left++;
			right--;
		}
		

	}

	if (start < right)
		sortY(start, right);
	if (left < num)
		sortY(left, num);
	
	/*if (_vY[0] > _vY[1])
	{
		int tempY = _vY[0];
		_vY[0] = _vY[1];
		_vY[1] = tempY;
		gameNode* temp;
		temp = _vGameNode[0];
		_vGameNode[0] = _vGameNode[1];
		_vGameNode[1] = temp;
	}*/
}

/*
void QuickSort(int A[], int p, int r)

}
*/
//void zOrderUpdate();
//그려라
void zOrderManager::paintZOrder()
{
	sortY(0, _vY.size()-1);
	for (_viGameNode = _vGameNode.begin(); _viGameNode != _vGameNode.end(); ++_viGameNode)
	{
		(*_viGameNode)->render();
	}
}