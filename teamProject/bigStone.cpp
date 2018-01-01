#include "stdafx.h"
#include "bigStone.h"


bigStone::bigStone()
{
}


bigStone::~bigStone()
{
}

HRESULT bigStone::init(POINT point)
{
	_itemImage = IMAGEMANAGER->addFrameImage("Å«µ¹µ¢ÀÌ", "./images/bigstone.bmp", 840, 120, 7, 1, true, RGB(255, 0, 255));
	_itemType = THROW;
	_itemEffect = 50;
	_x = point.x, _y = point.y;

	_price = 0; _count = 0;
	_itemState = DROP;
	_frameX = _frameCount = 0;
	return S_OK;
}

void bigStone::render()
{
	if (_itemState == DROP)
	{
		IMAGEMANAGER->findImage("Å«µ¹µ¢ÀÌ")->frameRender(getMemDC(), 
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).x,
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).y, 0,0);
	}

	else
	{
		IMAGEMANAGER->findImage("Å«µ¹µ¢ÀÌ")->frameRender(getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).x,
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).y, _frameX, 0);
			
	}
}
