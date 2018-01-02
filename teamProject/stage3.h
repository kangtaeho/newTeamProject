#pragma once
#include "gameNode.h"
#include "character.h"
#include "inventory.h"
#include "money.h"
#include "stone.h"
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

class stage3 : public gameNode
{
private:

	RECT _rc1;
	RECT* _currentRC;

	bool _stopCharacter;			//ĳ���Ͱ� �����?(�κ��丮 ���� ���)

	vector<item*> _vItem;	//�ٴڿ� �ִ� �����۰� ���Ͱ� ������ ���� ���� ������ ����
	vector<item*> _viItem;

	item* _stone; //�̴ϵ����� 

	bool _firstWave, _secondWave, _thirdWave;
public:
	stage3();
	~stage3();

	HRESULT init();
	void release();
	void update();
	void render();
	
	virtual void setMainPlayer(character* mainPlayer) { _mainPlayer = mainPlayer; }
	virtual character* getMainPlayer() { return _mainPlayer; }

	virtual void setInventory(inventory* inven) { _inven = inven; }
	virtual inventory* getInventory(){ return _inven; }

	void dropMoney(POINT point, int won);	//�� ��� �Լ� ���Ͱ� �׾������ �̰� ȣ���ϸ� �˴ϴ�.

	void makeEnemy();	//���� ���� �Լ�

	void characterMovement();							//ĳ���� Ű�������� �����ϴ� �Լ�

	void addImage();		//�̹̱� �߰����ִ� �Լ� ���� �̹����� ���⼭ add�ϴ°ɷ�
	void initialization();	//������ new���� �� init ���ִ� �Լ� ���� new �� init�� ���⼭ �ϴ°ɷ�
	void singletonInit();	//init���� �̱���� �������ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�
	void draw();			//�׷��ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�

};

