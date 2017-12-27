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
	//이미지 초기화
	_itemImage = IMAGEMANAGER->addFrameImage("돈", "./images/money.bmp", 132, 30,4,1 ,true, RGB(255, 0, 255));
	//타입 초기화
	_itemType = MONEY;
	//돈 획득량
	_itemEffect = 10;
	//좌표
	_x = point.x; _y = point.y;
	

	//돈타입은 가격, 갯수가 필요없다.
	_price = 0; _count = 0;


	return S_OK;
}