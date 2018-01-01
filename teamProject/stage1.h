#pragma once
#include "gameNode.h"
#include "item.h"
#include "knife.h"
#include "enemy.h"
#include "boss00.h"
#include "stone.h"
#include "character.h"
#include "inventory.h"
#include "enemyManager.h"
#include "money.h"
#include <vector>

/*
static enum stageState
{
READY,		//알파값을 위한 준비모드(재호 추가)
MOVING,
FIGHTING,
CLEAR
};
*/

class stage1 : public gameNode
{

private:

	vector<item*> _vItem;	//바닥에 있는 아이템과 몬스터가 떨구는 돈을 위한 아이템 벡터
	vector<item*> _viItem;

	RECT rc1;
	RECT* currentRC;
	image* DOOR; // 문추가(병철)
	RECT DOORRC; // 문추가(병철)

	//float doorX, doorY;
	
	item* _knife; // 칼 스테이지로 가져옴
	enemy* _enemy;
	boss00* _boss00;

	item* _stone; // 미니돌덩이 ㅇㅇ

	int _alpha;	//알파렌더를 위한 변수

	inventory* _inven;				//인벤토리 클래스 생성

	bool _stopCharacter;			//캐릭터가 멈췄니?(인벤토리 열때 사용)

	stageState _ss;	//스테이지 상태(stdafx.h에 정의되어있음)

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
	
	void dropMoney(POINT point, int won);	//돈 드랍 함수 몬스터가 죽었을경우 이것 호출하면 됩니다.

	void makeEnemy();	//몬스터 생성 함수

	void characterMovement();							//캐릭터 키매지저를 관리하는 함수
	void doorCollision();
};

