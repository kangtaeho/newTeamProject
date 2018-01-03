#include "stdafx.h"
#include "stage3.h"


stage3::stage3()
:_rc1(RectMakeCenter(100, 900, 100, 100)),	//절대값같은 수치는 여기서 초기화, 이미지의 크기처럼 무언가를 받아서 초기화 해야한다면 init에서
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
	addImage();			//이미지 add
	initialization();	//멤버변수 초기화(ex. 아이템 등)
	singletonInit();	//싱글톤 초기화(ex. 카메라 or 스테이지 사운드)


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
		SCENEMANAGER->changeScene("스테이지01");
		}*/
	


		for (int i = 0; i < _vItem.size(); i++)
		{
			_vItem[i]->update();
		}
}

void stage3::render()
{
	draw();
	//이거 지우고
//IMAGEMANAGER->findImage("스테이지_02")->render(getMemDC(), 0, 0);
//IMAGEMANAGER->findImage("스테이지_02_red")->render(getMemDC(), 0, 0);
}
void stage3::dropMoney(POINT point, int won)	//돈 드랍 함수 몬스터가 죽었을경우 이것 호출하면 됩니다.
{
	item* tempMoney = new money;
	tempMoney->init(point, won);

	_vItem.push_back(tempMoney);
}

void stage3::makeEnemy()	//몬스터 생성 함수
{

}

void stage3::characterMovement()							//캐릭터 키매지저를 관리하는 함수
{

}

void stage3::addImage()		//이미기 추가해주는 함수 이후 이미지는 여기서 add하는걸로
{
	IMAGEMANAGER->addImage("스테이지_02", "./images/03_stage00.bmp", 5809, 1251, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스테이지_02_red", "./images/03_stage00_red.bmp", 5809, 1251, true, RGB(255, 0, 255));

}
void stage3::initialization()	//변수들 new선언 및 init 해주는 함수 이후 new 및 init은 여기서 하는걸로
{


//_tire = new tire;
//_tire->init(PointMake(300, 1000));

	_stone = new stone;
	_stone->init(PointMake(300, 1000));

	_inven = new inventory;
	_inven->init();
}
void stage3::singletonInit()	//init에서 싱글톤들 세팅해주는 함수 이후 세팅은 여기서 하는걸로		  
{
	CAMERAMANAGER->backGroundSizeSetting(5809, 1251);

	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	CAMERAMANAGER->setCameraAim(&_rc1);
}
void stage3::draw()			//그려주는 함수 이후 렌더는 여기서 하는걸로								
{
	//이걸로 카메라처리 해주센
	IMAGEMANAGER->findImage("스테이지_02")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("스테이지_02_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rc1).x, CAMERAMANAGER->CameraRelativePoint(_rc1).y, 100, 100);
	_inven->render();

	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render();
	}
}