#pragma once
#include "gameNode.h"
#include "enemy.h"

class minion02 : public enemy
{

private:






public:
	minion02();
	~minion02();



	virtual HRESULT init(POINT point, int currentStage = 1);
	virtual void collision();


};

