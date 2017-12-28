#pragma once
#include "gameNode.h"
#include "item.h"
#include "knife.h"
#include "stone.h"
class stage1 : public gameNode
{

private:

	RECT rc1;
	RECT* currentRC;

	item* _knife; // 칼 스테이지로 가져옴
	item* _stone; // 미니돌덩이 ㅇㅇ
public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();
};

