#pragma once
#include "gameNode.h"
#include "startscene.h"
#include "stage1.h"
#include "stage2.h"
#include"inventory.h"

class mainGame : public gameNode
{
private:
	///����߰� fadein
	BYTE _alpha;
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

	//��ȣ �κ��丮 �׽�Ʈ
	inventory* _inven;

public:
	virtual HRESULT init();			
	virtual void release();			
	virtual void update();			
	virtual void render();	




	mainGame();
	~mainGame();
};

