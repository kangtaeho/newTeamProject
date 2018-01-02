#include "stdafx.h"
#include "stage1.h"


stage1::stage1()
{

}


stage1::~stage1()
{
}

HRESULT stage1::init()
{

	CAMERAMANAGER->backGroundSizeSetting(3456, 648);

	IMAGEMANAGER->addImage("��������_00", "./images/01_stage00.bmp", 3456, 648, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������_00_red", "./images/01_stage00_red.bmp", 3456, 648, true, RGB(255, 0, 255));
	//����ĥ�Ѱ� 
	IMAGEMANAGER->addImage("����ȭ��", "./images/backWindow.bmp", 1152, 648, true, RGB(255, 0, 255));

	DOOR = IMAGEMANAGER->addFrameImage("��������1_��", "./images/door.bmp", 460, 155, 3, 1, true, RGB(255, 0, 255));
	DOOR->setX(3225);
	DOOR->setY(258);




	DOOR->setFrameX(0);
	DOORRC = RectMakeCenter(3225, 190, 10, 10);

	//DOORRC = RectMakeCenter(1000, 300, 200, 200);

	
	//���İ�,���̺����� �ʱ�ȭ
	_alpha = _firstWave = _secondWave = 0;

	// ������������
	// ���� moving ���� ready�� ����
	_ss = READY;

	//ī�޶� ��Ʈ
	//rc1 = RectMakeCenter(50, 300 , 100, 100);
	rc1 = RectMakeCenter(3225, 300, 100, 100); //��Ʈ ���տ��� ����
	currentRC = &rc1;

	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	CAMERAMANAGER->setCameraAim(&rc1);

	//Į�߰� //��ö
	_knife = new knife;
	_knife->init(PointMake(1000, 350));

	//���ʹ� �߰�...��  //����

	/*_minion00 = new minion00;
	_minion00->init(PointMake(300 , 300 ));*/

	_boss00 = new boss00;
	_boss00->init(PointMake(500,300));

	_minion00 = new minion00;
	_minion00->init(PointMake(800, 300));

	_minion01 = new minion01;
	_minion01->init(PointMake(500, 500));

	//_minion02 = new minion02;
	//_minion02->init(PointMake(800, 500));

	//�̴ϵ����� //��ö
	_stone = new stone;
	_stone->init(PointMake(2000, 450));

	_bigStone = new bigStone;
	_bigStone->init(PointMake(2000, 380));

	_mainPlayer = new character;
	_mainPlayer->init();

	_inven = new inventory;
	_inven->init();

	_stopCharacter = false;

	_em = new enemyManager;
	_em->init();

	//������ ���Ϳ� ��, Į �߰�
	_vItem.push_back(_stone);
	_vItem.push_back(_knife);
	_vItem.push_back(_bigStone);

	SOUNDMANAGER->play("��������1",0.5f);
	SOUNDMANAGER->setCurrentBgmKey("��������1");

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
	//�������� ���°� ���������� �Ѿ�°��

	//else if (_ss == CLEAR)
	//{															
	//	//���İ� ���ҽ��� ����ȭ�� ��Ÿ���鼭						   
	//	if (_alpha >0)											
	//		_alpha -= 5;										
	//	//���İ��� 0�� �Ǹ� ���� ��������							 
	//	else													
	//SCENEMANAGER->changeScene("��������01");
	//}

	//�������� ���°� ���� Ŭ��� �ƴҶ��� ��� �ൿ �����ϵ��� // ���� ���� �ʾ����� �߰� 
	else if (_ss ==  MOVING || (_ss == CLEAR && !IntersectRect(&temp, &rc1, &DOORRC)))
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

		
		if (KEYMANAGER->isOnceKeyDown('3')) //������ Ŭ������·� ��ȯ
		{
			_ss = CLEAR; 
			
			
		}
		

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
		
		
	}

	//RECT temp;
	if (IntersectRect(&temp, &rc1, &DOORRC) && _ss == CLEAR) //Ŭ���� ���¿��� ���� ������� ���������� �Ѱܶ� //��ö
	{

		if (_alpha >0)
			_alpha -= 5;
		//���İ��� 0�� �Ǹ� ���� ��������							 
		else
			SCENEMANAGER->changeScene("��������01");
			SOUNDMANAGER->stop("��������1");
	}
}

void stage1::render()
{
	IMAGEMANAGER->findImage("��������_00")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("��������_00_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	//_knife->render();
	//_minion00->render();
	_boss00->render();
	_minion00->render();
	_minion01->render();
	//_minion02->render();
	//_stone->render();

	_mainPlayer->render();
	
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(rc1).x, CAMERAMANAGER->CameraRelativePoint(rc1).y, 100, 100);

	


		IMAGEMANAGER->findImage("��������1_��")->frameRender(getMemDC(), 
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(DOOR->getX(), DOOR->getY(), DOOR->getFrameWidth(), DOOR->getFrameHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(DOOR->getX(), DOOR->getY(), DOOR->getFrameWidth(), DOOR->getFrameHeight())).y, DOOR->getFrameX(), DOOR->getFrameY());

	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(DOORRC).x, CAMERAMANAGER->CameraRelativePoint(DOORRC).y, 10, 10);
	_inven->render();

	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render();
	}

	IMAGEMANAGER->findImage("����ȭ��")->alphaRender(getMemDC(), 0, 0, 255-_alpha);

}

void stage1::characterMovement() {

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

	//_minion00->update();
	_boss00->update();
	_minion00->update();
	_minion01->update();
	//_minion02->update();
	_mainPlayer->update();

	/*if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SCENEMANAGER->changeScene("��������01");
	}*/
}
void stage1::makeEnemy(){

	/*
	ī�޶� Ư�� �����϶� ���� ����
	ù ���̺갡 ���Գ� && ī�޶� Ư�� ������ �Գ�
	if (!firstWave && ī�޶� Ư�������̳�)
	{

	�̵��� 1���� ����
	_em -> setMinion()

	ī�޶� ���� �߰�(�⼺�� ��Ź�Ѵ�)


	}

	ù ���̺�� ���Դµ� ���ʹ� �Ŵ����� ũ�Ⱑ 0�̴� --> �� ������
	else if(firstWave && _em.size() == 0)
	{

	ī�޶� �ٽ� �̵�(�⼺�� ��Ź�Ѵ�)

	}

	�ι�° ���̺갡 ���Գ� && ī�޶� Ư�� �����̳�
	if(!secondWave && ī�޶� Ư�������̳�)
	{
	������ 1���� ����
	_em -> setPick()

	ī�޶� ���� �߰�(�̰͵� ��Ź��)
	}

	//�ι�° ���̺�� ���Դµ� ���ʹ� �Ŵ����� ũ�Ⱑ 0�̴� --> �� ������
	else if(secondWave && _em.size() == 0)
	{

	ī�޶� �ٽ� �̵�(�⼺�� ��Ź�Ѵ�)

	}

	*/
}
//�� ��� �Լ�			���        �󸶳�
void stage1::dropMoney(POINT point, int won){

	item* tempMoney = new money;
	tempMoney->init(point, won);

	_vItem.push_back(tempMoney);

}