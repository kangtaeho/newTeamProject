#pragma once
#include "item.h" //������ ������ �߰� //��ö
class knife : public item
{
public:
	knife();
	~knife();

	HRESULT init(POINT point);
	void render();
	virtual void move();
};

