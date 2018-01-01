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

	IMAGEMANAGER->addImage("��������_01", "./images/02_stage00.bmp", 5795, 2593, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������_01_red", "./images/02_stage00_red.bmp", 5795, 2593, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("����ȭ��", "./images/backWindow.bmp", 1152, 648, true, RGB(255, 0, 255));

	_boat = IMAGEMANAGER->addImage("�ʹ�", "./images/boat.bmp", 527, 75, true, RGB(255, 0, 255));
	
	_boat->setX(1450);
	_boat->setY(2400);

	_boatRC = RectMakeCenter(_boat->getX(), _boat->getY(), 527, 75);
	//���İ� �ʱ�ȭ
	_alpha = 0;
	_ss = READY;

	rc1 = RectMakeCenter(760, 2300, 100, 100);
	currentRC = &rc1;

	CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	CAMERAMANAGER->setCameraAim(&rc1);

	_mainPlayer = new character;
	_mainPlayer->init();

	SOUNDMANAGER->play("��������2",0.5f);

	return S_OK;
}

void stage2::release()
{
}

void stage2::update()
{
	//���������� ȣ��Ǿ� ��������ϰ�� ���İ� ����
	if (_ss == READY)
	{
		if (_alpha < 255)
			_alpha += 5;
		//���İ� �ִ�� �����̱� ����
		else
			_ss = MOVING;
	}
	else if (_ss == CLEAR)
	{
		if (_alpha >0)
			_alpha -= 5;
		else
			SCENEMANAGER->changeScene("3����������ȭ");
			SOUNDMANAGER->stop("��������2");
	}
	//���������� �غ� or Ŭ���� ���°� �ƴҶ��� ���� ����
	else if (_ss != READY || _ss != CLEAR)
	{
		//3Ű �Է½� ���� Ŭ������ȯ
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

		//ī�޶� ��ġ������ ���� ���̹����� �ٲ��� ��������2 ī�޶�� ����
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
			SCENEMANAGER->changeScene("��������00"); //02 �� �ٲ���ߵǰ�
		}
	}
}

void stage2::render()
{

	IMAGEMANAGER->findImage("��������_01")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("��������_01_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);

	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(rc1).x, CAMERAMANAGER->CameraRelativePoint(rc1).y, 100, 100);

	//�÷��̾ �迡 ������� ���Ű ���� �Ұ����ϰ� ���ְ�
	//�谡 �÷��̾�� ���� �������ߵǴµ� //�⼺�� ��Ź�ؿ�~~
	IMAGEMANAGER->findImage("�ʹ�")->render(getMemDC(), 
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boat->getX(), _boat->getY(), _boat->getWidth(), _boat->getHeight())).x,
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boat->getX(), _boat->getY(), _boat->getWidth(), _boat->getHeight())).y);
	//�� ����ȭ���� ���� �ؿ� �ֵ��� �ڵ����ּ���~~
	IMAGEMANAGER->findImage("����ȭ��")->alphaRender(getMemDC(), 0, 0, 255 - _alpha);
}
