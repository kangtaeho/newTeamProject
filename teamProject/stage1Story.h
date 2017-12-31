#pragma once
#include "gameNode.h"
class stage1Story :
	public gameNode
{
private:
	//스토리 이미지 인덱스
	int		_index;

	//스토리 이미지 배열
	image* _storyImage[4];
public:
	stage1Story();
	~stage1Story();

	HRESULT init();
	void release();
	void update();
	void render();

};

