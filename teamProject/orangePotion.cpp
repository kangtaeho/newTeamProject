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
	image* _itemImage;		//������ �̹���
	float _x, _y;			//������ ��ǥ
	tagItemType	_itemType;	//������ ����
	int _itemEffect;		//������ ȿ��(��ô -> ������ & ���� -> ȸ��)
	int _price;				//������ ����
	int _count;				//����ִ� ����
	*/

	//�̹��� �ʱ�ȭ
	_itemImage = IMAGEMANAGER->addImage("��Ȳ����", "./images/orangepotion.bmp", 35, 35, true, RGB(255, 0, 255));
	//Ÿ�� �ʱ�ȭ
	_itemType = POTION;
	//���� ȿ��
	_itemEffect = 5;
	//��������
	_price = 48;
	//����
	_count = 0;
	
	//����Ÿ���� ��ǥ�� �ʿ����
	//������Ʈó�� ������ �ʿ䰡 ������ �����Ҷ� ���� ��ġ�� �������ָ�ȴ�.
	_x = 0; _y = 0;




	return S_OK;
}