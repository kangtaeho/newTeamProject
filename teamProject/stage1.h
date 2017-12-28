#pragma once
#include "gameNode.h"
#include "item.h"
#include "knife.h"
#include "enemy.h"
class stage1 : public gameNode
{

private:

	RECT rc1;
	RECT* currentRC;

	item* _knife; // Ä® ½ºÅ×ÀÌÁö·Î °¡Á®¿È
	enemy* _enemy;

public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();
};

