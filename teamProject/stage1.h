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

	item* _knife; // 칼 스테이지로 가져옴
	enemy* _enemy;

	item* _stone; // 미니돌덩이 ㅇㅇ


	inventory* _inven;				//인벤토리 클래스 생성

	bool _stopCharacter;			//캐릭터가 멈췃니?(인벤토리 열때 사용)

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

	void characterMovement();							//캐릭터 키매지저를 관리하는 함수
};

