#include "stdafx.h"
#include "stage3Story.h"


stage3Story::stage3Story()
{
}


stage3Story::~stage3Story()
{
}

HRESULT stage3Story::init()
{
	_index = 0;

	_storyImage[0] = IMAGEMANAGER->addImage("��������3-1", "./images/stage3-1.bmp", 1152, 648, true, RGB(255, 0, 255));
	_storyImage[1] = IMAGEMANAGER->addImage("��������3-2", "./images/stage3-2.bmp", 1152, 648, true, RGB(255, 0, 255));
	_storyImage[2] = IMAGEMANAGER->addImage("��������3-3", "./images/stage3-3.bmp", 1152, 648, true, RGB(255, 0, 255));

	return S_OK;
}
void stage3Story::release()
{

}
void stage3Story::update()
{
	//XŰ ���������� ��ȭ �Ѿ
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_index++;

		//���� 3�������� �� ȣ��
		if (_index >= 3)
			SCENEMANAGER->changeScene("��������02", false);
	}
}
void stage3Story::render()
{
	_storyImage[_index]->render(getMemDC(), 0, 0);
}
