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

	/*
	image* _imageEnemy;				//이미지
	RECT _rcEnemy;				//렉트
	RECT _CollircEnemy;			//충돌렉트
	int _HP;					//체력
	int _maxHP;					//최대체력
	int _speed;					//속도
	int _x, _y;					//xy값
	float _ZMove;				//z무브
	float _jump, _Gravity;		//점프,중력

	animation* _enemyMotion;
	*/

	_imageEnemy = IMAGEMANAGER->addFrameImage("boss00", "./images/boss00.bmp", 0, 0, 3072, 1170, 16, 6, true, RGB(255, 0, 255));
	_x = point.x;
	_y = point.y;

	//디폴트

	_rcEnemy = RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight()); //기본렉트
	_CollircEnemy = RectMakeCenter(_x, _y, 50, 50); //충돌렉트
	//_BossDirection = BOSSDIRECTION_RIGHT_STOP; //기본상태
	_jump = 0; //점프력
	_Gravity = 0.1f; //중력
	_HP = 250; //체에력
	_speed = 3; //스퓌드


	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightStop", "boss00", rightStop, 1, 2, true);
	int leftStop[] = { 15 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftStop", "boss00", leftStop, 1, 2, true);
	int rightMove[] = { 0,1,2,1 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightMove", "boss00", rightMove, 4, 2, true);
	int leftMove[] = { 15,14,13,14 };
	KEYANIMANAGER->addArrayFrameAnimation("bossLeftMove", "boss00", leftMove, 4, 2, true);
	int rightOneJab[] = { 20,21 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightOneJab", "boss00", rightOneJab, 2, 2, true);
	int leftOneJab[] = { 27,26 };
	KEYANIMANAGER->addArrayFrameAnimation("bossLeftOneJab", "boss00", leftOneJab, 2, 2, true);
	int rightTwoJab[] = { 49,50,51 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightTwoJab", "boss00", rightTwoJab, 3, 2, true);
	int leftTwoJab[] = { 62,61,60 };
	KEYANIMANAGER->addArrayFrameAnimation("bossLeftTwoJab", "boss00", leftTwoJab, 3, 2, true);
	int rightHit[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("bossrightHit", "boss00", rightHit, 1, 2, true);
	int leftHit[] = { 12 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftHit", "boss00", leftHit, 1, 2, true);
	int rightHit2[] = { 5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("bossrightHit2", "boss00", rightHit2, 2, 2, true);
	int leftHit2[] = { 11,10 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftHit2", "boss00", leftHit2, 2, 2, true);

	//쓰러진상태
	int rightDown[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation("bossrightDown", "boss00", rightDown, 1, 2, true);
	int leftDown[] = { 8 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftDown", "boss00", leftDown, 1, 2, true);
	//연타공격이든 피없든 공중상태
	int rightComboDown[] = { 6 };
	KEYANIMANAGER->addArrayFrameAnimation("bossrightComboDown", "boss00", rightComboDown, 1, 6, true);
	int leftComboDown[] = { 9 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftComboDown", "boss00", leftComboDown, 1, 6, true);
	//다운 후 기상
	int rightStandUp[] = { 16 };
	KEYANIMANAGER->addArrayFrameAnimation("bossrightStandUp", "boss00", rightStandUp, 1, 6, true);
	int leftStandUp[] = { 31 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftStandUp", "boss00", leftStandUp, 1, 6, true);
	//쥬금
	int bossDead[] = { 22,23,32,33,34,35,36,37 };
	KEYANIMANAGER->addArrayFrameAnimation("bossDead", "boss00", bossDead, 8, 1, true);

	int clime[] = { 54,55 };
	KEYANIMANAGER->addArrayFrameAnimation("bossClime", "boss00", clime, 2, 2, true);


	_enemyMotion = KEYANIMANAGER->findAnimation("bossLeftMove");

	return S_OK;
}

//void boss00::release()
//{
//
//
//}

//void boss00::update()
//{
//
//	//_rcEnemy = RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
//
//	//KEYANIMANAGER->update();
//}

//void boss00::render()
//{
//	//에네미rc
//	//RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x, CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y, 100, 100);
//
//
//	/*IMAGEMANAGER->findImage("boss00")->frameRender(getMemDC(),
//		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _imageBoss->getFrameWidth(), _imageBoss->getFrameHeight())).x,
//		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _imageBoss->getFrameWidth(), _imageBoss->getFrameHeight())).y, 0, 0);*/
//
//	//_imageEnemy->aniRender(getMemDC(), _rcEnemy.left, _rcEnemy.top, _enemyMotion);
//}




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
