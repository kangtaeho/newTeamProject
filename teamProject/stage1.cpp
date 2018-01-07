#include "stdafx.h"
#include "stage1.h"


//������ �ʱ�ȭ�� ���⼭
stage1::stage1()	//���밪���� ��ġ�� ���⼭ �ʱ�ȭ, �̹����� ũ��ó�� ���𰡸� �޾Ƽ� �ʱ�ȭ �ؾ��Ѵٸ� init����
	:_alpha(0),							//���� �ʱ�ȭ
	_firstWave(false),					//ó�� ���̺�
	_secondWave(false),					//�ι�° ���̺�
	_stopCharacter(false),	//ĳ���Ͱ� �����? (�κ��丮 ų�� ���)
	_rc1(RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100)),	// ��ö��!!!!! ���Ⲩ �����ϸ�ȴ� ������ġ
	_DOORRC(RectMakeCenter(3225, 230, 10, 10)),
	_currentRC(&_rc1),
	_ss(READY),
	_isOpenDoor(false)
{

}


stage1::~stage1()
{
}

HRESULT stage1::init()
{
	addImage();	//����� �̹����� �߰�
	
	_door->setX(3225);
	_door->setY(258);
	
	

	// ������������
	// ���� moving ���� ready�� ����
	//_ss = READY;

	//ī�޶� ��Ʈ
	//rc1 = RectMakeCenter(50, 300 , 100, 100);
	//_rc1 = RectMakeCenter(3225, 300, 100, 100); //��Ʈ ���տ��� ����
	//_currentRC = &_rc1;
	
	initialization();	//���� ���� new �� init ����
	
	//������ ���Ϳ� ��, Į �߰�
	_vItem.push_back(_stone);
	//_vItem.push_back(_knife);
	//_vItem.push_back(_bigStone);

	_rc1 = RectMake(_mainPlayer->getRect().left, _mainPlayer->getRect().top, 100, 100);
	_currentRC = &_rc1;

	singletonInit();

	
	


	
	//���� ������ �̷�������(���Ŀ� makeEnemy �Լ����� ����)
	//_em->setBoss(PointMake(3000,300));

	return S_OK;
}

void stage1::release()
{
}

void stage1::update()
{

	

	RECT temp;
	//�������� ���°� ü���� �Ǿ� ��������ϰ�� ���İ� ����
	if (_ss == READY)
	{
		//���İ��� 255���ϸ� ����ȭ�� ���� ����ȭ�� ����
		if (_alpha < 255)
			_alpha += 5;
		//�ִ밪�� 255�� �����ϸ� �������� ���´� moving
		else
			_ss = MOVING;
	}

	else if (IntersectRect(&temp, &_rc1, &_DOORRC) && _ss == CLEAR) //Ŭ���� ���¿��� ���� ������� ���������� �Ѱܶ� //��ö
	{

		if (_alpha >0) 
			_alpha -= 5;
		//���İ��� 0�� �Ǹ� ���� ��������							 
		else
		{
			/*_mainPlayer->setX(760);
			_mainPlayer->setY(2310);
			_mainPlayer->UpdateRect();*/
			SCENEMANAGER->changeScene("��������01");
			SOUNDMANAGER->stop("��������1");
			SOUNDMANAGER->play("��������2", 0.5f);
		}
	}

	//�������� ���°� ���� Ŭ��� �ƴҶ��� ��� �ൿ �����ϵ��� // ���� ���� �ʾ����� �߰� 
	else if (_ss == MOVING || (_ss == CLEAR && !IntersectRect(&temp, &_rc1, &_DOORRC)))
	{
		
		if (!_stopCharacter) {
			characterMovement();
		}

		if (KEYMANAGER->isOnceKeyDown('1')&&!_inven->getOpenShop()) { //�κ��丮 ����
			if (_inven->getOpenInventory()) {
				_inven->closeInventory();
				_stopCharacter = false;
			}
			else {
				_inven->openInventory();
				_stopCharacter = true;
			}
		}

		if (KEYMANAGER->isOnceKeyDown('2')&&!_inven->getOpenInventory()) { //���� ����
			if (_inven->getOpenShop()) {
				_inven->closeShop();
				_stopCharacter = false;
			}
			else {
				_inven->openShop();
				_stopCharacter = true;
			}
		}

		
		//if (KEYMANAGER->isOnceKeyDown('3')) //������ Ŭ������·� ��ȯ
		//{
		//	_ss = CLEAR; 		
		//}
		

		if (KEYMANAGER->isOnceKeyDown('4')) //������ �����
		{
			dropMoney(PointMake(200,200),10);
		}

		if (KEYMANAGER->isOnceKeyDown('5')) //������Ʈ ������ ���󰡴� ���·� ����
		{
			for (int i = 0; i < _vItem.size(); i++)
			{
				_vItem[i]->setState(true);
			}
		}

		_inven->update();
	}

	_doorAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);

	if (_ss == CLEAR)
	{
		if (!_isOpenDoor)
		{
			_doorAni->start();
			_isOpenDoor = true;
		}
	
	}



	
}

