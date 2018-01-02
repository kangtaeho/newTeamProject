#pragma once
#include "gameNode.h"
#include "item.h"
#include "knife.h"
#include "bigStone.h"
#include "enemy.h"
#include "boss00.h"
#include "minion00.h"
#include "minion01.h"
#include "minion02.h"
#include "stone.h"
#include "character.h"
#include "inventory.h"
#include "enemyManager.h"
#include "money.h"
#include <vector>

/*
static enum stageState
{
READY,		//���İ��� ���� �غ���(��ȣ �߰�)
MOVING,
FIGHTING,
CLEAR
};
*/

class stage1 : public gameNode
{

private:

	vector<item*> _vItem;	//�ٴڿ� �ִ� �����۰� ���Ͱ� ������ ���� ���� ������ ����
	vector<item*> _viItem;

	RECT rc1;
	RECT* currentRC;
	image* DOOR; // ���߰�(��ö)
	RECT DOORRC; // ���߰�(��ö)

	//float doorX, doorY;
	
	item* _knife; // Į ���������� ������
	item* _stone; // �̴ϵ����� ����
	item* _bigStone; //ū ������ 
	//enemy* _enemy;
	//boss00* _boss00;
	//enemy* _minion00; //enemy��
	enemy* _boss00;
	enemy* _minion00;
	enemy* _minion01;
	enemy* _minion02;


	

	int _alpha;	//���ķ����� ���� ����

	inventory* _inven;				//�κ��丮 Ŭ���� ����

	bool _stopCharacter;			//ĳ���Ͱ� �����?(�κ��丮 ���� ���)

	stageState _ss;	//�������� ����(stdafx.h�� ���ǵǾ�����)

	enemyManager* _em;
	bool _firstWave;
	bool _secondWave;
public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();

	virtual void setMainPlayer(character* mainPlayer) { _mainPlayer = mainPlayer; }
	virtual character* getMainPlayer(){ return _mainPlayer; }
	
	void dropMoney(POINT point, int won);	//�� ��� �Լ� ���Ͱ� �׾������ �̰� ȣ���ϸ� �˴ϴ�.

	void makeEnemy();	//���� ���� �Լ�

	void characterMovement();							//ĳ���� Ű�������� �����ϴ� �Լ�

};

