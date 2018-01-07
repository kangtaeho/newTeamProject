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
	  
	  //����Ʈ
	  _currentStage = currentStage;
	  _countMove = 0;

	  _rcEnemy = RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight()); //�⺻��Ʈ
	  _CollircEnemy = RectMakeCenter(CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x + _imageEnemy->getFrameWidth() / 2,
		  CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y + _imageEnemy->getFrameHeight() / 2, 75, 75); //�浹��Ʈ

	  _jump = 0; //������
	  _Gravity = 0.1f; //�߷�
	  _HP = 10; //ü����
	  _speed = 3; //��Ƕ��
	  _isItemCollion = false;
	  _isGetItemEnemy = true;

	  _isTracePlayer = 0;

	  _isAttack = false;				//���� ���ݻ����̴�?
	  _attackAniStart = false;			//���� �ִ� ������
	  _dieAniStart = false;
	  _isHitted = false;
	  _hittedAniStart = false;
	  
	  _rndDirX = rndDirection(RND->getInt(3));
	  _rndDirY = rndDirection(RND->getInt(3));




	  _enemyCenterX = 0;
	  _enemyCenterY = 0;
	  _playerCenterX = 0;
	  _playerCenterY = 0;

	  _traceAngle = 0;

	  _enemyKeyName[0] = "enemy01RightStop";
	  _enemyKeyName[1] = "enemy01LeftStop";
	  _enemyKeyName[2] = "--���� ������--";
	  _enemyKeyName[3] = "--���� ������--";
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




	  //������ ����

	  int rightStop[] = { 0 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01RightStop", "enemy01", rightStop, 1,2,true);
	  //���� ����
	  int leftStop[] = { 15 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01LeftStop", "enemy01", leftStop, 1, 6, true);
	  //������ ������
	  int rightMove[] = { 0,1,2,1 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01RightMove", "enemy01", rightMove, 4, 2, true);
	  //���� ������
	  int leftMove[] = { 15,14,13,14 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01LeftMove", "enemy01", leftMove, 4, 2, true);
	  //������ ��µ
	  int rightOneJab[] = { 85,86 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01RightOneJab", "enemy01", rightOneJab, 2, 2, true);
	  //���� ��µ
	  int leftOneJab[] = { 90,89 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01LeftOneJab", "enemy01", leftOneJab, 2, 2, true);
	  //������ ��µ
	  int rightTwoJab[] = { 21,22 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01RightTwoJab", "enemy01", rightTwoJab, 2, 2, true);
	  //���� ��µ
	  int leftTwoJab[] = { 26,25 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01LeftTwoJab", "enemy01", leftTwoJab, 2, 2, true);
	  //������ ��������
	  int rightJumpAttack[] = { 19,20 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01RightJumpAttack", "enemy01", rightJumpAttack, 2, 2, true);
	  //���� ��������
	  int leftJumpAttack[] = { 28,27 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01LeftJumpAttack", "enemy01", leftJumpAttack, 2, 2, true);
	  //������ 1��Ʈ
	  int rightHit[] = { 5 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01RightHit", "enemy01", rightHit, 1, 2, true);
	  //���� 1��Ʈ
	  int leftHit[] = { 10 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01LeftHit", "enemy01", leftHit, 1, 2, true);
	  //������ ��������
	  int rightHit2[] = { 6,7 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightHit2", "enemy01", rightHit2, 2, 2, true);

	  //�÷��̾ ���ʿ��� ������(�÷��̾� ��ġ�� ����)
	  int leftHittied[] = { 46,47,48,47 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01LeftHitted", "enemy01", leftHittied, 4, 2, false);

	  //�÷��̾ �����ʿ��� ������(�÷��̾� ��ġ�� ������)
	  int rightHittied[] = { 35, 34, 33, 34 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightHitted", "enemy01", rightHittied, 4, 2, false);

	  //���� ��������
	  int leftHit2[] = { 9,8 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftHit2", "enemy01", leftHit2, 2, 2, true);
	  //������ ������
	  int rightCrouch[] = { 23 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightCrouch", "enemy01", rightCrouch, 1, 2, true);
	  //���� ������
	  int leftCrouch[] = { 24 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftCrouch", "enemy01", leftCrouch, 1, 2, true);
	  //������ ���������
	  int rightCrouchThrow[] = { 35,36,37 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightCrouchThrow", "enemy01", rightCrouchThrow, 3, 4, true);
	  //���� ���������
	  int leftCrouchThrow[] = { 44,43,42 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftCrouchThrow", "enemy01", leftCrouchThrow, 3, 4, true);

	  //������ ����������
	  int rightDown[] = { 17 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightDown", "enemy01", rightDown, 1, 6, true);
	  //���� ����������
	  int leftDown[] = { 30 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftDown", "enemy01", leftDown, 1, 6, true);

	  //������ ��Ÿ�����̵� �Ǿ��� ���߻���
	  int rightComboDown[] = { 16 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightComboDown", "enemy01", rightComboDown, 1, 6, true);
	  //����  �¾Ƽ� ���߻���
	  int leftComboDown[] = { 31 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftComboDown", "enemy01", leftComboDown, 1, 6, true);

	  //������ �ٿ� �� ���
	  int rightStandUp[] = { 18 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightStandUp", "enemy01", rightStandUp, 1, 6, true);
	  //���� �ٿ� �� ���
	  int leftStandUp[] = { 29 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftStandUp", "enemy01", leftStandUp, 1, 6, true);

	  //������ �ٿ� �� ���
	  int rightDownForever[] = { 17,82 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightDownForever", "enemy01", rightDownForever, 2, 4, true);
	  //���� �ٿ� �� ���
	  int leftDownForever[] = { 30,82 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftDownForever", "enemy01", leftDownForever, 2, 4, true);

	  //������ �� ����
	  int rightStoneUp[] = { 67 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightStoneUp", "enemy01", rightStoneUp, 1, 6, true);
	  //���� �� ����
	  int leftStoneUp[] = { 76 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftStoneUp", "enemy01", leftStoneUp, 1, 6, true);
	  //������ ����� ������
	  int rightStoneUpMove[] = { 66,67,68,67 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightStoneUpMove", "enemy01", rightStoneUpMove, 4, 2, true);
	  //���� ����� ������
	  int leftStoneUpMove[] = { 77,76,75,76 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftStoneUpMove", "enemy01", leftStoneUpMove, 4, 2, true);
	  //������ ������
	  int rightStoneThrow[] = { 53,54 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightStoneThrow", "enemy01", rightStoneThrow, 2, 3, true);
	  //���� ������
	  int leftStoneThrow[] = { 58,57 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftStoneThrow", "enemy01", leftStoneThrow, 2, 3, true);

	  //������ Į����
	  int rightKnifeThrow[] = { 51,52 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01rightKnifeThrow", "enemy01", rightKnifeThrow, 2, 2, true);
	  //���� Į����
	  int leftKnifeThrow[] = { 60,59 };
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01leftKnifeThrow", "enemy01", leftKnifeThrow, 2, 2, true);

	  
	  
	  
	  int clime[] = {4,5};
	  KEYANIMANAGER->addArrayFrameAnimation("enemy01Clime", "enemy01", clime, 2,2,true);
	  
	  
	  _enemyMotion = KEYANIMANAGER->findAnimation("enemy01LeftMove");

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