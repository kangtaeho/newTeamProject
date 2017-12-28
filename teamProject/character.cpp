#include "stdafx.h"
#include "character.h"


character::character()
{
}


character::~character()
{
}
HRESULT character::init()
{
	_image = IMAGEMANAGER->addFrameImage("JIMMY", "images/JIMMY.bmp", 1024, 700, 16, 14, true, RGB(255, 0, 255));

	_state = CHARA_RIGHT_STOP;

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_isRight = true;
	_JP = 0;
	_gravity = 0.2f;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	int RightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightStop", "JIMMY", RightStop, 1, 6, true);

	int LeftStop[] = { 127 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftStop", "JIMMY", LeftStop, 1, 6, true);

	int RightMove[] = 



	return S_OK;

}
void character::release()
{

}
void character::update() 
{

}
void character::render() 
{

}

void MakeRightStop(void* obj)
{
	
}
void MakeLeftStop(void* obj)	
{
	
}
void MakeRightStop(void* obj)
{
	
}
void MakeLeftStop(void* obj) 
{
	
}
void MakeRightFall(void* obj)	
{
	
}
void MakeLeftFall(void* obj)	
{
	
}
void MakeRightDown(void* obj)	
{
	
}
void MakeLeftDown(void* obj)	
{
	
}