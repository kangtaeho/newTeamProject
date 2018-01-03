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

	_rcItem = RectMakeCenter(CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).x + _itemImage->getFrameWidth() / 2
						   , CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).y + _itemImage->getFrameHeight() / 2,
						   30, 30);
}
void item::render()
{

}