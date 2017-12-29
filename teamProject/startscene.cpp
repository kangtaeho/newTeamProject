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


	return S_OK;
}
void startscene::release()
{

}
void startscene::update()
{
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		SCENEMANAGER->changeScene("스테이지00", false);
	}
}
void startscene::render()
{
	IMAGEMANAGER->findImage("selectScene")->render(getMemDC(),0, 0);
	IMAGEMANAGER->findImage("selecttri")->render(getMemDC(), 417, 375);
}