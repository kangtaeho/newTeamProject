#pragma once
#include "gameNode.h"

class option:public gameNode
{
private:
	image* _optionBmp;
	image* _bgmBmp;
	image* _effectBmp;
	image* _bgmProgBmp;
	image* _effectProgBmp;
	image* _bgmProgButtonBmp;
	image* _effectProgButtonBmp;
public:
	option();
	~option();

	HRESULT init();
	void release();
	void update();
	void render();
};

