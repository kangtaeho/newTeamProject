#pragma once
#include "gameNode.h"


class enemy : public gameNode
{


private:




public:
	enemy();
	~enemy();


	HRESULT init();
	void release();
	void update();
	void render();
};

