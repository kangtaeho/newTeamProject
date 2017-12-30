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
	//���İ� �ʱ�ȭ
	_alpha = 0;

	// ������������
	// ���� moving ���� ready�� ����
	_ss = READY;

	//ī�޶� ��Ʈ
	rc1 = RectMakeCenter(500, 300 , 100, 100);
	currentRC = &rc1;

	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	CAMERAMANAGER->setCameraAim(&rc1);

	//Į�߰� //��ö
	_knife = new knife;
	_knife->init(PointMake(1000, 350));

	//���ʹ� �߰�...��  //����
	_enemy = new enemy;
	_enemy->init(PointMake(1500,400));

	//�̴ϵ����� //��ö
	_stone = new stone;
	_stone->init(PointMake(2000, 450));

	_mainPlayer = new character;
	_mainPlayer->init();

	_inven = new inventory;
	_inven->init();

	_stopCharacter = false;

	return S_OK;
}

void stage1::release()
{
}

void stage1::update()
{
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
	else if (_ss == CLEAR)
	{
		if (_alpha >0)
			_alpha -= 5;
		else
			SCENEMANAGER->changeScene("��������01");
	}
	//�������� ���°� ���� Ŭ��� �ƴҶ��� ��� �ൿ �����ϵ���
	else if (_ss != READY || _ss != CLEAR)
	{
		if (!_stopCharacter) {
			characterMovement();
		}

		if (KEYMANAGER->isOnceKeyDown('1')) { //�κ��丮 ����
			if (_inven->getOpenInventory()) {
				_inven->closeInventory();
				_stopCharacter = false;
			}
			else {
				_inven->openInventory();
				_stopCharacter = true;
			}
		}

		if (KEYMANAGER->isOnceKeyDown('2')) { //���� ����
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

		_inven->update();
	}
}

void stage1::render()
{
	IMAGEMANAGER->findImage("��������_00")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("��������_00_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	_knife->render();
	_enemy->render();
	_stone->render();

	//�����̹ڽ��� ���ΰ��ӿ��� �׳� �����ھƹ��� // ��ö
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(rc1).x, CAMERAMANAGER->CameraRelativePoint(rc1).y, 100, 100);
	
	_inven->render();

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
			else
			{
				if (currentRC->right >= 3456)
				{
					currentRC->left -= 5;
					currentRC->right -= 5;
				}
				currentRC->left += 5;
				currentRC->right += 5;
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

	_enemy->update();

	/*if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SCENEMANAGER->changeScene("��������01");
	}*/
}