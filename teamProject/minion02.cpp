#include "stdafx.h"
#include "minion02.h"


minion02::minion02()
{
}


minion02::~minion02()
{
}


HRESULT minion02::init(POINT point, int currentStage)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("enemy06", "./images/enemy06.bmp", 0, 0, 3072, 1140, 16, 6, true, RGB(255, 0, 255));
	_x = point.x;
	_y = point.y;

	//디폴트
	_currentStage = currentStage;
	_countMove = 0;

	_rcEnemy = RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight()); //기본렉트
	_CollircEnemy = RectMakeCenter(CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x + _imageEnemy->getFrameWidth() / 2,
		CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y + _imageEnemy->getFrameHeight() / 2, 75, 75); //충돌렉트

	_enemyKeyName[0] = "enemyRightStop";
	_enemyKeyName[1] = "enemyLeftStop";
	_enemyKeyName[2] = "--값 없음--";
	_enemyKeyName[3] = "--값 없음--";
	_enemyKeyName[4] = "enemyRightMove";
	_enemyKeyName[5] = "enemyLeftMove";

	_isItemCollion = false;

	_jump = 0; //점프력
	_Gravity = 0.1f; //중력
	_HP = 100; //체에력
	_speed = 3; //스퓌드

	_rndDirX = rndDirection(RND->getInt(3));
	_rndDirY = rndDirection(RND->getInt(3));

	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightStop", "enemy06", rightStop, 1, 6, true);
	int leftStop[] = { 15 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftStop", "enemy06", leftStop, 1, 6, true);
	int rightMove[] = { 0,1,2,1 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightMove", "enemy06", rightMove, 4, 10, true);
	int leftMove[] = { 15,14,13,14 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyLeftMove", "enemy06", leftMove, 4, 10, true);
	int rightOneJab[] = { 20,21 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightOneJab", "enemy06", rightOneJab, 2, 10, true);
	int leftOneJab[] = { 27,26 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyLeftOneJab", "enemy06", leftOneJab, 2, 10, true);
	int rightTwoJab[] = { 22,23 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightTwoJab", "enemy06", rightTwoJab, 2, 10, true);
	int leftTwoJab[] = { 25,24 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyLeftTwoJab", "enemy06", leftTwoJab, 2, 10, true);
	int rightJumpAttack[] = { 19,81 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightJumpAttack", "enemy06", rightJumpAttack, 2, 10, true);
	int leftJumpAttack[] = { 28,94 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyLeftJumpAttack", "enemy06", leftJumpAttack, 2, 10, true);
	int rightHit[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightHit", "enemy06", rightHit, 1, 6, true);
	int leftHit[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftHit", "enemy06", leftHit, 1, 6, true);
	int rightHit2[] = { 6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightHit2", "enemy06", rightHit2, 2, 6, true);
	int leftHit2[] = { 9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftHit2", "enemy06", leftHit2, 2, 6, true);
	int rightCrouch[] = { 32 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightCrouch", "enemy06", rightCrouch, 1, 6, true);
	int leftCrouch[] = { 47 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftCrouch", "enemy06", leftCrouch, 1, 6, true);
	int rightCrouchThrow[] = { 36,37,38 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightCrouchThrow", "enemy06", rightCrouchThrow, 3, 10, true);
	int leftCrouchThrow[] = { 43,42,41 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftCrouchThrow", "enemy06", leftCrouchThrow, 3, 10, true);
	//쓰러진상태
	int rightDown[] = { 17 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightDown", "enemy06", rightDown, 1, 6, true);
	int leftDown[] = { 30 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftDown", "enemy06", leftDown, 1, 6, true);
	//연타공격이든 피없든 공중상태
	int rightComboDown[] = { 16 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightComboDown", "enemy06", rightComboDown, 1, 6, true);
	int leftComboDown[] = { 31 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftComboDown", "enemy06", leftComboDown, 1, 6, true);
	//다운 후 기상
	int rightStandUp[] = { 18 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightStandUp", "enemy06", rightStandUp, 1, 6, true);
	int leftStandUp[] = { 29 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftStandUp", "enemy06", leftStandUp, 1, 6, true);
	//다운 후 쥬금
	int rightDownForever[] = { 17,60 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightDownForever", "enemy06", rightDownForever, 2, 6, true);
	int leftDownForever[] = { 30,60 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftDownForever", "enemy06", leftDownForever, 2, 6, true);



	_enemyMotion = KEYANIMANAGER->findAnimation("enemyLeftTwoJab");

	return S_OK;
}

void minion02::collision()
{
}