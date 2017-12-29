#include "stdafx.h"
#include "stone.h"


stone::stone()
{
}


stone::~stone()
{
}

HRESULT stone::init(POINT point)
{

	_itemImage = IMAGEMANAGER->addFrameImage("¹Ì´Ïµ¹µ¢ÀÌ", "./images/ministone.bmp", 240, 48, 5, 1, true, RGB(255, 0,255));
	_itemType = THROW;
	_itemEffect = 50;
	_x = point.x; _y = point.y;

	_price = 0; _count = 0;

	return S_OK;
}

void stone::render()
{
	IMAGEMANAGER->findImage("¹Ì´Ïµ¹µ¢ÀÌ")->frameRender(getMemDC(), CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).y, 0, 0);
	//_itemImage->frameRender(getMemDC(), 300, 350, 0, 0);
}
