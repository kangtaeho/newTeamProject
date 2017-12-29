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

	_x = _StartX= WINSIZEX / 2;
	_y = _StartY= WINSIZEY / 2;
	_isRight = true;
	_JP = 0;
	_gravity = 0.2f;

	_state = CHARA_RIGHT_STOP;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_colliRect = RectMakeCenter(_x, _y, 54, 120);

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

	int RightJumpKick[] = { 19 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightJumpKick", "JIMMY", RightJumpKick, 1, 6, true);

	int LeftJumpKick[] = { 140 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftJumpKick", "JIMMY", LeftJumpKick, 1, 6, true);

	int RightATT[] = { 48,47,46,45,48,47,46 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightATT", "JIMMY", RightATT, 7, 10, false, MakeRightFall, this);

	int LeftATT[] = { 45,46,48,47,45,46,48 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftATT", "JIMMY", LeftATT, 7, 10, false, MakeLeftFall, this);

	int RightHead[] = { 11,12,11 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightHead", "JIMMY", RightHead, 3, 10, false, MakeRightStop, this);

	int LeftHead[] = { 116,115,116 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftHead", "JIMMY", LeftHead, 3, 10, false, MakeLeftStop, this);

	int RightUpper[] = { 13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightUpper", "JIMMY", RightUpper, 3, 10, false, MakeRightStop, this);

	int LeftUpper[] = { 114,113,112 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftUpper", "JIMMY", LeftUpper, 3, 10, false, MakeLeftStop, this);

	int RightHighKick[] = { 16,17,18 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightHighKick", "JIMMY", RightHighKick, 3, 10, false, MakeRightStop, this);

	int LeftHighKick[] = { 143,142,141 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftHighKick", "JIMMY", LeftHighKick, 3, 10, false, MakeLeftStop, this);

	int RightBackBlow[] = { 25 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightBackBlow", "JIMMY", RightBackBlow, 1, 6, false, MakeRightStop, this);

	int LeftBackBlow[] = { 134 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftBackBlow", "JIMMY", LeftBackBlow, 1, 6, false, MakeLeftStop, this);

	int RightGrab[] = { 20 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightgrab", "JIMMY", RightGrab, 1, 6, false, MakeRightHold, this);

	int RightHold[] = { 21 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightHold", "JIMMY", RightHold, 1, 6, true);

	int LeftGrab[] = { 140 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightgrab", "JIMMY", RightGrab, 1, 6, false, MakeLeftHold, this);

	int LeftHold[] = { 139 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightHold", "JIMMY", RightHold, 1, 6, true);

	int RightBackSting[] = { 54,55 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightBackSting", "JIMMY", RightBackSting, 2, 10, false, MakeRightHold, this);

	int LeftBackSting[] = { 170,169 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftBackSting", "JIMMY", LeftBackSting, 2, 10, false, MakeLeftHold, this);

	int RightTigerKick[] = { 26 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightTigerKick", "JIMMY", RightTigerKick, 1, 10, false, MakeRightHold, this);

	int LeftTigerKick[] = { 133 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftTigerKick", "JIMMY", LeftTigerKick, 1, 10, false, MakeLeftHold, this);

	int RightSwing[] = { 22,23,24 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightSwing", "JIMMY", RightSwing, 3, 10, false, MakeRightStop, this);

	int LeftSwing[] = { 138,137,136 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftSwing", "JIMMY", LeftSwing, 3, 10, false, MakeLeftStop, this);

	int RightJump[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightJump", "JIMMY", RightJump, 1, 6, true);

	int LeftJump[] = { 124 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftJump", "JIMMY", LeftJump, 1, 6, true);

	int RightBackKick[] = { 28,29,30 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightBackKick", "JIMMY", RightBackKick, 3, 10, false, MakeRightStop, this);

	int LeftBackKick[] = { 131,130,129 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftBackKick", "JIMMY", LeftBackKick, 3, 10, false, MakeLeftStop, this);

	int RightReadyDrill[] = { 32 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightReadyDrill", "JIMMY", RightReadyDrill, 1, 10, false, MakeRightDrill, this);

	int RightDrill[] = { 33,34,35 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightDrill", "JIMMY", RightDrill, 3, 10, true);
	int RightKneeKick[] = { 51 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightKneeKick", "JIMMY", RightKneeKick, 1, 6, true);


	int LeftReadyDrill[] = { 159 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftReadyDrill", "JIMMY", LeftReadyDrill, 1, 10, false, MakeLeftDrill, this);

	int LeftDrill[] = { 158,157,156 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftDrill", "JIMMY", LeftDrill, 3, 10, true);
	int LeftKneeKick[] = { 172 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftKneeKick", "JIMMY", LeftKneeKick, 1, 10, true);

	int StairMove[] = { 62,63 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYStairMove", "JIMMY", StairMove, 2, 10, true);

	int StairStop[] = { 62 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYStairStop", "JIMMY", StairStop, 1, 6, true);

	int RightHit[] = { 74 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightHit", "JIMMY", RightHit, 1, 10, true);

	int LeftHit[] = { 181 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftHit", "JIMMY", LeftHit, 1, 10, true);

	int RightStriked[] = { 77 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightStriked", "JIMMY", RightStriked, 1, 6, true);

	int LeftStriked[] = { 178 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftStriked", "JIMMY", LeftStriked, 1, 6, true);

	int RightDown[] = { 78 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYRightDown", "JIMMY", RightDown, 1, 80, true);

	int LeftDown[] = { 177 };
	KEYANIMANAGER->addArrayFrameAnimation("JIMMYLeftDown", "JIMMY", LeftDown, 1, 80, true);




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
	//case CHARA_LEFT:
	//	break;
	//case STOP:
	//	break;
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

void character::MakeRightStop(void* obj)
{
	character* C;

	C->setState(CHARA_RIGHT_STOP);
	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYRightStop"));
	C->getMotion()->start();
}
void character::MakeLeftStop(void* obj)
{
	character* C;

	C->setState(CHARA_LEFT_STOP);
	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYLeftStop"));
	C->getMotion()->start();
}
void character::MakeRightFall(void* obj)
{
	character* C;
	C->setJP(0);
	C->setState(CHARA_RIGHT_JUMP);
	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYRightJump"));
	C->getMotion()->start();

}
void character::MakeLeftFall(void* obj)
{
	character* C;
	C->setJP(0);
	C->setState(CHARA_LEFT_JUMP);
	C->setMotion(KEYANIMANAGER->findAnimation("JIMMYLeftJump"));
	C->getMotion()->start();
}
void character::MakeRightHold(void* obj)
{

}
void character::MakeLeftHold(void* obj)
{

}

//치송아 바로 커밋하지말고 반드시 디버깅 잘 되는거 확인하고
//커밋해줭 (from. 태호)
void character::MakeRightDrill(void* obj){}
void character::MakeLeftDrill(void* obj){}