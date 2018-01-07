#pragma once
#include "gameNode.h"


//에네미 상태설정 (더 추가 될수도 있음)

class stage1;

//잡몹
enum ENEMYDIRECTION
{
	
	//오른쪽
	ENEMYDIRECTION_RIGHT_STOP,				//멈춤
	ENEMYDIRECTION_RIGHT_MOVE,				//걸어감
	ENEMYDIRECTION_RIGHT_RUN,				//달리기
	ENEMYDIRECTION_RIGHT_ONE_JAB,			//원쨉공격
	ENEMYDIRECTION_RIGHT_TWO_JAB,			//투쨉공격
	ENEMYDIRECTION_RIGHT_JUMP_ATTACK,		//점프공격
	ENEMYDIRECTION_RIGHT_HIT,				//공격당함
	ENEMYDIRECTION_RIGHT_HIT2,				//경직걸리는공격당함
	ENEMYDIRECTION_RIGHT_CROUCH,			//잡기당함
	ENEMYDIRECTION_RIGHT_CROUCH_HIT,		//잡기당하고후드러맞음
	ENEMYDIRECTION_RIGHT_CROUCH_THROW,		//잡기당하고던지기당함
	ENEMYDIRECTION_RIGHT_DOWN,				//쓰러짐
	ENEMYDIRECTION_RIGHT_COMBO_DOWN,		//연속공격맞고쓰러짐
	ENEMYDIRECTION_RIGHT_DOWN_STAND,		//쓰러지고 일어남
	ENEMYDIRECTION_RIGHT_DOWN_FOREVER,		//쓰러지고 쥭음
	ENEMYDIRECTION_RIGHT_STONE_UP,			//돌을 들고있음
	ENEMYDIRECTION_RIGHT_STONE_UP_MOVE,		//돌을 들고움직임
	ENEMYDIRECTION_RIGHT_STONE_THROW,		//돌을 던짐
	ENEMYDIRECTION_RIGHT_KNIFE_UP,			//칼 들음
	ENEMYDIRECTION_RIGHT_KNIFE_THROW,		//칼 던짐
											
	//왼쪽									  //
	ENEMYDIRECTION_LEFT_STOP,				//멈춤
	ENEMYDIRECTION_LEFT_MOVE,				//걸어감
	ENEMYDIRECTION_LEFT_RUN,				//달리기
	ENEMYDIRECTION_LEFT_ONE_JAB,			//원쨉공격
	ENEMYDIRECTION_LEFT_TWO_JAB,			//투쨉공격
	ENEMYDIRECTION_LEFT_JUMP_ATTACK,		//점프공격
	ENEMYDIRECTION_LEFT_HIT,				//공격당함
	ENEMYDIRECTION_LEFT_HIT2,				//경직걸리는공격당함
	ENEMYDIRECTION_LEFT_CROUCH,				//잡기당함
	ENEMYDIRECTION_LEFT_CROUCH_HIT,			//잡기당하고후드러맞음
	ENEMYDIRECTION_LEFT_CROUCH_THROW,		//잡기당하고던지기당함
	ENEMYDIRECTION_LEFT_DOWN,				//쓰러짐
	ENEMYDIRECTION_LEFR_COMBO_DOWN,			//연속공격맞고쓰러짐
	ENEMYDIRECTION_LEFT_DOWN_STAND,			//쓰러지고 일어남
	ENEMYDIRECTION_LEFT_DOWN_FOREVER,		//쓰러지고 쥭음
	ENEMYDIRECTION_LEFT_STONE_UP,			//돌을 들고있음
	ENEMYDIRECTION_LEFT_STONE_UP_MOVE,		//돌을 들고움직임
	ENEMYDIRECTION_LEFT_STONE_THROW,		//돌을 던짐
	ENEMYDIRECTION_LEFT_KNIFE_UP,			//칼들음
	ENEMYDIRECTION_LEFT_KNIFE_THROW,		//칼던짐

	//공통
	ENEMYDIRECTION_Clime				//사다리

};


//보스
enum BOSSDIRECTION
{
	//오른쪽
	BOSSDIRECTION_RIGHT_STOP,				//멈춤
	BOSSDIRECTION_RIGHT_MOVE,				//걸어감
	BOSSDIRECTION_RIGHT_ONE_JAB,			//원쨉공격
	BOSSDIRECTION_RIGHT_TWO_JAB,			//투쨉공격
	BOSSDIRECTION_RIGHT_HIT,				//공격당함
	BOSSDIRECTION_RIGHT_HIT2,				//경직걸리는공격당함
	BOSSDIRECTION_RIGHT_DOWN,				//쓰러짐
	BOSSDIRECTION_RIGHT_COMBO_DOWN,			//연속공격맞고쓰러짐
	BOSSDIRECTION_RIGHT_DOWN_STAND,			//쓰러지고 일어남

											
	//왼쪽									  //
	BOSSDIRECTION_LEFT_STOP,				//멈춤
	BOSSDIRECTION_LEFT_MOVE,				//걸어감
	BOSSDIRECTION_LEFT_ONE_JAB,				//원쨉공격
	BOSSDIRECTION_LEFT_TWO_JAB,				//투쨉공격
	BOSSDIRECTION_LEFT_HIT,					//공격당함
	BOSSDIRECTION_LEFT_HIT2,				//경직걸리는공격당함
	BOSSDIRECTION_LEFT_DOWN,				//쓰러짐
	BOSSDIRECTION_LEFT_COMBO_DOWN,			//연속공격맞고쓰러짐
	BOSSDIRECTION_LEFT_DOWN_STAND,			//쓰러지고 일어남

