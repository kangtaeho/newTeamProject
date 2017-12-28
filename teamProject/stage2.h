#pragma once
#include "gameNode.h"
#include "character.h" //카메라 해주세요 기성씨~

class stage2 : public gameNode
{
private:


public:
	stage2();
	~stage2();

	HRESULT init();
	void release();
	void update();
	void render();

	virtual void setMainPlayer(character* mainPlayer) { _mainPlayer = mainPlayer; }
	virtual character* getMainPlayer(){ return _mainPlayer; }
}; 

