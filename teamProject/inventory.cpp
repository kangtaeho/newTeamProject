#include "stdafx.h"
#include "inventory.h"


inventory::inventory()
{
}


inventory::~inventory()
{
}

HRESULT inventory::init() {

	_inventoryBmp = IMAGEMANAGER->addImage("인벤토리창", "./images/inventory.bmp", 280, 396, true, RGB(255, 0, 255));

	return S_OK;
}

void inventory::release() {

}

void inventory::update() {

}

void inventory::render() {

}

void inventory::getItem() {

}