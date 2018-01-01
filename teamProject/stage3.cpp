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
		SCENEMANAGER->changeScene("��������01");
		}*/
	

}

void stage3::render()
{
	//�̰ɷ� ī�޶�ó�� ���ּ�
	IMAGEMANAGER->findImage("��������_02")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("��������_02_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(rc1).x, CAMERAMANAGER->CameraRelativePoint(rc1).y, 100, 100);
	//�̰� �����
//IMAGEMANAGER->findImage("��������_02")->render(getMemDC(), 0, 0);
//IMAGEMANAGER->findImage("��������_02_red")->render(getMemDC(), 0, 0);
}
