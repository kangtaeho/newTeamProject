#pragma once
#include "gameNode.h"


class mainGame : public gameNode
{
private:
	
	int a;
	int b;
	int c;
	int d;

public:
	virtual HRESULT init();			
	virtual void release();			
	virtual void update();			
	virtual void render();	


	mainGame();
	~mainGame();
};

