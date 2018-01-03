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

	addImage();

	//SCENEMANAGER->changeScene("��������00");

	//��ȣ : ���� ���۽����μ���
	SCENEMANAGER->changeScene("��ŸƮ", false);
	//SCENEMANAGER->changeScene("��������02", false);

	


	return S_OK;
}

void mainGame::release()			//�޸� ���� �Լ�
{
	gameNode::release();

	
}

void mainGame::update()				//���� �Լ�
{
	gameNode::update();
	
	if (KEYMANAGER->isOnceKeyDown('0')) {
		if (OPTION->getIsOpenOption()) {
			OPTION->closeOption();
		}
		else {
			OPTION->openOption();
		}
	}

	if (OPTION->getIsOpenOption()) {
		OPTION->update();
	}
	else {
		SCENEMANAGER->update();
	}

}

void mainGame::render()		//�׷��ִ� �Լ�(a.k.a WM_PAINT)
{
	//��� ��ȭ�� ����~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== �ǵ������� ======================
	
	

	//��ö�߰� //�����̹ڽ� ī�޶� ���� �ȹ��� ��ġ���� // 20121227 7:45
	//��ȣ : ������� ��ŸƮ �� or ��ȭ���̸� �����̹ڽ� �ȱ׸�����
	if (SCENEMANAGER->isStartScene("��ŸƮ") || SCENEMANAGER->isStartScene("1����������ȭ") || SCENEMANAGER->isStartScene("3����������ȭ" ))
	{
		SCENEMANAGER->render();
	}
	else{

		SCENEMANAGER->render();
		IMAGEMANAGER->findImage("�����̹ڽ�")->render(getMemDC(), 0, WINSIZEY - IMAGEMANAGER->findImage("�����̹ڽ�")->getHeight());

		//IMAGEMANAGER->findImage("�ǹڽ�")->render(getMemDC(), 400, 400);
		/*for (int i = 0;
			SCENEMANAGER->getCurrentScene()->getMainPlayer()->getHP(); i++)
		{
			IMAGEMANAGER->findImage("�ǹڽ�")->render(getMemDC(), 400, 400);
		}*/
	}

	//��ȣ : �̹��� ��� �����
	//IMAGEMANAGER->findImage("����")->render(getMemDC(), WINSIZEX/2 - 300, 40);
	
	OPTION->render();

	//==================== �ǵ������� =======================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
void mainGame::addImage()		//�̹̱� �߰����ִ� �Լ� ���� �̹����� ���⼭ add�ϴ°ɷ�
{
	SOUNDMANAGER->addSound("���ӽ���ȭ��", "./sounds/���ӽ���ȭ��.mp3", true, false);
	SOUNDMANAGER->addSound("��������1", "./sounds/��������1.mp3", true, true);
	SOUNDMANAGER->addSound("��������2", "./sounds/��������2.mp3", true, true);
	SOUNDMANAGER->addSound("��������3", "./sounds/��������3.mp3", true, true);
	SOUNDMANAGER->addSound("ũ��(������)", "./sounds/ũ��(������).wav", false, false);
	SOUNDMANAGER->addSound("���(�������Ҷ�)", "./sounds/���(�������Ҷ�).wav", false, false);
	SOUNDMANAGER->addSound("��(������)", "./sounds/��(������).wav", false, false);
	SOUNDMANAGER->addSound("��ġ������", "./sounds/��ġ������.wav", false, false);

	//��ö �߰� // �������� 1 �� //20171227 7:43
	SCENEMANAGER->addScene("��������00", new stage1);
	SCENEMANAGER->addScene("��������01", new stage2);

	SCENEMANAGER->addScene("��������02", new stage3);

	//��ȣ : ���ӽ���ȭ��
	SCENEMANAGER->addScene("��ŸƮ", new startscene);

	//��ȣ : 1,3�������� ��ȭȭ��
	SCENEMANAGER->addScene("1����������ȭ", new stage1Story);
	SCENEMANAGER->addScene("3����������ȭ", new stage3Story);

	IMAGEMANAGER->addImage("�����̹ڽ�", "./images/ui_box.bmp", 1152, 144, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("�ǹڽ�", "./images/hprect.bmp", 24, 24, true, RGB(255, 0, 255));

}
void mainGame::initialization()	//������ new���� �� init ���ִ� �Լ� ���� new �� init�� ���⼭ �ϴ°ɷ�
{

}
void mainGame::singletonInit()	//init���� �̱���� �������ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�		  
{

}