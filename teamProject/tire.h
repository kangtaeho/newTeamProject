#pragma once
#include "item.h"
class tire : public item
{
private:

public:
	tire();
	~tire();

	HRESULT init(POINT point);
	void render();
};

