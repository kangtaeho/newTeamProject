#pragma once
#include "gameNode.h"
#include "enemy.h"

class minion00 : public enemy
{
private:

public:
	minion00();
	~minion00();


	virtual HRESULT init(POINT point, int currentStage);
	
	virtual void collision();

	//¡÷ºÆ

};

