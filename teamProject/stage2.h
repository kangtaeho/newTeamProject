#pragma once
#include "gameNode.h"
#include "character.h"

class stage2 : public gameNode
{
private:

	character* _mainCharacter;

public:
	stage2();
	~stage2();

	HRESULT init();
	void release();
	void update();
	void render();
};

