#include "stdafx.h"
#include "stage3.h"


stage3::stage3()
{
}


stage3::~stage3()
{
}

HRESULT stage3::init()
{
	IMAGEMANAGER->addImage("��������_02", "./images/03_stage00.bmp", 5809, 1251, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������_02_red", "./images/03_stage00_red.bmp", 5809, 1251, true, RGB(255, 0, 255));


	//ī�޶� ��Ʈ
	//rc1 = RectMakeCenter(500, BACKGROUNDSIZEY / 2, 100, 100);
	//currentRC = &rc1;
	//
	//CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	//CAMERAMANAGER->setCameraAim(&rc1);
	return S_OK;
}

void stage3::release()
{
}

void stage3::update()
{
}

void stage3::render()
{
//IMAGEMANAGER->findImage("��������_00")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
//IMAGEMANAGER->findImage("��������_00_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
}
