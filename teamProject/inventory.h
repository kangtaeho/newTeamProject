#pragma once
#include "gameNode.h"
#include "orangePotion.h"
#include "redPotion.h"
#include "whitePotion.h"

class inventory:public gameNode
{
private:
	image* _blackWindowBmp;				// 흑백화면 만들기 위한 검정색 윈도우 창
	image* _inventoryBmp;				// 인벤토리 이미지
	image* _shopBmp;					// 상점 이미지

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

	void shopState();					//상점
	void inventoryState();				//내 인벤토리

	void openShop() { _openShop = true; }						// 상점열기
	void openInventory() { _openInventory = true; }					// 인벤토리열기
	void closeShop() { _openShop = false; }
	void closeInventory() { _openInventory = false; }

};

