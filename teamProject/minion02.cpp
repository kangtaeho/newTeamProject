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

	_enemyKeyName[0] = "enemy06RightStop";
	_enemyKeyName[1] = "enemy06LeftStop";
	_enemyKeyName[2] = "--값 없음--";
	_enemyKeyName[3] = "--값 없음--";
	_enemyKeyName[4] = "enemy06RightMove";
	_enemyKeyName[5] = "enemy06LeftMove";
	_enemyKeyName[6] = "enemy06RightOneJab";
	_enemyKeyName[7] = "enemy06LeftOneJab";
	_enemyKeyName[8] = "NONE";
	_enemyKeyName[9] = "NONE";
	_enemyKeyName[10] = "enemy06rightDownForever";
	_enemyKeyName[11] = "enemy06leftDownForever";
	_enemyKeyName[12] = "enemy06rightHit2";
	_enemyKeyName[13] = "enemy06leftHit2";
	_enemyKeyName[14] = "enemy06RightTwoJab";
	_enemyKeyName[15] = "enemy06LeftTwoJab";

	_isItemCollion = false;
	_isGetItemEnemy = false;
	_isTracePlayer = 0;

	_isAttack = false;					//적이 공격상태이니?
	_attackAniStart = false;			//어택 애니 시작중
	_dieAniStart = false;

	_isHitted = false;
	_hittedAniStart = false;

	_countAttack = 0;				//어택카운트
	_countHitted = 0;
	_traceAngle = 0;

	_jump = 0; //점프력
	_Gravity = 0.1f; //중력
	_HP = 10; //체에력
	_speed = 3; //스퓌드

	_enemyCenterX = 0;
	_enemyCenterY = 0;
	_playerCenterX = 0;
	_playerCenterY = 0;
	_rndAttackStyle = 0;

	_rndDirX = rndDirection(RND->getInt(3));
	_rndDirY = rndDirection(RND->getInt(3));

	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06RightStop", "enemy06", rightStop, 1, 6, true);
	int leftStop[] = { 15 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06LeftStop", "enemy06", leftStop, 1, 6, true);
	int rightMove[] = { 0,1,2,1 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06RightMove", "enemy06", rightMove, 4, 2, true);
	int leftMove[] = { 15,14,13,14 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06LeftMove", "enemy06", leftMove, 4, 2, true);
	int rightOneJab[] = { 20,21 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06RightOneJab", "enemy06", rightOneJab, 2, 2, true);
	int leftOneJab[] = { 27,26 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06LeftOneJab", "enemy06", leftOneJab, 2, 2, true);
	int rightTwoJab[] = { 22,23.22 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06RightTwoJab", "enemy06", rightTwoJab, 3, 2, false);
	int leftTwoJab[] = { 25,24,25 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06LeftTwoJab", "enemy06", leftTwoJab, 3, 2, false);
	int rightJumpAttack[] = { 19,81 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06RightJumpAttack", "enemy06", rightJumpAttack, 2, 2, true);
	int leftJumpAttack[] = { 28,94 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06LeftJumpAttack", "enemy06", leftJumpAttack, 2, 2, true);
	int rightHit[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06rightHit", "enemy06", rightHit, 1, 2, true);
	int leftHit[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06leftHit", "enemy06", leftHit, 1, 2, true);
	int rightHit2[] = { 6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06rightHit2", "enemy06", rightHit2, 2, 2, true);
	int leftHit2[] = { 9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06leftHit2", "enemy06", leftHit2, 2, 2, true);
	int rightCrouch[] = { 32 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06rightCrouch", "enemy06", rightCrouch, 1, 2, true);
	int leftCrouch[] = { 47 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06leftCrouch", "enemy06", leftCrouch, 1, 2, true);
	int rightCrouchThrow[] = { 36,37,38 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06rightCrouchThrow", "enemy06", rightCrouchThrow, 3, 2, true);
	int leftCrouchThrow[] = { 43,42,41 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06leftCrouchThrow", "enemy06", leftCrouchThrow, 3, 2, true);
	//쓰러진상태
	int rightDown[] = { 17 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06rightDown", "enemy06", rightDown, 1, 2, true);
	int leftDown[] = { 30 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06leftDown", "enemy06", leftDown, 1, 2, true);
	//연타공격이든 피없든 공중상태
	int rightComboDown[] = { 16 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06rightComboDown", "enemy06", rightComboDown, 1, 2, true);
	int leftComboDown[] = { 31 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06leftComboDown", "enemy06", leftComboDown, 1, 2, true);
	//다운 후 기상
	int rightStandUp[] = { 18 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06rightStandUp", "enemy06", rightStandUp, 1, 2, true);
	int leftStandUp[] = { 29 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06leftStandUp", "enemy06", leftStandUp, 1, 2, true);
	//다운 후 쥬금
	int rightDownForever[] = { 17,60 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06rightDownForever", "enemy06", rightDownForever, 2, 2, true);
	int leftDownForever[] = { 30,60 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy06leftDownForever", "enemy06", leftDownForever, 2, 2, true);



	_enemyMotion = KEYANIMANAGER->findAnimation("enemy06LeftTwoJab");

	return S_OK;
}

void minion02::collision()
{
}