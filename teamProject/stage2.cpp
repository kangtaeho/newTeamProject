#include "stdafx.h"
#include "stage2.h"


stage2::stage2()

{
}

stage2::~stage2()
{
}

HRESULT stage2::init()
{
	IMAGEMANAGER->addImage("��������_01", "./images/02_stage00.bmp", 5795, 2593, true, RGB(255, 0, 255));

	_mainPlayer = new character;
	_mainPlayer->init();

	return S_OK;
}

void stage2::release()
{
}

void stage2::update()
{
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SCENEMANAGER->changeScene("��������00");
	}
}

void stage2::render()
{

	IMAGEMANAGER->findImage("��������_01")->render(getMemDC(), 0, 0);
}
