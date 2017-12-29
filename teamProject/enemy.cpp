#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}



HRESULT enemy::init(POINT point)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("enemy01","./images/enemy01.bmp",0,0,1024,448,16,7,true,RGB(255,0,255));
	_x = point.x;
	_y = point.y;

	//디폴트

	_rcEnemy = RectMakeCenter(_x,_y,_imageEnemy->getFrameWidth(),_imageEnemy->getFrameHeight());
	_CollircEnemy = RectMakeCenter(_x, _y, 50, 50);
	_enemyDirection = ENEMYDIRECTION_RIGHT_STOP; //기본상태
	_jump = 0;
	_Gravity = 0.2f;
	_HP = 100;
	_speed = 3;


	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightStop", "enemy01", rightStop, 1,6,true);
	int leftStop[] = { 16 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftStop", "enemy01", leftStop, 1, 6, true);
	int rightMove[] = { 0,1,2,1 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightMove", "enemy01", rightMove, 4, 10, true);
	int leftMove[] = { 16,15,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyLeftMove", "enemy01", leftMove, 4, 10, true);
	int rightJumpAttack[] = { 20,21 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightJumpAttack", "enemy01", rightJumpAttack, 2, 10, true);
	int leftJumpAttack[] = { 29,28 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyLeftJumpAttack", "enemy01", leftJumpAttack, 2, 10, true);

	_enemyMotion = KEYANIMANAGER->findAnimation("enemyRightStop");

	return S_OK;
}

void enemy::release()
{


}

void enemy::update()
{
	//카메라확인겸 움직이는지 확인중
	//_x = (_rcEnemy.left + _rcEnemy.right) / 2;
	//_y = (_rcEnemy.top + _rcEnemy.bottom) / 2;

	//여기 모르겠음
	//if (_x < _backgroundsizex-300) _speed = 3;
	//if (_x > _backgroundsizex+300) _speed = -3;

	//_x -= _speed;
	//_rcEnemy = RectMakeCenter(_x, _y, 100, 100);

	switch (_enemyDirection)
	{
	case ENEMYDIRECTION_RIGHT_STOP:
		break;
	case ENEMYDIRECTION_LEFT_STOP:
		break;
	case ENEMYDIRECTION_RIGHT_MOVE:
		break;
	case ENEMYDIRECTION_LEFT_MOVE:
		break;
	case ENEMYDIRECTION_RIGHT_JUMP_ATTACK:
		break;
	case ENEMYDIRECTION_LEFT_JUMP_ATTACK:
		break;

	}



}

void enemy::render()
{
	//에네미rc
	//RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x, CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y, 100, 100);
	
	//되는지 실험중

	//IMAGEMANAGER->findImage("enemy01")->frameRender(getMemDC(),
	//	CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight())).x,
	//	CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight())).y, 0, 0);

	_imageEnemy->aniRender(getMemDC(), _rcEnemy.left, _rcEnemy.top, _enemyMotion);
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
