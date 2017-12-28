#pragma once
#include "gameNode.h"


//에네미 상태설정 (더 추가 될수도 있음)
enum ENEMYDIRECTION
{
	//오른쪽
	ENEMYDIRECTION_RIGHT_STOP,			  //오른쪽멈춤
	ENEMYDIRECTION_RIGHT_MOVE,			  //오른쪽움직임
	ENEMYDIRECTION_RIGHT_RUN,			  //오른쪽달림
	ENEMYDIRECTION_RIGHT_ATTACK,		  //오른쪽공격
	ENEMYDIRECTION_RIGHT_JUMP_ATTACK,     //오른쪽점프어택
	ENEMYDIRECTION_RIGHT_HIT,			  //오른쪽바라보면서 맞음
	ENEMYDIRECTION_RIGHT_CROUCH,		  //오른쪽에서 잡힘
	ENEMYDIRECTION_RIGHT_CROUCH_HIT,	  //오른쪽에서 잡혀서 맞음
	ENEMYDIRECTION_RIGHT_CROUCH_THROW,	  //오른쪽으로 던져짐
	ENEMYDIRECTION_RIGHT_DOWN,			  //쓰러짐
	ENEMYDIRECTION_RIGHT_DOWN_STAND,	  //쓰러졌다가 일어남
	ENEMYDIRECTION_RIGHT_DOWN_FOREVER,	  //영원히 죽음
	ENEMYDIRECTION_RIGHT_SOMETHING_THROW, //무언가를 던짐

	//왼쪽
	ENEMYDIRECTION_LEFT_STOP,				//왼쪽멈춤
	ENEMYDIRECTION_LEFT_MOVE,				//왼쪽움직임
	ENEMYDIRECTION_LEFT_RUN,				//왼쪽달림
	ENEMYDIRECTION_LEFT_ATTACK,				//왼쪽공격
	ENEMYDIRECTION_LEFT_JUMP_ATTACK,		//왼쪽점프어택
	ENEMYDIRECTION_LEFT_HIT,				//왼쪽바라보면서 맞음
	ENEMYDIRECTION_LEFT_CROUCH,				//왼쪽에서 잡힘
	ENEMYDIRECTION_LEFT_CROUCH_HIT,			//왼쪽에서 잡혀서 맞음
	ENEMYDIRECTION_LEFT_CROUCH_THROW,		//왼쪽으로 던져짐
	ENEMYDIRECTION_LEFT_DOWN,				//왼쪽으로 쓰러짐
	ENEMYDIRECTION_LEFT_DOWN_STAND,			//쓰러졌다가 일어남
	ENEMYDIRECTION_LEFT_DOWN_FOREVER,		//영원히 죽음
	ENEMYDIRECTION_LEFT_SOMETHING_THROW		//무언가를 던짐
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

