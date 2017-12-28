#include "stdafx.h"
#include "whitePotion.h"


whitePotion::whitePotion()
{
}


whitePotion::~whitePotion()
{
}

HRESULT whitePotion::init()
{
	//이미지 초기화
	_itemImage = IMAGEMANAGER->addImage("하얀포션", "./images/whitepotion.bmp", 35, 35, true, RGB(255, 0, 255));
	//타입 초기화
	_itemType = POTION;
	//물약 효과
	_itemEffect = 5;
	//상점가격
	_price = 96;
	//갯수
	_count = 0;

	//포션타입은 좌표가 필요없다
	//오브젝트처럼 움직일 필요가 없으니 랜더할때 지정 위치에 랜더해주면된다.
	_x = 0; _y = 0;
	

	return S_OK;
}