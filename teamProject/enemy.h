#pragma once
#include "gameNode.h"


//에네미 상태설정 (더 추가 될수도 있음)
enum ENEMYDIRECTION
{
	//오른쪽
	ENEMYDIRECTION_RIGHT_STOP,				//멈춤
	ENEMYDIRECTION_RIGHT_MOVE,				//걸어감
	ENEMYDIRECTION_RIGHT_RUN,				//달리기
	ENEMYDIRECTION_RIGHT_ATTACK,			//공격
	ENEMYDIRECTION_RIGHT_JUMP_ATTACK,		//점프공격
	ENEMYDIRECTION_RIGHT_HIT,				//공격
	ENEMYDIRECTION_RIGHT_CROUCH,			//잡기당함
	ENEMYDIRECTION_RIGHT_CROUCH_HIT,		//잡기당하고후드러맞음
	ENEMYDIRECTION_RIGHT_CROUCH_THROW,		//잡기당하고던지기당함
	ENEMYDIRECTION_RIGHT_DOWN,				//쓰러짐
	ENEMYDIRECTION_RIGHT_DOWN_STAND,		//쓰러지고 일어남
	ENEMYDIRECTION_RIGHT_DOWN_FOREVER,		//쓰러지고 쥭음
	ENEMYDIRECTION_RIGHT_SOMETHING_THROW,	//무언가를 던짐
											//
	//왼쪽								  /	 /
	ENEMYDIRECTION_LEFT_STOP,				//멈춤
	ENEMYDIRECTION_LEFT_MOVE,				//걸어감
	ENEMYDIRECTION_LEFT_RUN,				//달리기
	ENEMYDIRECTION_LEFT_ATTACK,				//공격
	ENEMYDIRECTION_LEFT_JUMP_ATTACK,		//점프공격
	ENEMYDIRECTION_LEFT_HIT,				//공격
	ENEMYDIRECTION_LEFT_CROUCH,				//잡기당함
	ENEMYDIRECTION_LEFT_CROUCH_HIT,			//잡기당하고후드러맞음
	ENEMYDIRECTION_LEFT_CROUCH_THROW,		//잡기당하고던지기당함
	ENEMYDIRECTION_LEFT_DOWN,				//쓰러짐
	ENEMYDIRECTION_LEFT_DOWN_STAND,			//쓰러지고 일어남
	ENEMYDIRECTION_LEFT_DOWN_FOREVER,		//쓰러지고 쥭음
	ENEMYDIRECTION_LEFT_SOMETHING_THROW		//무언가를 던짐
};


class enemy : public gameNode
{
private:
	ENEMYDIRECTION _enemyDirection;


	//이미지와 위치값과 렉트와 HP설정
	image* _imageEnemy;				//이미지
	RECT _rcEnemy;				//렉트
	RECT _CollircEnemy;			//충돌렉트
	int _HP;					//체력
	int _maxHP;					//최대체력
	int _speed;					//속도
	int _x, _y;					//xy값
	float _ZMove;				//z무브
	float _jump, _Gravity;		//점프,중력

	animation* _enemyMotion;



public:
	enemy();
	~enemy();


	HRESULT init(POINT point);
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

