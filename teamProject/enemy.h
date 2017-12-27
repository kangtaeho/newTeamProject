#pragma once
#include "gameNode.h"


//에네미 상태설정 (더 추가 될수도 있음)
enum ENEMYDIRECTION
{
	ENEMYDIRECTION_RIGHT_STOP,
	ENEMYDIRECTION_RIGHT_MOVE,
	ENEMYDIRECTION_RIGHT_RUN,
	ENEMYDIRECTION_RIGHT_ATTACK,
	ENEMYDIRECTION_RIGHT_JUMP_ATTACK,
	ENEMYDIRECTION_RIGHT_HIT,
	ENEMYDIRECTION_RIGHT_CROUCH,
	ENEMYDIRECTION_RIGHT_CROUCH_HIT,
	ENEMYDIRECTION_RIGHT_CROUCH_THROW,
	ENEMYDIRECTION_RIGHT_DOWN,
	ENEMYDIRECTION_RIGHT_DOWN_STAND,
	ENEMYDIRECTION_RIGHT_DOWN_FOREVER,
	ENEMYDIRECTION_LEFT_STOP,
	ENEMYDIRECTION_LEFT_MOVE,
	ENEMYDIRECTION_LEFT_RUN,
	ENEMYDIRECTION_LEFT_ATTACK,
	ENEMYDIRECTION_LEFT_JUMP_ATTACK,
	ENEMYDIRECTION_LEFT_HIT,
	ENEMYDIRECTION_LEFT_CROUCH,
	ENEMYDIRECTION_LEFT_CROUCH_HIT,
	ENEMYDIRECTION_LEFT_CROUCH_THROW,
	ENEMYDIRECTION_LEFT_DOWN,
	ENEMYDIRECTION_LEFT_DOWN_STAND,
	ENEMYDIRECTION_LEFT_DOWN_FOREVER
};


class enemy : public gameNode
{
private:
	ENEMYDIRECTION _enemyDirection;


	//이미지와 위치값과 렉트와 HP설정
	image* _image;
	float _x, _y;
	RECT _rc;
	int _currentHP;


	animation* _enemyMotion;



public:
	enemy();
	~enemy();


	HRESULT init();
	void release();
	void update();
	void render();


	//콜백함수를 위함

	static void rightAttack(void* obj);
	static void rightJumpAttack(void* obj);
	static void leftAttack(void* obj);
	static void leftJumpAttack(void* obj);

	//에네미 상태에 따른 접근자와 설정자겠지?
	ENEMYDIRECTION getEnemyDirection(void) { return _enemyDirection; }
	void setEnemyDirection(ENEMYDIRECTION direction) { _enemyDirection = direction; }

	//에네미의 모션에 따른 접근자와 설정자겠지?
	animation* getEnemyMotion(void) { return _enemyMotion; }
	void setEnemyMotion(animation* ani) { _enemyMotion = ani; }
};

