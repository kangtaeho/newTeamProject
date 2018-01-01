#include "stdafx.h"
#include "minion01.h"


minion01::minion01()
{
}


minion01::~minion01()
{
}

HRESULT minion01::init(POINT point)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("enemy07", "./images/enemy07.bmp", 0, 0, 3072, 1365, 16, 7, true, RGB(255, 0, 255));
	_x = point.x;
	_y = point.y;

	//����Ʈ

	_rcEnemy = RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight()); //�⺻��Ʈ
	_CollircEnemy = RectMakeCenter(_x, _y, 50, 50); //�浹��Ʈ
													//_EnemyDirection = ENEMYDIRECTION_RIGHT_STOP; //�⺻����
	_jump = 0; //������
	_Gravity = 0.1f; //�߷�
	_HP = 100; //ü����
	_speed = 3; //��Ƕ��


	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightStop", "enemy07", rightStop, 1, 6, true);
	int leftStop[] = { 15 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftStop", "enemy07", leftStop, 1, 6, true);
	int rightMove[] = { 0,1,2,1 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightMove", "enemy07", rightMove, 4, 10, true);
	int leftMove[] = { 15,14,13,14 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyLeftMove", "enemy07", leftMove, 4, 10, true);
	int rightRun[] = { 3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightRun", "enemy07", rightRun, 4, 6, true);
	int leftRun[] = { 12,11,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftRun", "enemy07", leftRun, 4, 6, true);
	int rightOneJab[] = { 33,34 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightOneJab", "enemy07", rightOneJab, 2, 10, true);
	int leftOneJab[] = { 46,45 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyLeftOneJab", "enemy07", leftOneJab, 2, 10, true);
	int rightTwoJab[] = { 87,96 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightTwoJab", "enemy07", rightTwoJab, 2, 10, true);
	int leftTwoJab[] = { 88,111 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyLeftTwoJab", "enemy07", leftTwoJab, 2, 10, true);
	int rightJumpAttack[] = { 32 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyRightJumpAttack", "enemy07", rightJumpAttack, 1, 10, true);
	int leftJumpAttack[] = { 47 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyLeftJumpAttack", "enemy07", leftJumpAttack, 1, 10, true);
	int rightHit[] = { 17 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightHit", "enemy07", rightHit, 1, 6, true);
	int leftHit[] = { 30 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftHit", "enemy07", leftHit, 1, 6, true);
	int rightHit2[] = { 18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightHit2", "enemy07", rightHit2, 2, 6, true);
	int leftHit2[] = { 29,28 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftHit2", "enemy07", leftHit2, 2, 6, true);
	int rightCrouch[] = { 35 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightCrouch", "enemy07", rightCrouch, 1, 6, true);
	int leftCrouch[] = { 44 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftCrouch", "enemy07", leftCrouch, 1, 6, true);
	int rightCrouchThrow[] = { 80,81,82 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightCrouchThrow", "enemy07", rightCrouchThrow, 3, 10, true);
	int leftCrouchThrow[] = { 95,94,93 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftCrouchThrow", "enemy07", leftCrouchThrow, 3, 10, true);
	//����������
	int rightDown[] = { 21 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightDown", "enemy07", rightDown, 1, 6, true);
	int leftDown[] = { 26 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftDown", "enemy07", leftDown, 1, 6, true);
	//��Ÿ�����̵� �Ǿ��� ���߻���
	int rightComboDown[] = { 20 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightComboDown", "enemy07", rightComboDown, 1, 6, true);
	int leftComboDown[] = { 27 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftComboDown", "enemy07", leftComboDown, 1, 6, true);
	//�ٿ� �� ���
	int rightStandUp[] = { 22 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightStandUp", "enemy07", rightStandUp, 1, 6, true);
	int leftStandUp[] = { 25 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftStandUp", "enemy07", leftStandUp, 1, 6, true);
	//�ٿ� �� ���
	int rightDownForever[] = { 21,84 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyrightDownForever", "enemy07", rightDownForever, 2, 6, true);
	int leftDownForever[] = { 26,84 };
	KEYANIMANAGER->addArrayFrameAnimation("enemyleftDownForever", "enemy07", leftDownForever, 2, 6, true);



	_enemyMotion = KEYANIMANAGER->findAnimation("enemyRightRun");

	return S_OK;
}

void minion01::collision()
{
}