#pragma once
#include "gameNode.h"
#include "character.h"

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
public:
	stage3();
	~stage3();

	HRESULT init();
	void release();
	void update();
	void render();
	
	virtual void setMainPlayer(character* mainPlayer) { _mainPlayer = mainPlayer; }
	virtual character* getMainPlayer() { return _mainPlayer; }
};

