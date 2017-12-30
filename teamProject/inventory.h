#pragma once
#include "gameNode.h"
#include "orangePotion.h"
#include "redPotion.h"
#include "whitePotion.h"

class inventory:public gameNode
{
private:
	image* _blackWindowBmp;							// 흑백화면 만들기 위한 검정색 윈도우 창
	image* _inventoryBmp;							// 인벤토리 이미지
	image* _shopBmp;								// 상점 이미지
	image* _selectBoxBmp;							// 선택 박스

	image* _RNumberBmp;								// 빨간포션 숫자 이미지
	image* _ONumberBmp;								// 주황포션 숫자 이미지
	image* _WNumberBmp;								// 하얀색포션 숫자 이미지

	POINT _selectShopPos[2][3];						// 상점에서 선택박스 움직일 때 좌표
	POINT _selectInvenPos[3];						// 인벤토리에서 선택박스 움직일 때 좌표
	
	int _currentMoney;								// 현재 가진 돈
	int _currentSelectX;							// 0일때 상점 1일때 인벤
	int _currentSelectY;							// 개별위치

	int _quickCount;								// 퀵슬롯에 들어갈 포션의 갯수
	int _quickPotion;								// 현재 퀵슬롯에 배치할 포션임팩트
													// 주황포션이 아이탬 이팩트 = 3
													// 흰포션이 5;
													// 빨간포션이 1;
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

	void shopState();								//상점
	void inventoryState();							//내 인벤토리

	void openShop() { _openShop = true; }			// 상점열기
	void openInventory() { _openInventory = true; }	// 인벤토리열기
	void closeShop() { _openShop = false; }
	void closeInventory() { _openInventory = false; }

	bool getOpenShop() { return _openShop; }
	bool getOpenInventory() { return _openInventory; }

	int getQuickCount() { return _quickCount; }
	int getQuickPotion() { return _quickPotion; }

};

