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
	image* _selectBoxBmp;				// 선택 박스

	image* _redPotionNumberBmp;			// 빨간포션 숫자 이미지
	image* _orangePotionNumberBmp;		// 주황포션 숫자 이미지
	image* _whitePotionNumberBmp;		// 하얀색포션 숫자 이미지

	POINT _selectShopPos;				// 상점에서 선택박스 움직일 때 좌표
	POINT _selectInvenPos;				// 인벤토리에서 선택박스 움직일 때 좌표
	
	int _currentMoney;					// 현재 가진 돈

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

	void shopState();					//상점
	void inventoryState();				//내 인벤토리

	void openShop() { _openShop = true; }							// 상점열기
	void openInventory() { _openInventory = true; }					// 인벤토리열기
	void closeShop() { _openShop = false; }
	void closeInventory() { _openInventory = false; }

};

