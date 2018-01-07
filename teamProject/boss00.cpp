#include "stdafx.h"
#include "boss00.h"


boss00::boss00()
{
}


boss00::~boss00()
{
}

HRESULT boss00::init(POINT point, int currentStage)
{

	_imageEnemy = IMAGEMANAGER->addFrameImage("boss00", "./images/boss00.bmp", 0, 0, 3072, 1170, 16, 6, true, RGB(255, 0, 255));
	_x = point.x;
	_y = point.y;

	//����Ʈ
	_currentStage = currentStage;
	_countMove = 0;
	
	_rcEnemy = RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight()); //�⺻��Ʈ
	_CollircEnemy = RectMakeCenter(CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x + _imageEnemy->getFrameWidth() / 2,
		CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y + _imageEnemy->getFrameHeight() / 2, 75, 75); //�浹��Ʈ

	_jump = 0; //������
	_Gravity = 0.1f; //�߷�
	_HP = 25; //ü����
	_speed = 3; //��Ƕ��

	_rndDirX = rndDirection(RND->getInt(3));
	_rndDirY = rndDirection(RND->getInt(3));

	_traceAngle = 0;
	_isTracePlayer = 0;
	_rndAttackStyle = 0;
	_alphaValue = 255;

	_isItemCollion = false;				//�������̶� �ε�����
	_isAttack = false;					//�÷��̾ �������̴�?
	_attackAniStart = false;			//���� �ִϸ��̼� ������
	_hittedAniStart = false;			//�´� �ִϸ��̼� ������
	_dieAniStart = false;

	_isDead = false;
	_isHitted = false;

	_enemyKeyName[0] = "bossRightStop";
	_enemyKeyName[1] = "bossLeftStop";
	_enemyKeyName[2] = "--�� ����--";
	_enemyKeyName[3] = "--�� ����--";
	_enemyKeyName[4] = "bossRightMove";
	_enemyKeyName[5] = "bossLeftMove";
	_enemyKeyName[6] = "bossRightOneJab";
	_enemyKeyName[7] = "bossLeftOneJab";
	_enemyKeyName[8] = "NONE";
	_enemyKeyName[9] = "NONE";
	_enemyKeyName[10] = "bossDead";
	_enemyKeyName[11] = "bossDead";
	_enemyKeyName[12] = "bossrightHit2";
	_enemyKeyName[13] = "bossleftHit2";
	_enemyKeyName[14] = "bossRightTwoJab";
	_enemyKeyName[15] = "bossLeftTwoJab";

	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightStop", "boss00", rightStop, 1, 2, true);
	int leftStop[] = { 15 };
	KEYANIMANAGER->addArrayFrameAnimation("bossLeftStop", "boss00", leftStop, 1, 2, true);
	int rightMove[] = { 0,1,2,1 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightMove", "boss00", rightMove, 4, 2, true);
	int leftMove[] = { 15,14,13,14 };
	KEYANIMANAGER->addArrayFrameAnimation("bossLeftMove", "boss00", leftMove, 4, 2, true);
	int rightOneJab[] = { 20,21,20 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightOneJab", "boss00", rightOneJab, 3, 2, false);
	int leftOneJab[] = { 27,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("bossLeftOneJab", "boss00", leftOneJab, 3, 2, false);
	int rightTwoJab[] = { 49,50,51,50 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightTwoJab", "boss00", rightTwoJab, 4, 2, false);
	int leftTwoJab[] = { 62,61,60 ,61};
	KEYANIMANAGER->addArrayFrameAnimation("bossLeftTwoJab", "boss00", leftTwoJab, 4, 2, false);
	int rightHit[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("bossrightHit", "boss00", rightHit, 1, 2, true);
	int leftHit[] = { 12 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftHit", "boss00", leftHit, 1, 2, true);
	int rightHit2[] = { 5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("bossrightHit2", "boss00", rightHit2, 2, 2, false);
	int leftHit2[] = { 11,10 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftHit2", "boss00", leftHit2, 2, 2, false);

	//����������
	int rightDown[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation("bossrightDown", "boss00", rightDown, 1, 2, true);
	int leftDown[] = { 8 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftDown", "boss00", leftDown, 1, 2, true);
	//��Ÿ�����̵� �Ǿ��� ���߻���
	int rightComboDown[] = { 6 };
	KEYANIMANAGER->addArrayFrameAnimation("bossrightComboDown", "boss00", rightComboDown, 1, 6, true);
	int leftComboDown[] = { 9 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftComboDown", "boss00", leftComboDown, 1, 6, true);
	//�ٿ� �� ���
	int rightStandUp[] = { 16 };
	KEYANIMANAGER->addArrayFrameAnimation("bossrightStandUp", "boss00", rightStandUp, 1, 6, true);
	int leftStandUp[] = { 31 };
	KEYANIMANAGER->addArrayFrameAnimation("bossleftStandUp", "boss00", leftStandUp, 1, 6, true);
	//���
	int bossDead[] = { 22,23,32,33,34,35,36,37 };
	KEYANIMANAGER->addArrayFrameAnimation("bossDead", "boss00", bossDead, 8, 2, false);

	int clime[] = { 54,55 };
	KEYANIMANAGER->addArrayFrameAnimation("bossClime", "boss00", clime, 2, 2, true);


	_enemyMotion = KEYANIMANAGER->findAnimation("bossDead");

	return S_OK;
}

//���⼭���� �ݹ��Լ�
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
