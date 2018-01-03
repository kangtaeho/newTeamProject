#include "stdafx.h"
#include "stage2.h"


stage2::stage2() //���밪���� ��ġ�� ���⼭ �ʱ�ȭ, �̹����� ũ��ó�� ���𰡸� �޾Ƽ� �ʱ�ȭ �ؾ��Ѵٸ� init����
: _alpha(0),
_ss(READY),
_rc1(RectMakeCenter(560, 2286, 100, 100)), //ī�޶��� ��Ʈ ��ǥ
_playerStartPoint(PointMake(760, 2310)), //�������� 2 �÷��̾� ������ǥ
_currentRC(&_rc1),
_firstWave(false),
_secondWave(false),
_thirdWave(false)
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

	_boatX = 1450;
	_boatY = 2400;

	//_boat->setX(1450);
	//_boat->setY(2400);
	_boatRC = RectMakeCenter(_boatX, _boatY, 527, 75);
	
	//_elevator->setX(5520);
	//_elevator->setY(2186);

	_elevatorX = 5520;
	_elevatorY = 2186;

	_elevatorRC = RectMakeCenter(_elevatorX, _elevatorY, 10, 10);

	_elevatorSwitchOn = false;

	_liver->setX(0);
	_liver->setY(2450);

	_frameX = _frameCount = 0;
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
					_currentRC->bottom -= 5;
					_currentRC->top -= 5;
				}
				else
				{
					_currentRC->bottom -= 5;
					_currentRC->top -= 5;
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
					_currentRC->bottom += 5;
					_currentRC->top += 5;
				}
				else {
					_currentRC->bottom += 5;
					_currentRC->top += 5;
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
					_currentRC->left -= 5;
					_currentRC->right -= 5;
				}
				else if (CAMERAMANAGER->getCameraCondition() == CAMERA_STAGE2)
				{
					CAMERAMANAGER->stage2CameraFollow(true, -5);
					_currentRC->left -= 5;
					_currentRC->right -= 5;
				}
				else
				{
					if (_currentRC->left <= 0)
					{
						_currentRC->left += 5;
						_currentRC->right += 5;
					}
					_currentRC->left -= 5;
					_currentRC->right -= 5;
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
					_currentRC->left += 5;
					_currentRC->right += 5;
				}
				else if (CAMERAMANAGER->getCameraCondition() == CAMERA_STAGE2)
				{
					CAMERAMANAGER->stage2CameraFollow(true, 5);
					_currentRC->left += 5;
					_currentRC->right += 5;
				}
				else
				{
					if (_currentRC->right >= 5795)
					{
						_currentRC->left -= 5;
						_currentRC->right -= 5;
					}
					_currentRC->left += 5;
					_currentRC->right += 5;
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

		if (KEYMANAGER->isOnceKeyDown('P'))
		{
			SCENEMANAGER->changeScene("��������00"); 
		}
	}
	

	//�������� ��Ʈ ����
	RECT temp;
	if (IntersectRect(&temp, &_rc1, &_elevatorRC)) 
	{
		_elevatorSwitchOn = true;
	}

	if (_elevatorSwitchOn && _elevatorRC.top > 140)
	{
		elevatorMove();
		_elevatorRC.top -= 5;
		_elevatorRC.bottom -= 5;

		_currentRC->top -= 5;
		_currentRC->bottom -= 5;

		CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
		_currentRC = &_rc1;
		CAMERAMANAGER->setCameraAim(_currentRC);
	}
	
	//boatMove(); 
	_frameCount++;
	if (_frameCount % 10 == 0)
	{
		_frameX++;
		if (_frameX > _liver->getMaxFrameX()) _frameX = 0;
	}
	
	_mainPlayer->update();
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
	/*
	ī�޶� Ư�� �����϶� ���� ����
	ù ���̺갡 ���Գ� && ī�޶� Ư�� ������ �Գ�
	if (!_firstWave && ī�޶� Ư�������̳�)
	{

	�̵��� 2���� ����
	_em -> setMinion()
	_em -> setMinion2()

	ī�޶� ���� �߰�(�⼺�� ��Ź�Ѵ�) �߰�
	CAMERAMANAGER->setCameraCondition(CAMERA_FREE);

	}

	ù ���̺�� ���Դµ� ���ʹ� �Ŵ����� ũ�Ⱑ 0�̴� --> �� ������
	else if(_firstWave && _em.size() == 0)
	{

	ī�޶� �ٽ� �̵�(�⼺�� ��Ź�Ѵ�) �߰�
	currentRC = &rc1;
	CAMERAMANAGER->setCameraAim(currentRC);
	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	}

	�ι�° ���̺갡 ���Գ� && ī�޶� Ư�� �����̳�
	if(!_secondWave && ī�޶� Ư�������̳�)
	{
	�̵���1 ������ 1���� ����
	_em -> setMinion2()
	_em -> setPick()
	

	ī�޶� ���� �߰�(�̰͵� ��Ź��) �߰�
	CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	}

	//�ι�° ���̺�� ���Դµ� ���ʹ� �Ŵ����� ũ�Ⱑ 0�̴� --> �� ������
	else if(_secondWave && _em.size() == 0)
	{

	ī�޶� �ٽ� �̵�(�⼺�� ��Ź�Ѵ�) �߰�
	currentRC = &rc1;
	CAMERAMANAGER->setCameraAim(currentRC);
	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	}

	if(!_thirdWave && ī�޶� Ư�������̳�)
	{
	�̵���1 ������ 1���� ����
	_em -> setMinion2()
	_em -> setPick()


	ī�޶� ���� �߰�(�̰͵� ��Ź��) �߰�
	CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	}

	//����° ���̺�� ���Դµ� ���ʹ� �Ŵ����� ũ�Ⱑ 0�̴� --> �� ������
	else if(_thirdWave && _em.size() == 0)
	{

	ī�޶� �ٽ� �̵�(�⼺�� ��Ź�Ѵ�) �߰�
	currentRC = &rc1;
	CAMERAMANAGER->setCameraAim(currentRC);
	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	}

	*/
}

