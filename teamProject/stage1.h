#pragma once
#include "gameNode.h"
#include "item.h"
#include "knife.h"
class stage1 : public gameNode
{

private:

	RECT rc1;
	RECT* currentRC;

	item* _knife; // 칼 스테이지로 가져옴
public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();
};

