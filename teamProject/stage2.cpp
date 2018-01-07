#include "stdafx.h"
#include "stage2.h"


stage2::stage2() //���밪���� ��ġ�� ���⼭ �ʱ�ȭ, �̹����� ũ��ó�� ���𰡸� �޾Ƽ� �ʱ�ȭ �ؾ��Ѵٸ� init����
	: _alpha(0),
	_ss(READY),
	_rc1(RectMakeCenter(760, 2280, 100, 100)), //ī�޶��� ��Ʈ ��ǥ
	//_rc2(RectMakeCenter(760, 2280, 100, 100)),
	//_rc3(RectMakeCenter(760, 2280, 100, 100)),
	_playerStartPoint(PointMake(760, 2310)), //�������� 2 �÷��̾� ������ǥ
	_currentRC(&_rc1),
	_firstWave(false),
	_secondWave(false),
	_thirdWave(false),
	_boatSwitchOn(false),	//��� �浹�߳� ??
	_elevatorSwitchOn(false),//������ �浹�߳�??
	_finishBoat(false),
	_finishElevator(false)
{
}

stage2::~stage2()
{
}

HRESULT stage2::init()
{
	
	addImage();			//�̹��� add
	initialization();	//���� new �� init
	singletonInit();	//�̱��� init

	_boatX = 1420;
	_boatY = 2400;

	//_boat->setX(1450);
	//_boat->setY(2400);
	_boatRC = RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight());
	
	//_elevator->setX(5520);
	//_elevator->setY(2186);

	_elevatorX = 5520;
	_elevatorY = 2186;

	_elevatorRC = RectMakeCenter(_elevatorX, _elevatorY+ 30, 10, 10);



	_liver->setX(2900);
	_liver->setY(2450);

	_liverAni->start();
	


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
		_mainPlayer->setX(760);
		_mainPlayer->setY(2280);
		_mainPlayer->setStage(IMAGEMANAGER->findImage("��������_01_red"), 2);
		_mainPlayer->SetMemoryEnemyManager(_em);
		_em->setCharacterMemoryAddressLink(_mainPlayer);
		//_mainPlayer->UpdateRect();
		/*_rc1 = RectMake(_mainPlayer->getRect().left, _mainPlayer->getRect().top, 100, 100);
		_currentRC = &_rc1;*/
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
		{
			SCENEMANAGER->changeScene("3����������ȭ");
			SOUNDMANAGER->stop("��������2");
		}
	}
	//���������� �غ� or Ŭ���� ���°� �ƴҶ��� ���� ����
	else if (_ss != READY || _ss != CLEAR)
	{
		if (KEYMANAGER->isOnceKeyDown('1') && !_inven->getOpenShop()) { //�κ��丮 ����
			if (_inven->getOpenInventory()) {
				_inven->closeInventory();
				_stopCharacter = false;
			}
			else {
				_inven->openInventory();
				_stopCharacter = true;
			}
		}

		if (KEYMANAGER->isOnceKeyDown('2') && !_inven->getOpenInventory()) { //���� ����
			if (_inven->getOpenShop()) {
				_inven->closeShop();
				_stopCharacter = false;
			}
			else {
				_inven->openShop();
				_stopCharacter = true;
			}
		}
		//3Ű �Է½� ���� Ŭ������ȯ
		if (KEYMANAGER->isOnceKeyDown('3'))
		{
			_ss = CLEAR; //���� ������ Ŭ����� ��ȯ 
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (CAMERAMANAGER->getCameraCondition() != CAMERA_EFFECT)
			{
				if (CAMERAMANAGER->getCameraCondition() == CAMERA_FREE)
				{
					CAMERAMANAGER->cameraMove(false, 0);
					//_currentRC->bottom -= 5;
					//_currentRC->top -= 5;
				}
				else
				{
					//_currentRC->bottom -= 5;
					//_currentRC->top -= 5;
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
					//_currentRC->bottom += 5;
					//_currentRC->top += 5;
				}
				else {
					//_currentRC->bottom += 5;
					//_currentRC->top += 5;
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
					//_currentRC->left -= 5;
					//_currentRC->right -= 5;
				}
				else if (CAMERAMANAGER->getCameraCondition() == CAMERA_STAGE2)
				{
					CAMERAMANAGER->stage2CameraFollow(true, -5);
					//_currentRC->left -= 5;
					//_currentRC->right -= 5;
				}
				else
				{
					//if (_currentRC->left <= 0)
					//{
					//	_currentRC->left += 5;
					//	_currentRC->right += 5;
					//}
					//_currentRC->left -= 5;
					//_currentRC->right -= 5;
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
					//_currentRC->left += 5;
					//_currentRC->right += 5;
				}
				else if (CAMERAMANAGER->getCameraCondition() == CAMERA_STAGE2)
				{
					CAMERAMANAGER->stage2CameraFollow(true, 5);
					//_currentRC->left += 5;
					//_currentRC->right += 5;
				}
				else
				{
					//if (_currentRC->right >= 5795)
					//{
					//	_currentRC->left -= 5;
					//	_currentRC->right -= 5;
					//}
					//_currentRC->left += 5;
					//_currentRC->right += 5;
				}
			}
		}

		//ī�޶� ��ġ������ ���� ���̹����� �ٲ��� ��������2 ī�޶�� ����
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
			_currentRC = &_rc1;
			CAMERAMANAGER->setCameraAim(_currentRC);
			CAMERAMANAGER->setCameraCondition(CAMERA_STAGE2);
		}
		//ȣ�η�
		if (KEYMANAGER->isOnceKeyDown('G'))
		{
			CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
			_currentRC = &_rc1;
			CAMERAMANAGER->setCameraAim(_currentRC);
			
		}

		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
		}

		//if (KEYMANAGER->isOnceKeyDown('P'))
		//{
		//	SCENEMANAGER->changeScene("��������00"); 
		//}
		RECT temp;
		//��Ʈ ����
		if (IntersectRect(&temp, &_rc1, &_boatRC))
		{
			_boatSwitchOn = true;
		}

		if (_boatSwitchOn && _boatRC.right < 5230)
		{
			boatMove();
		}
		else if (_boatSwitchOn && _boatRC.right >= 5200)
		{
			_boatSwitchOn = false;
			_finishBoat = true;
		}


		//�������� 
		if (IntersectRect(&temp, &_rc1, &_elevatorRC) && _em->getVMinion().size() == 0)
		{
			_elevatorSwitchOn = true;
		}

		if (_elevatorSwitchOn && _elevatorRC.top > 140)
		{
			elevatorMove();
		}
		else if (_elevatorSwitchOn && _elevatorRC.top <= 140)
		{
			_elevatorSwitchOn = false;
			_finishElevator = true;

		}

		//�� ������ ���� �ð�
		_liverAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);

		
		_em->update();

		for (int i = 0; i < _vItem.size(); i++)
		{
			_vItem[i]->update();
		}

		makeEnemy();
		
	}
	_rc1 = RectMakeCenter(_mainPlayer->getX() - 30, _mainPlayer->getY() +25 , 100, 100);
	_rc2 = RectMakeCenter(_mainPlayer->getX(), 2280, 100, 100);
	_rc3 = RectMakeCenter(5516, 2280, 100, 100);
	if (!_boatSwitchOn && !_finishBoat)
	{
		_mainPlayer->update();
		playerItemCollisioin();
	}
	if (!_elevatorSwitchOn && _finishBoat && !_finishElevator)
	{
		_mainPlayer->update();
		playerItemCollisioin();
	}
	if (_finishElevator)
	{
		_mainPlayer->update();
		playerItemCollisioin();
	}
}

