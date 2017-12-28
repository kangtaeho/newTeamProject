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
	rc1 = RectMakeCenter(500, BACKGROUNDSIZEY / 2, 100, 100);
	currentRC = &rc1;

	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	CAMERAMANAGER->setCameraAim(&rc1);

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


	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (CAMERAMANAGER->getCameraCondition() != CAMERA_EFFECT)
		{
			if (CAMERAMANAGER->getCameraCondition() == CAMERA_FREE)
			{
				CAMERAMANAGER->cameraMove(false, 0);
				currentRC->bottom -= 5;
				currentRC->top -= 5;
			}
			else
			{
				currentRC->bottom -= 5;
				currentRC->top -= 5;
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (CAMERAMANAGER->getCameraCondition() != CAMERA_EFFECT)
		{
			if (CAMERAMANAGER->getCameraCondition() == CAMERA_FREE)
			{
				CAMERAMANAGER->cameraMove(false, 0);
				currentRC->bottom += 5;
				currentRC->top += 5;
			}
			else {
				currentRC->bottom += 5;
				currentRC->top += 5;
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (CAMERAMANAGER->getCameraCondition() != CAMERA_EFFECT)
		{
			if (CAMERAMANAGER->getCameraCondition() == CAMERA_FREE)
			{
				CAMERAMANAGER->cameraMove(true, 0);
				currentRC->left -= 5;
				currentRC->right -= 5;
			}
			else
			{
				if (currentRC->left <= 0)
				{
					currentRC->left += 5;
					currentRC->right += 5;
				}
				currentRC->left -= 5;
				currentRC->right -= 5;
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (CAMERAMANAGER->getCameraCondition() != CAMERA_EFFECT)
		{
			if (CAMERAMANAGER->getCameraCondition() == CAMERA_FREE)
			{
				CAMERAMANAGER->cameraMove(true, 0);
				currentRC->left += 5;
				currentRC->right += 5;
			}
			else
			{
				if (currentRC->right >= BACKGROUNDSIZEX)
				{
					currentRC->left -= 5;
					currentRC->right -= 5;
				}
				currentRC->left += 5;
				currentRC->right += 5;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		currentRC = &rc1;
		CAMERAMANAGER->setCameraAim(currentRC);
		CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);

	}

	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	}

	
}

void stage1::render()
{
	IMAGEMANAGER->findImage("스테이지_00")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	

	//유아이박스는 메인게임에다 그냥 고정박아버림 // 병철

	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(rc1).x, CAMERAMANAGER->CameraRelativePoint(rc1).y, 100, 100);
	
}
