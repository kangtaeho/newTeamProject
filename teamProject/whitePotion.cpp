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
	//�̹��� �ʱ�ȭ
	_itemImage = IMAGEMANAGER->addImage("�Ͼ�����", "./images/whitepotion.bmp", 35, 35, true, RGB(255, 0, 255));
	//Ÿ�� �ʱ�ȭ
	_itemType = POTION;
	//���� ȿ��
	_itemEffect = 5;
	//��������
	_price = 96;
	//����
	_count = 0;

	//����Ÿ���� ��ǥ�� �ʿ����
	//������Ʈó�� ������ �ʿ䰡 ������ �����Ҷ� ���� ��ġ�� �������ָ�ȴ�.
	_x = 0; _y = 0;
	

	return S_OK;
}