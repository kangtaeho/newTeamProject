#include "stdafx.h"
#include "minion00.h"


minion00::minion00()
{
}


minion00::~minion00()
{
}




HRESULT minion00::init(POINT point, int currentStage)
{
	  _imageEnemy = IMAGEMANAGER->addFrameImage("enemy01","./images/enemy01.bmp",0, 0, 3072,1344,16,7,true,RGB(255,0,255));
	  _x = point.x;
	  _y = point.y;
	  
	  //디폴트
	  _currentStage = currentStage;
	  _countMove = 0;

	  _rcEnemy = RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight()); //기본렉트
	  _CollircEnemy = RectMakeCenter(CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x + _imageEnemy->getFrameWidth() / 2,
		  CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y + _imageEnemy->getFrameHeight() / 2, 75, 75); //충돌렉트

	  _jump = 0; //점프력
	  _Gravity = 0.1f; //중력
	  _HP = 100; //체에력
	  _speed = 3; //스퓌드
	  _isItemCollion = false;
	  _isGetItemEnemy = true;

	  _isTracePlayer = 0;

	  _isAttack = false;				//적이 공격상태이니?
	  _attackAniStart = false;			//어택 애니 시작중
	  _dieAniStart = false;				//죽는거 애니메이션 시작했냐?
	  _isHitted = false;				//처맞고있니?
	  _hittedAniStart = false;			//맞는 애니메이션 시작?
	  _isDead = false;					//죽었니?
	  _deleteEnemy = false;				//에너미 백터 재거 할래?
	  
	  _rndDirX = rndDirection(RND->getInt(3));
	  _rndDirY = rndDirection(RND->getInt(3));




	  _enemyCenterX = 0;
	  _enemyCenterY = 0;
	  _playerCenterX = 0;
	  _playerCenterY = 0;

	  _countAttack = 0;
	  _countHitted = 0;

	  _traceAngle = 0;
	  _rndAttackStyle = 0;
	  _alphaValue = 255;

	  _enemyKeyName[0] = "enemy01RightStop";
	  _enemyKeyName[1] = "enemy01LeftStop";
	  _enemyKeyName[2] = "--아직 값없음--";
	  _enemyKeyName[3] = "--아직 값없음--";
	  _enemyKeyName[4] = "enemy01RightMove";
	  _enemyKeyName[5] = "enemy01LeftMove";

	  _enemyKeyName[6] = "enemy01RightOneJab";
	  _enemyKeyName[7] = "enemy01LeftOneJab";
	  _enemyKeyName[8] = "enemy01RightTwoJab";
	  _enemyKeyName[9] = "enemy01LeftTwoJab";
	  _enemyKeyName[10] = "enemy01rightDownForever";
	  _enemyKeyName[11] = "enemy01leftDownForever";
	  _enemyKeyName[12] = "enemy01LeftHittied";
	  _enemyKeyName[13] = "enemy01RightHittied";
	  _enemyKeyName[14] = "enemy01RightTwoJab";
	  _enemyKeyName[15] = "enemy01LeftTwoJab";




	  //오른쪽 멈춤

	  int rightStop[] = { 0 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01RightStop", "enemy01", rightStop, 1,2,true);
	  //왼쪽 멈춤
	  int leftStop[] = { 15 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01LeftStop", "enemy01", leftStop, 1, 6, true);
	  //오른쪽 움직임
	  int rightMove[] = { 0,1,2,1 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01RightMove", "enemy01", rightMove, 4, 2, true);
	  //왼쪽 움직임
	  int leftMove[] = { 15,14,13,14 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01LeftMove", "enemy01", leftMove, 4, 2, true);
	  //오른쪽 원쨉
	  int rightOneJab[] = { 85,86 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01RightOneJab", "enemy01", rightOneJab, 2, 2, true);
	  //왼쪽 원쨉
	  int leftOneJab[] = { 90,89 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01LeftOneJab", "enemy01", leftOneJab, 2, 2, true);
	  //오른쪽 투쨉
	  int rightTwoJab[] = { 21,22,21 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01RightTwoJab", "enemy01", rightTwoJab, 3, 2, false);
	  //왼쪽 투쨉
	  int leftTwoJab[] = { 26,25,26 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01LeftTwoJab", "enemy01", leftTwoJab, 3, 2, false);
	  //오른쪽 점프공격
	  int rightJumpAttack[] = { 19,20 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01RightJumpAttack", "enemy01", rightJumpAttack, 2, 2, true);
	  //왼쪽 점프공격
	  int leftJumpAttack[] = { 28,27 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01LeftJumpAttack", "enemy01", leftJumpAttack, 2, 2, true);
	  //오른쪽 1히트
	  int rightHit[] = { 5 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01RightHit", "enemy01", rightHit, 1, 2, true);
	  //왼쪽 1히트
	  int leftHit[] = { 10 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01LeftHit", "enemy01", leftHit, 1, 2, true);
	  //오른쪽 경직당함
	  int rightHit2[] = { 6,7 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightHit2", "enemy01", rightHit2, 2, 2, true);

	  //플레이어가 왼쪽에서 때릴때(플레이어 위치가 왼쪽)
	  int leftHittied[] = { 46,47,48,47 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01LeftHitted", "enemy01", leftHittied, 4, 2, false);

	  //플레이어가 오른쪽에서 때릴때(플레이어 위치가 오른쪽)
	  int rightHittied[] = { 35, 34, 33, 34 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightHitted", "enemy01", rightHittied, 4, 2, false);

	  //왼쪽 경직당함
	  int leftHit2[] = { 9,8 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftHit2", "enemy01", leftHit2, 2, 2, true);
	  //오른쪽 잡기당함
	  int rightCrouch[] = { 23 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightCrouch", "enemy01", rightCrouch, 1, 2, true);
	  //왼쪽 잡기당함
	  int leftCrouch[] = { 24 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftCrouch", "enemy01", leftCrouch, 1, 2, true);
	  //오른쪽 던지기당함
	  int rightCrouchThrow[] = { 35,36,37 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightCrouchThrow", "enemy01", rightCrouchThrow, 3, 4, true);
	  //왼쪽 던지기당함
	  int leftCrouchThrow[] = { 44,43,42 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftCrouchThrow", "enemy01", leftCrouchThrow, 3, 4, true);

	  //오른쪽 쓰러진상태
	  int rightDown[] = { 17 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightDown", "enemy01", rightDown, 1, 6, true);
	  //왼쪽 쓰러진상태
	  int leftDown[] = { 30 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftDown", "enemy01", leftDown, 1, 6, true);

	  //오른쪽 연타공격이든 피없든 공중상태
	  int rightComboDown[] = { 16 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightComboDown", "enemy01", rightComboDown, 1, 6, true);
	  //왼쪽  맞아서 공중상태
	  int leftComboDown[] = { 31 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftComboDown", "enemy01", leftComboDown, 1, 6, true);

	  //오른쪽 다운 후 기상
	  int rightStandUp[] = { 18 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightStandUp", "enemy01", rightStandUp, 1, 6, true);
	  //왼쪽 다운 후 기상
	  int leftStandUp[] = { 29 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftStandUp", "enemy01", leftStandUp, 1, 6, true);

	  //오른쪽 다운 후 쥬금
	  int rightDownForever[] = { 17,82 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightDownForever", "enemy01", rightDownForever, 2, 2, false);
	  //왼쪽 다운 후 쥬금
	  int leftDownForever[] = { 30,82 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftDownForever", "enemy01", leftDownForever, 2, 2, false);

	  //오른쪽 돌 들음
	  int rightStoneUp[] = { 67 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightStoneUp", "enemy01", rightStoneUp, 1, 6, true);
	  //왼쪽 돌 들음
	  int leftStoneUp[] = { 76 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftStoneUp", "enemy01", leftStoneUp, 1, 6, true);
	  //오른쪽 돌들고 움직임
	  int rightStoneUpMove[] = { 66,67,68,67 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightStoneUpMove", "enemy01", rightStoneUpMove, 4, 2, true);
	  //왼쪽 돌들고 움직임
	  int leftStoneUpMove[] = { 77,76,75,76 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftStoneUpMove", "enemy01", leftStoneUpMove, 4, 2, true);
	  //오른쪽 돌던짐
	  int rightStoneThrow[] = { 53,54 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightStoneThrow", "enemy01", rightStoneThrow, 2, 3, true);
	  //왼쪽 돌던짐
	  int leftStoneThrow[] = { 58,57 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftStoneThrow", "enemy01", leftStoneThrow, 2, 3, true);

	  //오른쪽 칼던짐
	  int rightKnifeThrow[] = { 51,52 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightKnifeThrow", "enemy01", rightKnifeThrow, 2, 2, true);
	  //왼쪽 칼던짐
	  int leftKnifeThrow[] = { 60,59 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftKnifeThrow", "enemy01", leftKnifeThrow, 2, 2, true);

	  
	  
	  
	  int clime[] = {4,5};
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01Clime", "enemy01", clime, 2,2,true);
	  
	  
	  _enemyMotion = KEYANIMANAGER->findAnimation("enemy01LeftMove");

	return S_OK;
}

void minion00::collision()
{

}