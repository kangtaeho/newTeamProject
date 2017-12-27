#pragma once
#include "gameNode.h"
#include "stage1.h"

class mainGame : public gameNode
{
private:
	
	int a;
	int b;
	int c;
	int d;

	//ÇöÀç¾À
	gameNode* _currentScene;

	//½ºÅ×ÀÌÁö 1 ¾À
	gameNode* _stage1;
	//gameNode* _stage2;
	
public:
	virtual HRESULT init();			
	virtual void release();			
	virtual void update();			
	virtual void render();	




	mainGame();
	~mainGame();
};

