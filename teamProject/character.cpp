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
	_image = IMAGEMANAGER->addFrameImage("JIMMY", "images/JIMMY.bmp", 1024, 700, 16, 14, true, RGB(255, 0, 255));

	_state = CHARA_RIGHT_STOP;

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_isRight = true;
	_JP = 0;
	_gravity = 0.2f;

	_state = CHARA_RIGHT_STOP;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	int RightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightStop", "JIMMY", RightStop, 1, 6, true);

	int LeftStop[] = { 127 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftStop", "JIMMY", LeftStop, 1, 6, true);

	int RightMove[] = { 0,1,2,1 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightMove", "JIMMY", RightMove, 4, 10, true);

	int LeftMove[] = { 127,126,125,126 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightMove", "JIMMY", RightMove, 4, 10, true);

	int RightLand[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightLand", "JIMMY", RightLand, 1, 6, false,MakeRightStop,this);

	int LeftLand[] = { 123 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftLand", "JIMMY", LeftStop, 1, 6, false, MakeLeftStop, this);

	int RightPunchOne[] = { 5,6,5 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightPunchOne", "JIMMY", RightPunchOne, 3, 10, false, MakeRightStop, this);

	int LeftPunchOne[] = { 122,121,122 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftPunchOne", "JIMMY", LeftPunchOne, 3, 10, false, MakeLeftStop, this);

	int RightPunchTwo[] = { 7,8,7 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightPunchTwo", "JIMMY", RightPunchTwo, 3, 10, false, MakeRightStop, this);

	int LeftPunchTwo[] = { 120,119,120 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftPunchTwo", "JIMMY", LeftPunchTwo, 3, 10, false, MakeLeftStop, this);

	int RightKick[] = { 9,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightKick", "JIMMY", RightKick, 3, 10, false, MakeRightStop, this);

	int LeftKick[] = { 118,117,118 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftKick", "JIMMY", LeftKick, 3, 10, false, MakeLeftStop, this);

	int RightHead[] = { 11,12,11 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightHead", "JIMMY", RightHead, 3, 10, false, MakeRightStop, this);

	int LeftHead[] = { 116,115,116 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftHead", "JIMMY", LeftHead, 3, 10, false, MakeLeftStop, this);

		return S_OK;

}
void character::release()
{

}
void character::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_y -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x -= 5;
	}
	switch (_state)
	{
	case CHARA_RIGHT_STOP:
		break;
	case CHARA_LEFT:
		break;
	case STOP:
		break;
	case CHARA_RIGHT_MOVE:
		break;
	case CHARA_LEFT_MOVE:
		break;
	case CHARA_RIGHT_LAND:
		break;
	case CHARA_LEFT_LAND:
		break;
	case CHARA_RIGHT_PUNCH_ONE:
		break;
	case CHARA_RIGHT_PUNCH_TWO:
		break;
	case CHARA_LEFT_PUNCH_ONE:
		break;
	case CHARA_LEFT_PUNCH_TWO:
		break;
	case CHARA_RIGHT_KICK:
		break;
	case CHARA_LEFT_KICK:
		break;
	case CHARA_RIGHT_HEAD:
		break;
	case CHARA_LEFT_HEAD:
		break;
	case CHARA_RIGHT_UPPER:
		break;
	case CHARA_LEFT_UPPER:
		break;
	case CHARA_RIGHT_HIGHKICK:
		break;
	case CHARA_LEFT_HIGHKICK:
		break;
	case CHARA_RIGHT_BACKBLOW:
		break;
	case CHARA_LEFT_BACKBLOW:
		break;
	case CHARA_RIGHT_HOLD:
		break;
	case CHARA_LEFT_HOLD:
		break;
	case CHARA_RIGHT_JUMP:
		break;
	case CHARA_LEFT_JUMP:
		break;
	case CHARA_RIGHT_MOVE_JUMP:
		break;
	case CHARA_LEFT_MOVE_JUMP:
		break;
	case CHARA_RIGHT_BACKKICK:
		break;
	case CHARA_LEFT_BACKKICK:
		break;
	case CHARA_RIGHT_DRILL:
		break;
	case CHARA_LEFT_DRILL:
		break;
	case CHARA_STAIR:
		break;
	case CHARA_RIGHT_HIT:
		break;
	case CHARA_LEFT_HIT:
		break;
	case CHARA_RIGHT_STRIKED:
		break;
	case CHARA_LEFT_STRIKED:
		break;
	case CHARA_RIGHT_DOWN:
		break;
	case CHARA_LEFT_DOWN:
		break;
	case CHARA_RIGHT_JUMP_KICK:
		break;
	case CHARA_LEFT_JUMP_KICK:
		break;
	case CHARA_RIGHT_ATT:
		break;
	case CHARA_LEFT_ATT:
		break;
	default:
		break;
	}
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}
void character::render()
{
	_image->aniRender(getMemDC(), _rc.left, _rc.top,_motion);
}

void MakeRightStop(void* obj)
{

}
void MakeLeftStop(void* obj)
{

}
void MakeRightLand(void* obj)
{

}
void MakeLeftLand(void* obj)
{

}
void MakeRightFall(void* obj)
{

}
void MakeLeftFall(void* obj)
{

}
void MakeRightDown(void* obj)
{

}
void MakeLeftDown(void* obj)
{

}
