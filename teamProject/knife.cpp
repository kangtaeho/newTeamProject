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
	
	_itemImage = IMAGEMANAGER->addFrameImage("������", "./images/knife.bmp", 88, 11, 8, 1, true, RGB(255, 0, 255));
	_itemType = THROW; //������ Ÿ��
	_itemEffect = 30; // ������
	_x = point.x; _y = point.y;

	_price = 0; _count = 0;

	return S_OK;
}

void knife::render()
{
	_itemImage->frameRender(getMemDC(), 300,400, 1, 0);
}
