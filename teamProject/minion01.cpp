#include "stdafx.h"
#include "minion01.h"


minion01::minion01()
{
}


minion01::~minion01()
{
}

HRESULT minion01::init(POINT point, int currentStage)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("enemy07", "./images/enemy07.bmp", 0, 0, 3072, 1365, 16, 7, true, RGB(255, 0, 255));
	_x = point.x;
	_y = point.y;

	_currentStage = currentStage;
	_countMove = 0;
	//디폴트

	_rcEnemy = RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight()); //기본렉트
	_CollircEnemy = RectMakeCenter(CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x+ _imageEnemy->getFrameWidth()/2, 
									CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y+ _imageEnemy->getFrameHeight()/2, 75, 75); //충돌렉트
													//_EnemyDirection = ENEMYDIRECTION_RIGHT_STOP; //기본상태
	_jump = 0; //점프력
	_Gravity = 0.1f; //중력
	_HP = 10; //체에력
	_speed = 3; //스퓌드

	_traceAngle = 0;
	_isTracePlayer = 0;
	_countAttack = 0;				//어택카운트
	_countHitted = 0;

	_isAttack = false;					//적이 공격상태이니?
	_attackAniStart = false;			//어택 애니 시작중
	_dieAniStart = false;

	_rndDirX = rndDirection(RND->getInt(3));
	_rndDirY = rndDirection(RND->getInt(3));
	_isItemCollion = false;
	_isGetItemEnemy = false;

	_isHitted = false;
	_hittedAniStart = false;



	_enemyCenterX = 0;
	_enemyCenterY = 0;
	_playerCenterX = 0;
	_playerCenterY = 0;
	_rndAttackStyle = 0;


	_enemyKeyName[0] = "enemy07RightStop";
	_enemyKeyName[1] = "enemy07LeftStop";
	_enemyKeyName[2] = "enemy07RightRun";
	_enemyKeyName[3] = "enemy07LeftRun";
	_enemyKeyName[4] = "enemy07RightMove";
	_enemyKeyName[5] = "enemy07LeftMove";
	_enemyKeyName[6] = "enemy07RightOneJab";
	_enemyKeyName[7] = "enemy07LeftOneJab";
	_enemyKeyName[8] = "NONE";
	_enemyKeyName[9] = "NONE";
	_enemyKeyName[10] = "enemy07rightDownForever";
	_enemyKeyName[11] = "enemy07leftDownForever";
	_enemyKeyName[12] = "enemy07RightHittied";
	_enemyKeyName[13] = "enemy07LeftHittied";
	_enemyKeyName[14] = "enemy07RightTwoJab";
	_enemyKeyName[15] = "enemy07LeftTwoJab";



	int rightHittied[] = { 38,37,36,37,};
	KEYANIMANAGER->addArrayFrameAnimation("enemy07RightHittied", "enemy07", rightHittied, 4, 2, false);
	int leftHittied[] = { 42,43,44,43};
	KEYANIMANAGER->addArrayFrameAnimation("enemy07LeftHittied", "enemy07", leftHittied, 4, 2, false);

	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07RightStop", "enemy07", rightStop, 1, 2, true);
	int leftStop[] = { 15 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07LeftStop", "enemy07", leftStop, 1, 2, true);
	int rightMove[] = { 0,1,2,1 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07RightMove", "enemy07", rightMove, 4, 2, true);
	int leftMove[] = { 15,14,13,14 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07LeftMove", "enemy07", leftMove, 4, 2, true);
	int rightRun[] = { 3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07RightRun", "enemy07", rightRun, 4, 2, true);
	int leftRun[] = { 12,11,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07LeftRun", "enemy07", leftRun, 4, 2, true);
	int rightOneJab[] = { 33,34 ,33};
	KEYANIMANAGER->addArrayFrameAnimation("enemy07RightOneJab", "enemy07", rightOneJab, 3, 2, false);
	int leftOneJab[] = { 46,45 ,46};
	KEYANIMANAGER->addArrayFrameAnimation("enemy07LeftOneJab", "enemy07", leftOneJab, 3, 2, false);
	int rightTwoJab[] = { 87,96,87 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07RightTwoJab", "enemy07", rightTwoJab, 3, 2, false);
	int leftTwoJab[] = { 88,111,88 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07LeftTwoJab", "enemy07", leftTwoJab, 3, 2, false);
	int rightJumpAttack[] = { 32 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07RightJumpAttack", "enemy07", rightJumpAttack, 1, 2, true);
	int leftJumpAttack[] = { 47 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07LeftJumpAttack", "enemy07", leftJumpAttack, 1, 2, true);
	int rightHit[] = { 17 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07rightHit", "enemy07", rightHit, 1, 2, true);
	int leftHit[] = { 30 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07leftHit", "enemy07", leftHit, 1, 2, true);
	int rightHit2[] = { 18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07rightHit2", "enemy07", rightHit2, 2, 2, true);
	int leftHit2[] = { 29,28 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07leftHit2", "enemy07", leftHit2, 2, 2, true);
	int rightCrouch[] = { 35 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07rightCrouch", "enemy07", rightCrouch, 1, 2, true);
	int leftCrouch[] = { 44 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07leftCrouch", "enemy07", leftCrouch, 1, 2, true);
	int rightCrouchThrow[] = { 80,81,82 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07rightCrouchThrow", "enemy07", rightCrouchThrow, 3, 2, true);
	int leftCrouchThrow[] = { 95,94,93 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07leftCrouchThrow", "enemy07", leftCrouchThrow, 3, 2, true);
	//쓰러진상태
	int rightDown[] = { 21 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07rightDown", "enemy07", rightDown, 1, 2, true);
	int leftDown[] = { 26 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07leftDown", "enemy07", leftDown, 1, 2, true);
	//연타공격이든 피없든 공중상태
	int rightComboDown[] = { 20 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07rightComboDown", "enemy07", rightComboDown, 1, 2, true);
	int leftComboDown[] = { 27 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07leftComboDown", "enemy07", leftComboDown, 1, 2, true);
	//다운 후 기상
	int rightStandUp[] = { 22 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07rightStandUp", "enemy07", rightStandUp, 1, 2, true);
	int leftStandUp[] = { 25 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07leftStandUp", "enemy07", leftStandUp, 1, 2, true);
	//다운 후 쥬금
	int rightDownForever[] = { 21,84 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07rightDownForever", "enemy07", rightDownForever, 2, 2, true);
	int leftDownForever[] = { 26,84 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy07leftDownForever", "enemy07", leftDownForever, 2, 2, true);



	_enemyMotion = KEYANIMANAGER->findAnimation("enemy07RightRun");

	return S_OK;
}

void minion01::collision()
{

}