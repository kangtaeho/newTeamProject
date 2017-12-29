#pragma once
#include "gameNode.h"
class stage1Story :
	public gameNode
{
	image* _storyImage[4];
	int _index;
public:
	stage1Story();
	~stage1Story();

	HRESULT init();
	void release();
	void update();
	void render();
};

