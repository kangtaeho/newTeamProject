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
	CHARA_RIGHT_MOVE_JUMP_KICK,
	CHARA_LEFT_MOVE_JUMP_KICK,
	CHARA_RIGHT_ATT,
	CHARA_LEFT_ATT,
	CHARA_RIGHT_KNIFE_HAND,	//오른쪽 칼 쥐는거 (왼쪽 추가해야함)
	CHARA_RIGHT_KNIFE_THROWING,	//오른쪽 칼 던지는거 (왼쪽 추가해야함)
	CHARA_RIGHT_STONE_STOP,		//큰돌 작은돌 가만히 있는거 공용
	CHARA_RIGHT_STONE_HAND,	//오른쪽 돌 드는거 (왼쪽 추가해야함)
	CHARA_RIGHT_STONE_THROWING,	//오른쪽 돌 던지는거 (왼쪽 추가해야함)

	CHARA_LEFT_KNIFE_HAND,	//왼쪽 칼 쥐는거 (오른쪽 추가해야함)
	CHARA_LEFT_KNIFE_THROWING,	//왼쪽 칼 던지는거 (오른쪽 추가해야함)
	CHARA_LEFT_STONE_STOP,		//큰돌 작은돌 가만히 있는거 공용
	CHARA_LEFT_STONE_HAND,	//왼쪽 돌 드는거 (오른쪽 추가해야함)
	CHARA_LEFT_STONE_THROWING	//왼쪽 돌 던지는거 (오른쪽 추가해야함)
};

class item;
class enemyManager;

class character : public gameNode
{
private:
	float _x, _y;
	float _StartX, _StartY;//점프시 돌아올 지점
	float _Zmove;//상하 이동용
	float _JP, _gravity;//점프, 중력
	int _HP, _maxHP;//현피, 맥피
	bool _isRight;//오른쪽?
	bool _isOn;		//2스테이지 땅위?
	int _zOrderY;

	RECT _rc;//렌더용 렉트
	RECT _colliRect;//통신용 렉트
	RECT _rightATK;
	RECT _leftATK;

	//스테이지 담을 변수(설정자)
	//스테이지당 픽셀충돌 검사할 이미지 변수(설정자)

	int _stageCount;
	image * _stage;

	CHARA _state;//상태값
	animation * _motion;//모션
	image * _image;
	image* _JIMMYKnife;
	char test[128];

	item* _item;
	item* _potion;
	enemyManager* _EM;

	bool _isHanded;			//손에 쥐었냐
	bool _isItemCollision;	//투척 아이템과 충돌했냐
	int _itemType;			//무슨 투척 아이템이냐(0 == 칼, 1 == 작은돌, 2 == 큰돌)
public:
	character();
	~character();
	HRESULT init();
	void release();
	void update();
	void render();

	//렉트최신화함수

	RECT getRect() { return _colliRect; }

	RECT getUnderBarRect(){ return _rc; }

	float getX() { return _x; }
	void setX(float X) { _x = X; }
	float getY() { return _y; }
	void setY(float Y) { _y = Y; }

	float getCenterX() {
		return CAMERAMANAGER->CameraRelativePoint(_rc).x + _image->getFrameWidth() / 2+25;
	}

	float getCenterY() {
		return CAMERAMANAGER->CameraRelativePoint(_rc).y + _image->getFrameHeight() / 2+75;
	}

	//상태값 HIT로 바뀌고 데미지
	void hurt(int damage, float x);
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
	static void MakeRightBK(void* obj);
	static void MakeLeftBK(void* obj);


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

	//키 애니메이션 초기화 함수
	void addImage();

	//돌입할 스테이지(충돌할 이미지)
	void setStage(image* stage, int stageCount) { _stage = stage; _stageCount = stageCount; }
		
	//HP반환
	int getHP(){ return _HP; }
	void setHP(int HP) { _HP = HP; }
	int getZOrderY(){ return _zOrderY; }

	item* getQuickPotion(){ return _potion; }

	void setIsItemCollision(bool isItemCollision){ //설정자
		_isItemCollision = isItemCollision;}	
	bool getIsItemCollision(){ return _isItemCollision; } //접근자
	
	bool getIsHanded(){ return _isHanded; }

	void setItemType(int itemType){ //무슨 투척 아이템이냐(0 == 칼, 1 == 작은돌, 2 == 큰돌)
		_itemType = itemType;
	}			

	void drinkPotion();

	void setItem(item* item){ _item = item; }

	void SetMemoryEnemyManager(enemyManager* EM) { _EM = EM; }
	void setMemoryPotion(item* potion){ _potion = potion; }
};


