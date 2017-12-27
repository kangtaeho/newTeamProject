#pragma once
#include "gameNode.h"
class stage1 : public gameNode
{

private:
	image* _stage1;

public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();
};

