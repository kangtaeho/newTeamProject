#include "stdafx.h"
#include "stage1.h"


//������ �ʱ�ȭ�� ���⼭
stage1::stage1()	//���밪���� ��ġ�� ���⼭ �ʱ�ȭ, �̹����� ũ��ó�� ���𰡸� �޾Ƽ� �ʱ�ȭ �ؾ��Ѵٸ� init����
:_alpha(0),							//���� �ʱ�ȭ
_firstWave(false),					//ó�� ���̺�
_secondWave(false),					//�ι�° ���̺�
_stopCharacter(false),				//ĳ���Ͱ� �����? (�κ��丮 ų�� ���)
_rc1(RectMakeCenter(WINSIZEX/2, WINSIZEY/2, 100, 100)),	// ��ö��!!!!! ���Ⲩ �����ϸ�ȴ� ������ġ
_DOORRC(RectMakeCenter(3225, 190, 10, 10)),
_currentRC(&_rc1),
_ss(READY)
{

}


stage1::~stage1()
{
}

HRESULT stage1::init()
{
	addImage();	//����� �̹����� �߰�
	
	_DOOR->setX(3225);
	_DOOR->setY(258);
	_DOOR->setFrameX(0);
	

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
	_vItem.push_back(_knife);
	_vItem.push_back(_bigStone);

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
			SCENEMANAGER->changeScene("��������01");
			SOUNDMANAGER->stop("��������1");
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
		for (int i = 0; i < _vItem.size(); i++)
		{
			_vItem[i]->update();
		}		
		makeEnemy();
		enemyItemCollision();
	}

	_em->update();
}

void stage1::render()
{
	draw();
}

void stage1::characterMovement() {

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
	_mainPlayer->update();

	/*if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SCENEMANAGER->changeScene("��������01");
	}*/
}
void stage1::makeEnemy(){

	
	//ī�޶� Ư�� �����϶� ���� ����
	//ù ���̺갡 ���Գ� && ī�޶� Ư�� ������ �Գ�
	if (!_firstWave /*&& CAMERAMANAGER->getCameraPoint().x >=2070*/ )
	{
		_firstWave = true;
		CAMERAMANAGER->backGroundSizeSetting(2070, 648);
	//�̵��� 1���� ����
		_em->setMinion1(PointMake(1500, 400));
		_em->setMinion(PointMake(1000, 400));
		_em->setMinion2(PointMake(1200, 400));
	//_em->getVMinion()[0]->setStageMemoryLink(this);
	//ī�޶� ���� �߰�(�⼺�� ��Ź�Ѵ�) �߰� 
	//CAMERAMANAGER->setCameraCondition(CAMERA_FREE);

	}
	

	else if(_firstWave && _em->getVMinion().size() == 0)
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
		_em->setPick(PointMake(3000, 400));
	//_em->getVMinion()[0]->setStageMemoryLink(this);
	////ī�޶� ���� �߰�(�̰͵� ��Ź��) �߰�
	//CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	}

	////�ι�° ���̺�� ���Դµ� ���ʹ� �Ŵ����� ũ�Ⱑ 0�̴� --> �� ������
	else if(_secondWave && _em->getVMinion().size() == 0)
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

	_DOOR = IMAGEMANAGER->addFrameImage("��������1_��", "./images/door.bmp", 460, 155, 3, 1, true, RGB(255, 0, 255));
}

void stage1::initialization(){
	//Į�߰� //��ö
	_knife = new knife;
	_knife->init(PointMake(1000, 350));

	//���ʹ� �߰�...��  //����

	//_boss00 = new boss00;
	//_boss00->init(PointMake(500, 300));
	
	//_minion00 = new minion00;
	//_minion00->init(PointMake(800, 300));
	//
	//_minion01 = new minion01;
	//_minion01->init(PointMake(650, 300));
	//
	//_minion02 = new minion02;
	//_minion02->init(PointMake(350, 300));

	//�̴ϵ����� //��ö
	_stone = new stone;
	_stone->init(PointMake(2000, 450));

	_bigStone = new bigStone;
	_bigStone->init(PointMake(2000, 380));

	_mainPlayer = new character;
	_mainPlayer->init();

	_inven = new inventory;
	_inven->init();

	_em = new enemyManager;
	_em->init();

	_em->setCharacterMemoryAddressLink(_mainPlayer);
}

void stage1::singletonInit(){
	CAMERAMANAGER->backGroundSizeSetting(3456, 648);

	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	CAMERAMANAGER->setCameraAim(&_rc1);

	SOUNDMANAGER->play("��������1", 0.5f);
	SOUNDMANAGER->setCurrentBgmKey("��������1");
}

void stage1::draw(){
	IMAGEMANAGER->findImage("��������_00")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("��������_00_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);

	//_boss00->render();
	//_minion00->render();
	//_minion01->render();
	//_minion02->render();


	_em->render();
	_mainPlayer->render();

	//ī�޶� ��Ʈ(���� �ּ�ó���� ���� ���쵵��!)
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rc1).x, CAMERAMANAGER->CameraRelativePoint(_rc1).y, 100, 100);
	
	IMAGEMANAGER->findImage("��������1_��")->frameRender(getMemDC(),
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_DOOR->getX(), _DOOR->getY(), _DOOR->getFrameWidth(), _DOOR->getFrameHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_DOOR->getX(), _DOOR->getY(), _DOOR->getFrameWidth(), _DOOR->getFrameHeight())).y,
		_DOOR->getFrameX(), _DOOR->getFrameY());

	//�� ��Ʈ(���� �����ϵ���)
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_DOORRC).x, CAMERAMANAGER->CameraRelativePoint(_DOORRC).y, 10, 10);
	_inven->render();

	//������ ����
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render();
	}

	//���ķ����� ���� ����ȭ�� ����
	IMAGEMANAGER->findImage("����ȭ��")->alphaRender(getMemDC(), 0, 0, 255 - _alpha);


	//for (int i = 0; i < _vItem.size(); ++i) {
	//	if (_vItem.size() == 0)return;
	//
	//	setColorRect(getMemDC(), _vItem[i]->getItemRC(), 20, 20, 140);
	//}
	//
	//for (int i = 0; i < _em->getVMinion().size(); ++i) {
	//	if (_em->getVMinion().size() == 0)return;
	//
	//	setColorRect(getMemDC(), _em->getVMinion()[i]->getCollircEnemy(), 30, 50, 80);
	//}
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

			//�� �� �������̸� �浹üũ
			RECT temp;
			if (IntersectRect(&temp, &_vItem[j]->getItemRC(), &_em->getVMinion()[i]->getCollircEnemy()))
			{
				//������ ���°� �������̸� �ǰ� (continue ��� ������ ����)
				if (!_em->getVMinion()[i]->getIsGetItemEemey()) continue;
				if (_vItem[j]->getState() == 1) continue;

				//��ӻ���
				else
				{
					//���� true ����
					_em->getVMinion()[i]->setIsItemCollion(true);
				}
			}
			//�� �浹�� �⺻ false
			//else
			//{
			//	_em->getVMinion()[i]->setIsItemCollion(false);
			//}
		}
	}
}