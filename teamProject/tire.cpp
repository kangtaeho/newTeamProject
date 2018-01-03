#include "stdafx.h"
#include "tire.h"


tire::tire()
{
}


tire::~tire()
{
}

HRESULT tire::init(POINT point)
{
	_itemImage = IMAGEMANAGER->addFrameImage("타이어", "./images/tire.bmp", 312, 78, 4, 1, true, RGB(255, 0, 255));
	_itemType = THROW;
	_itemEffect = 50;
	_x = point.x; _y = point.y;

	_price = 0; _count = 0;

	_itemState = DROP;

	_frameX = _frameCount = 0;
	return S_OK;
}

void tire::render()
{

	if (_itemState == DROP)
	{
		IMAGEMANAGER->findImage("타이어")->frameRender(getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).x,
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).y, 0, 0);
	}
	//날라가는 상태
	else
	{
		IMAGEMANAGER->findImage("타이어")->frameRender(getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).x,
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).y, _frameX, 0);
	}
}
