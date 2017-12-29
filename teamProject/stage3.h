#pragma once
#include "gameNode.h"
#include "character.h"
class stage3 : public gameNode
{
private:
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

