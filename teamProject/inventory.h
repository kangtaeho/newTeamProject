#pragma once
#include "gameNode.h"
#include "orangePotion.h"
#include "redPotion.h"
#include "whitePotion.h"

class inventory:public gameNode
{
private:
	image* _inventoryBmp;				// �κ��丮 �̹���
	float _x, _y;						// �κ��丮 �̹����� �Ѹ� left, top ��ǥ


public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();

	void getItem();						//�������� �ֿ��� ��

};

