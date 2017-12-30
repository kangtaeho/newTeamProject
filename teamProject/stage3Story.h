#pragma once
#include "gameNode.h"
class stage3Story :
	public gameNode
{
private:
	//스토리 이미지 인덱스
	int		_index;

	//스토리 이미지 배열
	image* _storyImage[3];
public:
	stage3Story();
	~stage3Story();


	HRESULT init();
	void release();
	void update();
	void render();

};

