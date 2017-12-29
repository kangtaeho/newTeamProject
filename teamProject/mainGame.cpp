#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()			//초기화 함수
{
	gameNode::init(true);

	//병철 추가 // 스테이지 1 씬 //20171227 7:43
	SCENEMANAGER->addScene("스테이지00", new stage1);
	SCENEMANAGER->addScene("스테이지01", new stage2);

	//재호 : 게임시작화면
	SCENEMANAGER->addScene("스타트", new startscene);


	//SCENEMANAGER->changeScene("스테이지00");

	//재호 : 게임 시작신으로설정
	SCENEMANAGER->changeScene("스타트", false);


	IMAGEMANAGER->addImage("유아이박스", "./images/ui_box.bmp", 1152, 144, true, RGB(255, 0, 255));

	//재호 : 이미지 출력 실험용
	//IMAGEMANAGER->addImage("상점", "./images/shop.bmp", 262, 396, true, RGB(255, 0, 255));

	_inven = new inventory;
	_inven->init();

	return S_OK;
}

void mainGame::release()			//메모리 해제 함수
{
	gameNode::release();

	
}

void mainGame::update()				//연산 함수
{
	gameNode::update();

	

	SCENEMANAGER->update();



	


}

void mainGame::render()		//그려주는 함수(a.k.a WM_PAINT)
{
	//흰색 도화지 한장~
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== 건들지마라 ======================
	
	

	//병철추가 //유아이박스 카메라 영향 안받음 위치고정 // 20121227 7:45
	//재호 : 현재신이 스타트 신이면 유아이박스 안그리도록
	if (SCENEMANAGER->isStartScene("스타트"))
	{
		SCENEMANAGER->render();
	}
	else{

		SCENEMANAGER->render();
		IMAGEMANAGER->findImage("유아이박스")->render(getMemDC(), 0, WINSIZEY - IMAGEMANAGER->findImage("유아이박스")->getHeight());

	}
	

	//재호 : 이미지 출력 실험용
	//IMAGEMANAGER->findImage("상점")->render(getMemDC(), WINSIZEX/2 - 300, 40);
	
	//태호 : 인벤토리 랜더 실험용
	if (KEYMANAGER->isToggleKey('0')) {
		_inven->render();
	}

	//==================== 건들지마라 =======================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
