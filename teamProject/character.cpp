#include "stdafx.h"
#include "character.h"
#include "item.h"
#include "enemyManager.h"


character::character()
{
}


character::~character()
{
}

HRESULT character::init()
{
	addImage();

	_state = CHARA_RIGHT_STOP;
	_Zmove = CHARASPEED;
	_x = _StartX = WINSIZEX / 2;
	_y = _StartY = WINSIZEY / 2;
	_isRight = true;
	_isOn = true;
	_JP = 0;
	_gravity = 0.1f;
	_HP = _maxHP = 10;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_colliRect = RectMakeCenter(_x, _y, 54, 120);

	_isItemCollision = false;
	_isHanded = false;

	_potion = NULL;

	return S_OK;

}
void character::release()
{

}
void character::update()
{
	//if (KEYMANAGER->isStayKeyDown(VK_UP))
	//{
	//}
	//if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	//{
	//}
	//if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	//{
	//}
	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	//{
	//}
	if (KEYMANAGER->isOnceKeyDown('6'))
	{
		hurt(1, WINSIZEX + 100);
	}
	

	switch (_state)
	{
		//�������
	case CHARA_RIGHT_STOP:
	case CHARA_LEFT_STOP:
	case CHARA_RIGHT_STONE_STOP:
	case CHARA_LEFT_STONE_STOP:
		if (KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			//_isRight��� ������ �ʿ����
			//why?? ĳ������ ���¿� right, left ������ ����ֱ� �����̴�.
			if (_state == CHARA_RIGHT_STOP)
			{
				_state = CHARA_RIGHT_MOVE;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightMove");
				_motion->start();
			}
			else if (_state == CHARA_LEFT_STOP)
			{
				_state = CHARA_LEFT_MOVE;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftMove");
				_motion->start();
			}
			else if (_state == CHARA_RIGHT_STONE_STOP)
			{
				//ū���� ������
				if (_itemType == 2 || _itemType == 0)
				{
					_state = CHARA_RIGHT_STONE_HAND;
					_motion->stop();
					_motion = KEYANIMANAGER->findAnimation("JIMMYRightStoneMove");
					_motion->start();
				}
			}
			else if (_state == CHARA_LEFT_STONE_STOP)
			{
				//ū���� ������
				if (_itemType == 2 || _itemType == 0)
				{
					_state = CHARA_LEFT_STONE_HAND;
					_motion->stop();
					_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStoneMove");
					_motion->start();
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown('Z'))//����
		{
			if (_stageCount != 2)
			{
				_StartY = _y;
			}
			_JP = CHARASPEED;
			if (_state == CHARA_RIGHT_STOP)
			{
				_state = CHARA_RIGHT_JUMP;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightJump");
				_motion->start();
			}
			else if (_state == CHARA_LEFT_STOP)
			{
				_state = CHARA_LEFT_JUMP;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftJump");
				_motion->start();
			}
		}

		if (_stageCount == 2 && !_isOn)
		{
			_y -= _JP;
			_JP -= _gravity;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_state == CHARA_RIGHT_STONE_STOP || _state == CHARA_LEFT_STONE_STOP)//�Ǵ� �����϶�
			{
				_isRight = false;
				_state = CHARA_LEFT_STONE_HAND;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStoneMove");
				_motion->start();
			}
			else
			{
				_isRight = false;
				_state = CHARA_LEFT_MOVE;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftMove");
				_motion->start();
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_state == CHARA_RIGHT_STONE_STOP || _state == CHARA_LEFT_STONE_STOP)//�Ǵ� �����϶�
			{
				_state = CHARA_RIGHT_STONE_HAND;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightStoneMove");
				_motion->start();
			}
			else
			{
				_isRight = true;
				_state = CHARA_RIGHT_MOVE;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightMove");
				_motion->start();
			}
		}
		if (KEYMANAGER->isOnceKeyDown('X'))//�ָ�
		{
			//������ �浹 ����
			if (_state == CHARA_RIGHT_STONE_STOP)
			{
				_state = CHARA_RIGHT_STONE_THROWING;
				_item->setState(true);
				_item->setIsRight(true);
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightStoneThrow");
				_motion->start();
				_item->setThrowPower(0);
				_item->setEndY(_rc.bottom);
				_isHanded = false;
			}
			else if (_state == CHARA_LEFT_STONE_STOP)
			{
				_state = CHARA_LEFT_STONE_THROWING;
				_item->setState(true);
				_item->setIsRight(false);
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStoneThrow");
				_motion->start();
				_item->setThrowPower(0);
				_item->setEndY(_rc.bottom);
				_isHanded = false;
			}
			else
			{
				if (_isItemCollision == true && _state == CHARA_RIGHT_STOP)
				{
					_isHanded = true;
					//���� ��
					if (_itemType == 0)
					{
						_state = CHARA_RIGHT_STONE_STOP;
						_item->setX(_x);
						_item->setY(_rc.top + 5);
						_motion = KEYANIMANAGER->findAnimation("JIMMYRightStoneStop");
						_motion->start();
					}
					//ū ��
					else if (_itemType == 2)
					{
						_state = CHARA_RIGHT_STONE_STOP;
						_item->setX(_x);
						_item->setY(_rc.top - 20);
						_motion = KEYANIMANAGER->findAnimation("JIMMYRightStoneStop");
						_motion->start();
					}
				}
				else if (_isItemCollision == true && _state == CHARA_LEFT_STOP)
				{
					_isHanded = true;
					//���� ��
					if (_itemType == 0)
					{
						_state = CHARA_LEFT_STONE_STOP;
						_item->setX(_x);
						_item->setY(_rc.top + 5);
						_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStoneStop");
						_motion->start();
					}
					//ū ��
					else if (_itemType == 2)
					{
						_state = CHARA_LEFT_STONE_STOP;
						_item->setX(_x);
						_item->setY(_rc.top - 20);
						_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStoneStop");
						_motion->start();
					}
				}
				//������ �浹 ����
				else {
					if (_state == CHARA_RIGHT_STOP)
					{
						_state = CHARA_RIGHT_PUNCH_ONE;
						_motion->stop();
						_motion = KEYANIMANAGER->findAnimation("JIMMYRightPunchOne");
						_motion->start();
					}
					else if (_state == CHARA_LEFT_STOP)
					{
						_state = CHARA_LEFT_PUNCH_ONE;
						_motion->stop();
						_motion = KEYANIMANAGER->findAnimation("JIMMYLeftPunchOne");
						_motion->start();
					}

					SOUNDMANAGER->play("��(������)", 1.0);
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown('C'))//ű
		{
			SOUNDMANAGER->play("���(�������Ҷ�)", 1.0);
			if (_state == CHARA_RIGHT_STOP)
			{
				_state = CHARA_RIGHT_KICK;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightKick");
				_motion->start();
			}
			else if (_state == CHARA_LEFT_STOP)
			{
				_state = CHARA_LEFT_KICK;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftKick");
				_motion->start();
			}
		}
		break;

	case CHARA_RIGHT_MOVE://���������� �����̴� ��
	case CHARA_RIGHT_STONE_HAND:
	{
		if (_stageCount == 2 && !_isOn)
		{
			_y -= _JP;
			_JP -= _gravity;
		}
		 //�����¿�Ű�� �������°� �ƴ϶��
		 if (!KEYMANAGER->isStayKeyDown(VK_UP))
		 if (!KEYMANAGER->isStayKeyDown(VK_DOWN))
		 if (!KEYMANAGER->isStayKeyDown(VK_RIGHT))
		 {
			 //������ �����̴� �����̸�
			 if (_state == CHARA_RIGHT_MOVE)
			 {
				 _state = CHARA_RIGHT_STOP;//������·� ������
				 _motion = KEYANIMANAGER->findAnimation("JIMMYRightStop");
				 _motion->start();
			 }
			 //���� ��� ������
			 else
			 {
				 _state = CHARA_RIGHT_STONE_STOP;
				 _motion = KEYANIMANAGER->findAnimation("JIMMYRightStoneStop");
				 _motion->start();
			 }
		 }
		 //�� ��� ������ ���� XX
		 if (KEYMANAGER->isOnceKeyDown('Z') && _state == CHARA_RIGHT_MOVE)//����
		 {
		  //SOUNDMANAGER->play("���(�������Ҷ�)", 1.0);
			 if (_stageCount != 2)
			 {
				 _StartY = _y;
			 }
		  _JP = CHARASPEED;
		  _state = CHARA_RIGHT_MOVE_JUMP;
		  _motion->stop();
		  _motion = KEYANIMANAGER->findAnimation("JIMMYRightJump");
		  _motion->start();
		 }


		 //if (KEYMANAGER->isOnceKeyUp(VK_UP))
		 //{
		 //	_state = CHARA_RIGHT_STOP;//������·� ������
		 //	_motion->stop();
		 //	_motion = KEYANIMANAGER->findAnimation("JIMMYRightStop");
		 //	_motion->start();
		 //}
		 //else 
		 if (KEYMANAGER->isStayKeyDown(VK_UP)&&_stageCount!=2)
		 {
		  COLORREF color = GetPixel(_stage->getMemDC(), _x, _rc.bottom - 3);

		  int r = GetRValue(color);
		  int g = GetGValue(color);
		  int b = GetBValue(color);

		  if ((r == 255 && g == 0 && b == 0))
		  {
			  //if(��ٸ��� Ż �� �ְ� �Ǿ���)
			  //{
			  //_state = CHARA_STAIR;
			  //_motion = KEYANIMANAGER->findAnimation("JIMMYStairStop");
			  //_motion->start();
			  //}
			  //else
			  _y -= _Zmove;

			  //���� y�� ����
			  if (_state == CHARA_RIGHT_STONE_HAND)
			  {
				  _item->setY(_item->getY() - _Zmove);
			  }
		  }
		 }
		 if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _stageCount != 2)
		 {
		  COLORREF color = GetPixel(_stage->getMemDC(), _x, _rc.bottom + 3);

		  int r = GetRValue(color);
		  int g = GetGValue(color);
		  int b = GetBValue(color);

		  if ((r == 255 && g == 0 && b == 0))
		  {
			  //if(��ٸ��� Ż �� �ְ� �Ǿ���)
			  //{
			  //_state = CHARA_STAIR;
			  //_motion = KEYANIMANAGER->findAnimation("JIMMYStairStop");
			  //_motion->start();
			  //}
			  //else
			  _y += _Zmove;

			  //���� y�� ����
			  if (_state == CHARA_RIGHT_STONE_HAND)
			  {
				  _item->setY(_item->getY() + _Zmove);
			  }
		  }
		 }

		 //if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		 //{
		 //	_state = CHARA_RIGHT_STOP;//������·� ������
		 //	_motion->stop();
		 //	_motion = KEYANIMANAGER->findAnimation("JIMMYRightStop");
		 //	_motion->start();
		 //}
		 //else
		 if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		 {
			
			// else
		  _x += CHARASPEED;
		  if (_state == CHARA_RIGHT_STONE_HAND)
		  {
			  _item->setX(_x);
		  }
		 }

		 //if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_DOWN) || KEYMANAGER->isOnceKeyUp(VK_UP))
		 //{
		 //	_state = CHARA_RIGHT_STOP;//������·� ������
		 //	_motion = KEYANIMANAGER->findAnimation("JIMMYRightStop");
		 //	_motion->start();
		 //}


		 break;
	}
	case CHARA_LEFT_MOVE://�������� �����̴� ��
	case CHARA_LEFT_STONE_HAND:
	{
		if (_stageCount == 2 && !_isOn)
		{
			_y -= _JP;
			_JP -= _gravity;
		}
		//�����¿�Ű�� �������°� �ƴ϶��
		if (!KEYMANAGER->isStayKeyDown(VK_UP))
			if (!KEYMANAGER->isStayKeyDown(VK_DOWN))
				if (!KEYMANAGER->isStayKeyDown(VK_LEFT))
				{
					if (_state == CHARA_LEFT_MOVE)
					{
						_state = CHARA_LEFT_STOP;//������·� ������
						_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStop");
						_motion->start();
					}
					else
					{
						_state = CHARA_LEFT_STONE_STOP;//������·� ������
						_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStoneStop");
						_motion->start();
					}
				}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_x -= CHARASPEED;
			if (_state == CHARA_LEFT_STONE_HAND)
			{
				_item->setX(_x);
			}
		}

		if (KEYMANAGER->isOnceKeyDown('Z') && _state == CHARA_LEFT_MOVE)//����
		{
			if (_stageCount != 2)
			{
				_StartY = _y;
			}
			_JP = CHARASPEED;
			_state = CHARA_LEFT_MOVE_JUMP;
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation("JIMMYLeftJump");
			_motion->start();
		}

		if (KEYMANAGER->isStayKeyDown(VK_UP) && _stageCount != 2)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), _x, _rc.bottom - 3);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0))
			{
				//if(��ٸ��� Ż �� �ְ� �Ǿ���)
				//{
				//_state = CHARA_STAIR;
				//_motion = KEYANIMANAGER->findAnimation("JIMMYStairStop");
				//_motion->start();
				//}
				//else
				_y -= _Zmove;
				if (_state == CHARA_LEFT_STONE_HAND)
				{
					_item->setY(_item->getY() - _Zmove);
				}
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _stageCount != 2)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), _x, _rc.bottom + 3);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0))
			{
				//if(��ٸ��� Ż �� �ְ� �Ǿ���)
				//{
				//_state = CHARA_STAIR;
				//_motion = KEYANIMANAGER->findAnimation("JIMMYStairStop");
				//_motion->start();
				//}
				//else
				_y += _Zmove;
				if (_state == CHARA_LEFT_STONE_HAND)
				{
					_item->setY(_item->getY() + _Zmove);
				}
			}
		}

		break;
	}
	case CHARA_RIGHT_LAND:
	case CHARA_LEFT_LAND:
		if (KEYMANAGER->isOnceKeyDown('X'))//�ָ�
		{
			SOUNDMANAGER->play("��(������)", 1.0);
			if (_isRight)
			{
				_state = CHARA_RIGHT_UPPER;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightUpper");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_UPPER;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftUpper");
				_motion->start();
			}

		}

		//��ű �ϰ��� y�� �����۾� ���ߵȴ�.
		if (KEYMANAGER->isOnceKeyDown('C'))//ű
		{
			if (_stageCount != 2)
			{
				_StartY = _y;
			}
			_JP = CHARAJUMP;
			if (_isRight)
			{
				_state = CHARA_RIGHT_DRILL;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightKneeKick");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_DRILL;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftKneeKick");
				_motion->start();
			}
		}
		break;

	case CHARA_RIGHT_PUNCH_ONE:
	case CHARA_LEFT_PUNCH_ONE:
		//��ġ�� ������ȯ
		for (int i = 0; i <_EM->getVMinion().size(); ++i)
		{
			RECT temp;
			if (_state== CHARA_RIGHT_PUNCH_ONE)
			{
				if (IntersectRect(&temp, &_rightATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
					break;
				}
			}
			else
			{
				if (IntersectRect(&temp, &_leftATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
					break;
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_isRight)
			{
				_state = CHARA_RIGHT_BACKBLOW;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightBackBlow");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_HEAD;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftHead");
				_motion->start();
			}
		}
		//��ġ�� ������ȯ
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_isRight)
			{
				_state = CHARA_RIGHT_HEAD;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightHead");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_BACKBLOW;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftBackBlow");
				_motion->start();
			}
		}
		else if (KEYMANAGER->isOnceKeyDown('X'))
		{
			SOUNDMANAGER->play("��(������)", 1.0);
			if (_isRight)
			{
				_state = CHARA_RIGHT_PUNCH_TWO;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightPunchTwo");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_PUNCH_TWO;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftPunchTwo");
				_motion->start();
			}
		}
		break;
	case CHARA_RIGHT_PUNCH_TWO:
	case CHARA_LEFT_PUNCH_TWO:
		for (int i = 0; i <_EM->getVMinion().size(); ++i)
		{
			RECT temp;
			if (_state == CHARA_RIGHT_PUNCH_TWO)
			{
				if (IntersectRect(&temp, &_rightATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
				}
			}
			else
			{
				if (IntersectRect(&temp, &_leftATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
				}
			}
		}
		//��ġ�� ������ȯ
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_isRight)
			{
				_state = CHARA_RIGHT_BACKBLOW;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightBackBlow");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_HEAD;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftHead");
				_motion->start();
			}
		}
		//��ġ�� ������ȯ
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_isRight)
			{
				_state = CHARA_RIGHT_HEAD;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightHead");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_BACKBLOW;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftBackBlow");
				_motion->start();
			}
		}
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			for (int i = 0; i < _EM->getVMinion().size(); ++i)
			{
				RECT temp;
				if (_state == CHARA_RIGHT_PUNCH_TWO)
				{
					if (IntersectRect(&temp, &_rightATK, &_EM->getVMinion()[i]->getCollircEnemy()))
					{
						_state = CHARA_RIGHT_UPPER;
						_motion->stop();
						_motion = KEYANIMANAGER->findAnimation("JIMMYRightUpper");
						_motion->start();
						_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
						_EM->getVMinion()[i]->setIsTracePlayer(5);
						_EM->getVMinion()[i]->setIsHitted(true);
					}
				}
				else
				{
					if (IntersectRect(&temp, &_leftATK, &_EM->getVMinion()[i]->getCollircEnemy()))
					{
						_state = CHARA_LEFT_UPPER;
						_motion->stop();
						_motion = KEYANIMANAGER->findAnimation("JIMMYLeftUpper");
						_motion->start();
						_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
						_EM->getVMinion()[i]->setIsTracePlayer(5);
						_EM->getVMinion()[i]->setIsHitted(true);
					}
				}
			}
		}
		
		break;
	case CHARA_LEFT_KICK:
	case CHARA_RIGHT_KICK:
		for (int i = 0; i <_EM->getVMinion().size(); ++i)
		{
			RECT temp;
			if (_state == CHARA_RIGHT_KICK)
			{
				if (IntersectRect(&temp, &_rightATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
				}
			}
			else
			{
				if (IntersectRect(&temp, &_leftATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
				}
			}
		}
		//ű�� ������ȯ
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_isRight)
			{
				_state = CHARA_RIGHT_BACKBLOW;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightBackBlow");
				_motion->start();
			}
			else
			{
				if (_stageCount != 2)
				{
					_StartY = _y;
				}
				_JP = CHARAJUMP;
				_JP = _JP / 2;
				_state = CHARA_LEFT_BACKKICK;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftBackKick");
				_motion->start();
			}
		}
		//ű�� ������ȯ
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_isRight)
			{
				if (_stageCount != 2)
				{
					_StartY = _y;
				}
				_JP = CHARAJUMP;
				_JP = _JP / 2;
				_state = CHARA_RIGHT_BACKKICK;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightBackKick");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_BACKBLOW;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftBackBlow");
				_motion->start();
			}
		}
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			for (int i = 0; i < _EM->getVMinion().size(); ++i)
			{
				RECT temp;
				if (_state == CHARA_RIGHT_KICK)
				{
					if (IntersectRect(&temp, &_rightATK, &_EM->getVMinion()[i]->getCollircEnemy()))
					{
						_state = CHARA_RIGHT_HIGHKICK;
						_motion->stop();
						_motion = KEYANIMANAGER->findAnimation("JIMMYRightHighKick");
						_motion->start();
						_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
						_EM->getVMinion()[i]->setIsTracePlayer(5);
						_EM->getVMinion()[i]->setIsHitted(true);
					}
				}
				else
				{
					if (IntersectRect(&temp, &_leftATK, &_EM->getVMinion()[i]->getCollircEnemy()))
					{
						_state = CHARA_LEFT_HIGHKICK;
						_motion->stop();
						_motion = KEYANIMANAGER->findAnimation("JIMMYLeftHighKick");
						_motion->start();
						_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
						_EM->getVMinion()[i]->setIsTracePlayer(5);
						_EM->getVMinion()[i]->setIsHitted(true);
					}
				}
			}
		}
		//if(������ ������ ������)
		//  {����ű
		//	if (_isRight)
		//	{
		//		
		//		
		//		
		//	}
		//	else
		//	{
		//		
		//		
		//		
		//	}
		//  }
		break;
	case CHARA_RIGHT_HEAD:
	case CHARA_LEFT_HEAD:
		for (int i = 0; i <_EM->getVMinion().size(); ++i)
		{
			RECT temp;
			if (_state == CHARA_RIGHT_HEAD)
			{
				if (IntersectRect(&temp, &_rightATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
				}
			}
			else
			{
				if (IntersectRect(&temp, &_leftATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown('X'))//�ָ�
		{
			if (_stageCount != 2)
			{
				_StartY = _y;
			}
			_JP = CHARAJUMP;
			if (_isRight)
			{
				_state = CHARA_RIGHT_DRILL;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightDrill");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_DRILL;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftDrill");
				_motion->start();
			}
		}
		break;
	case CHARA_RIGHT_HOLD:
	case CHARA_LEFT_HOLD:
		//��Ǹ��ְ� �������ֵ���
		break;
	case CHARA_RIGHT_JUMP:
	case CHARA_LEFT_JUMP:
		_y -= _JP;
		_JP -= _gravity;
		if (_StartY <= _y&&_stageCount != 2)
		{
			_y = _StartY;
			if (_isRight)
			{
				_state = CHARA_RIGHT_LAND;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightLand");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_LAND;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftLand");
				_motion->start();
			}
		}
		if (KEYMANAGER->isOnceKeyDown('C')|| KEYMANAGER->isOnceKeyDown('X'))//������
		{
			SOUNDMANAGER->play("���(�������Ҷ�)", 1.0);
			if (_JP*_JP <= 1)
			{
				_JP = 0;
				if (_isRight)
				{
					_state = CHARA_RIGHT_ATT;
					_motion->stop();
					_motion = KEYANIMANAGER->findAnimation("JIMMYRightATT");
					_motion->start();
				}
				else
				{
					_state = CHARA_LEFT_ATT;
					_motion->stop();
					_motion = KEYANIMANAGER->findAnimation("JIMMYLeftATT");
					_motion->start();
				}
			}
			else
			{
				if (_isRight)
				{
					_state = CHARA_RIGHT_JUMP_KICK;
					_motion->stop();
					_motion = KEYANIMANAGER->findAnimation("JIMMYRightJumpKick");
					_motion->start();
				}
				else
				{
					_state = CHARA_LEFT_JUMP_KICK;
					_motion->stop();
					_motion = KEYANIMANAGER->findAnimation("JIMMYLeftJumpKick");
					_motion->start();
				}
			}
		}
		break;
	case CHARA_RIGHT_MOVE_JUMP:
	case CHARA_LEFT_MOVE_JUMP:
		
		_y -= _JP;
		_JP -= _gravity;
		if (_isRight)
		{
			_x += CHARASPEED;
		}
		else
		{
			_x -= CHARASPEED;
		}
		if (_StartY <= _y&&_stageCount != 2)
		{
			_JP = 0;
			_y = _StartY;
			if (_isRight)
			{
				_state = CHARA_RIGHT_LAND;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightLand");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_LAND;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftLand");
				_motion->start();
			}
		}
		if (KEYMANAGER->isOnceKeyDown('C') || KEYMANAGER->isOnceKeyDown('X'))//������
		{
			SOUNDMANAGER->play("���(�������Ҷ�)", 1.0);
			if (_JP*_JP <= 1)
			{
				_JP = 0;
				if (_isRight)
				{
					_state = CHARA_RIGHT_ATT;
					_motion->stop();
					_motion = KEYANIMANAGER->findAnimation("JIMMYRightATT");
					_motion->start();
				}
				else
				{
					_state = CHARA_LEFT_ATT;
					_motion->stop();
					_motion = KEYANIMANAGER->findAnimation("JIMMYLeftATT");
					_motion->start();
				}
			}
			else
			{
				if (_isRight)
				{
					_state = CHARA_RIGHT_MOVE_JUMP_KICK;
					_motion->stop();
					_motion = KEYANIMANAGER->findAnimation("JIMMYRightJumpKick");
					_motion->start();
				}
				else
				{
					_state = CHARA_LEFT_MOVE_JUMP_KICK;
					_motion->stop();
					_motion = KEYANIMANAGER->findAnimation("JIMMYLeftJumpKick");
					_motion->start();
				}
			}
		}
		break;
	case CHARA_RIGHT_BACKKICK:
	case CHARA_LEFT_BACKKICK:
		for (int i = 0; i <_EM->getVMinion().size(); ++i)
		{
			RECT temp;
			if (_state == CHARA_RIGHT_BACKKICK)
			{
				if (IntersectRect(&temp, &_rightATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
				}
			}
			else
			{
				if (IntersectRect(&temp, &_leftATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
				}
			}
		}
		_y -= _JP;
		_JP -= _gravity*2;
		if (_isRight)
		{
			_x += 2;
		}
		else
		{
			_x -= 2;
		}
		if (_StartY < _y&&_stageCount != 2)
		{
			_state = CHARA_LEFT_STOP;
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStop");
			_motion->start();
		}
		break;
	case CHARA_RIGHT_DRILL:
	case CHARA_LEFT_DRILL:
		for (int i = 0; i <_EM->getVMinion().size(); ++i)
		{
			RECT temp;
			if (_state == CHARA_RIGHT_DRILL)
			{
				if (IntersectRect(&temp, &_rightATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
				}
			}
			else
			{
				if (IntersectRect(&temp, &_leftATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
				}
			}
		}
		//��ű�� �����ٰ�
		_y -= _JP/2;
		_JP -= _gravity*2;
		if (_isRight)
		{
			_x += CHARASPEED;
		}
		else
		{
			_x -= CHARASPEED;
		}
		if (_JP <= 0)
		{
			_JP = 0;
			if (_isRight)
			{
				_state = CHARA_RIGHT_JUMP;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightJump");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_JUMP;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftJump");
				_motion->start();
			}
		}
		break;
	case CHARA_STAIR:
		//����� Ż �� �ִ� ���°� �Ǿ���(�������� ����ʿ�)
		if (!(KEYMANAGER->isStayKeyDown(VK_UP) && KEYMANAGER->isStayKeyDown(VK_DOWN)))
		{
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation("JIMMYStairStop");
			_motion->start();
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			//if(�� �ö�Դ�)
			//{
			//	if (_isRight)
			//	{
			//		_state = CHARA_RIGHT_STOP;
			//		_motion = KEYANIMANAGER->findAnimation("JIMMYRightStop");
			//		_motion->start();
			//	}
			//	else
			//	{
			//		_state = CHARA_LEFT_STOP;
			//		_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStop");
			//		_motion->start();
			//	}
			//}
			//else
			_y -= CHARASPEED;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_motion = KEYANIMANAGER->findAnimation("JIMMYStairMove");
			_motion->start();
		}
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			_state = CHARA_STAIR;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			//if(�� �����Դ�)
			//{
			//	if (_isRight)
			//	{
			//		_state = CHARA_RIGHT_STOP;
			//		_motion = KEYANIMANAGER->findAnimation("JIMMYRightStop");
			//		_motion->start();
			//	}
			//	else
			//	{
			//		_state = CHARA_LEFT_STOP;
			//		_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStop");
			//		_motion->start();
			//	}
			//}
			//else
			_y += CHARASPEED;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation("JIMMYStairMove");
			_motion->start();
		}
		break;
	case CHARA_RIGHT_HIT:
	case CHARA_LEFT_HIT:
		//������ �Դ� �Լ�����
		break;
	case CHARA_RIGHT_STRIKED:
	case CHARA_LEFT_STRIKED:
		//�������� �Լ�����
		_y -= _JP;
		_JP -= _gravity;
		if (_isRight)
		{
			_x -= CHARASPEED;
		}
		else
		{
			_x += CHARASPEED;
		}
		if (_StartY < _y&&_stageCount != 2)
		{
			if (_isRight)
			{
				_state = CHARA_RIGHT_DOWN;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightDown");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_DOWN;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftDown");
				_motion->start();
			}
		}
		break;
	case CHARA_RIGHT_DOWN:
	case CHARA_LEFT_DOWN:
		//����
		//��üfps������
		break;
	case CHARA_RIGHT_JUMP_KICK:
	case CHARA_LEFT_JUMP_KICK:
		for (int i = 0; i <_EM->getVMinion().size(); ++i)
		{
			RECT temp;
			if (_state == CHARA_RIGHT_JUMP_KICK)
			{
				if (IntersectRect(&temp, &_rightATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
				}
			}
			else
			{
				if (IntersectRect(&temp, &_leftATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
				}
			}
		}
		_y -= _JP;
		_JP -= _gravity;
		if (_StartY <= _y&&_stageCount != 2)
		{
			_JP = 0;
			_y = _StartY;
			if (_isRight)
			{
				_state = CHARA_RIGHT_LAND;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightLand");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_LAND;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftLand");
				_motion->start();
			}
		}
		break;
	case CHARA_RIGHT_MOVE_JUMP_KICK:
	case CHARA_LEFT_MOVE_JUMP_KICK:
		for (int i = 0; i <_EM->getVMinion().size(); ++i)
		{
			RECT temp;
			if (_state == CHARA_RIGHT_MOVE_JUMP_KICK)
			{
				if (IntersectRect(&temp, &_rightATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
				}
			}
			else
			{
				if (IntersectRect(&temp, &_leftATK, &_EM->getVMinion()[i]->getCollircEnemy()))
				{
					_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
					_EM->getVMinion()[i]->setIsTracePlayer(5);
					_EM->getVMinion()[i]->setIsHitted(true);
				}
			}
		}
		_y -= _JP;
		_JP -= _gravity;
		if (_isRight)
		{
			_x += CHARASPEED;
		}
		else
		{
			_x -= CHARASPEED;
		}
		if (_StartY <= _y&&_stageCount != 2)
		{
			_JP = 0;
			_y = _StartY;
			if (_isRight)
			{
				_state = CHARA_RIGHT_LAND;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightLand");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_LAND;
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftLand");
				_motion->start();
			}
		}
		break;
	case CHARA_RIGHT_ATT:
	case CHARA_LEFT_ATT:
		//JP�� 0�ػ���
		for (int i = 0; i < _EM->getVMinion().size(); ++i)
		{
			RECT temp;
			if (IntersectRect(&temp, &_rightATK, &_EM->getVMinion()[i]->getCollircEnemy()))
			{
				_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
				_EM->getVMinion()[i]->setIsTracePlayer(5);
				_EM->getVMinion()[i]->setIsHitted(true);
			}
			if (IntersectRect(&temp, &_leftATK, &_EM->getVMinion()[i]->getCollircEnemy()))
			{
				_EM->getVMinion()[i]->setHP(_EM->getVMinion()[i]->getHP() - 1);
				_EM->getVMinion()[i]->setIsTracePlayer(5);
				_EM->getVMinion()[i]->setIsHitted(true);
			}
		}
		break;
		
	default:
		break;
	}
	
	 if (_stageCount == 2)
			 {
				 for (int i = _x; i < _x + 27; i++)
				 {
					 COLORREF color = GetPixel(_stage->getMemDC(), i, _rc.bottom);
					 //������ i+2�������� ī�޶� X
					 //_rc.bottom+2�������� ī�޶� Y
					 //�� �ٲ�� �ʳ����� ��ġ�� �ľ��� �� ����
					 int r = GetRValue(color);
					 int g = GetGValue(color);
					 int b = GetBValue(color);

					 if ((r == 255 && g == 0 && b == 0))
					 {
						 //_JP = 0;
						 _isOn = true;
						/* _gravity = 0;*/
						// _y = _rc.bottom - 60;

						 if (_state == CHARA_RIGHT_JUMP ||
							 _state == CHARA_RIGHT_MOVE_JUMP ||
							 _state == CHARA_RIGHT_JUMP_KICK ||
							 _state == CHARA_RIGHT_MOVE_JUMP_KICK)
						 {
							 if (_JP < 0)
							 {
								 _state = CHARA_RIGHT_LAND;
								 _motion->stop();
								 _motion = KEYANIMANAGER->findAnimation("JIMMYRightLand");
								 _motion->start();
							 }
						 }
						 else if (_state == CHARA_LEFT_MOVE_JUMP_KICK ||
							 _state == CHARA_LEFT_JUMP_KICK ||
							 _state == CHARA_LEFT_JUMP ||
							 _state == CHARA_LEFT_MOVE_JUMP)
						 {
							 if (_JP < 0)
							 {
								 _state = CHARA_LEFT_LAND;
								 _motion->stop();
								 _motion = KEYANIMANAGER->findAnimation("JIMMYLeftLand");
								 _motion->start();
							 }
						 }
						 else if (_state == CHARA_RIGHT_BACKKICK)
						 {
							 _state = CHARA_RIGHT_STOP;
							 _motion->stop();
							 _motion = KEYANIMANAGER->findAnimation("JIMMYRightStop");
							 _motion->start();
						 }
						 else if (_state == CHARA_LEFT_BACKKICK)
						 {
							 _state = CHARA_LEFT_STOP;
							 _motion->stop();
							 _motion = KEYANIMANAGER->findAnimation("JIMMYLeftStop");
							 _motion->start();
						 }
						 else if (_state == CHARA_RIGHT_STRIKED)
						 {
							 _state = CHARA_RIGHT_DOWN;
							 _motion->stop();
							 _motion = KEYANIMANAGER->findAnimation("JIMMYRightDown");
							 _motion->start();
						 }
						 else if (_state == CHARA_LEFT_STRIKED)
						 {
							 _state = CHARA_LEFT_DOWN;
							 _motion->stop();
							 _motion = KEYANIMANAGER->findAnimation("JIMMYLeftDown");
							 _motion->start();
						 }

					 }
					 else
					 {
						 _isOn = false;
						 //_gravity = 0.1f;
					 }
				 }
			 }
	
	
	KEYANIMANAGER->update();
	UpdateRect();
	drinkPotion();
	sprintf(test, "%d", _isOn);

	
}
void character::render()
{
	//_image->frameRender(getMemDC(), 100, 100, 0, 0);
	//_image->aniRender(getMemDC(), _rc.left, _rc.top, _motion);
	_image->aniRender(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rc).x, CAMERAMANAGER->CameraRelativePoint(_rc).y, _motion);

	/*
	RECT _rc;//������ ��Ʈ
	RECT _colliRect;//��ſ� ��Ʈ
	*/
	//Rectangle(getMemDC(), _rc.left,  _rc.top,  _rc.right, _rc.bottom);

	setColorRect(getMemDC(), _colliRect, 30, 40, 150);
	Rectangle(getMemDC(), _rightATK.left, _rightATK.top, _rightATK.right, _rightATK.bottom);
	Rectangle(getMemDC(), _leftATK.left, _leftATK.top, _leftATK.right, _leftATK.bottom);



	char str[256];
	wsprintf(str, "camX : %d, camY : %d", CAMERAMANAGER->CameraRelativePoint(_rc).x, CAMERAMANAGER->CameraRelativePoint(_rc).y);
	TextOut(getMemDC(), WINSIZEX/2, 10, str, strlen(str));
	TextOut(getMemDC(), 100, 100, test, strlen(test));
}

void character::MakeRightStop(void* obj)
{
	character* C = (character*)obj;

	C->setState(CHARA_RIGHT_STOP);
	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYRightStop"));
	C->getMotion()->start();
}
void character::MakeLeftStop(void* obj)
{
	character* C = (character*)obj;

	C->setState(CHARA_LEFT_STOP);
	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYLeftStop"));
	C->getMotion()->start();
}
void character::MakeRightFall(void* obj)
{
	character* C = (character*)obj;
	C->setJP(0);
	C->setState(CHARA_RIGHT_JUMP);
	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYRightJump"));
	C->getMotion()->start();

}
void character::MakeLeftFall(void* obj)
{
	character* C = (character*)obj;
	C->setJP(0);
	C->setState(CHARA_LEFT_JUMP);
	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYLeftJump"));
	C->getMotion()->start();
}
void character::MakeRightHold(void* obj)
{
	character* C = (character*)obj;

	C->setState(CHARA_RIGHT_HOLD);
	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYRightHold"));
	C->getMotion()->start();
}
void character::MakeLeftHold(void* obj)
{
	character* C = (character*)obj;

	C->setState(CHARA_LEFT_HOLD);
	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYLeftHold"));
	C->getMotion()->start();
}
//��״� ����Ͽɴϴ�!!!
void character::MakeRightDrill(void* obj)
{
	character* C = (character*)obj;

	C->setState(CHARA_RIGHT_DRILL);
	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYRightDrill"));
	C->getMotion()->start();
}
void character::MakeLeftDrill(void* obj)
{
	character* C = (character*)obj;

	C->setState(CHARA_LEFT_DRILL);
	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYLeftDrill"));
	C->getMotion()->start();
}

void character::MakeRightLand(void* obj)
{
	character* C = (character*)obj;

	C->setState(CHARA_RIGHT_LAND);
	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYRightLand"));
	C->getMotion()->start();
}
void character::MakeLeftLand(void* obj)
{
	character* C = (character*)obj;

	C->setState(CHARA_LEFT_LAND);
	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYLeftLand"));
	C->getMotion()->start();
}

void character::MakeRightBK(void* obj)
{
	character* C = (character*)obj;

	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYRightBackKickKeep"));
	C->getMotion()->start();
}
void character::MakeLeftBK(void* obj)
{
	character* C = (character*)obj;

	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYLeftBackKickKeep"));
	C->getMotion()->start();
}

void character::UpdateRect()
{
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_colliRect = RectMakeCenter(_x, _y, 54, 120);
	_rightATK = RectMakeCenter(CAMERAMANAGER->CameraRelativePoint(_rc).x + 137, CAMERAMANAGER->CameraRelativePoint(_rc).y+80, 50, 50);
	_leftATK = RectMakeCenter(CAMERAMANAGER->CameraRelativePoint(_rc).x + 63, CAMERAMANAGER->CameraRelativePoint(_rc).y+80, 50, 50);
}

//���°��� HIT�� �ٲٰ� damage��ŭ ������
void character::hurt(int damage, float x)
{
	_HP -= damage;

	if (_state == CHARA_RIGHT_JUMP
		|| _state == CHARA_RIGHT_MOVE_JUMP
		|| _state == CHARA_RIGHT_BACKKICK
		|| _state == CHARA_RIGHT_DRILL
		|| _state == CHARA_RIGHT_JUMP_KICK
		|| _state == CHARA_RIGHT_MOVE_JUMP_KICK
		|| _state == CHARA_RIGHT_ATT)
	{
		_state = CHARA_RIGHT_STRIKED;
		_motion = KEYANIMANAGER->findAnimation("JIMMYRightStriked");
		_motion->start();
	}
	//����� ��ġ�� ������ ũ�ٸ�(���� ������)
	else if (_state == CHARA_LEFT_ATT
		|| _state == CHARA_LEFT_JUMP_KICK
		|| _state == CHARA_LEFT_DRILL
		|| _state == CHARA_LEFT_MOVE_JUMP_KICK
		|| _state == CHARA_LEFT_JUMP
		|| _state == CHARA_LEFT_BACKKICK
		|| _state == CHARA_LEFT_MOVE_JUMP)
	{
		_state = CHARA_LEFT_STRIKED;
		_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStriked");
		_motion->start();
	}
	else
	{
		if (_HP <= 0)
		{
			//_HP -= damage;
			_JP = CHARAJUMP;
			_JP = _JP / 2;
			_StartY = _y;
			//����� ��ġ�� ������ �۴ٸ�(���� ����)
			if (x<_x)
			{
				_isRight = false;
				_state = CHARA_LEFT_STRIKED;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStriked");
				_motion->start();
			}
			//����� ��ġ�� ������ ũ�ٸ�(���� ������)
			else if (_x<x)
			{
				_isRight = true;
				_state = CHARA_RIGHT_STRIKED;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightStriked");
				_motion->start();
			}
		}
		else
		{
			if (_isRight)
			{
				_state = CHARA_RIGHT_HIT;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightHit");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_HIT;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftHit");
				_motion->start();
			}
		}
	}
	
}
//���°� STRIKED�� �ٲ�� damage��ŭ ������ ������
//x���� Ŭ���� ���� �������� ���������� ������
void character::strike(int damage, float x)
{
	_HP -= damage;
	_JP = CHARAJUMP;
	_JP = _JP / 2;
	_StartY = _y;
	//����� ��ġ�� ������ �۴ٸ�(���� ����)
	if (x<_x)
	{
		_isRight = false;
		_state = CHARA_LEFT_STRIKED;
		_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStriked");
		_motion->start();
	}
	//����� ��ġ�� ������ ũ�ٸ�(���� ������)
	else if (_x<x)
	{
		_isRight = true;
		_state = CHARA_RIGHT_STRIKED;
		_motion = KEYANIMANAGER->findAnimation("JIMMYRightStriked");
		_motion->start();
	}
}