void stage1::render()
{
	draw();
}

void stage1::characterMovement() {

	ZORDERMANAGER->allClear();
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (CAMERAMANAGER->getCameraCondition() != CAMERA_EFFECT)
		{
			if (CAMERAMANAGER->getCameraCondition() == CAMERA_FREE)
			{
				CAMERAMANAGER->cameraMove(false, 0);
				_currentRC->bottom -= 4;
				_currentRC->top -= 4;
			}
			else
			{
				_currentRC->bottom -= 4;
				_currentRC->top -= 4;
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
				_currentRC->bottom += 4;
				_currentRC->top += 4;
			}
			else {
				_currentRC->bottom += 4;
				_currentRC->top += 4;
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
				_currentRC->left -= 4;
				_currentRC->right -= 4;
			}
			else
			{
				if (_currentRC->left <= 0)
				{
					_currentRC->left += 4;
					_currentRC->right += 4;
				}
				_currentRC->left -= 4;
				_currentRC->right -= 4;
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
				_currentRC->left += 4;
				_currentRC->right += 4;
			}
			else
			{
				if (_currentRC->right >= 3456)
				{
					_currentRC->left -= 4;
					_currentRC->right -= 4;
				}
				_currentRC->left += 4;
				_currentRC->right += 4;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_currentRC = &_rc1;
		CAMERAMANAGER->setCameraAim(_currentRC);
		CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);

	}

	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	}

	//_boss00->update();
	//_minion00->update();
	//_minion01->update();
	//_minion02->update();
	_rc1 = RectMake(_mainPlayer->getX() - 30, _mainPlayer->getY() - 30, 100, 100);
	_mainPlayer->update();

	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->update();

		ZORDERMANAGER->addZOrder(_vItem[i], _vItem[i]->getItemRC().bottom);
	}
	makeEnemy();
	enemyItemCollision();
	playerItemCollisioin();

		_em->update();
	
	ZORDERMANAGER->addZOrder(_mainPlayer, _mainPlayer->getZOrderY());
	//ZORDERMANAGER->addZOrder(_stone, _stone->getItemRC().bottom);
	/*if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SCENEMANAGER->changeScene("��������01");
	}*/
}
void stage1::makeEnemy() {


	//ī�޶� Ư�� �����϶� ���� ����
	//ù ���̺갡 ���Գ� && ī�޶� Ư�� ������ �Գ�
	if (!_firstWave /*&& CAMERAMANAGER->getCameraPoint().x >=2070*/)
	{
		_firstWave = true;
		CAMERAMANAGER->backGroundSizeSetting(2070, 648);
	//�̵��� 1���� ����\


		_em->setMinion1(PointMake(1500, 400),1);
		//_em->setMinion(PointMake(1000, 400));
		//_em->setMinion2(PointMake(1200, 400));
	//_em->getVMinion()[0]->setStageMemoryLink(this);
	//ī�޶� ���� �߰�(�⼺�� ��Ź�Ѵ�) �߰� 
	//CAMERAMANAGER->setCameraCondition(CAMERA_FREE);

	}


	else if (_firstWave && _em->getVMinion().size() == 0)
	{
		CAMERAMANAGER->backGroundSizeSetting(3456, 648);
		//_em->setMinion1(PointMake(1500, 300));
	////ī�޶� �ٽ� �̵�(�⼺�� ��Ź�Ѵ�) �߰�
		_currentRC = &_rc1;
		CAMERAMANAGER->setCameraAim(_currentRC);
		CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	}

	////�ι�° ���̺갡 ���Գ� && ī�޶� Ư�� �����̳�
	if (!_secondWave && _firstWave &&_em->getVMinion().size() == 0 /*&& ī�޶� Ư�������̳�*/)
	{
		////������ 1���� ����
		_secondWave = true;
		_em->setPick(PointMake(3000, 400),1);
	//_em->getVMinion()[0]->setStageMemoryLink(this);
	////ī�޶� ���� �߰�(�̰͵� ��Ź��) �߰�
	//CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
		//_em->getVMinion()[0]->setStageMemoryLink(this);
		////ī�޶� ���� �߰�(�̰͵� ��Ź��) �߰�
		//CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	}

	////�ι�° ���̺�� ���Դµ� ���ʹ� �Ŵ����� ũ�Ⱑ 0�̴� --> �� ������
	else if (_secondWave && _em->getVMinion().size() == 0)
	{
		CAMERAMANAGER->backGroundSizeSetting(3456, 648);
		//ī�޶� �ٽ� �̵�(�⼺�� ��Ź�Ѵ�) �߰� 
		_currentRC = &_rc1;
		CAMERAMANAGER->setCameraAim(_currentRC);
		CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
		_ss = CLEAR;
	}

	

	
}
//�� ��� �Լ�			���        �󸶳�
void stage1::dropMoney(POINT point, int won){

	item* tempMoney = new money;
	tempMoney->init(point, won);

	_vItem.push_back(tempMoney);
	

}
void stage1::addImage(){
	IMAGEMANAGER->addImage("��������_00", "./images/01_stage00.bmp", 3456, 648, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������_00_red", "./images/01_stage00_red.bmp", 3456, 648, true, RGB(255, 0, 255));
	//����ĥ�Ѱ� 
	IMAGEMANAGER->addImage("����ȭ��", "./images/backWindow.bmp", 1152, 648, true, RGB(255, 0, 255));

	_door = IMAGEMANAGER->addFrameImage("��������1_��", "./images/door.bmp", 460, 155, 3, 1, false, RGB(255, 0, 255));
	
	
}

void stage1::initialization()
{

	//Į�߰� //��ö
	//_knife = new knife;
	//_knife->init(PointMake(1000, 350));


	_doorAni = new animation;
	_doorAni->init(_door->getWidth(), _door->getHeight(), _door->getFrameWidth(), _door->getFrameHeight());
	_doorAni->setDefPlayFrame(false, false);
	_doorAni->setFPS(1);
	_stone = new stone;
	_stone->init(PointMake(2000, 450));

	//_bigStone = new bigStone;
	//_bigStone->init(PointMake(2000, 380));

	_mainPlayer = new character;
	_mainPlayer->init();
	_mainPlayer->setStage(IMAGEMANAGER->findImage("��������_00_red"), 1);

	_inven = new inventory;
	_inven->init();

	_em = new enemyManager;
	_em->init();

	_inven->setMainPlayerMemoryLink(_mainPlayer);
	_mainPlayer->SetMemoryEnemyManager(_em);
	_em->setCharacterMemoryAddressLink(_mainPlayer);
	_em->setStage1MemoryAddressLink(this,1);
}

void stage1::singletonInit(){
	CAMERAMANAGER->backGroundSizeSetting(3456, 648);

	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	CAMERAMANAGER->setCameraAim(&_rc1);

	SOUNDMANAGER->play("��������1", 0.5f);
	SOUNDMANAGER->setCurrentBgmKey("��������1");

	ZORDERMANAGER->addZOrder(_mainPlayer, _mainPlayer->getZOrderY());
}

void stage1::draw(){
	IMAGEMANAGER->findImage("��������_00")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);	
	if (KEYMANAGER->isToggleKey('8'))
	IMAGEMANAGER->findImage("��������_00_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	_door->aniRender(getMemDC(),
								CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_door->getX(), _door->getY(), _door->getFrameWidth(), _door->getFrameHeight())).x,
								CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_door->getX(), _door->getY(), _door->getFrameWidth(), _door->getFrameWidth())).y, _doorAni);
	
	ZORDERMANAGER->paintZOrder();
	_inven->render();


	//���ķ����� ���� ����ȭ�� ����
	IMAGEMANAGER->findImage("����ȭ��")->alphaRender(getMemDC(), 0, 0, 255 - _alpha);

}
void stage1::enemyItemCollision(){

	//���Ͱ� ������ Ȯ���� �ʿ����.
	if (_em->getVMinion().size() == 0) return;
	//�������� ������ Ȯ���� �ʿ����.
	if (_vItem.size() == 0) return;

	for (int i = 0; i < _em->getVMinion().size(); i++)
	{
		for (int j = 0; j < _vItem.size(); j++)
		{
			//��Ÿ���̸� üũ �ѱ��.
			if (_vItem[j]->getItemType() == 2) continue;

			//������¸� �ѱ��.
			if (_vItem[j]->getState() == 0) continue;

			//�� �� �������̸鼭 ���󰡴� ���¸� �浹üũ
			RECT temp;
			if (IntersectRect(&temp, &_vItem[j]->getItemRC(), &_em->getVMinion()[i]->getCollircEnemy()))
			{
				_em->getVMinion()[i]->setIsTracePlayer(5);
				_em->getVMinion()[i]->setHP(-_vItem[j]->getItemEffect());				
				_em->getVMinion()[i]->setIsHitted(true);
			}
		}
	}
}
void stage1::playerItemCollisioin(){
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
				ZORDERMANAGER->allClear();
				_inven->setCurrentMoney(_vItem[i]->getItemEffect());
				SAFE_DELETE(_vItem[i]);
				_vItem.erase(_vItem.begin() + i);
				continue;
			}
			//��ô����Ÿ���̸�
			else if (_vItem[i]->getItemType() == 1)
			{
				//�̹� ���� ��� �ִ� ���¸�
				if (_mainPlayer->getIsHanded())
				{
					++i;
					continue;
				}
				_mainPlayer->setIsItemCollision(true);
				_mainPlayer->setItem(_vItem[i]);
				if (i == 0) //��, Į ū��
				{
					_mainPlayer->setItemType(0);
				}
				if (i == 1) //��, Į ū��
				{
					_mainPlayer->setItemType(1);
				}
				if (i == 2) //��, Į ū��
				{
					_mainPlayer->setItemType(2);
				}
				break;
			}
			++i;
		}
		else
		{
			//������ ��������� �ؿ� �������
			if (_mainPlayer->getIsHanded())
			{
				++i;
				continue;
			}

			_mainPlayer->setIsItemCollision(false);
			++i;
		}

	}
	
}