#include "stdafx.h"
#include "stage1Story.h"


stage1Story::stage1Story()
{
}


stage1Story::~stage1Story()
{

}
HRESULT stage1Story::init()
{
	_index = 0;
	_storyImage[0] = IMAGEMANAGER->addImage("stage1-1", "./images/stage1-1.bmp", 1152, 648, true, RGB(255, 0, 255));
	_storyImage[1] = IMAGEMANAGER->addImage("stage1-2", "./images/stage1-2.bmp", 1152, 648, true, RGB(255, 0, 255));
	_storyImage[2] = IMAGEMANAGER->addImage("stage1-3", "./images/stage1-3.bmp", 1152, 648, true, RGB(255, 0, 255));
	_storyImage[3] = IMAGEMANAGER->addImage("stage1-4", "./images/stage1-4.bmp", 1152, 648, true, RGB(255, 0, 255));

	return S_OK;
}
void stage1Story::release()
{

}
void stage1Story::update()
{
	if (KEYMANAGER->isOnceKeyDown('X'))
	{

	}
}
void stage1Story::render()
{

}