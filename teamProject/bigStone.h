#pragma once
#include "item.h"
class bigStone : public item
{


public:
	bigStone();
	~bigStone();

	HRESULT init(POINT point);
	void render();
};

