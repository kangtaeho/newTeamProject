#pragma once
#include "gameNode.h"
#include "orangePotion.h"
#include "redPotion.h"
#include "whitePotion.h"

class inventory:public gameNode
{
private:
	image* _inventoryBmp;				// 인벤토리 이미지
	float _x, _y;						// 인벤토리 이미지를 뿌릴 left, top 좌표


public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();

	void getItem();						//아이탬을 주웠을 때

};