void stage2::characterMovement()							//ĳ���� Ű�������� �����ϴ� �Լ�
{

}

void stage2::addImage()									//�̹̱� �߰����ִ� �Լ� ���� �̹����� ���⼭ add�ϴ°ɷ�
{
	_liver = IMAGEMANAGER->addFrameImage("����", "./images/liver_2frame.bmp", 11590, 128, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("��������_01", "./images/02_stage00.bmp", 5795, 2593, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������_01_red", "./images/02_stage00_red.bmp", 5795, 2593, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("����ȭ��", "./images/backWindow.bmp", 1152, 648, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ʹ�_red", "./images/boat_red.bmp", 527, 75, true, RGB(255, 0, 255));

	_boat = IMAGEMANAGER->addImage("�ʹ�", "./images/boat.bmp", 527, 75, true, RGB(255, 0, 255));
	_elevator = IMAGEMANAGER->addImage("����������", "./images/elevator.bmp", 210, 260, true, RGB(255, 0, 255));



	
}
void stage2::initialization()								//������ new���� �� init ���ִ� �Լ� ���� new �� init�� ���⼭ �ϴ°ɷ�
{
	_mainPlayer = new character;
	_mainPlayer->init();

	_inven = new inventory;
	_inven->init();
}
void stage2::singletonInit()								//init���� �̱���� �������ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�		  
{
	CAMERAMANAGER->backGroundSizeSetting(5795, 2593);
	CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	CAMERAMANAGER->setCameraAim(&_rc1);

	SOUNDMANAGER->play("��������2", 0.5f);
}
void stage2::draw()									//�׷��ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�								
{

	IMAGEMANAGER->findImage("����������")->render(getMemDC(),
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_elevatorX, _elevatorY, _elevator->getWidth(), _elevator->getHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_elevatorX, _elevatorY, _elevator->getWidth(), _elevator->getHeight())).y);



	IMAGEMANAGER->findImage("��������_01")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("��������_01_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);



	//���������� rc ������ �浹��
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_elevatorRC).x, CAMERAMANAGER->CameraRelativePoint(_elevatorRC).y, 10, 10);

	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rc1).x, CAMERAMANAGER->CameraRelativePoint(_rc1).y, 100, 100);


	
	//�÷��̾ �迡 ������� ���Ű ���� �Ұ����ϰ� ���ְ�
	//�谡 �÷��̾�� ���� �������ߵǴµ� //�⼺�� 8~~ //����� �ȿ�����
	IMAGEMANAGER->findImage("�ʹ�")->render(getMemDC(),
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).y);

	

	IMAGEMANAGER->findImage("�ʹ�_red")->render(getMemDC(),
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).y);

	IMAGEMANAGER->findImage("����")->frameRender(getMemDC(),
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_liver->getX(), _liver->getY(), _liver->getFrameWidth(), _liver->getFrameHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_liver->getX(), _liver->getY(), _liver->getFrameWidth(), _liver->getFrameHeight())).y, _frameX, 0);

	

	_mainPlayer->render();


	//�� ����ȭ���� ���� �ؿ� �ֵ��� �ڵ����ּ���~~
	IMAGEMANAGER->findImage("����ȭ��")->alphaRender(getMemDC(), 0, 0, 255 - _alpha);
}

void stage2::boatMove()
{
	
	_boatX += 5;

}

void stage2::elevatorMove() 
{
	_elevatorY -= 5;
}