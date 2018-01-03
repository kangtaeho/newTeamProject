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

	_storyImage[0] = IMAGEMANAGER->addImage("��������1-1", "./images/stage1-1.bmp", 1152, 648, true, RGB(255, 0, 255));
	_storyImage[1] = IMAGEMANAGER->addImage("��������1-2", "./images/stage1-2.bmp", 1152, 648, true, RGB(255, 0, 255));
	_storyImage[2] = IMAGEMANAGER->addImage("��������1-3", "./images/stage1-3.bmp", 1152, 648, true, RGB(255, 0, 255));
	_storyImage[3] = IMAGEMANAGER->addImage("��������1-4", "./images/stage1-4.bmp", 1152, 648, true, RGB(255, 0, 255));

	return S_OK;
}
void stage1Story::release()
{

}
void stage1Story::update()
{
	//XŰ ���������� ��ȭ �Ѿ
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_index++;
		//�̹��� �ε��� �ѱ涧 �� ��ȯ
		if (_index >= 4)
			SCENEMANAGER->changeScene("��������00", false);
	}
}
void stage1Story::render()
{
	_storyImage[_index]->render(getMemDC(), 0, 0);
}
