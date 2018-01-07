#pragma once
#include "gameNode.h"
#include "enemy.h"

class boss00 : public enemy
{
private:
	
public:
	boss00();
	~boss00();

	virtual HRESULT init(POINT point, int currentStage = 1);

	virtual void collision();

	static void rightAttack(void* obj);
	static void rightJumpAttack(void* obj);
	static void leftAttack(void* obj);
	static void leftJumpAttack(void* obj);

};

