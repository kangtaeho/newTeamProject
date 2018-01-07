#pragma once //µπ∏Õ¿Ã æ∆¿Ã≈€ √ﬂ∞° // ∫¥√∂
#include "item.h"
class stone :public item
{

private:
	float _gravity;
	float _throwPower;
public:
	stone();
	~stone();

	HRESULT init(POINT point);
	void render();
	virtual void move();
};

