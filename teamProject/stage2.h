#pragma once
#include "gameNode.h"
#include "inventory.h"
#include "character.h" //카메라 해주세요 기성씨~
#include "enemyManager.h"
#include "money.h"

/*
static enum stageState
{
READY,		//알파값을 위한 준비모드(재호 추가)
MOVING,
FIGHTING,
CLEAR
};
*/

class stage2 : public gameNode
{
private:
	//카메라 렉트
	RECT _rc1;
	RECT* _currentRC;

	//엘레베이터 렉트
	image* _elevator;
	RECT _elevatorRC;

	float _elevatorX, _elevatorY; //엘레베이터 x,y좌표

	POINT _playerStartPoint; //플레이어의 시작 좌표

	//쪽배 렉트
	image* _boat;
	RECT _boatRC;

	float _boatX, _boatY; //쪽배 x,y좌표

	bool _boatSwitchOn;		//보트랑 충돌했냐 ??
	bool _elevatorSwitchOn; //엘레베이터 렉트 건드렸냐??

	//강물

	image* _liver;
	animation* _liverAni;

	enemyManager* _em;


	

	vector<item*> _vItem;	//바닥에 있는 아이템과 몬스터가 떨구는 돈을 위한 아이템 벡터
	vector<item*> _viItem;	


	//스테이지 1과 마찬가지로 알파렌더를 위한 변수
	int _alpha;

	stageState _ss;	//스테이지 상태(stdafx.h에 정의되어있음)
	bool _stopCharacter;			//캐릭터가 멈췄니?(인벤토리 열때 사용)
	
	bool _firstWave, _secondWave, _thirdWave;
	//inventory* _inven;
public:
	stage2();
	~stage2();

	HRESULT init();
	void release();
	void update();
	void render();

	void boatMove();	 //보트 무브 함수 
	void elevatorMove(); //엘베 무브 함수

	virtual void setMainPlayer(character* mainPlayer) { _mainPlayer = mainPlayer; }
	virtual character* getMainPlayer(){ return _mainPlayer; }

	virtual void setInventory(inventory* inven) { _inven = inven; }
	virtual inventory* getInventory(){ return _inven; }

	void dropMoney(POINT point, int won);	//돈 드랍 함수 몬스터가 죽었을경우 이것 호출하면 됩니다.

	void makeEnemy();	//몬스터 생성 함수

	void characterMovement();							//캐릭터 키매지저를 관리하는 함수

	void addImage();		//이미기 추가해주는 함수 이후 이미지는 여기서 add하는걸로
	void initialization();	//변수들 new선언 및 init 해주는 함수 이후 new 및 init은 여기서 하는걸로
	void singletonInit();	//init에서 싱글톤들 세팅해주는 함수 이후 세팅은 여기서 하는걸로
	void draw();			//그려주는 함수 이후 렌더는 여기서 하는걸로
}; 

