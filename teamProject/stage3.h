#pragma once
#include "gameNode.h"
#include "character.h"
#include "inventory.h"
/*
static enum stageState
{
READY,		//알파값을 위한 준비모드(재호 추가)
MOVING,
FIGHTING,
CLEAR
};
*/

class stage3 : public gameNode
{
private:

	RECT rc1;
	RECT* currentRC;

	bool _stopCharacter;			//캐릭터가 멈췄니?(인벤토리 열때 사용)
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
};

