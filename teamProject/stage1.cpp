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
	//칼추가 //병철
	_knife = new knife;
	_knife->init(PointMake(300, 300));
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
	

	//유아이박스는 메인게임에다 그냥 고정박아버림 // 병철
	
}
