#pragma once //������ ������ �߰� // ��ö
#include "item.h"
class stone :public item
{

private:
public:
	stone();
	~stone();

	HRESULT init(POINT point);
	void render();
	virtual void move();
};

