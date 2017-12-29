#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()			//�ʱ�ȭ �Լ�
{
	gameNode::init(true);

	//��ö �߰� // �������� 1 �� //20171227 7:43
	SCENEMANAGER->addScene("��������00", new stage1);
	SCENEMANAGER->addScene("��������01", new stage2);

	//��ȣ : ���ӽ���ȭ��
	SCENEMANAGER->addScene("��ŸƮ", new startscene);


	//SCENEMANAGER->changeScene("��������00");

	//��ȣ : ���� ���۽����μ���
	SCENEMANAGER->changeScene("��ŸƮ", false);


	IMAGEMANAGER->addImage("�����̹ڽ�", "./images/ui_box.bmp", 1152, 144, true, RGB(255, 0, 255));

	//��ȣ : �̹��� ��� �����
	//IMAGEMANAGER->addImage("����", "./images/shop.bmp", 262, 396, true, RGB(255, 0, 255));

	_inven = new inventory;
	_inven->init();

	return S_OK;
}

void mainGame::release()			//�޸� ���� �Լ�
{
	gameNode::release();

	
}

void mainGame::update()				//���� �Լ�
{
	gameNode::update();

	

	SCENEMANAGER->update();



	


}

void mainGame::render()		//�׷��ִ� �Լ�(a.k.a WM_PAINT)
{
	//��� ��ȭ�� ����~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== �ǵ������� ======================
	
	

	//��ö�߰� //�����̹ڽ� ī�޶� ���� �ȹ��� ��ġ���� // 20121227 7:45
	//��ȣ : ������� ��ŸƮ ���̸� �����̹ڽ� �ȱ׸�����
	if (SCENEMANAGER->isStartScene("��ŸƮ"))
	{
		SCENEMANAGER->render();
	}
	else{

		SCENEMANAGER->render();
		IMAGEMANAGER->findImage("�����̹ڽ�")->render(getMemDC(), 0, WINSIZEY - IMAGEMANAGER->findImage("�����̹ڽ�")->getHeight());

	}
	

	//��ȣ : �̹��� ��� �����
	//IMAGEMANAGER->findImage("����")->render(getMemDC(), WINSIZEX/2 - 300, 40);
	
	//��ȣ : �κ��丮 ���� �����
	if (KEYMANAGER->isToggleKey('0')) {
		_inven->render();
	}

	//==================== �ǵ������� =======================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
