#pragma once
#include "gameNode.h"
#include "item.h"
#include "stone.h"
class stage1 : public gameNode
{

private:
	image* _stage1;

	item* _stone;
public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();
};