void stage2::render()
{
	draw();
}
void stage2::dropMoney(POINT point, int won)				//�� ��� �Լ� ���Ͱ� �׾������ �̰� ȣ���ϸ� �˴ϴ�.
{
	item* tempMoney = new money;
	tempMoney->init(point, won);

	_vItem.push_back(tempMoney);
}

void stage2::makeEnemy()									//���� ���� �Լ�
{
	
	/*ī�޶� Ư�� �����϶� ���� ����
	ù ���̺갡 ���Գ� && ī�޶� Ư�� ������ �Գ�*/
	if (!_firstWave)
	{
		_firstWave = true;
		//�̵��� 2���� ����
		_em->setMinion(PointMake(700, 2350), 2);
		_em->setMinion2(PointMake(550, 2350), 2);

		//ī�޶� ���� �߰�(�⼺�� ��Ź�Ѵ�) �߰�
		//CAMERAMANAGER->setCameraCondition(CAMERA_FREE);

	}

	//ù ���̺�� ���Դµ� ���ʹ� �Ŵ����� ũ�Ⱑ 0�̴� --> �� ������
	else if (_firstWave && _em->getVMinion().size() == 0)
	{

		//ī�޶� �ٽ� �̵�(�⼺�� ��Ź�Ѵ�) �߰�
		CAMERAMANAGER->backGroundSizeSetting(5795, 2593);
		_currentRC = &_rc2;
		CAMERAMANAGER->setCameraAim(_currentRC);
		CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);



	}

	//�ι�° ���̺갡 ���Գ� && ī�޶� Ư�� �����̳�
	if (!_secondWave && _firstWave&&_em->getVMinion().size() == 0 && _currentRC->right >= 5200)
	{
		//�̵���1 ������ 1���� ����
		_secondWave = true;
		//_em->setMinion(PointMake(5700, 2100), 2);
		//_em->setMinion(PointMake(5700, 2150), 2);
		//_em->setMinion(PointMake(5700, 2200), 2);
		//_em->setMinion(PointMake(5700, 2250), 2);
		_em->setMinion(PointMake(5700, 2300), 2);
		//_em->setMinion(PointMake(5700, 2350), 2);
		_em->setMinion1(PointMake(5700, 2300), 2);
		CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	}

	//�ι�° ���̺�� ���Դµ� ���ʹ� �Ŵ����� ũ�Ⱑ 0�̴� --> �� ������
	else if (_secondWave && !_thirdWave && _em->getVMinion().size() == 0 && _currentRC->left >= 400)
	{

		//ī�޶� �ٽ� �̵�(�⼺�� ��Ź�Ѵ�) �߰�
		CAMERAMANAGER->backGroundSizeSetting(5795, 2593);

		_currentRC = &_rc3;
		CAMERAMANAGER->setCameraAim(_currentRC);
		CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
		if (_elevatorSwitchOn)
		{
			CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
			_currentRC = &_rc1;
			CAMERAMANAGER->setCameraAim(_currentRC);
		}


	}

	if (!_thirdWave && _secondWave&&_em->getVMinion().size() == 0  && _finishElevator)
	{
		//�̵���1 ������ 1���� ����
		_thirdWave = true;
		//_em->setBoss(PointMake(5700, 230), 2);
		//_em->setBoss(PointMake(5700, 240), 2);
		_em->setBoss(PointMake(5700, 245), 2);
	//	_em->setBoss(PointMake(5700, 260), 2);
	/*	_em->setBoss(PointMake(5700, 260), 2);
		_em->setBoss(PointMake(5700, 260), 2);
		_em->setBoss(PointMake(5700, 260), 2);
		_em->setBoss(PointMake(5700, 260), 2);*/

		_currentRC = &_rc1;
		CAMERAMANAGER->setCameraAim(_currentRC);
		CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	}

	else if (_thirdWave && _em->getVMinion().size() == 0)
	{
		_ss = CLEAR;
		//SCENEMANAGER->changeScene("3����������ȭ",false);
	}
	//�ι�° ���̺�� ���Դµ� ���ʹ� �Ŵ����� ũ�Ⱑ 0�̴� --> �� ������
	//else if (_secondWave && _em->getVMinion().size() == 0)
	//{
	//
	//	//ī�޶� �ٽ� �̵�(�⼺�� ��Ź�Ѵ�) �߰�
	//	CAMERAMANAGER->backGroundSizeSetting(5795, 2593);
	//
	//	_currentRC = &_rc1;
	//	CAMERAMANAGER->setCameraAim(_currentRC);
	//	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	//
	//}
	//if (!_thirdWave && _secondWave&&_em->getVMinion().size() == 0&& _currentRC->top<= 140)
	//{
	////�̵���1 ������ 1���� ����
	////	_em->setBoss(PointMake(4864, 70), 2);


	//_currentRC = &_rc2;
	//CAMERAMANAGER->setCameraAim(_currentRC);
	//CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	//}

	//����° ���̺�� ���Դµ� ���ʹ� �Ŵ����� ũ�Ⱑ 0�̴� --> �� ������
	//else if(_thirdWave && _em.size() == 0)
	//{

	////ī�޶� �ٽ� �̵�(�⼺�� ��Ź�Ѵ�) �߰�
	//currentRC = &rc1;
	//CAMERAMANAGER->setCameraAim(currentRC);
	//CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	//}

	
}

