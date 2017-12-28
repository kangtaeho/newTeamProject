#pragma once
#include "item.h"
class whitePotion :
	public item
{
public:
	whitePotion();
	~whitePotion();

	virtual HRESULT init();
};

