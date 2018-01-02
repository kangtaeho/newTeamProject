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

	_storyImage[0] = IMAGEMANAGER->addImage("스테이지1-1", "./images/stage1-1.bmp", 1152, 648, true, RGB(255, 0, 255));
	_storyImage[1] = IMAGEMANAGER->addImage("스테이지1-2", "./images/stage1-2.bmp", 1152, 648, true, RGB(255, 0, 255));
	_storyImage[2] = IMAGEMANAGER->addImage("스테이지1-3", "./images/stage1-3.bmp", 1152, 648, true, RGB(255, 0, 255));
	_storyImage[3] = IMAGEMANAGER->addImage("스테이지1-4", "./images/stage1-4.bmp", 1152, 648, true, RGB(255, 0, 255));

	return S_OK;
}
void stage1Story::release()
{

}
void stage1Story::update()
{
	//X키 누를때마다 대화 넘어감
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_index++;
		//이미지 인덱스 넘길때 씬 전환
		if (_index >= 4)
			SCENEMANAGER->changeScene("스테이지00", false);
	}
}
void stage1Story::render()
{
	_storyImage[_index]->render(getMemDC(), 0, 0);
}
