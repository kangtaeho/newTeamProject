#pragma once
#include "gameNode.h"
#include "item.h"
#include "money.h"
#include "character.h"
#include "minion00.h"
#include "minion01.h"
#include "minion02.h"
#include "boss00.h"
#include "minion01.h"
#include <vector>


class stage1;
class stage2;
class stage3;

class enemyManager :public gameNode
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

	stage1* _stage1;
	stage2* _stage2;
	//stage3* _stage3;
	int _stageNum;

	//minion01* _mini;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//�̵���
	void setMinion(POINT point,int stageCount);
	void setMinion1(POINT point, int stageCount);
	void setMinion2(POINT point, int stageCount);
	//����
	void setPick(POINT point, int stageCount);
	//����
	void setBoss(POINT point, int stageCount);

	//�� ����� ����
	void removeEnemy(int arrNum);
	//�� ����� ����
	void removeItem(int arrNum);
	//fight!!
	void collision(void);

	//�÷��̾�� ������ ����Լ�(���� ����)
	void setCharacterMemoryAddressLink(character* mainPlayer) { _mainPlayer = mainPlayer; }
	//�������� ���� ����Լ�
	void setStage1MemoryAddressLink(stage1* stage1, int stageNum);
	void setStage2MemoryAddressLink(stage2* stage2, int stageNum);
	/*void setStage3MemoryAddressLink(stage3* stage3, int stageNum);*/

	//�÷��̾�� ������ ����� ���� ������
	vector<enemy*> getVMinion() { return _vEnemy; }

	void traceCharacter();
	void deadEnemy();

};

