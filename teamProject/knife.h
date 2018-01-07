#pragma once
#include "item.h" //나이프 아이템 추가 //병철
class knife : public item
{
public:
	knife();
	~knife();

	HRESULT init(POINT point);
	void render();
	virtual void move();
};

