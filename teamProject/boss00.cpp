#include "stdafx.h"
#include "boss00.h"


boss00::boss00()
{
}


boss00::~boss00()
{
}

HRESULT boss00::init(POINT point)
{
	_imageBoss = IMAGEMANAGER->addFrameImage("boss00", "./images/boss00.bmp", 0, 0, 1024, 390, 16, 6, true, RGB(255, 0, 255));
	_x = point.x;
	_y = point.y;

	//디폴트

	_rcBoss = RectMakeCenter(_x, _y, _imageBoss->getFrameWidth(), _imageBoss->getFrameHeight()); //기본렉트
	_CollircBoss = RectMakeCenter(_x, _y, 50, 50); //충돌렉트
	_BossDirection = BOSSDIRECTION_RIGHT_STOP; //기본상태
	_jump = 0; //점프력
	_Gravity = 0.1f; //중력
	_HP = 250; //체에력
	_speed = 3; //스퓌드


	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightStop", "boss00", rightStop, 1, 6, true);
	int leftStop[] = { 16 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftStop", "boss00", leftStop, 1, 6, true);
	int rightMove[] = { 0,1,2,1 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightMove", "boss00", rightMove, 4, 10, true);
	int leftMove[] = { 16,15,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("bossLeftMove", "boss00", leftMove, 4, 10, true);
	int rightOneJab[] = { 86,87 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightOneJab", "boss00", rightOneJab, 2, 10, true);
	int leftOneJab[] = { 91,90 };
	KEYANIMANAGER->addArrayFrameAnimation("bossLeftOneJab", "boss00", leftOneJab, 2, 10, true);
	int rightTwoJab[] = { 22,23 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightTwoJab", "boss00", rightTwoJab, 2, 10, true);
	int leftTwoJab[] = { 27,26 };
	KEYANIMANAGER->addArrayFrameAnimation("bossLeftTwoJab", "boss00", leftTwoJab, 2, 10, true);
	int rightHit[] = { 6 };
	KEYANIMANAGER->addArrayFrameAnimation("bossrightHit", "boss00", rightHit, 1, 6, true);
	int leftHit[] = { 11 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftHit", "boss00", leftHit, 1, 6, true);
	int rightHit2[] = { 7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("bossrightHit2", "boss00", rightHit2, 2, 6, true);
	int leftHit2[] = { 10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftHit2", "boss00", leftHit2, 2, 6, true);

	//쓰러진상태
	int rightDown[] = { 18 };
	KEYANIMANAGER->addArrayFrameAnimation("bossrightDown", "boss00", rightDown, 1, 6, true);
	int leftDown[] = { 31 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftDown", "boss00", leftDown, 1, 6, true);
	//연타공격이든 피없든 공중상태
	int rightComboDown[] = { 17 };
	KEYANIMANAGER->addArrayFrameAnimation("bossrightComboDown", "boss00", rightComboDown, 1, 6, true);
	int leftComboDown[] = { 32 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftComboDown", "boss00", leftComboDown, 1, 6, true);
	//다운 후 기상
	int rightStandUp[] = { 19 };
	KEYANIMANAGER->addArrayFrameAnimation("bossrightStandUp", "boss00", rightStandUp, 1, 6, true);
	int leftStandUp[] = { 30 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftStandUp", "boss00", leftStandUp, 1, 6, true);
	//쥬금
	int bossDead[] = { 23,24,33,34,35,36,37,38 };
	KEYANIMANAGER->addArrayFrameAnimation("bossDead", "boss00", bossDead, 8, 10, true);

	int clime[] = { 4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("bossClime", "boss00", clime, 2, 8, true);


	_BossMotion = KEYANIMANAGER->findAnimation("bossRightStop");

	return S_OK;
}

void boss00::release()
{


}

void boss00::update()
{
	//카메라확인겸 움직이는지 확인중
	//_x = (_rcEnemy.left + _rcEnemy.right) / 2;
	//_y = (_rcEnemy.top + _rcEnemy.bottom) / 2;

	//여기 모르겠음
	//if (_x < _backgroundsizex-300) _speed = 3;
	//if (_x > _backgroundsizex+300) _speed = -3;

	//_x -= _speed;
	//_rcEnemy = RectMakeCenter(_x, _y, 100, 100);

	




	//_rcEnemy = RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());

	//KEYANIMANAGER->update();
}

void boss00::render()
{
	//에네미rc
	//RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x, CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y, 100, 100);


	IMAGEMANAGER->findImage("boss00")->frameRender(getMemDC(),
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _imageBoss->getFrameWidth(), _imageBoss->getFrameHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _imageBoss->getFrameWidth(), _imageBoss->getFrameHeight())).y, 0, 0);

	//_imageEnemy->aniRender(getMemDC(), _rcEnemy.left, _rcEnemy.top, _enemyMotion);
}




//여기서부터 콜백함수
void boss00::rightAttack(void * obj)
{

}

void boss00::rightJumpAttack(void * obj)
{

}

void boss00::leftAttack(void * obj)
{

}

void boss00::leftJumpAttack(void * obj)
{

}


void boss00::collision()
{

}
