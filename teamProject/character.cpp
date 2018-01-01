#include "stdafx.h"
#include "character.h"


character::character()
{
}


character::~character()
{
}
HRESULT character::init()
{
	_image = IMAGEMANAGER->addFrameImage("JIMMY", "./images/JIMMY.bmp", 3072, 2100, 16, 14, true, RGB(255, 0, 255));

	_state = CHARA_RIGHT_STOP;
	_Zmove = CHARASPEED;
	_x = _StartX= WINSIZEX / 2;
	_y = _StartY= WINSIZEY / 2;
	_isRight = true;
	_JP = 0;
	_gravity = 0.1f;

	_state = CHARA_RIGHT_STOP;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_colliRect = RectMakeCenter(_x, _y, 54, 120);

	//�����ʸ���
	int RightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightStop", "JIMMY", RightStop, 1, 6, true);

	//���ʸ���
	int LeftStop[] = { 127 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftStop", "JIMMY", LeftStop, 1, 6, true);

	//������ ������
	int RightMove[] = { 0,1,2,1 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightMove", "JIMMY", RightMove, 4, 10, true);

	//���� ������
	int LeftMove[] = { 127,126,125,126 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftMove", "JIMMY", LeftMove, 4, 10, true);

	//������ ����+�Ͼ
	int RightLand[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightLand", "JIMMY", RightLand, 1, 6, false,MakeRightStop,this);

	//���� ����+�Ͼ
	int LeftLand[] = { 123 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftLand", "JIMMY", LeftStop, 1, 6, false, MakeLeftStop, this);

	//������ ��ġ 1Ÿ
	int RightPunchOne[] = { 5,6,5 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightPunchOne", "JIMMY", RightPunchOne, 3, 10, false, MakeRightStop, this);

	//���� ��ġ 1Ÿ
	int LeftPunchOne[] = { 122,121,122 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftPunchOne", "JIMMY", LeftPunchOne, 3, 10, false, MakeLeftStop, this);

	//������ ��ġ 2Ÿ
	int RightPunchTwo[] = { 7,8,7 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightPunchTwo", "JIMMY", RightPunchTwo, 3, 10, false, MakeRightStop, this);

	//���� ��ġ 2Ÿ
	int LeftPunchTwo[] = { 120,119,120 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftPunchTwo", "JIMMY", LeftPunchTwo, 3, 10, false, MakeLeftStop, this);

	//������ ������
	int RightKick[] = { 9,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightKick", "JIMMY", RightKick, 3, 10, false, MakeRightStop, this);

	//���� ������
	int LeftKick[] = { 118,117,118 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftKick", "JIMMY", LeftKick, 3, 10, false, MakeLeftStop, this);

	//������ ���� ������
	int RightJumpKick[] = { 19 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightJumpKick", "JIMMY", RightJumpKick, 1, 6, true);

	//���� ���� ������
	int LeftJumpKick[] = { 140 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftJumpKick", "JIMMY", LeftJumpKick, 1, 6, true);

	//������ ����ȸ������
	int RightATT[] = { 48,47,46,45,48,47,46 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightATT", "JIMMY", RightATT, 7, 10, false, MakeRightFall, this);

	//���� ����ȸ������
	int LeftATT[] = { 45,46,48,47,45,46,48 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftATT", "JIMMY", LeftATT, 7, 10, false, MakeLeftFall, this);

	//������ ��ġ��
	int RightHead[] = { 11,12,11 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightHead", "JIMMY", RightHead, 3, 10, false, MakeRightStop, this);

	//���� ��ġ��
	int LeftHead[] = { 116,115,116 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftHead", "JIMMY", LeftHead, 3, 10, false, MakeLeftStop, this);

	//������ ������
	int RightUpper[] = { 13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightUpper", "JIMMY", RightUpper, 3, 10, false, MakeRightStop, this);

	//���� ������
	int LeftUpper[] = { 114,113,112 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftUpper", "JIMMY", LeftUpper, 3, 10, false, MakeLeftStop, this);

	//������ ����ű
	int RightHighKick[] = { 16,17,18 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightHighKick", "JIMMY", RightHighKick, 3, 10, false, MakeRightStop, this);

	//���� ����ű
	int LeftHighKick[] = { 143,142,141 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftHighKick", "JIMMY", LeftHighKick, 3, 10, false, MakeLeftStop, this);

	//������ ��ġŰ(������ �������̰� ���ʶ���)
	int RightBackBlow[] = { 25 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightBackBlow", "JIMMY", RightBackBlow, 1, 6, false, MakeRightStop, this);

	//���� ��ġŰ(������ �����̰� �����ʶ���)
	int LeftBackBlow[] = { 134 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftBackBlow", "JIMMY", LeftBackBlow, 1, 6, false, MakeLeftStop, this);

	//������ ��� �ڼ�
	int RightGrab[] = { 20 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightgrab", "JIMMY", RightGrab, 1, 6, false, MakeRightHold, this);

	//������ ������ �ڼ�
	int RightHold[] = { 21 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightHold", "JIMMY", RightHold, 1, 6, true);

	//���� ��� �ڼ�
	int LeftGrab[] = { 140 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftgrab", "JIMMY", LeftGrab, 1, 6, false, MakeLeftHold, this);

	//���� ������ �ڼ�
	int LeftHold[] = { 139 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftHold", "JIMMY", LeftHold, 1, 6, true);

	//������ ��� �����
	int RightBackSting[] = { 54,55 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightBackSting", "JIMMY", RightBackSting, 2, 10, false, MakeRightHold, this);

	//���� ��� �����
	int LeftBackSting[] = { 170,169 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftBackSting", "JIMMY", LeftBackSting, 2, 10, false, MakeLeftHold, this);

	//������ ��� ����
	int RightTigerKick[] = { 26 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightTigerKick", "JIMMY", RightTigerKick, 1, 10, false, MakeRightHold, this);

	//���� ��� ����
	int LeftTigerKick[] = { 133 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftTigerKick", "JIMMY", LeftTigerKick, 1, 10, false, MakeLeftHold, this);

	//������ ������
	int RightSwing[] = { 22,23,24 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightSwing", "JIMMY", RightSwing, 3, 10, false, MakeRightStop, this);

	//���� ������
	int LeftSwing[] = { 138,137,136 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftSwing", "JIMMY", LeftSwing, 3, 10, false, MakeLeftStop, this);

	//������ ����
	int RightJump[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightJump", "JIMMY", RightJump, 1, 6, true);

	//���� ����
	int LeftJump[] = { 124 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftJump", "JIMMY", LeftJump, 1, 6, true);

	//������ 2�� ������
	int RightBackKick[] = { 28,29,30 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightBackKick", "JIMMY", RightBackKick, 3, 10, false, MakeRightStop, this);

	//���� 2�� ������
	int LeftBackKick[] = { 131,130,129 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftBackKick", "JIMMY", LeftBackKick, 3, 10, false, MakeLeftStop, this);

	//������ �غ��� �غ�
	int RightReadyDrill[] = { 32 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightReadyDrill", "JIMMY", RightReadyDrill, 1, 10, false, MakeRightDrill, this);

	//������ �غ���
	int RightDrill[] = { 33,34,35 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightDrill", "JIMMY", RightDrill, 3, 10, true);
	//������ ���ߴ�ű
	int RightKneeKick[] = { 51 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightKneeKick", "JIMMY", RightKneeKick, 1, 6, true);

	//���� �غ��� �غ�
	int LeftReadyDrill[] = { 159 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftReadyDrill", "JIMMY", LeftReadyDrill, 1, 10, false, MakeLeftDrill, this);

	//���� �غ���
	int LeftDrill[] = { 158,157,156 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftDrill", "JIMMY", LeftDrill, 3, 10, true);
	//���� ���ߴ�ű
	int LeftKneeKick[] = { 172 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftKneeKick", "JIMMY", LeftKneeKick, 1, 10, true);

	//��ٸ� �̵�
	int StairMove[] = { 62,63 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYStairMove", "JIMMY", StairMove, 2, 10, true);

	//��ٸ� ����
	int StairStop[] = { 62 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYStairStop", "JIMMY", StairStop, 1, 6, true);

	//������ �ǰ�
	int RightHit[] = { 74 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightHit", "JIMMY", RightHit, 1, 10, true);

	//���� �ǰ�
	int LeftHit[] = { 181 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftHit", "JIMMY", LeftHit, 1, 10, true);

	//������ ������
	int RightStriked[] = { 77 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightStriked", "JIMMY", RightStriked, 1, 6, true);

	//���� ������
	int LeftStriked[] = { 178 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftStriked", "JIMMY", LeftStriked, 1, 6, true);

	//������ ����
	int RightDown[] = { 78 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightDown", "JIMMY", RightDown, 1, 2, false, MakeRightLand, this);

	//���ʴ���
	int LeftDown[] = { 177 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftDown", "JIMMY", LeftDown, 1, 2, false, MakeLeftLand, this);

	_motion = KEYANIMANAGER->findAnimation("JIMMYRightStop");


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
	switch (_state)
	{
		//�������
	case CHARA_RIGHT_STOP:
	case CHARA_LEFT_STOP:
		//if (KEYMANAGER->isOnceKeyDown(VK_UP)|| KEYMANAGER->isOnceKeyDown(VK_DOWN))
		//{
		//	if (_isRight)
		//	{
		//		_motion = KEYANIMANAGER->findAnimation("JIMMYRightMove");
		//		_motion->start();
		//		_state = CHARA_RIGHT_MOVE;
		//	}
		//	else
		//	{
		//		_state = CHARA_LEFT_MOVE;
		//		_motion = KEYANIMANAGER->findAnimation("JIMMYLeftMove");
		//		_motion->start();
		//	}
		//}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_isRight = false;
			_state=CHARA_LEFT_MOVE;
			_motion=KEYANIMANAGER->findAnimation("JIMMYLeftMove");
			_motion->start();
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_isRight = true;
			_motion = KEYANIMANAGER->findAnimation("JIMMYRightMove");
			_motion->start();
			_state = CHARA_RIGHT_MOVE;
		}
		
		break;
	
	case CHARA_RIGHT_MOVE://���������� �����̴� ��
		//�����¿�Ű�� �������°� �ƴ϶��
		//if (!(KEYMANAGER->isStayKeyDown(VK_UP)
		//	&& KEYMANAGER->isStayKeyDown(VK_DOWN)
		//	&& KEYMANAGER->isStayKeyDown(VK_LEFT)
		//	&&KEYMANAGER->isStayKeyDown(VK_RIGHT)))
		//{
		//		_state = CHARA_RIGHT_STOP;//������·� ������
		//		_motion = KEYANIMANAGER->findAnimation("JIMMYRightStop");
		//		_motion->start();
		//}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			//if(��ٸ��� Ż �� �ְ� �Ǿ���)
			//{
			//_state = CHARA_STAIR;
			//_motion = KEYANIMANAGER->findAnimation("JIMMYStairStop");
			//_motion->start();
			//}
			//else
			_y -= _Zmove;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_y += _Zmove;
		}
		
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_x += CHARASPEED;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_state = CHARA_RIGHT_STOP;//������·� ������
			_motion = KEYANIMANAGER->findAnimation("JIMMYRightStop");
			_motion->start();
		}
		break;
	case CHARA_LEFT_MOVE://�������� �����̴� ��
		//�����¿�Ű�� �������°� �ƴ϶��
		//if (!(KEYMANAGER->isStayKeyDown(VK_UP)
		//	&& KEYMANAGER->isStayKeyDown(VK_DOWN)
		//	&& KEYMANAGER->isStayKeyDown(VK_LEFT)
		//	&& KEYMANAGER->isStayKeyDown(VK_RIGHT)))
		//{
		//	_state = CHARA_RIGHT_STOP;//������·� ������
		//	_motion = KEYANIMANAGER->findAnimation("JIMMYRightStop");
		//	_motion->start();
		//}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			//if(��ٸ��� Ż �� �ְ� �Ǿ���)
			//{
			//_state = CHARA_STAIR;
			//_motion = KEYANIMANAGER->findAnimation("JIMMYStairStop");
			//_motion->start();
			//}
			//else
			_y -= _Zmove;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_y += _Zmove;
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_x -= CHARASPEED;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_state = CHARA_LEFT_STOP;//������·� ������
			_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStop");
			_motion->start();
		}
		break;
	case CHARA_RIGHT_LAND:
	case CHARA_LEFT_LAND:
		if (KEYMANAGER->isOnceKeyDown('X'))//�ָ�
		{
			if (_isRight)
			{
				_state = CHARA_RIGHT_UPPER;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightUpper");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_UPPER;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftUpper");
				_motion->start();
			}
		}
		if (KEYMANAGER->isOnceKeyDown('C'))//ű
		{
			_StartY = _y;
			_JP = CHARAJUMP;
			if (_isRight)
			{
				_state = CHARA_RIGHT_DRILL;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightKneeKick");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_DRILL;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftKneeKick");
				_motion->start();
			}
		}
		break;
	case CHARA_RIGHT_PUNCH_ONE:
	case CHARA_LEFT_PUNCH_ONE:
		//��ġ�� ������ȯ
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
				_state = CHARA_LEFT_HEAD;
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
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightHead");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_BACKBLOW;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftBackBlow");
				_motion->start();
			}
		}
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			if (_isRight)
			{
				_state = CHARA_RIGHT_PUNCH_TWO;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightPunchTwo");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_PUNCH_TWO;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftPunchTwo");
				_motion->start();
			}
		}
		break;
	case CHARA_RIGHT_PUNCH_TWO:
	case CHARA_LEFT_PUNCH_TWO:
		//��ġ�� ������ȯ
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
				_state = CHARA_LEFT_HEAD;
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
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightHead");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_BACKBLOW;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftBackBlow");
				_motion->start();
			}
		}
		//if(������ ������ ������)
		//  {������
		//	if (_isRight)
		//	{
		//		_state = CHARA_RIGHT_UPPER;
		//		_motion = KEYANIMANAGER->findAnimation("JIMMYRightUpper");
		//		_motion->start();
		//	}
		//	else
		//	{
		//		_state = CHARA_LEFT_UPPER;
		//		_motion = KEYANIMANAGER->findAnimation("JIMMYLeftUpper");
		//		_motion->start();
		//	}
		//  }
		break;
	case CHARA_LEFT_KICK:
	case CHARA_RIGHT_KICK:
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
				_JP = CHARAJUMP;
				_JP = _JP / 2;
				_state = CHARA_LEFT_BACKKICK;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftBackKick");
				_motion->start();
			}
		}
		//ű�� ������ȯ
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_isRight)
			{
				_JP = CHARAJUMP;
				_JP = _JP / 2;
				_state = CHARA_RIGHT_BACKKICK;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightBackKick");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_BACKBLOW;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftBackBlow");
				_motion->start();
			}
		}
		//if(������ ������ ������)
		//  {����ű
		//	if (_isRight)
		//	{
		//		_state = CHARA_RIGHT_HIGHKICK;
		//		_motion = KEYANIMANAGER->findAnimation("JIMMYRightHighKick");
		//		_motion->start();
		//	}
		//	else
		//	{
		//		_state = CHARA_LEFT_HIGHKICK;
		//		_motion = KEYANIMANAGER->findAnimation("JIMMYLeftHighKick");
		//		_motion->start();
		//	}
		//  }
		break;
	case CHARA_RIGHT_HEAD:
	case CHARA_LEFT_HEAD:
		if (KEYMANAGER->isOnceKeyDown('X'))//�ָ�
		{
			if (_isRight)
			{
				_state = CHARA_RIGHT_DRILL;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightDrill");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_DRILL;
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
		if (_StartY <= _y)
		{
			_y = _StartY;
			if (_isRight)
			{
				_state = CHARA_RIGHT_LAND;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightLand");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_LAND;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftLand");
				_motion->start();
			}
		}
		if (KEYMANAGER->isOnceKeyDown('C'))//������
		{
			if (_JP*_JP < 1)
			{
				_JP = 0;
				if (_isRight)
				{
					_state = CHARA_RIGHT_ATT;
					_motion = KEYANIMANAGER->findAnimation("JIMMYRightATT");
					_motion->start();
				}
				else
				{
					_state = CHARA_LEFT_ATT;
					_motion = KEYANIMANAGER->findAnimation("JIMMYLeftATT");
					_motion->start();
				}
			}
			if (_isRight)
			{
				_state = CHARA_RIGHT_JUMP_KICK;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightJumpKick");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_JUMP_KICK;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftJumpKick");
				_motion->start();
			}
			if (KEYMANAGER->isOnceKeyDown('X'))
			{
				if (_isRight)
				{
					_state = CHARA_RIGHT_JUMP_KICK;
					_motion = KEYANIMANAGER->findAnimation("JIMMYRightJumpKick");
					_motion->start();
				}
				else
				{
					_state = CHARA_LEFT_JUMP_KICK;
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
		if (_StartY <= _y)
		{
			_JP = 0;
			_y = _StartY;
			if (_isRight)
			{
				_state = CHARA_RIGHT_LAND;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightLand");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_LAND;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftLand");
				_motion->start();
			}
		}
		break;
	case CHARA_RIGHT_BACKKICK:
	case CHARA_LEFT_BACKKICK:
		_y -= _JP;
		_JP -= _gravity;
		if (_isRight)
		{
			_x += 2;
		}
		else
		{
			_x -= 2;
		}
		if (_StartY <= _y)
		{
			_JP=0;
			_y = _StartY;
			if (_isRight)
			{
				_state = CHARA_RIGHT_STOP;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightStop");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_STOP;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStop");
				_motion->start();
			}
		}
		break;
	case CHARA_RIGHT_DRILL:
	case CHARA_LEFT_DRILL:
		//��ű�� �����ٰ�
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
		if (_JP <= 0)
		{
			if (_isRight)
			{
				_state = CHARA_RIGHT_JUMP;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightJump");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_LAND;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftJump");
				_motion->start();
			}
		}
		break;
	case CHARA_STAIR:
		//����� Ż �� �ִ� ���°� �Ǿ���(�������� ����ʿ�)
		if (!(KEYMANAGER->isStayKeyDown(VK_UP)&& KEYMANAGER->isStayKeyDown(VK_DOWN)))
		{
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
		if (_isRight)
		{
			_x -= CHARASPEED;
		}
		else
		{
			_x += CHARASPEED;
		}
		break;
	case CHARA_RIGHT_DOWN:
	case CHARA_LEFT_DOWN:
		//����
		//��üfps������
		break;
	case CHARA_RIGHT_JUMP_KICK:
	case CHARA_LEFT_JUMP_KICK:
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
		if (_StartY <= _y)
		{
			_JP = 0;
			_y = _StartY;
			if (_isRight)
			{
				_state = CHARA_RIGHT_LAND;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightLand");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_LAND;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftLand");
				_motion->start();
			}
		}
		break;
	case CHARA_RIGHT_ATT:
	case CHARA_LEFT_ATT:
		//JP�� 0�ػ���
		break;
	default:
		break;
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))//����
	{
		if (_state == CHARA_RIGHT_STOP || _state == CHARA_LEFT_STOP)
		{
			_StartX = _y;
			_JP = CHARASPEED;
			if (_isRight)
			{
				_state = CHARA_RIGHT_JUMP;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightJump");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_JUMP;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftJump");
				_motion->start();
			}
		}
		if (_state == CHARA_RIGHT_MOVE)
		{
			_StartX = _y;
			_JP = CHARASPEED;
			_state = CHARA_RIGHT_MOVE_JUMP;
			_motion = KEYANIMANAGER->findAnimation("JIMMYRIghtMoveJump");
			_motion->start();
		}
		if (_state == CHARA_LEFT_MOVE)
		{
			_StartX = _y;
			_JP = CHARASPEED;
			_state = CHARA_LEFT_MOVE_JUMP;
			_motion = KEYANIMANAGER->findAnimation("JIMMYLeftMoveJump");
			_motion->start();
		}
	}
	if (KEYMANAGER->isOnceKeyDown('X'))//�ָ�
	{
		if (_state == CHARA_RIGHT_STOP || _state == CHARA_LEFT_STOP
			|| _state == CHARA_RIGHT_MOVE || _state == CHARA_LEFT_MOVE)
		{
			if (_isRight)
			{
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightPunchOne");
				_motion->start();
				_state = CHARA_RIGHT_PUNCH_ONE;
			}
			else
			{
				_state = CHARA_LEFT_PUNCH_ONE;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftPunchOne");
				_motion->start();
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('C'))//ű
	{
		if (_state == CHARA_RIGHT_STOP || _state == CHARA_LEFT_STOP
			|| _state == CHARA_RIGHT_MOVE || _state == CHARA_LEFT_MOVE)
		{
			if (_isRight)
			{
				_state = CHARA_RIGHT_KICK;
				_motion = KEYANIMANAGER->findAnimation("JIMMYRightKick");
				_motion->start();
			}
			else
			{
				_state = CHARA_LEFT_KICK;
				_motion = KEYANIMANAGER->findAnimation("JIMMYLeftKick");
				_motion->start();
			}
		}
	}
	KEYANIMANAGER->update();
	UpdateRect();

}
void character::render()
{
	//_image->frameRender(getMemDC(), 100, 100, 0, 0);
	_image->aniRender(getMemDC(), _rc.left, _rc.top,_motion);

	//char 
}

void character::MakeRightStop(void* obj)
{
	character* C=(character*) obj;

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

void character::UpdateRect()
{
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_colliRect = RectMakeCenter(_x, _y, 54,120);
}

//���°��� HIT�� �ٲٰ� damage��ŭ ������
void character::hurt(int damage)
{
	_HP -= damage;
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

//���°� STRIKED�� �ٲ�� damage��ŭ ������ ������
//x���� Ŭ���� ���� �������� ���������� ������
void character::strike(int damage, float x)
{
	_HP -= damage;
	_JP = CHARAJUMP;
	_JP = _JP / 2;
	//����� ��ġ�� ������ �۴ٸ�(���� ����)
	if (x<_x)
	{
		_isRight = false;
		_state = CHARA_RIGHT_STRIKED;
		_motion = KEYANIMANAGER->findAnimation("JIMMYRightStriked");
		_motion->start();
	}
	//����� ��ġ�� ������ ũ�ٸ�(���� ������)
	else if(_x<x)
	{
		_isRight = true;
		_state = CHARA_LEFT_STRIKED;
		_motion = KEYANIMANAGER->findAnimation("JIMMYLeftStriked");
		_motion->start();
	}
}