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

	addImage();

	//SCENEMANAGER->changeScene("스테이지00");

	//재호 : 게임 시작신으로설정
	SCENEMANAGER->changeScene("스타트", false);

	//이걸 주석 풀면 바로 2스테에서 튀어나옴
	//SCENEMANAGER->changeScene("스테이지01", false);

	//이걸 주석풀면 바로 3스테에서 튀어나옴
	//SCENEMANAGER->changeScene("스테이지02", false);

	


	return S_OK;
}

void mainGame::release()			//메모리 해제 함수
{
	gameNode::release();

	
}

void mainGame::update()				//연산 함수
{
	gameNode::update();
	
	if (KEYMANAGER->isOnceKeyDown('0')) {
		if (OPTION->getIsOpenOption()) {
			OPTION->closeOption();
		}
		else {
			OPTION->openOption();
		}
	}

	if (OPTION->getIsOpenOption()) {
		OPTION->update();
	}
	else {
		SCENEMANAGER->update();
	}

}

void mainGame::render()		//그려주는 함수(a.k.a WM_PAINT)
{
	//흰색 도화지 한장~

	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
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

		IMAGEMANAGER->findImage("퀵포션박스")->render(getMemDC(), 700, 538);
		if (SCENEMANAGER->getCurrentScene()->getMainPlayer()->getQuickPotion() != NULL)
		SCENEMANAGER->getCurrentScene()->getMainPlayer()->getQuickPotion()->getItemImage()->render(getMemDC(), 703, 540);
		//IMAGEMANAGER->findImage("피박스")->render(getMemDC(), 400, 400);
		for (int i = 0;
			i < SCENEMANAGER->getCurrentScene()->getMainPlayer()->getHP(); i++)
		{
			IMAGEMANAGER->findImage("피박스")->render(getMemDC(), 100 + (30*i), 538);
		}
	}

	//재호 : 이미지 출력 실험용
	//IMAGEMANAGER->findImage("상점")->render(getMemDC(), WINSIZEX/2 - 300, 40);
	
	OPTION->render();

	//==================== 건들지마라 =======================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
void mainGame::addImage()		//이미기 추가해주는 함수 이후 이미지는 여기서 add하는걸로
{
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

	SCENEMANAGER->addScene("스테이지02", new stage3);

	//재호 : 게임시작화면
	SCENEMANAGER->addScene("스타트", new startscene);

	//재호 : 1,3스테이지 대화화면
	SCENEMANAGER->addScene("1스테이지대화", new stage1Story);
	SCENEMANAGER->addScene("3스테이지대화", new stage3Story);

	IMAGEMANAGER->addImage("유아이박스", "./images/ui_box.bmp", 1152, 144, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("퀵포션박스", "./images/circle.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("피박스", "./images/hprect.bmp", 24, 24, true, RGB(255, 0, 255));

}
void mainGame::initialization()	//변수들 new선언 및 init 해주는 함수 이후 new 및 init은 여기서 하는걸로
{

}
void mainGame::singletonInit()	//init에서 싱글톤들 세팅해주는 함수 이후 세팅은 여기서 하는걸로		  
{

}