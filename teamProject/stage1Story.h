#pragma once
#include "gameNode.h"
class stage1Story :
	public gameNode
{
private:
	//���丮 �̹��� �ε���
	int		_index;

	//���丮 �̹��� �迭
	image* _storyImage[4];
public:
	stage1Story();
	~stage1Story();

	HRESULT init();
	void release();
	void update();
	void render();

};

