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

	_blackWindowBmp = IMAGEMANAGER->addImage("흑백창", "./images/blackWindow.bmp", 1152, 648, true, RGB(255, 0, 255));
	_inventoryBmp = IMAGEMANAGER->addImage("인벤토리창", "./images/inventory.bmp", 280, 396, true, RGB(255, 0, 255));

	
	return S_OK;
}

void inventory::release() {

}

void inventory::update() {

}

void inventory::render() {
	
	_inventoryBmp->render(getMemDC(), WINSIZEX / 2 - _inventoryBmp->getWidth() / 2, WINSIZEY / 2 - _inventoryBmp->getHeight() / 2);
	
}

void inventory::shopState() {

	if (!_openShop) return;

}

void inventory::inventoryState() {
	
	if (!_openInventory) return;

}