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
	IMAGEMANAGER->addImage("스테이지_02", "./images/03_stage00.bmp", 5809, 1251, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스테이지_02_red", "./images/03_stage00_red.bmp", 5809, 1251, true, RGB(255, 0, 255));


	//카메라 렉트
	rc1 = RectMakeCenter(50, 300, 100, 100);
	currentRC = &rc1;
	//
	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	CAMERAMANAGER->setCameraAim(&rc1);
	return S_OK;
}

void stage3::release()
{
}

void stage3::update()
{

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (CAMERAMANAGER->getCameraCondition() != CAMERA_EFFECT)
			{
				if (CAMERAMANAGER->getCameraCondition() == CAMERA_FREE)
				{
					CAMERAMANAGER->cameraMove(false, 0);
					currentRC->bottom -= 10;
					currentRC->top -= 10;
				}
				else
				{
					currentRC->bottom -= 10;
					currentRC->top -= 10;
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
					currentRC->bottom += 10;
					currentRC->top += 10;
				}
				else {
					currentRC->bottom += 10;
					currentRC->top += 10;
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
					currentRC->left -= 10;
					currentRC->right -= 10;
				}
				else
				{
					if (currentRC->left <= 0)
					{
						currentRC->left += 10;
						currentRC->right += 10;
					}
					currentRC->left -= 10;
					currentRC->right -= 10;
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
					currentRC->left += 10;
					currentRC->right += 10;
				}
				else
				{
					if (currentRC->right >= 3456)
					{
						currentRC->left -= 10;
						currentRC->right -= 10;
					}
					currentRC->left += 10;
					currentRC->right += 10;
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

		//_enemy->update();
		//_mainPlayer->update();

		/*if (KEYMANAGER->isOnceKeyDown('P'))
		{
		SCENEMANAGER->changeScene("스테이지01");
		}*/
	

}

void stage3::render()
{
	//이걸로 카메라처리 해주센
	IMAGEMANAGER->findImage("스테이지_02")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("스테이지_02_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(rc1).x, CAMERAMANAGER->CameraRelativePoint(rc1).y, 100, 100);
	//이거 지우고
//IMAGEMANAGER->findImage("스테이지_02")->render(getMemDC(), 0, 0);
//IMAGEMANAGER->findImage("스테이지_02_red")->render(getMemDC(), 0, 0);
}
