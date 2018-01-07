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

	_rcItem = RectMakeCenter(CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).x+ _itemImage->getFrameWidth()/2
						   , CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).y+ _itemImage->getFrameHeight() / 2,
						     30, 30);

	_price = 0; _count = 0;

	_itemState = DROP;

	_frameX = _frameCount = 0;
	return S_OK;
}

void knife::render()
{
	//떨어진 상태
	if (_itemState == DROP)
	{
		IMAGEMANAGER->findImage("나이프")->frameRender(getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).x,
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).y, 0, 0);
	}
	//날라가는 상태
	else
	{
		IMAGEMANAGER->findImage("나이프")->frameRender(getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).x,
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).y, _frameX, 0);
	}

	//_itemImage->frameRender(getMemDC(), 300, 300, 0, 0);
}
void knife::move(){
	//아이템이 떨어져있는 상태 = 움직일 필요없으니
	if (_itemState == DROP) return;

	if (_x > CAMERAMANAGER->getBackGroundSizeX() - _itemImage->getFrameWidth())
	{
		_itemState = DROP;
		//_x = CAMERAMANAGER->getBackGroundSizeX() - _itemImage->getFrameWidth();
		return;
	}
	_x += 5;
}