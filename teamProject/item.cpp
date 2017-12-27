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

//������Ʈ(��ô)��		�̹��� Ű,    �̹��� �����̸�,   ����,     ����,   ��ǥ			������ 
HRESULT item::init(string strKey, const char* fileName, int width, int height, POINT point, int itemEffect)
{
	_itemImage = IMAGEMANAGER->addImage(strKey, fileName, width, height, true, RGB(255, 0, 255));
	_x = point.x;
	_y = point.y;
	_itemType = THROW;
	_itemEffect = itemEffect;
	_price = 0;


	return S_OK;
}
/*
image* _itemImage;		//������ �̹���
float _x, _y;			//������ ��ǥ
tagItemType	_itemType;	//������ ����
int _itemEffect;		//������ ȿ��(��ô -> ������ & ���� -> ȸ��)
int _price;				//������ ����
*/
//����(����)��		�̹��� Ű,    �̹��� �����̸�,   ����,     ����,           ��ǥ		ȸ����			����  *** �������� �ƴ� �׳� �̹����� ������!!!!
HRESULT item::init(string strKey, const char* fileName, int width, int height, POINT point, int itemEffect, int price)
{
	_itemImage = IMAGEMANAGER->addImage(strKey, fileName, width, height, true, RGB(255, 0, 255));
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