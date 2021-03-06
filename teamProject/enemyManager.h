#pragma once
#include "gameNode.h"
#include "item.h"
#include "money.h"
#include "character.h"
#include "minion00.h"
#include "minion01.h"
#include "minion02.h"
#include "boss00.h"
#include "minion01.h"
#include <vector>


class stage1;
class stage2;
class stage3;

class enemyManager :public gameNode
{

private:
	//생성되는 적을 담을 벡터
	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _viEnemy;
	

	//적이 죽고 생성되는 돈을 담을 벡터
	vector<item*> _vItem;
	vector<item*>::iterator _viItem;

	//연결 할 플레이어 변수
	character* _mainPlayer;

	stage1* _stage1;
	stage2* _stage2;
	//stage3* _stage3;
	int _stageNum;

	//minion01* _mini;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//쫄따구
	void setMinion(POINT point,int stageCount);
	void setMinion1(POINT point, int stageCount);
	void setMinion2(POINT point, int stageCount);
	//정예
	void setPick(POINT point, int stageCount);
	//보스
	void setBoss(POINT point, int stageCount);

	//적 사망시 제거
	void removeEnemy(int arrNum);
	//돈 습득시 제거
	void removeItem(int arrNum);
	//fight!!
	void collision(void);

	//플레이어와 연결할 통신함수(이후 수정)
	void setCharacterMemoryAddressLink(character* mainPlayer) { _mainPlayer = mainPlayer; }
	//스테이지 연결 통신함수
	void setStage1MemoryAddressLink(stage1* stage1, int stageNum);
	void setStage2MemoryAddressLink(stage2* stage2, int stageNum);
	/*void setStage3MemoryAddressLink(stage3* stage3, int stageNum);*/

	//플레이어와 적들의 통신을 위한 접근자
	vector<enemy*> getVMinion() { return _vEnemy; }

	void traceCharacter();
	void deadEnemy();

};

