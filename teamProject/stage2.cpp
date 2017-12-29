#include "stdafx.h"
#include "stage2.h"


stage2::stage2()

{
}

stage2::~stage2()
{
}

HRESULT stage2::init()
{
	CAMERAMANAGER->backGroundSizeSetting(5795, 2593);

	IMAGEMANAGER->addImage("스테이지_01", "./images/02_stage00.bmp", 5795, 2593, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스테이지_01_red", "./images/02_stage00_red.bmp", 5795, 2593, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("쪽배", "./images/boat.bmp", 527,75,true,RGB(255,0,255) );
	rc1 = RectMakeCenter(760, 2300, 100, 100);
	currentRC = &rc1;

	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	CAMERAMANAGER->setCameraAim(&rc1);

	_mainPlayer = new character;
	_mainPlayer->init();

	return S_OK;
}

void stage2::release()
{
}

void stage2::update()
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
				if (currentRC->right >= 5795)
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

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SCENEMANAGER->changeScene("스테이지00");
	}
}

void stage2::render()
{

	IMAGEMANAGER->findImage("스테이지_01")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("스테이지_01_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(rc1).x, CAMERAMANAGER->CameraRelativePoint(rc1).y, 100, 100);
}
