#pragma once
#include "item.h"
class redPotion :
	public item
{
public:
	redPotion();
	~redPotion();

	virtual HRESULT init();
};

