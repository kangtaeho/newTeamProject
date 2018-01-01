#pragma once
#include "gameNode.h"
#include "enemy.h"

enum BOSSDIRECTION
{
	//오른쪽
	BOSSDIRECTION_RIGHT_STOP,				//멈춤
	BOSSDIRECTION_RIGHT_MOVE,				//걸어감
	BOSSDIRECTION_RIGHT_RUN,				//달리기
	BOSSDIRECTION_RIGHT_ONE_JAB,			//원쨉공격
	BOSSDIRECTION_RIGHT_TWO_JAB,			//투쨉공격
	BOSSDIRECTION_RIGHT_JUMP_ATTACK,		//점프공격
	BOSSDIRECTION_RIGHT_HIT,				//공격당함
	BOSSDIRECTION_RIGHT_HIT2,				//경직걸리는공격당함
	BOSSDIRECTION_RIGHT_CROUCH,			//잡기당함
	BOSSDIRECTION_RIGHT_CROUCH_HIT,		//잡기당하고후드러맞음
	BOSSDIRECTION_RIGHT_CROUCH_THROW,		//잡기당하고던지기당함
	BOSSDIRECTION_RIGHT_DOWN,				//쓰러짐
	BOSSDIRECTION_RIGHT_COMBO_DOWN,		//연속공격맞고쓰러짐
	BOSSDIRECTION_RIGHT_DOWN_STAND,		//쓰러지고 일어남
	BOSSDIRECTION_RIGHT_DOWN_FOREVER,		//쓰러지고 쥭음
	BOSSDIRECTION_RIGHT_STONE_UP,			//돌을 들고있음
	BOSSDIRECTION_RIGHT_STONE_UP_MOVE,		//돌을 들고움직임
	BOSSDIRECTION_RIGHT_STONE_THROW,		//돌을 던짐
	BOSSDIRECTION_RIGHT_KNIFE_UP,			//칼 들음
	BOSSDIRECTION_RIGHT_KNIFE_THROW,		//칼 던짐


	//왼쪽									  //
	BOSSDIRECTION_LEFT_STOP,				//멈춤
	BOSSDIRECTION_LEFT_MOVE,				//걸어감
	BOSSDIRECTION_LEFT_RUN,				//달리기
	BOSSDIRECTION_LEFT_ONE_JAB,			//원쨉공격
	BOSSDIRECTION_LEFT_TWO_JAB,			//투쨉공격
	BOSSDIRECTION_LEFT_JUMP_ATTACK,		//점프공격
	BOSSDIRECTION_LEFT_HIT,				//공격당함
	BOSSDIRECTION_LEFT_HIT2,				//경직걸리는공격당함
	BOSSDIRECTION_LEFT_CROUCH,				//잡기당함
	BOSSDIRECTION_LEFT_CROUCH_HIT,			//잡기당하고후드러맞음
	BOSSDIRECTION_LEFT_CROUCH_THROW,		//잡기당하고던지기당함
	BOSSDIRECTION_LEFT_DOWN,				//쓰러짐
	BOSSDIRECTION_LEFR_COMBO_DOWN,			//연속공격맞고쓰러짐
	BOSSDIRECTION_LEFT_DOWN_STAND,			//쓰러지고 일어남
	BOSSDIRECTION_LEFT_DOWN_FOREVER,		//쓰러지고 쥭음
	BOSSDIRECTION_LEFT_STONE_UP,			//돌을 들고있음
	BOSSDIRECTION_LEFT_STONE_UP_MOVE,		//돌을 들고움직임
	BOSSDIRECTION_LEFT_STONE_THROW,		//돌을 던짐
	BOSSDIRECTION_LEFT_KNIFE_UP,			//칼들음
	BOSSDIRECTION_LEFT_KNIFE_THROW,		//칼던짐

	//공통
	BOSSDIRECTION_Clime,					//사다리
	BOSSDIRECTION_RIGHT_DEAD				//죽음씬
};


class boss00 : public enemy
{
private:
	BOSSDIRECTION _BossDirection;


	//이미지와 위치값과 렉트와 HP설정
	/*
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
	*/
	



public:
	boss00();
	~boss00();


	virtual HRESULT init(POINT point);
	//virtual void release();
	//virtual void update();
	//virtual void render();
	virtual void collision();


	//콜백함수를 위함

	static void rightAttack(void* obj);
	static void rightJumpAttack(void* obj);
	static void leftAttack(void* obj);
	static void leftJumpAttack(void* obj);

	/*virtual ENEMYDIRECTION getEnemyDirection(void) { return _BossDirection; }
	virtual void setEnemyDirection(ENEMYDIRECTION direction) { _BossDirection; }*/

	////에네미 상태에 따른 접근자와 설정자겠지?
	//BOSSDIRECTION getEnemyDirection(void) { return _BossDirection; }
	//void setEnemyDirection(BOSSDIRECTION direction) { _BossDirection = direction; }

	////에네미의 모션에 따른 접근자와 설정자겠지?
	//animation* getBossMotion(void) { return _BossMotion; }
	//void getBossMotion(animation* ani) { _BossMotion = ani; }
};

