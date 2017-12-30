#pragma once
#include "gameNode.h"
#include "startscene.h"
#include "stage1.h"
#include "stage2.h"

class mainGame : public gameNode
{
private:
	
	//현재씬
	gameNode* _currentScene;
	gameNode* _loadingScene;
	//스테이지 1 씬
	gameNode* _stage1;
	gameNode* _stage2;
	

	/*
	재호 : 아이템클래스 사용 예시 (변수명은 그때그때 바꾸길)
	item _item; (.h파일)

	초기화
	_item = new money; (이후 .cpp파일, money말고 포션종류, 오브젝트 등 자기가 필요한 아이템에 따라 변경가능)
	_item -> init(PointMake(10, 10));

	
	포션초기화
	_item = new redPotion;
	_item -> init();

	포션 렌더일경우
	_item->getItemImage()->render(getMemDC(), x좌표, y좌표);

	오브젝트, 돈 렌더는 잠시 보류
	*/


public:
	virtual HRESULT init();			
	virtual void release();			
	virtual void update();			
	virtual void render();	




	mainGame();
	~mainGame();
};

