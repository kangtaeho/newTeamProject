#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{

}

HRESULT item::init()
{

	return S_OK;
}

//재호 : 오브젝트(투척)용		이미지 키,    이미지 파일이름,   넓이,     높이,			X프레임,    Y프레임       좌표			데미지 
HRESULT item::init(string strKey, const char* fileName, int width, int height, int frameX, int frameY, POINT point, int itemEffect)
{
	_itemImage = IMAGEMANAGER->addFrameImage(strKey, fileName, width, height, frameX, frameY, true, RGB(255, 0, 255));
	// IMAGEMANAGER->addImage(strKey, fileName, width, height, true, RGB(255, 0, 255));
	_x = point.x;
	_y = point.y;
	_itemType = THROW;
	_itemEffect = itemEffect;
	_price = 0;


	return S_OK;
}
/*
image* _itemImage;		//아이템 이미지
float _x, _y;			//아이템 좌표
tagItemType	_itemType;	//아이템 종류
int _itemEffect;		//아이템 효과(투척 -> 데미지 & 물약 -> 회복)
int _price;				//아이템 가격
*/
//재호 : 상점(물약)용		이미지 키,    이미지 파일이름,   넓이,     높이,           좌표		회복량			가격  *** 프레임이 아닌 그냥 이미지로 만들어둠!!!!
HRESULT item::init(string strKey, const char* fileName, int width, int height, int frameX, int frameY, POINT point, int itemEffect, int price)
{
	_itemImage = IMAGEMANAGER->addFrameImage(strKey, fileName, width, height, frameX, frameY, true, RGB(255, 0, 255));
	//_itemImage = IMAGEMANAGER->addImage(strKey, fileName, width, height, true, RGB(255, 0, 255));

	_x = point.x;
	_y = point.y;
	_itemType = POTION;
	_itemEffect = itemEffect;
	_price = price;

	return S_OK;
}
void item::release()
{

}
void item::update()
{

}
void item::render()
{

}