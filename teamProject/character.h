#pragma once
#include "gameNode.h"

#define CHARASPEED 4;
#define CHARAJUMP 8;

enum CHARA {
	CHARA_RIGHT_STOP,
	CHARA_LEFT_STOP,
	CHARA_RIGHT_MOVE,
	CHARA_LEFT_MOVE,
	CHARA_RIGHT_LAND,
	CHARA_LEFT_LAND,
	CHARA_RIGHT_PUNCH_ONE,
	CHARA_RIGHT_PUNCH_TWO,
	CHARA_LEFT_PUNCH_ONE,
	CHARA_LEFT_PUNCH_TWO,
	CHARA_RIGHT_KICK,
	CHARA_LEFT_KICK,
	CHARA_RIGHT_HEAD,
	CHARA_LEFT_HEAD,
	CHARA_RIGHT_UPPER,
	CHARA_LEFT_UPPER,
	CHARA_RIGHT_HIGHKICK,
	CHARA_LEFT_HIGHKICK,
	CHARA_RIGHT_BACKBLOW,
	CHARA_LEFT_BACKBLOW,
	CHARA_RIGHT_HOLD,
	CHARA_LEFT_HOLD,
	CHARA_RIGHT_JUMP,
	CHARA_LEFT_JUMP,
	CHARA_RIGHT_MOVE_JUMP,
	CHARA_LEFT_MOVE_JUMP,
	CHARA_RIGHT_BACKKICK,
	CHARA_LEFT_BACKKICK,
	CHARA_RIGHT_DRILL,
	CHARA_LEFT_DRILL,
	CHARA_STAIR,
	CHARA_RIGHT_HIT,
	CHARA_LEFT_HIT,
	CHARA_RIGHT_STRIKED,
	CHARA_LEFT_STRIKED,
	CHARA_RIGHT_DOWN,
	CHARA_LEFT_DOWN,
	CHARA_RIGHT_JUMP_KICK,
	CHARA_LEFT_JUMP_KICK,
	CHARA_RIGHT_ATT,
	CHARA_LEFT_ATT,
};

class character : public gameNode
{
private:
	float _x, _y;
	float _StartX, _StartY;//점프시 돌아올 지점
	float _Zmove;//상하 이동용
	float _JP, _gravity;//점프, 중력
	int _HP, _maxHP;//현피, 맥피
	bool _isRight;//오른쪽?

	RECT _rc;//렌더용 렉트
	RECT _colliRect;//통신용 렉트

	CHARA _state;//상태값
	animation * _motion;//모션
	image * _image;

public:
	character();
	~character();
	HRESULT init();
	void release();
	void update();
	void render();

	//렉트최신화함수
	void RectUpdate();

	RECT getRect() { return _colliRect; }
	float getX() { return _x; }
	void setX(float X) { _x = X; }
	float getY() { return _y; }
	void setY(float Y) { _y = Y; }

	//상태값 HIT로 바뀌고 데미지
	void hurt(int damage);
	//상태값 STRIKED로 바뀌고 데미지 입으며
	//x값이 클때는 왼쪽 작을때는 오른쪽으로 쓰러짐
	void strike(int damage, float x);

	static void MakeRightStop(void* obj);
	static void MakeLeftStop(void* obj);
	static void MakeRightFall(void* obj);
	static void MakeLeftFall(void* obj);
	static void MakeRightHold(void* obj);
	static void MakeLeftHold(void* obj);
	static void MakeRightDrill(void* obj);
	static void MakeLeftDrill(void* obj);
	static void MakeRightLand(void* obj);
	static void MakeLeftLand(void* obj);

	//캐릭터 상태접근자,설정자
	CHARA getState() { return _state; }
	void setState(CHARA C) { _state = C; }

	//캐릭터 모션접근자,설정자
	animation * getMotion() { return _motion; }
	void setMotion(animation * ani) { _motion = ani; }

	//점프파워 설정
	void setJP(float J) { _JP = J; }

	//상하이동가능
	void ZmoveOn() { _Zmove = CHARASPEED; }

	//상하이동불가능
	void ZmoveOff() { _Zmove = 0; };

	//렉트최신화
	void UpdateRect();
};

