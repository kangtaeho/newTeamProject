#pragma once
#include "gameNode.h"
#include "inventory.h"
#include "character.h" //ī�޶� ���ּ��� �⼺��~
#include "enemyManager.h"
#include "money.h"

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
	//ī�޶� ��Ʈ
	RECT _rc1;
	RECT* _currentRC;

	//���������� ��Ʈ
	image* _elevator;
	RECT _elevatorRC;

	float _elevatorX, _elevatorY; //���������� x,y��ǥ

	POINT _playerStartPoint; //�÷��̾��� ���� ��ǥ

	//�ʹ� ��Ʈ
	image* _boat;
	RECT _boatRC;

	float _boatX, _boatY; //�ʹ� x,y��ǥ

	bool _boatSwitchOn;		//��Ʈ�� �浹�߳� ??
	bool _elevatorSwitchOn; //���������� ��Ʈ �ǵ�ȳ�??

	//����

	image* _liver;
	animation* _liverAni;

	enemyManager* _em;


	

	vector<item*> _vItem;	//�ٴڿ� �ִ� �����۰� ���Ͱ� ������ ���� ���� ������ ����
	vector<item*> _viItem;	


	//�������� 1�� ���������� ���ķ����� ���� ����
	int _alpha;

	stageState _ss;	//�������� ����(stdafx.h�� ���ǵǾ�����)
	bool _stopCharacter;			//ĳ���Ͱ� �����?(�κ��丮 ���� ���)
	
	bool _firstWave, _secondWave, _thirdWave;
	//inventory* _inven;
public:
	stage2();
	~stage2();

	HRESULT init();
	void release();
	void update();
	void render();

	void boatMove();	 //��Ʈ ���� �Լ� 
	void elevatorMove(); //���� ���� �Լ�

	virtual void setMainPlayer(character* mainPlayer) { _mainPlayer = mainPlayer; }
	virtual character* getMainPlayer(){ return _mainPlayer; }

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

