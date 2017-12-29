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

	_RPotion = new redPotion;
	_RPotion->init();
	
	return S_OK;
}

void inventory::release() {

}

void inventory::update() {

	_RPotion->update();
}

void inventory::render() {
	
	_blackWindowBmp->alphaRender(getMemDC(), 100);
	_shopBmp->render(getMemDC(), WINSIZEX / 2 - _shopBmp->getWidth() / 2, WINSIZEY / 2 - _shopBmp->getHeight() / 2);
	//_inventoryBmp->render(getMemDC(), WINSIZEX / 2 - _inventoryBmp->getWidth() / 2, WINSIZEY / 2 - _inventoryBmp->getHeight() / 2);
	
}

void inventory::shopState() {

	if (!_openShop) return;	

}

void inventory::inventoryState() {
	
	if (!_openInventory) return;

}