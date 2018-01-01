#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "item.h"
#include "money.h"
#include "character.h"
#include <vector>
#include "minion00.h"
#include "boss00.h"

class enemyManager :
	public gameNode
{




private:
	//�����Ǵ� ���� ���� ����
	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _viEnemy;
	

	//���� �װ� �����Ǵ� ���� ���� ����
	vector<item*> _vItem;
	vector<item*>::iterator _viItem;

	//���� �� �÷��̾� ����
	character* _mainPlayer;



public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//�̵���
	void setMinion(void);
	//����
	void setPick(void);
	//����
	void setBoss(void);

	//�� ����� ����
	void removeEnemy(int arrNum);
	//�� ����� ����
	void removeItem(int arrNum);
	//fight!!
	void collision(void);

	//�÷��̾�� ������ ����Լ�(���� ����)
	void setCharacterMemoryAddressLink(character* mainPlayer) { _mainPlayer = mainPlayer; }

	//�÷��̾�� ������ ����� ���� ������
	vector<enemy*> getVMinion() { return _vEnemy; }

};

