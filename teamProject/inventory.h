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

	int _currentMoney;

	bool _openShop;
	bool _openInventory;

public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();

	void shopState();					//����
	void inventoryState();				//�� �κ��丮

	void openShop() { _openShop = true; }						// ��������
	void openInventory() { _openInventory = true; }					// �κ��丮����
	void closeShop() { _openShop = false; }
	void closeInventory() { _openInventory = false; }

};

