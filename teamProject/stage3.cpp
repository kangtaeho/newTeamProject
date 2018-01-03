#include "stdafx.h"
#include "stage3.h"


stage3::stage3()
:_rc1(RectMakeCenter(100, 900, 100, 100)),	//���밪���� ��ġ�� ���⼭ �ʱ�ȭ, �̹����� ũ��ó�� ���𰡸� �޾Ƽ� �ʱ�ȭ �ؾ��Ѵٸ� init����
_currentRC(&_rc1),
_firstWave(false),
_secondWave(false),
_thirdWave(false)
{
}


stage3::~stage3()
{
}

HRESULT stage3::init()
{
	addImage();			//�̹��� add
	initialization();	//������� �ʱ�ȭ(ex. ������ ��)
	singletonInit();	//�̱��� �ʱ�ȭ(ex. ī�޶� or �������� ����)


	_vItem.push_back(_stone);
	//_vItem.push_back(_tire);
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
					_currentRC->bottom -= 10;
					_currentRC->top -= 10;
				}
				else
				{
					_currentRC->bottom -= 10;
					_currentRC->top -= 10;
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
					_currentRC->bottom += 10;
					_currentRC->top += 10;
				}
				else {
					_currentRC->bottom += 10;
					_currentRC->top += 10;
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
					_currentRC->left -= 10;
					_currentRC->right -= 10;
				}
				else if (CAMERAMANAGER->getCameraCondition() == CAMERA_STAGE2)
				{
					CAMERAMANAGER->stage2CameraFollow(true, -10);
					_currentRC->left -= 10;
					_currentRC->right -= 10;
				}
				else
				{
					if (_currentRC->left <= 0)
					{
						_currentRC->left += 10;
						_currentRC->right += 10;
					}
					_currentRC->left -= 10;
					_currentRC->right -= 10;
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
					_currentRC->left += 10;
					_currentRC->right += 10;
				}
				else if (CAMERAMANAGER->getCameraCondition() == CAMERA_STAGE2)
				{
					CAMERAMANAGER->stage2CameraFollow(true, 10);
					_currentRC->left += 10;
					_currentRC->right += 10;
				}
				else
				{
					if (_currentRC->right >= 5550)
					{
						_currentRC->left -= 10;
						_currentRC->right -= 10;
					}
					_currentRC->left += 10;
					_currentRC->right += 10;
				}
			}
		}

		if (KEYMANAGER->isOnceKeyDown('G'))
		{
			_currentRC = &_rc1;
			CAMERAMANAGER->setCameraAim(_currentRC);
			CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);

		}

		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
		}
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
			_currentRC = &_rc1;
			CAMERAMANAGER->setCameraAim(_currentRC);
			CAMERAMANAGER->setCameraCondition(CAMERA_STAGE2);
		}
		//_enemy->update();
		//_mainPlayer->update();

		/*if (KEYMANAGER->isOnceKeyDown('P'))
		{
		SCENEMANAGER->changeScene("��������01");
		}*/
	


		for (int i = 0; i < _vItem.size(); i++)
		{
			_vItem[i]->update();
		}
}

void stage3::render()
{
	draw();
	//�̰� �����
//IMAGEMANAGER->findImage("��������_02")->render(getMemDC(), 0, 0);
//IMAGEMANAGER->findImage("��������_02_red")->render(getMemDC(), 0, 0);
}
void stage3::dropMoney(POINT point, int won)	//�� ��� �Լ� ���Ͱ� �׾������ �̰� ȣ���ϸ� �˴ϴ�.
{
	item* tempMoney = new money;
	tempMoney->init(point, won);

	_vItem.push_back(tempMoney);
}

void stage3::makeEnemy()	//���� ���� �Լ�
{

}

void stage3::characterMovement()							//ĳ���� Ű�������� �����ϴ� �Լ�
{

}

void stage3::addImage()		//�̹̱� �߰����ִ� �Լ� ���� �̹����� ���⼭ add�ϴ°ɷ�
{
	IMAGEMANAGER->addImage("��������_02", "./images/03_stage00.bmp", 5809, 1251, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������_02_red", "./images/03_stage00_red.bmp", 5809, 1251, true, RGB(255, 0, 255));

}
void stage3::initialization()	//������ new���� �� init ���ִ� �Լ� ���� new �� init�� ���⼭ �ϴ°ɷ�
{


//_tire = new tire;
//_tire->init(PointMake(300, 1000));

	_stone = new stone;
	_stone->init(PointMake(300, 1000));

	_inven = new inventory;
	_inven->init();
}
void stage3::singletonInit()	//init���� �̱���� �������ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�		  
{
	CAMERAMANAGER->backGroundSizeSetting(5809, 1251);

	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	CAMERAMANAGER->setCameraAim(&_rc1);
}
void stage3::draw()			//�׷��ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�								
{
	//�̰ɷ� ī�޶�ó�� ���ּ�
	IMAGEMANAGER->findImage("��������_02")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("��������_02_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rc1).x, CAMERAMANAGER->CameraRelativePoint(_rc1).y, 100, 100);
	_inven->render();

	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render();
	}
}