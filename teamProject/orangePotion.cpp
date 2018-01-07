#include "stdafx.h"
#include "orangePotion.h"


orangePotion::orangePotion()
{
}


orangePotion::~orangePotion()
{
}

HRESULT orangePotion::init()
{
	/*
	image* _itemImage;		//아이템 이미지
	float _x, _y;			//아이템 좌표
	tagItemType	_itemType;	//아이템 종류
	int _itemEffect;		//아이템 효과(투척 -> 데미지 & 물약 -> 회복)
	int _price;				//아이템 가격
	int _count;				//들고있는 갯수
	*/

	//이미지 초기화
	_itemImage = IMAGEMANAGER->addImage("주황포션", "./images/orangepotion.bmp", 35, 35, true, RGB(255, 0, 255));
	//타입 초기화
	_itemType = POTION;
	//물약 효과
	_itemEffect = 5;
	//상점가격
	_price = 48;
	//갯수
	_count = 0;
	
	//포션타입은 좌표가 필요없다
	//오브젝트처럼 움직일 필요가 없으니 랜더할때 지정 위치에 랜더해주면된다.
	_x = 0; _y = 0;




	return S_OK;
}