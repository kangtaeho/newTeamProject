#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}



HRESULT enemy::init(/*const char* imageName,*/POINT point)
{
	//  _imageEnemy = IMAGEMANAGER->addFrameImage("enemy01","./images/enemy01.bmp",0,0,3072,1344,16,7,true,RGB(255,0,255));
	//  _x = point.x;
	//  _y = point.y;
	//  
	//  //����Ʈ
	//  
	//  _rcEnemy = RectMakeCenter(_x,_y,_imageEnemy->getFrameWidth(),_imageEnemy->getFrameHeight()); //�⺻��Ʈ
	//  _CollircEnemy = RectMakeCenter(_x, _y, 50, 50); //�浹��Ʈ
	//  _enemyDirection = ENEMYDIRECTION_RIGHT_STOP; //�⺻����
	//  _jump = 0; //������
	//  _Gravity = 0.1f; //�߷�
	//  _HP = 100; //ü����
	//  _speed = 3; //��Ƕ��
	//  
	//  
	//  int rightStop[] = { 0 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyRightStop", "enemy01", rightStop, 1,6,true);
	//  int leftStop[] = { 16 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyleftStop", "enemy01", leftStop, 1, 6, true);
	//  int rightMove[] = { 0,1,2,1 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyRightMove", "enemy01", rightMove, 4, 10, true);
	//  int leftMove[] = { 16,15,14,15 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyLeftMove", "enemy01", leftMove, 4, 10, true);
	//  int rightOneJab[] = { 86,87 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyRightOneJab", "enemy01", rightOneJab, 2, 10, true);
	//  int leftOneJab[] = { 91,90 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyLeftOneJab", "enemy01", leftOneJab, 2, 10, true);
	//  int rightTwoJab[] = { 22,23 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyRightTwoJab", "enemy01", rightTwoJab, 2, 10, true);
	//  int leftTwoJab[] = { 27,26 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyLeftTwoJab", "enemy01", leftTwoJab, 2, 10, true);
	//  int rightJumpAttack[] = { 20,21 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyRightJumpAttack", "enemy01", rightJumpAttack, 2, 10, true);
	//  int leftJumpAttack[] = { 29,28 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyLeftJumpAttack", "enemy01", leftJumpAttack, 2, 10, true);
	//  int rightHit[] = { 6 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyrightHit", "enemy01", rightHit, 1, 6, true);
	//  int leftHit[] = { 11 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyleftHit", "enemy01", leftHit, 1, 6, true);
	//  int rightHit2[] = { 7,8 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyrightHit2", "enemy01", rightHit2, 2, 6, true);
	//  int leftHit2[] = { 10,9 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyleftHit2", "enemy01", leftHit2, 2, 6, true);
	//  int rightCrouch[] = { 24 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyrightCrouch", "enemy01", rightCrouch, 1, 6, true);
	//  int leftCrouch[] = { 25 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyleftCrouch", "enemy01", leftCrouch, 1, 6, true);
	//  int rightCrouchThrow[] = { 36,37,38 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyrightCrouchThrow", "enemy01", rightCrouchThrow, 3, 10, true);
	//  int leftCrouchThrow[] = { 45,44,43 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyleftCrouchThrow", "enemy01", leftCrouchThrow, 3, 10, true);
	//  //����������
	//  int rightDown[] = { 18 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyrightDown", "enemy01", rightDown, 1, 6, true);
	//  int leftDown[] = { 31 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyleftDown", "enemy01", leftDown, 1, 6, true);
	//  //��Ÿ�����̵� �Ǿ��� ���߻���
	//  int rightComboDown[] = { 17 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyrightComboDown", "enemy01", rightComboDown, 1, 6, true);
	//  int leftComboDown[] = { 32 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyleftComboDown", "enemy01", leftComboDown, 1, 6, true);
	//  //�ٿ� �� ���
	//  int rightStandUp[] = { 19 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyrightStandUp", "enemy01", rightStandUp, 1, 6, true);
	//  int leftStandUp[] = { 30 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyleftStandUp", "enemy01", leftStandUp, 1, 6, true);
	//  //�ٿ� �� ���
	//  int rightDownForever[] = { 18,83 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyrightDownForever", "enemy01", rightDownForever, 2, 6, true);
	//  int leftDownForever[] = { 31,83 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyleftDownForever", "enemy01", leftDownForever, 2, 6, true);
	//  //���鶧 ���º�ȭ
	//  int rightStoneUp[] = { 68 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyrightStoneUp", "enemy01", rightStoneUp, 1, 6, true);
	//  int leftStoneUp[] = { 77 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyleftStoneUp", "enemy01", leftStoneUp, 1, 6, true);
	//  int rightStoneUpMove[] = { 67,68,69,68 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyrightStoneUpMove", "enemy01", rightStoneUpMove, 4, 10, true);
	//  int leftStoneUpMove[] = { 78,77,76,77 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyleftStoneUpMove", "enemy01", leftStoneUpMove, 4, 10, true);
	//  int rightStoneThrow[] = { 54,55 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyrightStoneThrow", "enemy01", rightStoneThrow, 2, 10, true);
	//  int leftStoneThrow[] = { 59,58 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyleftStoneThrow", "enemy01", leftStoneThrow, 2, 10, true);
	//  //Į�鶧 ���º�ȭ
	//  int rightKnifeThrow[] = { 52,53 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyrightKnifeThrow", "enemy01", rightKnifeThrow, 2, 10, true);
	//  int leftKnifeThrow[] = { 61,60 };
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyleftKnifeThrow", "enemy01", leftKnifeThrow, 2, 10, true);
	//  
	//  
	//  
	//  int clime[] = {4,5};
	//  KEYANIMANAGER->addArrayFrameAnimation("enemyClime", "enemy01", clime, 2,8,true);
	//  
	//  
	//  _enemyMotion = KEYANIMANAGER->findAnimation("enemyRightStop");

	return S_OK;
}

