#pragma once
#include "gameNode.h"
#include "inventory.h"

class stage3Story :
	public gameNode
{
private:
	//���丮 �̹��� �ε���
	int		_index;

	//���丮 �̹��� �迭
	image* _storyImage[3];
public:
	stage3Story();
	~stage3Story();


	HRESULT init();
	void release();
	void update();
	void render();

	virtual void setMainPlayer(character* mainPlayer) { _mainPlayer = mainPlayer; }
	virtual character* getMainPlayer(){ return _mainPlayer; }

	virtual void setInventory(inventory* inven) { _inven = inven; }
	virtual inventory* getInventory(){ return _inven; }
};

