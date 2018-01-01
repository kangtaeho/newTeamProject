#pragma once
#include "gameNode.h"
#include "enemy.h"

class minion02 : public enemy
{
public:
	minion02();
	~minion02();



	virtual HRESULT init(POINT point);
	virtual void collision();


};