	//공통
	BOSSDIRECTION_DEAD						//죽음씬
};


class enemy : public gameNode
{
protected:
	//
	ENEMYDIRECTION _enemyDirection;
	BOSSDIRECTION _bossDirection;

	//이미지와 위치값과 렉트와 HP설정
	image* _imageEnemy;				//이미지
	RECT _rcEnemy;					//렉트
	RECT _CollircEnemy;				//충돌렉트
	int _HP;						//체력
	int _maxHP;						//최대체력
	int _speed;						//속도
	float _x, _y;						//xy값 (절대 좌표)
	float _ZMove;					//z무브
	float _jump, _Gravity;			//점프,중력

	int _countMove;					//카운트 무브 (AI 상태 시간)

	int _rndDirX;					//X방향설정
	int _rndDirY;					//Y방향설정
	int _currentStage;				//현재 스테이지 (굉장히 중요! 스테이 1은 xy다 움직이지만
									//스테이지 2부터는 안움직이니깐 그때마다 예외처리가 달라야함
									//굉장히 중요하다.

	int _rndTum;					//랜덤 텀
	int _rndTum2;					//랜덤 텀2

	float _traceAngle;


	float _enemyCenterX, _enemyCenterY;
	float _playerCenterX, _playerCenterY;

	animation* _enemyMotion;
	animation* _bossMotion;


	string _enemyKeyName[14];

	bool _isItemCollion;			//아이템이랑 부딪혔냐
	bool _isGetItemEnemy;			//아이탬을 잡을수 있는 에너미니?
	bool _isAttack;					//플레이어를 공격중이니?
	bool _attackAniStart;			//어택 애니메이션 시작중
	bool _hittedAniStart;			//맞는 애니메이션 시작중
	bool _dieAniStart;
	
	int _isTracePlayer;				//플레이어를 만났니?
									// 0 이 패트롤 상태 // 1번 : 플레이 발견 // 3번 : 플레이어 공격

	bool _isLeft = true;					//왼쪽입니까?
	bool _isRight = true;

	bool _isHitted;				//플레이어 한테 맞았습니까?

	int _countAttack = 0;				//어택카운트
	int _countHitted = 0;

	stage1* _stage1;

public:
	enemy();
	~enemy();

	virtual HRESULT init(POINT point, int currentStage = 1);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void collision();


	//콜백함수를 위함

	static void rightAttack(void* obj);
	static void rightJumpAttack(void* obj);
	static void leftAttack(void* obj);
	static void leftJumpAttack(void* obj);

	//에네미 상태에 따른 접근자와 설정자겠지?
	/*virtual ENEMYDIRECTION getEnemyDirection(void) {  }
	virtual void setEnemyDirection(ENEMYDIRECTION direction) { }*/
	//
	////에네미의 모션에 따른 접근자와 설정자겠지?
	animation* getEnemyMotion(void) { return _enemyMotion; }
	void setEnemyMotion(animation* ani) { _enemyMotion = ani; }

	animation* getBossMotion(void) { return _bossMotion; }
	void setBossMotion(animation* ani) { _bossMotion = ani; }


	void enemyMove();
	int rndDirection(int value);


	bool getIsGetItemEemey() { return _isGetItemEnemy; }

	void setIsTracePlayer(int isTracePlayer) { _isTracePlayer = isTracePlayer; }
	void setTraceAngle(float traceAngle) { _traceAngle= traceAngle; } //각도 구하기
	float getTraceAngle() { return _traceAngle; }

	float getCenterX() { return  CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x + _imageEnemy->getFrameWidth() / 2; }
	float getCenterY() { return  CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y + _imageEnemy->getFrameHeight() / 2; }

	//적의 절대좌표 반환
	float getAbsoluteX(){ return _x; }
	float getAbsoluteY(){ return _y; }


	void setPlayerCenterX(float playerCenterX) { _playerCenterX = playerCenterX; }
	void setPlayerCenterY(float playerCenterY) { _playerCenterY = playerCenterY; }

	int getCountMove() { return _countMove; }

	RECT getCollircEnemy(){ return _CollircEnemy; }
	void setIsItemCollion(bool isItemCollion){ _isItemCollion = isItemCollion; }

	void setStageMemoryLink(stage1* stage1){ _stage1 = stage1; }

	void setIsAttack(bool isAttack) { _isAttack = isAttack; }
	bool getIsAttack() { return _isAttack; }

	void setIsHitted(bool isHitted) { _isHitted = isHitted; }
	bool getIsHitted() { return _isHitted; }


	bool getIsRight() { return _isRight; }
	bool getIsLeft() { return _isLeft; }

	void setHP(int HP) { _HP = HP; }
	int getHP() { return _HP; }

	int getCountHitted() { return _countHitted; }
	int getIsTracePlayer() { return _isTracePlayer; }
};

//이제 콜백함수가 필요한 모션들이라던가 그런거 뭐해야될까영
//더 추가해야될건 뭐가있을까여