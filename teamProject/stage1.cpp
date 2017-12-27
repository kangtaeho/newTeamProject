#include "stdafx.h"
#include "stage1.h"


stage1::stage1()
{

}


stage1::~stage1()
{
}

HRESULT stage1::init()
{
	IMAGEMANAGER->addImage("스테이지_00", "./images/01_stage00.bmp", 3456, 648, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("유아이박스", "./images/ui_box.bmp", 1152, 144, true, RGB(255, 0, 255));

	return S_OK;
}

void stage1::release()
{
}

void stage1::update()
{
}

void stage1::render()
{
	IMAGEMANAGER->findImage("스테이지_00")->render(getMemDC(),0,0);

	//병철추가 //유아이박스 카메라 영향 안받음 위치고정 // 20121227 7:45
	IMAGEMANAGER->findImage("유아이박스")->render(getMemDC(), 0, WINSIZEY - IMAGEMANAGER->findImage("유아이박스")->getHeight());
}
