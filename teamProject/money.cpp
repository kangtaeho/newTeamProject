#include "stdafx.h"
#include "money.h"


money::money()
{
}


money::~money()
{
}
HRESULT money::init(POINT point)
{
	//�̹��� �ʱ�ȭ
	_itemImage = IMAGEMANAGER->addFrameImage("��", "./images/money.bmp", 132, 30,4,1 ,true, RGB(255, 0, 255));
	//Ÿ�� �ʱ�ȭ
	_itemType = MONEY;
	//�� ȹ�淮
	_itemEffect = 10;
	//��ǥ
	_x = point.x; _y = point.y;
	

	//��Ÿ���� ����, ������ �ʿ����.
	_price = 0; _count = 0;


	return S_OK;
}