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

	//�����
	gameNode* _currentScene;

	//�������� 1 ��
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

