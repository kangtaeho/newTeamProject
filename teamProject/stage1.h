#pragma once
#include "gameNode.h"
#include "item.h"
#include "knife.h"
#include "bigStone.h"
#include "enemy.h"
#include "boss00.h"
#include "minion00.h"
#include "minion01.h"
#include "minion02.h"
#include "stone.h"
#include "character.h"
#include "inventory.h"
#include "enemyManager.h"
#include "money.h"
#include <vector>

/*
static enum stageState
{
READY,		//알파값을 위한 준비모드(재호 추가)
MOVING,
FIGHTING,
CLEAR
};
*/

class stage1 : public gameNode
{

private:

	vector<item*> _vItem;	//바닥에 있는 아이템과 몬스터가 떨구는 돈을 위한 아이템 벡터
	vector<item*> _viItem;

	RECT _rc1;
	RECT* _currentRC;
	image* _DOOR; // 문추가(병철)
	RECT _DOORRC; // 문추가(병철)

	//float doorX, doorY;
	
	item* _knife; // 칼 스테이지로 가져옴
	item* _stone; // 미니돌덩이 ㅇㅇ
	item* _bigStone; //큰 돌덩이 
	//enemy* _enemy;
	//boss00* _boss00;
	//enemy* _minion00; //enemy로
	enemy* _boss00;
	enemy* _minion00;
	enemy* _minion01;
	enemy* _minion02;


	

	int _alpha;	//알파렌더를 위한 변수

	//inventory* _inven;				//인벤토리 클래스 생성

	bool _stopCharacter;			//캐릭터가 멈췄니?(인벤토리 열때 사용)

	stageState _ss;	//스테이지 상태(stdafx.h에 정의되어있음)

	enemyManager* _em;
	bool _firstWave;
	bool _secondWave;
public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();

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
	void draw();	//그려주는 함수 이후 렌더는 여기서 하는걸로


	vector<item*> getVItem() { return _vItem; }
};

