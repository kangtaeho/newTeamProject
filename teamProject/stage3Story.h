#pragma once
#include "gameNode.h"
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

};

