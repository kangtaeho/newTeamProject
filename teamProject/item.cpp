#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{

}

HRESULT item::init()
{

	return S_OK;
}

HRESULT item::init(POINT point)
{

	return S_OK;
}
HRESULT item::init(POINT point, int money)
{

	return S_OK;
}


void item::release()
{

}
void item::update()
{

	_frameCount++;
	if (_frameCount %10 == 0)
	{
		_frameX++;
		if (_frameX > _itemImage->getMaxFrameX()) _frameX = 0;
	}
}
void item::render()
{

}