void enemy::release()
{


}

void enemy::update()
{
	//ī�޶�Ȯ�ΰ� �����̴��� Ȯ����
	//_x = (_rcEnemy.left + _rcEnemy.right) / 2;
	//_y = (_rcEnemy.top + _rcEnemy.bottom) / 2;

	//���� �𸣰���
	//if (_x < _backgroundsizex-300) _speed = 3;
	//if (_x > _backgroundsizex+300) _speed = -3;

	//_x -= _speed;
	//_rcEnemy = RectMakeCenter(_x, _y, 100, 100);

	//          switch (_enemyDirection)
	//          {
	//          case ENEMYDIRECTION_RIGHT_STOP:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_MOVE:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_RUN:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_ONE_JAB:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_TWO_JAB:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_JUMP_ATTACK:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_HIT:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_HIT2:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_CROUCH:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_CROUCH_HIT:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_CROUCH_THROW:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_DOWN:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_COMBO_DOWN:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_DOWN_STAND:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_DOWN_FOREVER:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_STONE_UP:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_STONE_UP_MOVE:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_STONE_THROW:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_KNIFE_UP:
	//          	break;
	//          case ENEMYDIRECTION_RIGHT_KNIFE_THROW:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_STOP:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_MOVE:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_RUN:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_ONE_JAB:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_TWO_JAB:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_JUMP_ATTACK:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_HIT:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_HIT2:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_CROUCH:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_CROUCH_HIT:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_CROUCH_THROW:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_DOWN:
	//          	break;
	//          case ENEMYDIRECTION_LEFR_COMBO_DOWN:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_DOWN_STAND:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_DOWN_FOREVER:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_STONE_UP:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_STONE_UP_MOVE:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_STONE_THROW:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_KNIFE_UP:
	//          	break;
	//          case ENEMYDIRECTION_LEFT_KNIFE_THROW:
	//          	break;
	//          case ENEMYDIRECTION_Clime:
	//          	break;
	//          default:
	//          	break;
	//          }
	//_rcEnemy = RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
	_enemyMotion->start();
	KEYANIMANAGER->update();
}

void enemy::render()
{
	//���׹�rc
	//RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x, CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y, 100, 100);
	
	//�Ǵ��� ������

	//IMAGEMANAGER->findImage("enemy01")->frameRender(getMemDC(),
	//	CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight())).x,
	//	CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight())).y, 0, 0);

	_imageEnemy->aniRender(getMemDC(), _rcEnemy.left, _rcEnemy.top, _enemyMotion);
}




//���⼭���� �ݹ��Լ�
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


void enemy::collision()
{

}



//ENEMY01  �̹���