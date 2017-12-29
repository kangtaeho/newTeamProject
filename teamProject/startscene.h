#pragma once
#include "gameNode.h"
class startscene :
	public gameNode
{
	//화살표가 스타트인지 옵션인지
	bool _index;
public:
	startscene();
	~startscene();

	HRESULT init();
	void release();
	void update();
	void render();

};

