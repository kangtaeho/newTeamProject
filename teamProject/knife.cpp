#include "stdafx.h"
#include "knife.h"


knife::knife()
{
}


knife::~knife()
{
}

HRESULT knife::init(POINT point)
{
	
	_itemImage = IMAGEMANAGER->addFrameImage("나이프", "./images/knife.bmp", 264, 33, 8, 1, true, RGB(255, 0, 255));
	_itemType = THROW; //던지는 타입
	_itemEffect = 30; // 데미지
	_x = point.x; _y = point.y;

	_price = 0; _count = 0;

	return S_OK;
}

void knife::render()
{
	IMAGEMANAGER->findImage("나이프")->frameRender(getMemDC(), 
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).y, 0, 0);

	//_itemImage->frameRender(getMemDC(), 300, 300, 0, 0);
}
