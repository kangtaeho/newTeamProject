#pragma once
#include "gameNode.h"
#include "item.h"
#include "knife.h"
class stage1 : public gameNode
{

private:

	RECT rc1;
	RECT* currentRC;

	item* _knife;
public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();
};