void stage2::characterMovement()							//ĳ���� Ű�������� �����ϴ� �Լ�
{

}

void stage2::addImage()									//�̹̱� �߰����ִ� �Լ� ���� �̹����� ���⼭ add�ϴ°ɷ�
{
	_liver = IMAGEMANAGER->addFrameImage("����", "./images/liver_2frame.bmp", 11590, 126, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("��������_01", "./images/02_stage00.bmp", 5795, 2593, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������_01_red", "./images/02_stage00_red.bmp", 5795, 2593, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("����ȭ��", "./images/backWindow.bmp", 1152, 648, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ʹ�_red", "./images/boat_red.bmp", 527, 75, true, RGB(255, 0, 255));

	_boat = IMAGEMANAGER->addImage("�ʹ�", "./images/boat.bmp", 527, 75, true, RGB(255, 0, 255));
	_elevator = IMAGEMANAGER->addImage("����������", "./images/elevator.bmp", 210, 260, true, RGB(255, 0, 255));



	
}
void stage2::initialization()								//������ new���� �� init ���ִ� �Լ� ���� new �� init�� ���⼭ �ϴ°ɷ�
{

	//�� �ִϸ��̼�
	_liverAni = new animation;
	_liverAni->init(_liver->getWidth(), _liver->getHeight(), _liver->getFrameWidth(), _liver->getFrameHeight());
	_liverAni->setDefPlayFrame(true, true);
	_liverAni->setFPS(1);


	_mainPlayer = new character;
	_mainPlayer->init();

	_inven = new inventory;
	_inven->init();

	_em = new enemyManager;
	_em->init();

	_em->setStage2MemoryAddressLink(this,2);
}
void stage2::singletonInit()								//init���� �̱���� �������ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�		  
{
	ZORDERMANAGER->allClear();
	CAMERAMANAGER->backGroundSizeSetting(1152, 2593);
	CAMERAMANAGER->setCameraCondition(CAMERA_STAGE2);
	CAMERAMANAGER->setCameraAim(&_rc1);

	SOUNDMANAGER->play("��������2", 0.5f);
}
void stage2::draw()									//�׷��ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�								
{
	if (!_elevatorSwitchOn)
	{
		IMAGEMANAGER->findImage("����������")->render(getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_elevatorX, _elevatorY, _elevator->getWidth(), _elevator->getHeight())).x,
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_elevatorX, _elevatorY, _elevator->getWidth(), _elevator->getHeight())).y);



		IMAGEMANAGER->findImage("��������_01")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
		IMAGEMANAGER->findImage("��������_01_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);

		//���������� rc ������ �浹��
		//RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_elevatorRC).x, CAMERAMANAGER->CameraRelativePoint(_elevatorRC).y, 10, 10);
		//RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rc1).x, CAMERAMANAGER->CameraRelativePoint(_rc1).y, 100, 100);




		//�ʹ�
		_boat->render(getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).x,
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).y);

		//�ʹ� �ȼ��浹 �÷�
		IMAGEMANAGER->findImage("�ʹ�_red")->render(getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).x,
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).y);

		_liver->aniRender(getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_liver->getX(), _liver->getY(), _liver->getFrameWidth(), _liver->getFrameHeight())).x,
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_liver->getX(), _liver->getY(), _liver->getFrameWidth(), _liver->getFrameHeight())).y, _liverAni);


		_mainPlayer->render();
		_em->render();
	}
	else
	{
		IMAGEMANAGER->findImage("����������")->render(getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_elevatorX, _elevatorY, _elevator->getWidth(), _elevator->getHeight())).x,
			CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_elevatorX, _elevatorY, _elevator->getWidth(), _elevator->getHeight())).y);

		_mainPlayer->render();

		IMAGEMANAGER->findImage("��������_01")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
		IMAGEMANAGER->findImage("��������_01_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	}
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render();
	}

	_inven->render();


	//�� ����ȭ���� ���� �ؿ� �ֵ��� �ڵ����ּ���~~
	IMAGEMANAGER->findImage("����ȭ��")->alphaRender(getMemDC(), 0, 0, 255 - _alpha);
}

