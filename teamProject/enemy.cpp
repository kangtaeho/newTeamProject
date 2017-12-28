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
	_enemyDirection = ENEMYDIRECTION_RIGHT_STOP;
	_jump = 0;
	_Gravity = 0.2f;

	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightStop", "enemy01", rightStop, 1,6,true);
	int leftStop[] = { 16 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftStop", "enemy01", leftStop, 1, 6, true);
	int rightMove[] = { 0,1,2,1 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightMove", "enemy01", rightMove, 4, 10, true);
	int leftMove[] = { 16,15,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyLeftMove", "enemy01", leftMove, 4, 10, true);

	return S_OK;
}

void enemy::release()
{


}

void enemy::update()
{
	//카메라확인겸 움직이는지 확인중
	_x = (_rcEnemy.left + _rcEnemy.right) / 2;
	_y = (_rcEnemy.top + _rcEnemy.bottom) / 2;


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
