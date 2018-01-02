#pragma once
#include "gameNode.h"
#include "inventory.h"
#include "character.h" //카메라 해주세요 기성씨~

/*
static enum stageState
{
READY,		//알파값을 위한 준비모드(재호 추가)
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

	//스테이지 1과 마찬가지로 알파렌더를 위한 변수
	int _alpha;

	stageState _ss;	//스테이지 상태(stdafx.h에 정의되어있음)
	bool _stopCharacter;			//캐릭터가 멈췄니?(인벤토리 열때 사용)
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

