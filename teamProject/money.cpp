#include "stdafx.h"
#include "money.h"


money::money()
{
}


money::~money()
{
}

HRESULT money::init(POINT point, int money)
{
	//ÀÌ¹ÌÁö ÃÊ±âÈ­
	_itemImage = IMAGEMANAGER->addFrameImage("µ·", "./images/money.bmp", 132, 30,4,1 ,true, RGB(255, 0, 255));
	//Å¸ÀÔ ÃÊ±âÈ­
	_itemType = MONEY;
	//µ· È¹µæ·®
	_itemEffect = money;
	//ÁÂÇ¥
	_x = point.x; _y = point.y;
	

	//µ·Å¸ÀÔÀº °¡°Ý, °¹¼ö°¡ ÇÊ¿ä¾ø´Ù.
	_price = 0; _count = 0;

	_frameX = _frameCount = 0;

	return S_OK;
}

void money::render(){
	IMAGEMANAGER->findImage("µ·")->frameRender(getMemDC(), CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).y, _frameX, 0);
}