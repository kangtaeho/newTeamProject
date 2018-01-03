#pragma once
#include "gameNode.h"
#include "enemy.h"

class minion01 : public enemy
{
private:


public:
	minion01();
	~minion01();


	virtual HRESULT init(POINT point, int currentStage=1);
	virtual void collision();


};

