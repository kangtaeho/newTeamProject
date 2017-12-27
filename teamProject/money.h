#pragma once
#include "item.h"
class money :
	public item
{
public:
	money();
	~money();

	virtual HRESULT init(POINT point);
};

