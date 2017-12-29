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

	CAMERAMANAGER->backGroundSizeSetting(3456, 648);

	IMAGEMANAGER->addImage("스테이지_00", "./images/01_stage00.bmp", 3456, 648, true, RGB(255, 0, 255));
	//레드칠한거 
	IMAGEMANAGER->addImage("스테이지_00_red", "./images/01_stage00_red.bmp", 3456, 648, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("흑백창", "./images/backWindow.bmp", 1152, 648, true, RGB(255, 0, 255));

	// 스테이지상태
	_ss = MOVING;
	_alpha = 255;
	//카메라 렉트
	rc1 = RectMakeCenter(50, 300 , 100, 100);
	currentRC = &rc1;

	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	CAMERAMANAGER->setCameraAim(&rc1);

	//칼추가 //병철
	_knife = new knife;
	_knife->init(PointMake(1000, 350));

	_enemy = new enemy;
	_enemy->init();

	//미니돌덩이 //병철
	_stone = new stone;
	_stone->init(PointMake(2000, 450));

	_mainPlayer = new character;
	_mainPlayer->init();
	return S_OK;
}

void stage1::release()
{
}

void stage1::update()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_ss = CLEAR;
	}

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
				if (currentRC->right >= 3456)
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

	_enemy->update();

	if (KEYMANAGER->isOnceKeyDown('P') || _alpha <=0)
	{
		SCENEMANAGER->changeScene("스테이지01");
	}
	
	
	if (_ss == CLEAR)
	{
		if (_alpha>0)
		_alpha-=5;
	}
}

void stage1::render()
{
	IMAGEMANAGER->findImage("스테이지_00")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("스테이지_00_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	_knife->render();
	_enemy->render();
	_stone->render();
	

	//유아이박스는 메인게임에다 그냥 고정박아버림 // 병철

	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(rc1).x, CAMERAMANAGER->CameraRelativePoint(rc1).y, 100, 100);

	IMAGEMANAGER->findImage("흑백창")->alphaRender(getMemDC(), 255 - _alpha);
}
 