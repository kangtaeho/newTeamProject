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

	IMAGEMANAGER->addImage("검은화면", "./images/backWindow.bmp", 1152, 648, true, RGB(255, 0, 255));
	//알파값 초기화
	_alpha = 0;
	_ss = READY;

	rc1 = RectMakeCenter(500, 2393, 100, 100);
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
	//스테이지가 호출되어 레디상태일경우 알파값 덧셈
	if (_ss == READY)
	{
		if (_alpha < 255)
			_alpha += 5;
		//알파값 최대면 움직이기 가능
		else
			_ss = MOVING;
	}
	else if (_ss == CLEAR)
	{
		if (_alpha >0)
			_alpha -= 5;
		else
			SCENEMANAGER->changeScene("3스테이지대화");
	}
	//스테이지가 준비 or 클리어 상태가 아닐때만 조작 가능
	else if (_ss != READY || _ss != CLEAR)
	{
		//3키 입력시 강제 클리어전환
		if (KEYMANAGER->isOnceKeyDown('3'))
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
}

void stage2::render()
{

	IMAGEMANAGER->findImage("스테이지_01")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("스테이지_01_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);

	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(rc1).x, CAMERAMANAGER->CameraRelativePoint(rc1).y, 100, 100);

	//이 검은화면이 제밀 밑에 있도록 코드쳐주세요~~
	IMAGEMANAGER->findImage("검은화면")->alphaRender(getMemDC(), 0, 0, 255 - _alpha);
}
