#include "stdafx.h"
#include "startscene.h"


startscene::startscene()
{
}


startscene::~startscene()
{

}
HRESULT startscene::init()
{
	IMAGEMANAGER->addImage("selectScene", "./images/background.bmp", 1152, 648, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("selecttri", "./images/selecttri.bmp", 30, 35, true, RGB(255, 0, 255));

	_index = true;
	return S_OK;
}
void startscene::release()
{

}
void startscene::update()
{
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_index)
		SCENEMANAGER->changeScene("스테이지00", false);

		//옵션화면 미구현
		/*else
			SCENEMANAGER->changeScene("스테이지00", false);*/
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_index)
			_index = false;
		else
			_index = true;
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (!_index)
			_index = true;
		else
			_index = false;
	}
}
void startscene::render()
{
	IMAGEMANAGER->findImage("selectScene")->render(getMemDC(),0, 0);
	if (_index)
	IMAGEMANAGER->findImage("selecttri")->render(getMemDC(), 417, 375);
	else
		IMAGEMANAGER->findImage("selecttri")->render(getMemDC(), 417, 445);
}