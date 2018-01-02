#pragma once
#include "gameNode.h"
#include "enemy.h"

class minion01 : public enemy
{
private:






public:
	minion01();
	~minion01();


	virtual HRESULT init(POINT point);
	virtual void collision();


};

