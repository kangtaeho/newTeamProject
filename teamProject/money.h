#pragma once
#include "item.h"
class money :
	public item
{
public:
	money();
	~money();

	HRESULT init(POINT point);
	void render();
};

