#pragma once
#include "item.h"

class orangePotion :
	public item
{
public:
	orangePotion();
	~orangePotion();

	virtual HRESULT init();
	/*virtual void release();
	virtual void update();
	virtual void render();*/
};

