#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}



HRESULT enemy::init()
{
	//_image = IMAGEMANAGER->addFrameImage("enemy",)


	//디폴트
	_rcEnemy = RectMakeCenter(BACKGROUNDSIZEX / 3, BACKGROUNDSIZEY / 2, 100, 100);
	_speed = 3;
	_currentRC = &_rcEnemy;

	

	return S_OK;
}

void enemy::release()
{


}

void enemy::update()
{
	//카메라확인겸 움직이는지 확인중
	int _x = (_rcEnemy.left + _rcEnemy.right) / 2;
	int	_y = (_rcEnemy.top + _rcEnemy.bottom) / 2;


	if (_x < BACKGROUNDSIZEX / 3 - 300) _speed = 3;
	if (_x > BACKGROUNDSIZEX / 3 + 300) _speed = -3;

	_x += _speed;
	_rcEnemy = RectMakeCenter(_x, _y, 100, 100);
}

void enemy::render()
{
	//에네미rc
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x, CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y, 100, 100);

}




//여기서부터 콜백함수
void enemy::rightAttack(void * obj)
{
}

void enemy::rightJumpAttack(void * obj)
{
}

void enemy::leftAttack(void * obj)
{
}

void enemy::leftJumpAttack(void * obj)
{
}
