#include "stdafx.h"
#include "redPotion.h"


redPotion::redPotion()
{
}


redPotion::~redPotion()
{
}


HRESULT redPotion::init()
{
	//�̹��� �ʱ�ȭ
	_itemImage = IMAGEMANAGER->addImage("��������", "./images/redpotion.bmp", 35, 35, true, RGB(255, 0, 255));
	//Ÿ�� �ʱ�ȭ
	_itemType = POTION;
	//���� ȿ��
	_itemEffect = 1;
	//��������
	_price = 5;
	//����
	_count = 0;

	//����Ÿ���� ��ǥ�� �ʿ����
	//������Ʈó�� ������ �ʿ䰡 ������ �����Ҷ� ���� ��ġ�� �������ָ�ȴ�.
	_x = 0; _y = 0;

	

	return S_OK;
}