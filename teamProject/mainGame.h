#pragma once
#include "gameNode.h"
#include "startscene.h"
#include "stage1.h"
#include "stage2.h"

class mainGame : public gameNode
{
private:
	
	//�����
	gameNode* _currentScene;
	gameNode* _loadingScene;
	//�������� 1 ��
	gameNode* _stage1;
	gameNode* _stage2;
	

	/*
	��ȣ : ������Ŭ���� ��� ���� (�������� �׶��׶� �ٲٱ�)
	item _item; (.h����)

	�ʱ�ȭ
	_item = new money; (���� .cpp����, money���� ��������, ������Ʈ �� �ڱⰡ �ʿ��� �����ۿ� ���� ���氡��)
	_item -> init(PointMake(10, 10));

	
	�����ʱ�ȭ
	_item = new redPotion;
	_item -> init();

	���� �����ϰ��
	_item->getItemImage()->render(getMemDC(), x��ǥ, y��ǥ);

	������Ʈ, �� ������ ��� ����
	*/


public:
	virtual HRESULT init();			
	virtual void release();			
	virtual void update();			
	virtual void render();	




	mainGame();
	~mainGame();
};

