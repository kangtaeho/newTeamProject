#pragma once
#include "gameNode.h"
#include "orangePotion.h"
#include "redPotion.h"
#include "whitePotion.h"

class inventory:public gameNode
{
private:
	image* _blackWindowBmp;				// ���ȭ�� ����� ���� ������ ������ â
	image* _inventoryBmp;				// �κ��丮 �̹���
	image* _shopBmp;					// ���� �̹���
	image* _selectBoxBmp;				// ���� �ڽ�

	image* _redPotionNumberBmp;			// �������� ���� �̹���
	image* _orangePotionNumberBmp;		// ��Ȳ���� ���� �̹���
	image* _whitePotionNumberBmp;		// �Ͼ������ ���� �̹���

	POINT _selectShopPos;				// �������� ���ùڽ� ������ �� ��ǥ
	POINT _selectInvenPos;				// �κ��丮���� ���ùڽ� ������ �� ��ǥ
	
	int _currentMoney;					// ���� ���� ��

	bool _openShop;
	bool _openInventory;

	redPotion* _RPotion;
	orangePotion* _OPotion;
	whitePotion* _WPotion;

public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();

	void shopState();					//����
	void inventoryState();				//�� �κ��丮

	void openShop() { _openShop = true; }							// ��������
	void openInventory() { _openInventory = true; }					// �κ��丮����
	void closeShop() { _openShop = false; }
	void closeInventory() { _openInventory = false; }

};