void stage2::boatMove()
{
	
	_boatX += 5;
	_boatRC.left += 5;
	_boatRC.right += 5;

	_currentRC->left += 5;
	_currentRC->right += 5;
	
	_mainPlayer->MakeRightStop(_mainPlayer);
	_mainPlayer->setX(_mainPlayer->getX() + 5);
	//_mainPlayer->setY(_boatRC.top);
	_mainPlayer->UpdateRect();
	
	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	_currentRC = &_rc1;
	CAMERAMANAGER->setCameraAim(_currentRC);
	

}

void stage2::elevatorMove() 
{
	_elevatorY -= 5;

	_elevatorRC.top -= 5;
	_elevatorRC.bottom -= 5;

	_currentRC->top -= 5;
	_currentRC->bottom -= 5;

	_mainPlayer->MakeRightStop(_mainPlayer);
	_mainPlayer->setY(_mainPlayer->getY() - 5);
	_mainPlayer->UpdateRect();

	
}
void stage2::playerItemCollisioin(){
	//�������� ������ Ȯ���� �ʿ����.
	if (_vItem.size() == 0) return;

	for (int i = 0; i < _vItem.size(); /*++i*/)
	{
		RECT temp;
		if (IntersectRect(&temp, &_mainPlayer->getRect(), &_vItem[i]->getAbsoluteRC()))
		{
			//��Ÿ���̸� ������ �÷��ְ� 
			if (_vItem[i]->getItemType() == 2)
			{
				_inven->setCurrentMoney(_vItem[i]->getItemEffect());
				SAFE_DELETE(_vItem[i]);
				_vItem.erase(_vItem.begin() + i);
				continue;
			}
			
			++i;
		}
		else ++i;

	}

}