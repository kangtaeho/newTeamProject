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

	_itemImage = IMAGEMANAGER->addFrameImage("�̴ϵ�����", "./images/ministone.bmp", 240, 48, 5, 1, true, RGB(255, 0,255));
	_itemType = THROW;
	_itemEffect = 50;
	_x = point.x; _y = point.y;

	_price = 0; _count = 0;

	_itemState = DROP;

	_frameX = _frameCount = 0;

	_gravity =0.1;
	_isRight = true;
	//_throwPower = 1;
	return S_OK;
}

void stone::render()
{
	if (_itemState == DROP)
	{
		IMAGEMANAGER->findImage("�̴ϵ�����")->frameRender(getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).x,
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).y, 0, 0);
	}
	//���󰡴� ����
	else
	{
		IMAGEMANAGER->findImage("�̴ϵ�����")->frameRender(getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).x,
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight())).y, _frameX, 0);
	}
	//_itemImage->frameRender(getMemDC(), 300, 350, 0, 0);
}
void stone::move(){
	//�������� �������ִ� ���� = ������ �ʿ������
	if (_itemState == DROP) return;

	if (_x > CAMERAMANAGER->getBackGroundSizeX() - _itemImage->getFrameWidth()
		|| _y > _endY - _itemImage->getFrameHeight())
	{
		_itemState = DROP;
		//_x = CAMERAMANAGER->getBackGroundSizeX() - _itemImage->getFrameWidth();
		return;
	}
	if (_isRight) _x += 3;	
	else _x -= 3;

	_y -= _throwPower;
	_throwPower -= _gravity;
}