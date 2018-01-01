#include "stdafx.h"
#include "minion00.h"


minion00::minion00()
{
}


minion00::~minion00()
{
}




HRESULT minion00::init(POINT point)
{
	  _imageEnemy = IMAGEMANAGER->addFrameImage("enemy01","./images/enemy01.bmp",0,0,3072,1344,16,7,true,RGB(255,0,255));
	  _x = point.x;
	  _y = point.y;
	  
	  //����Ʈ
	  
	  _rcEnemy = RectMakeCenter(_x,_y,_imageEnemy->getFrameWidth(),_imageEnemy->getFrameHeight()); //�⺻��Ʈ
	  _CollircEnemy = RectMakeCenter(_x, _y, 50, 50); //�浹��Ʈ
	  //_EnemyDirection = ENEMYDIRECTION_RIGHT_STOP; //�⺻����
	  _jump = 0; //������
	  _Gravity = 0.1f; //�߷�
	  _HP = 100; //ü����
	  _speed = 3; //��Ƕ��
	  
	  
	  int rightStop[] = { 0 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyRightStop", "enemy01", rightStop, 1,6,true);
	  int leftStop[] = { 15 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyleftStop", "enemy01", leftStop, 1, 6, true);
	  int rightMove[] = { 0,1,2,1 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyRightMove", "enemy01", rightMove, 4, 10, true);
	  int leftMove[] = { 15,14,13,14 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyLeftMove", "enemy01", leftMove, 4, 10, true);
	  int rightOneJab[] = { 85,86 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyRightOneJab", "enemy01", rightOneJab, 2, 10, true);
	  int leftOneJab[] = { 90,89 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyLeftOneJab", "enemy01", leftOneJab, 2, 10, true);
	  int rightTwoJab[] = { 21,22 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyRightTwoJab", "enemy01", rightTwoJab, 2, 10, true);
	  int leftTwoJab[] = { 26,25 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyLeftTwoJab", "enemy01", leftTwoJab, 2, 10, true);
	  int rightJumpAttack[] = { 19,20 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyRightJumpAttack", "enemy01", rightJumpAttack, 2, 10, true);
	  int leftJumpAttack[] = { 28,27 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyLeftJumpAttack", "enemy01", leftJumpAttack, 2, 10, true);
	  int rightHit[] = { 5 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyrightHit", "enemy01", rightHit, 1, 6, true);
	  int leftHit[] = { 10 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyleftHit", "enemy01", leftHit, 1, 6, true);
	  int rightHit2[] = { 6,7 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyrightHit2", "enemy01", rightHit2, 2, 6, true);
	  int leftHit2[] = { 9,8 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyleftHit2", "enemy01", leftHit2, 2, 6, true);
	  int rightCrouch[] = { 23 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyrightCrouch", "enemy01", rightCrouch, 1, 6, true);
	  int leftCrouch[] = { 24 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyleftCrouch", "enemy01", leftCrouch, 1, 6, true);
	  int rightCrouchThrow[] = { 35,36,37 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyrightCrouchThrow", "enemy01", rightCrouchThrow, 3, 10, true);
	  int leftCrouchThrow[] = { 44,43,42 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyleftCrouchThrow", "enemy01", leftCrouchThrow, 3, 10, true);
	  //����������
	  int rightDown[] = { 17 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyrightDown", "enemy01", rightDown, 1, 6, true);
	  int leftDown[] = { 30 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyleftDown", "enemy01", leftDown, 1, 6, true);
	  //��Ÿ�����̵� �Ǿ��� ���߻���
	  int rightComboDown[] = { 16 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyrightComboDown", "enemy01", rightComboDown, 1, 6, true);
	  int leftComboDown[] = { 31 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyleftComboDown", "enemy01", leftComboDown, 1, 6, true);
	  //�ٿ� �� ���
	  int rightStandUp[] = { 18 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyrightStandUp", "enemy01", rightStandUp, 1, 6, true);
	  int leftStandUp[] = { 29 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyleftStandUp", "enemy01", leftStandUp, 1, 6, true);
	  //�ٿ� �� ���
	  int rightDownForever[] = { 17,82 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyrightDownForever", "enemy01", rightDownForever, 2, 6, true);
	  int leftDownForever[] = { 30,82 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyleftDownForever", "enemy01", leftDownForever, 2, 6, true);
	  //���鶧 ���º�ȭ
	  int rightStoneUp[] = { 67 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyrightStoneUp", "enemy01", rightStoneUp, 1, 6, true);
	  int leftStoneUp[] = { 76 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyleftStoneUp", "enemy01", leftStoneUp, 1, 6, true);
	  int rightStoneUpMove[] = { 66,67,68,67 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyrightStoneUpMove", "enemy01", rightStoneUpMove, 4, 10, true);
	  int leftStoneUpMove[] = { 77,76,75,76 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyleftStoneUpMove", "enemy01", leftStoneUpMove, 4, 10, true);
	  int rightStoneThrow[] = { 53,54 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyrightStoneThrow", "enemy01", rightStoneThrow, 2, 10, true);
	  int leftStoneThrow[] = { 58,57 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyleftStoneThrow", "enemy01", leftStoneThrow, 2, 10, true);
	  //Į�鶧 ���º�ȭ
	  int rightKnifeThrow[] = { 51,52 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyrightKnifeThrow", "enemy01", rightKnifeThrow, 2, 10, true);
	  int leftKnifeThrow[] = { 60,59 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemyleftKnifeThrow", "enemy01", leftKnifeThrow, 2, 10, true);
	  
	  
	  
	  int clime[] = {4,5};
	  KEYANIMANAGER->addArrayFrameAnimation("enemyClime", "enemy01", clime, 2,8,true);
	  
	  
	  _enemyMotion = KEYANIMANAGER->findAnimation("enemyLeftMove");

	return S_OK;
}



//void minion00::release()
//{
//
//
//}
//
//void minion00::update()
//{
//	//ī�޶�Ȯ�ΰ� �����̴��� Ȯ����
//	//_x = (_rcEnemy.left + _rcEnemy.right) / 2;
//	//_y = (_rcEnemy.top + _rcEnemy.bottom) / 2;
//
//	//���� �𸣰���
//	//if (_x < _backgroundsizex-300) _speed = 3;
//	//if (_x > _backgroundsizex+300) _speed = -3;
//
//	//_x -= _speed;
//	_rcEnemy = RectMakeCenter(_x, _y, 100, 100);
//
//	          //switch (_EnemyDirection)
//	          //{
//	          //case ENEMYDIRECTION_RIGHT_STOP:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_MOVE:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_RUN:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_ONE_JAB:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_TWO_JAB:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_JUMP_ATTACK:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_HIT:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_HIT2:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_CROUCH:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_CROUCH_HIT:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_CROUCH_THROW:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_DOWN:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_COMBO_DOWN:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_DOWN_STAND:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_DOWN_FOREVER:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_STONE_UP:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_STONE_UP_MOVE:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_STONE_THROW:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_KNIFE_UP:
//	          //	break;
//	          //case ENEMYDIRECTION_RIGHT_KNIFE_THROW:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_STOP:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_MOVE:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_RUN:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_ONE_JAB:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_TWO_JAB:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_JUMP_ATTACK:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_HIT:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_HIT2:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_CROUCH:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_CROUCH_HIT:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_CROUCH_THROW:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_DOWN:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFR_COMBO_DOWN:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_DOWN_STAND:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_DOWN_FOREVER:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_STONE_UP:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_STONE_UP_MOVE:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_STONE_THROW:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_KNIFE_UP:
//	          //	break;
//	          //case ENEMYDIRECTION_LEFT_KNIFE_THROW:
//	          //	break;
//	          //case ENEMYDIRECTION_Clime:
//	          //	break;
//	          //default:
//	          //	break;
//	          //}
//	_rcEnemy = RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
//
//	KEYANIMANAGER->update();
//}
//
//void minion00::render()
//{
//	//���׹�rc
//	//RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x, CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y, 100, 100);
//
//	//�Ǵ��� ������
//
//	IMAGEMANAGER->findImage("enemy01")->frameRender(getMemDC(),
//		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight())).x,
//		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight())).y, 0, 0);
//
//	//_imageEnemy->aniRender(getMemDC(), _rcEnemy.left, _rcEnemy.top, _enemyMotion);
//}

void minion00::collision()
{
}