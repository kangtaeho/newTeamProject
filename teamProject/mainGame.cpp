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

	SOUNDMANAGER->addSound("게임시작화면", "./sounds/게임시작화면.mp3", true, false);
	SOUNDMANAGER->addSound("스테이지1", "./sounds/스테이지1.mp3", true, true);
	SOUNDMANAGER->addSound("스테이지2", "./sounds/스테이지2.mp3", true, true);
	SOUNDMANAGER->addSound("스테이지3", "./sounds/스테이지3.mp3", true, true);
	SOUNDMANAGER->addSound("크억(죽을때)", "./sounds/크억(죽을때).wav", false, false);
	SOUNDMANAGER->addSound("흐앗(발차기할때)", "./sounds/흐앗(발차기할때).wav", false, false);
	SOUNDMANAGER->addSound("흣(때릴때)", "./sounds/흣(때릴때).wav", false, false);
	SOUNDMANAGER->addSound("펀치맞을때", "./sounds/펀치맞을때.wav", false, false);



	//병철 추가 // 스테이지 1 씬 //20171227 7:43
	SCENEMANAGER->addScene("스테이지00", new stage1);
	SCENEMANAGER->addScene("스테이지01", new stage2);

	//재호 : 게임시작화면
	SCENEMANAGER->addScene("스타트", new startscene);
	//재호 : 1,3스테이지 대화화면
	SCENEMANAGER->addScene("1스테이지대화", new stage1Story);
	SCENEMANAGER->addScene("3스테이지대화", new stage3Story);

	//SCENEMANAGER->changeScene("스테이지00");

	//재호 : 게임 시작신으로설정
	SCENEMANAGER->changeScene("스타트", false);


	IMAGEMANAGER->addImage("유아이박스", "./images/ui_box.bmp", 1152, 144, true, RGB(255, 0, 255));

	//재호 : 이미지 출력 실험용
	//IMAGEMANAGER->addImage("상점", "./images/shop.bmp", 262, 396, true, RGB(255, 0, 255));

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
	//재호 : 현재신이 스타트 신 or 대화씬이면 유아이박스 안그리도록
	if (SCENEMANAGER->isStartScene("스타트") || SCENEMANAGER->isStartScene("1스테이지대화") || SCENEMANAGER->isStartScene("3스테이지대화" ))
	{
		SCENEMANAGER->render();
	}
	else{

		SCENEMANAGER->render();
		IMAGEMANAGER->findImage("유아이박스")->render(getMemDC(), 0, WINSIZEY - IMAGEMANAGER->findImage("유아이박스")->getHeight());

	}
	

	//재호 : 이미지 출력 실험용
	//IMAGEMANAGER->findImage("상점")->render(getMemDC(), WINSIZEX/2 - 300, 40);
	

	//==================== 건들지마라 =======================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
