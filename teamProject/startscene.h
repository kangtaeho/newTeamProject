#pragma once
#include "gameNode.h"
class startscene :
	public gameNode
{
public:
	startscene();
	~startscene();

	HRESULT init();
	void release();
	void update();
	void render();

};

