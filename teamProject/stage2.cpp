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

	_boat = IMAGEMANAGER->addImage("쪽배", "./images/boat.bmp", 527, 75, true, RGB(255, 0, 255));
	
	_boat->setX(1450);
	_boat->setY(2400);

	_boatRC = RectMakeCenter(_boat->getX(), _boat->getY(), 527, 75);
	//알파값 초기화
	_alpha = 0;
	_ss = READY;

	rc1 = RectMakeCenter(760, 2300, 100, 100);
	currentRC = &rc1;

	CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	CAMERAMANAGER->setCameraAim(&rc1);

	_mainPlayer = new character;
	_mainPlayer->init();

	SOUNDMANAGER->play("스테이지2",0.5f);

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
			SOUNDMANAGER->stop("스테이지2");
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
				else if (CAMERAMANAGER->getCameraCondition() == CAMERA_STAGE2)
				{
					CAMERAMANAGER->stage2CameraFollow(true, -5);
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
				else if (CAMERAMANAGER->getCameraCondition() == CAMERA_STAGE2)
				{
					CAMERAMANAGER->stage2CameraFollow(true, 5);
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

		//카메라 위치보정을 위해 에이밍으로 바꾼후 스테이지2 카메라로 변경
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
			currentRC = &rc1;
			CAMERAMANAGER->setCameraAim(currentRC);
			CAMERAMANAGER->setCameraCondition(CAMERA_STAGE2);
		}
		if (KEYMANAGER->isOnceKeyDown('G'))
		{
			CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
			currentRC = &rc1;
			CAMERAMANAGER->setCameraAim(currentRC);
		}

		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
		}

		if (KEYMANAGER->isOnceKeyDown('P'))
		{
			SCENEMANAGER->changeScene("스테이지00"); //02 로 바꿔줘야되고
		}
	}
}

void stage2::render()
{

	IMAGEMANAGER->findImage("스테이지_01")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("스테이지_01_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);

	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(rc1).x, CAMERAMANAGER->CameraRelativePoint(rc1).y, 100, 100);

	//플레이어가 배에 닿았을때 모든키 제어 불가능하게 해주고
	//배가 플레이어랑 같이 움직여야되는데 //기성씨 부탁해요~~
	IMAGEMANAGER->findImage("쪽배")->render(getMemDC(), 
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boat->getX(), _boat->getY(), _boat->getWidth(), _boat->getHeight())).x,
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boat->getX(), _boat->getY(), _boat->getWidth(), _boat->getHeight())).y);
	//이 검은화면이 제밀 밑에 있도록 코드쳐주세요~~
	IMAGEMANAGER->findImage("검은화면")->alphaRender(getMemDC(), 0, 0, 255 - _alpha);
}
