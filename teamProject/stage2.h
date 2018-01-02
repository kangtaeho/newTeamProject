#pragma once
#include "gameNode.h"
#include "inventory.h"
#include "character.h" //ī�޶� ���ּ��� �⼺��~

/*
static enum stageState
{
READY,		//���İ��� ���� �غ���(��ȣ �߰�)
MOVING,
FIGHTING,
CLEAR
};
*/

class stage2 : public gameNode
{
private:
	RECT rc1;
	RECT* currentRC;

	image* _boat;
	RECT _boatRC;

	//�������� 1�� ���������� ���ķ����� ���� ����
	int _alpha;

	stageState _ss;	//�������� ����(stdafx.h�� ���ǵǾ�����)
	bool _stopCharacter;			//ĳ���Ͱ� �����?(�κ��丮 ���� ���)
	//inventory* _inven;
public:
	stage2();
	~stage2();

	HRESULT init();
	void release();
	void update();
	void render();

	virtual void setMainPlayer(character* mainPlayer) { _mainPlayer = mainPlayer; }
	virtual character* getMainPlayer(){ return _mainPlayer; }

	virtual void setInventory(inventory* inven) { _inven = inven; }
	virtual inventory* getInventory(){ return _inven; }
}; 

