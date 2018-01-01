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
	image* _imageEnemy;				//�̹���
	RECT _rcEnemy;				//��Ʈ
	RECT _CollircEnemy;			//�浹��Ʈ
	int _HP;					//ü��
	int _maxHP;					//�ִ�ü��
	int _speed;					//�ӵ�
	int _x, _y;					//xy��
	float _ZMove;				//z����
	float _jump, _Gravity;		//����,�߷�

	animation* _enemyMotion;
	*/

	_imageEnemy = IMAGEMANAGER->addFrameImage("boss00", "./images/boss00.bmp", 0, 0, 3072, 1170, 16, 6, true, RGB(255, 0, 255));
	_x = point.x;
	_y = point.y;

	//����Ʈ

	_rcEnemy = RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight()); //�⺻��Ʈ
	_CollircEnemy = RectMakeCenter(_x, _y, 50, 50); //�浹��Ʈ
	//_BossDirection = BOSSDIRECTION_RIGHT_STOP; //�⺻����
	_jump = 0; //������
	_Gravity = 0.1f; //�߷�
	_HP = 250; //ü����
	_speed = 3; //��Ƕ��


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
//	//���׹�rc
//	//RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x, CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y, 100, 100);
//
//
//	/*IMAGEMANAGER->findImage("boss00")->frameRender(getMemDC(),
//		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _imageBoss->getFrameWidth(), _imageBoss->getFrameHeight())).x,
//		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _imageBoss->getFrameWidth(), _imageBoss->getFrameHeight())).y, 0, 0);*/
//
//	//_imageEnemy->aniRender(getMemDC(), _rcEnemy.left, _rcEnemy.top, _enemyMotion);
//}




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
