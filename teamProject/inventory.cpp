#include "stdafx.h"
#include "inventory.h"


inventory::inventory()
	:_openShop(false),
	_openInventory(false)
{
}


inventory::~inventory()
{
}

HRESULT inventory::init() {

	_blackWindowBmp = IMAGEMANAGER->addImage("흑백창", "./images/backWindow.bmp", 1152, 648, true, RGB(255, 0, 255));
	_inventoryBmp = IMAGEMANAGER->addImage("인벤토리창", "./images/inventory.bmp", 280, 396, true, RGB(255, 0, 255));
	_shopBmp = IMAGEMANAGER->addImage("상점창", "./images/shop.bmp", 560, 396, true, RGB(255, 0, 255));
	_selectBoxBmp = IMAGEMANAGER->addImage("선택박스", "./images/chooseBar.bmp", 38, 39, true, RGB(255, 0, 255));

	_selectShopPos[0][0].x = 17;
	_selectShopPos[0][0].y = 107;
	_selectShopPos[0][1].x = 17;
	_selectShopPos[0][1].y = 153;
	_selectShopPos[0][2].x = 17;
	_selectShopPos[0][2].y = 199;
	_selectShopPos[1][0].x = 297;
	_selectShopPos[1][0].y = 107;
	_selectShopPos[1][1].x = 297;
	_selectShopPos[1][1].y = 153;
	_selectShopPos[1][2].x = 297;
	_selectShopPos[1][2].y = 199;

	_RPotion = new redPotion;
	_RPotion->init();
	
	return S_OK;
}

void inventory::release() {

}

void inventory::update() {

	shopState();
	inventoryState();

	_RPotion->update();
}

void inventory::render() {
	
	_blackWindowBmp->alphaRender(getMemDC(), 100);
	_shopBmp->render(getMemDC(), WINSIZEX / 2 - _shopBmp->getWidth() / 2, WINSIZEY / 2 - _shopBmp->getHeight() / 2);
	//_inventoryBmp->render(getMemDC(), WINSIZEX / 2 - _inventoryBmp->getWidth() / 2, WINSIZEY / 2 - _inventoryBmp->getHeight() / 2);
	
}

void inventory::shopState() {

	if (!_openShop) return;	

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
		_currentSelectX--;
		if (_currentSelectX < 0) _currentSelectX = 0;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
		_currentSelectX++;
		if (_currentSelectX > 1) _currentSelectX = 1;			
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
		_currentSelectY--;
		if (_currentSelectY < 0) _currentSelectY = 0;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
		_currentSelectY++;
		if (_currentSelectY >2) _currentSelectY = 2;
	}

}

void inventory::inventoryState() {
	
	if (!_openInventory) return;

}