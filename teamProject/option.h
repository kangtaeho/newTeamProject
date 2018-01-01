#pragma once
#include "gameNode.h"

class option:public gameNode
{
private:
	image* _blackWindow;
	image* _optionBmp;
	image* _bgmBmp;
	image* _effectBmp;
	image* _bgmProgBmp;
	image* _effectProgBmp;
	image* _bgmProgButtonBmp;
	image* _effectProgButtonBmp;
	image* _optionSelectBmp;
	image* _closeOptionBmp;

	int _currentSelectY;

	POINT _selectOption[3];

	bool _isOpenOption;
	bool _onBgm;
	bool _onEffect;

public:
	option();
	~option();

	HRESULT init();
	void release();
	void update();
	void render();

	void bgmSystem();
	void effectSystem();

	void openOption() { _isOpenOption = true; }
	void closeOption() { _isOpenOption = false; }
};