void character::addImage()
{
	_image = IMAGEMANAGER->addFrameImage("JIMMY", "./images/JIMMY.bmp", 3072, 2100, 16, 14, true, RGB(255, 0, 255));

	//�����ʸ���
	int RightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightStop", "JIMMY", RightStop, 1, 6, true);

	//���ʸ���
	int LeftStop[] = { 127 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftStop", "JIMMY", LeftStop, 1, 6, true);

	//������ ������
	int RightMove[] = { 0, 1, 2, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightMove", "JIMMY", RightMove, 4, 4, true);

	//���� ������
	int LeftMove[] = { 127, 126, 125, 126 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftMove", "JIMMY", LeftMove, 4, 4, true);

	//������ ����+�Ͼ
	int RightLand[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightLand", "JIMMY", RightLand, 1, 1, false, MakeRightStop, this);

	//���� ����+�Ͼ
	int LeftLand[] = { 123 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftLand", "JIMMY", LeftLand, 1, 1, false, MakeLeftStop, this);

	//������ ��ġ 1Ÿ
	int RightPunchOne[] = { 7, 8, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightPunchOne", "JIMMY", RightPunchOne, 3, 4, false, MakeRightStop, this);

	//���� ��ġ 1Ÿ
	int LeftPunchOne[] = { 120, 119, 120 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftPunchOne", "JIMMY", LeftPunchOne, 3, 4, false, MakeLeftStop, this);

	//������ ��ġ 2Ÿ
	int RightPunchTwo[] = { 5, 6, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightPunchTwo", "JIMMY", RightPunchTwo, 3, 4, false, MakeRightStop, this);

	//���� ��ġ 2Ÿ
	int LeftPunchTwo[] = { 122, 121, 122 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftPunchTwo", "JIMMY", LeftPunchTwo, 3, 4, false, MakeLeftStop, this);

	//������ ������
	int RightKick[] = { 9, 10, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightKick", "JIMMY", RightKick, 3, 4, false, MakeRightStop, this);

	//���� ������
	int LeftKick[] = { 118, 117, 118 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftKick", "JIMMY", LeftKick, 3, 4, false, MakeLeftStop, this);

	//������ ���� ������
	int RightJumpKick[] = { 19 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightJumpKick", "JIMMY", RightJumpKick, 1, 6, true);

	//���� ���� ������
	int LeftJumpKick[] = { 140 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftJumpKick", "JIMMY", LeftJumpKick, 1, 6, true);

	//������ ����ȸ������
	int RightATT[] = { 48, 47, 46, 45, 48, 47, 46 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightATT", "JIMMY", RightATT, 7, 5, false, MakeRightFall, this);

	//���� ����ȸ������
	int LeftATT[] = { 45, 46, 48, 47, 45, 46, 48 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftATT", "JIMMY", LeftATT, 7, 5, false, MakeLeftFall, this);

	//������ ��ġ��
	int RightHead[] = { 11, 12, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightHead", "JIMMY", RightHead, 3, 3, false, MakeRightStop, this);

	//���� ��ġ��
	int LeftHead[] = { 116, 115, 116 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftHead", "JIMMY", LeftHead, 3, 3, false, MakeLeftStop, this);

	//������ ������
	int RightUpper[] = { 13, 14, 15 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightUpper", "JIMMY", RightUpper, 3, 4, false, MakeRightStop, this);

	//���� ������
	int LeftUpper[] = { 114, 113, 112 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftUpper", "JIMMY", LeftUpper, 3, 4, false, MakeLeftStop, this);

	//������ ����ű
	int RightHighKick[] = { 16, 17, 18 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightHighKick", "JIMMY", RightHighKick, 3, 4, false, MakeRightStop, this);

	//���� ����ű
	int LeftHighKick[] = { 143, 142, 141 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftHighKick", "JIMMY", LeftHighKick, 3, 4, false, MakeLeftStop, this);

	//������ ��ġŰ(������ �������̰� ���ʶ���)
	int RightBackBlow[] = { 25 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightBackBlow", "JIMMY", RightBackBlow, 1, 3, false, MakeRightStop, this);

	//���� ��ġŰ(������ �����̰� �����ʶ���)
	int LeftBackBlow[] = { 134 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftBackBlow", "JIMMY", LeftBackBlow, 1, 3, false, MakeLeftStop, this);

	//������ ��� �ڼ�
	int RightGrab[] = { 20 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightgrab", "JIMMY", RightGrab, 1, 4, false, MakeRightHold, this);

	//������ ������ �ڼ�
	int RightHold[] = { 21 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightHold", "JIMMY", RightHold, 1, 4, true);

	//���� ��� �ڼ�
	int LeftGrab[] = { 140 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftgrab", "JIMMY", LeftGrab, 1, 4, false, MakeLeftHold, this);

	//���� ������ �ڼ�
	int LeftHold[] = { 139 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftHold", "JIMMY", LeftHold, 1, 4, true);

	//������ ��� �����
	int RightBackSting[] = { 54, 55 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightBackSting", "JIMMY", RightBackSting, 2, 4, false, MakeRightHold, this);

	//���� ��� �����
	int LeftBackSting[] = { 170, 169 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftBackSting", "JIMMY", LeftBackSting, 2, 4, false, MakeLeftHold, this);

	//������ ��� ����
	int RightTigerKick[] = { 26 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightTigerKick", "JIMMY", RightTigerKick, 1, 4, false, MakeRightHold, this);

	//���� ��� ����
	int LeftTigerKick[] = { 133 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftTigerKick", "JIMMY", LeftTigerKick, 1, 4, false, MakeLeftHold, this);

	//������ ������
	int RightSwing[] = { 22, 23, 24 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightSwing", "JIMMY", RightSwing, 3, 4, false, MakeRightStop, this);

	//���� ������
	int LeftSwing[] = { 138, 137, 136 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftSwing", "JIMMY", LeftSwing, 3, 4, false, MakeLeftStop, this);

	//������ ����
	int RightJump[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightJump", "JIMMY", RightJump, 1, 6, true);

	//���� ����
	int LeftJump[] = { 124 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftJump", "JIMMY", LeftJump, 1, 6, true);

	//������ 2�� ������
	int RightBackKick[] = { 28, 29,30 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightBackKick", "JIMMY", RightBackKick, 2, 1, false, MakeRightFall, this);

	//���� 2�� ������
	int LeftBackKick[] = { 131, 130,129 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftBackKick", "JIMMY", LeftBackKick, 2, 1, false, MakeLeftFall, this);

	//������ 2�� ����������
	int RightBackKickKeep[] = { 29 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightBackKickKeep", "JIMMY", RightBackKickKeep, 1, 6, true);

	//���� 2�� ����������
	int LeftBackKickKeep[] = { 130 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftBackKickKeep", "JIMMY", LeftBackKickKeep, 1, 6, true);

	//������ �غ��� �غ�
	int RightReadyDrill[] = { 32 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightReadyDrill", "JIMMY", RightReadyDrill, 1, 4, false, MakeRightDrill, this);

	//������ �غ���
	int RightDrill[] = { 33, 34, 35 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightDrill", "JIMMY", RightDrill, 3, 6, true);
	//������ ���ߴ�ű
	int RightKneeKick[] = { 51 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightKneeKick", "JIMMY", RightKneeKick, 1, 6, true);

	//���� �غ��� �غ�
	int LeftReadyDrill[] = { 159 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftReadyDrill", "JIMMY", LeftReadyDrill, 1, 4, false, MakeLeftDrill, this);

	//���� �غ���
	int LeftDrill[] = { 158, 157, 156 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftDrill", "JIMMY", LeftDrill, 3, 6, true);
	//���� ���ߴ�ű
	int LeftKneeKick[] = { 172 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftKneeKick", "JIMMY", LeftKneeKick, 1, 6, true);

	//��ٸ� �̵�
	int StairMove[] = { 62, 63 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYStairMove", "JIMMY", StairMove, 2, 4, true);

	//��ٸ� ����
	int StairStop[] = { 62 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYStairStop", "JIMMY", StairStop, 1, 6, true);

	//������ �ǰ�
	int RightHit[] = { 74 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightHit", "JIMMY", RightHit, 1, 3, false, MakeRightStop, this);

	//���� �ǰ�
	int LeftHit[] = { 181 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftHit", "JIMMY", LeftHit, 1, 3, false, MakeLeftStop, this);

	//������ ������
	int RightStriked[] = { 77 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightStriked", "JIMMY", RightStriked, 1, 6, true);

	//���� ������
	int LeftStriked[] = { 178 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftStriked", "JIMMY", LeftStriked, 1, 6, true);

	//������ ����
	int RightDown[] = { 78 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightDown", "JIMMY", RightDown, 1, 1, false, MakeRightLand, this);

	//���ʴ���
	int LeftDown[] = { 177 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftDown", "JIMMY", LeftDown, 1, 1, false, MakeLeftLand, this);

	//������ Į ��ô
	int RightKnifeThrowing[] = { 65, 66 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightKnifeThrowingn", "JIMMY", 
		RightKnifeThrowing, 2, 1, false, MakeRightStop, this);

	//�� ��� ������
	int RightStoneStop[] = { 70 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightStoneStop", "JIMMY",
		RightStoneStop, 1, 1, true);

	//�� ��� ������
	int RightStoneMove[] = { 70, 71 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightStoneMove", "JIMMY",
		RightStoneMove, 2, 4, true);
	//���� Į ��ô(�̱���)

	//������ �� ��ô
	int RightStoneThrow[] = { 72, 73 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightStoneThrow", "JIMMY",
		RightStoneThrow, 2, 4, false, MakeRightStop, this);

	// ���� ���� ��
	int LeftStoneStop[] = { 185 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftStoneStop", "JIMMY",
		LeftStoneStop, 1, 4, true);

	int LeftStoneMove[] = { 185, 184 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftStoneMove", "JIMMY",
		LeftStoneMove, 2, 4, true);

	//������
	_JIMMYKnife = IMAGEMANAGER->addFrameImage("JIMMYKNIFE", "./images/JIMMY.bmp", 1536, 150, 8, 1, true, RGB(255, 0, 255));

	int KnifeRightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYKnifeRightStop", "JIMMYKNIFE", KnifeRightStop, 1, 6, true);

	int KnifeLeftStop[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYKnifeLeftStop", "JIMMYKNIFE", KnifeLeftStop, 1, 6, true);

	int KnifeRightMove[] = { 0,1,2 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYKnifeRightMove", "JIMMYKNIFE", KnifeRightMove, 3, 4, true);

	int KnifeLeftMove[] = { 7,6,5 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYKnifeLeftMove", "JIMMYKNIFE", KnifeLeftMove, 3, 4, true);

	int KnifeRightJump[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYKnifeRightJump", "JIMMYKNIFE", KnifeRightJump, 1, 6, true);

	int KnifeLeftJump[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYKnifeLeftJump", "JIMMYKNIFE", KnifeLeftJump, 1, 6, true);

	int KnifeRightThrow[] = { 65,66 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYKnifeRightThrow", "JIMMY", KnifeRightThrow, 2, 4, true);

	int KnifeLeftThrow[] = { 190,189 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYKnifeLeftThrow", "JIMMY", KnifeLeftThrow, 2, 4, true);

	int LeftStoneThrow[] = { 183, 182 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftStoneThrow", "JIMMY",
		LeftStoneThrow, 2, 4, false, MakeLeftStop, this);


	_motion = KEYANIMANAGER->findAnimation("JIMMYRightStop");
}

void character::drinkPotion()
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (_potion == NULL) return;
		if (_potion->getCount() <= 0) return;
		_HP += _potion->getItemEffect();
		if (_HP >= 10) _HP = 10;
		_potion->setCount(_potion->getCount()-1);
	}
}