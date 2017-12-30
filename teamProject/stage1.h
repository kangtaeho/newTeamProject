#pragma once
#include "gameNode.h"
#include "item.h"
#include "knife.h"
#include "enemy.h"
#include "stone.h"
#include "character.h"
#include "inventory.h"

static enum stageState 
{
	MOVING,
	FIGHTING,
	CLEAR


};

class stage1 : public gameNode
{

private:

	RECT rc1;
	RECT* currentRC;

	item* _knife; // Į ���������� ������
	enemy* _enemy;

	item* _stone; // �̴ϵ����� ����


	inventory* _inven;				//�κ��丮 Ŭ���� ����

	bool _stopCharacter;			//ĳ���Ͱ� �ح���?(�κ��丮 ���� ���)

	stageState _ss;
public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();

	virtual void setMainPlayer(character* mainPlayer) { _mainPlayer = mainPlayer; }
	virtual character* getMainPlayer(){ return _mainPlayer; }

	void characterMovement();							//ĳ���� Ű�������� �����ϴ� �Լ�
};

