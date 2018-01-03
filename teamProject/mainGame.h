#pragma once
#include "gameNode.h"
#include "startscene.h"
#include "stage1.h"
#include "stage1Story.h"
#include "stage2.h"
#include "stage3.h"
#include "stage3Story.h"


class mainGame : public gameNode
{
private:
	
	//현재씬
	gameNode* _currentScene;
	gameNode* _loadingScene;

	//이거 필요없어서 주석처리함 (재호)
	////스테이지 1 씬
	//gameNode* _stage1;
	//gameNode* _stage2;
	

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

	void addImage();		//이미기 추가해주는 함수 이후 이미지는 여기서 add하는걸로
	void initialization();	//변수들 new선언 및 init 해주는 함수 이후 new 및 init은 여기서 하는걸로
	void singletonInit();	//init에서 싱글톤들 세팅해주는 함수 이후 세팅은 여기서 하는걸로


	mainGame();
	~mainGame();
};

