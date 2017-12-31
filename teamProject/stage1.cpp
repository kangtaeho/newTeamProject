#include "stdafx.h"
#include "stage1.h"


stage1::stage1()
{

}


stage1::~stage1()
{
}

HRESULT stage1::init()
{

	CAMERAMANAGER->backGroundSizeSetting(3456, 648);

	IMAGEMANAGER->addImage("스테이지_00", "./images/01_stage00.bmp", 3456, 648, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스테이지_00_red", "./images/01_stage00_red.bmp", 3456, 648, true, RGB(255, 0, 255));
	//레드칠한거 
	IMAGEMANAGER->addImage("검은화면", "./images/backWindow.bmp", 1152, 648, true, RGB(255, 0, 255));
	//알파값,웨이브정보 초기화
	_alpha = _firstWave = _secondWave = 0;

	// 스테이지상태
	// 기존 moving 에서 ready로 수정
	_ss = READY;

	//카메라 렉트
	rc1 = RectMakeCenter(500, 300 , 100, 100);
	currentRC = &rc1;

	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	CAMERAMANAGER->setCameraAim(&rc1);

	//칼추가 //병철
	_knife = new knife;
	_knife->init(PointMake(1000, 350));

	//에너미 추가...중  //수빈

	for (int i = 0; i < 4; i++)
	{
		_enemy = new enemy;
		_enemy->init(PointMake(300 + i * 25, 300 + i * 25));
	}

		_boss00 = new boss00;
		_boss00->init(PointMake(500,300));

	//미니돌덩이 //병철
	_stone = new stone;
	_stone->init(PointMake(2000, 450));

	_mainPlayer = new character;
	_mainPlayer->init();

	_inven = new inventory;
	_inven->init();

	_stopCharacter = false;

	_em = new enemyManager;
	_em->init();

	SOUNDMANAGER->play("스테이지1",0.5f);

	return S_OK;
}

void stage1::release()
{
}

void stage1::update()
{
	//스테이지 상태가 체인지 되어 레디상태일경우 알파값 증가
	if (_ss == READY)
	{
		//알파값이 255이하면 검은화면 들어가고 메인화면 등장
		if (_alpha < 255)
			_alpha += 5;
		//최대값인 255에 도달하면 스테이지 상태는 moving
		else
			_ss = MOVING;
	}
	else if (_ss == CLEAR)
	{
		if (_alpha >0)
			_alpha -= 5;
		else
			SCENEMANAGER->changeScene("스테이지01");
	}
	//스테이지 상태가 레디나 클리어가 아닐때만 모든 행동 가능하도록
	else if (_ss != READY || _ss != CLEAR)
	{
		if (!_stopCharacter) {
			characterMovement();
		}

		if (KEYMANAGER->isOnceKeyDown('1')&&!_inven->getOpenShop()) { //인벤토리 오픈
			if (_inven->getOpenInventory()) {
				_inven->closeInventory();
				_stopCharacter = false;
			}
			else {
				_inven->openInventory();
				_stopCharacter = true;
			}
		}

		if (KEYMANAGER->isOnceKeyDown('2')&&!_inven->getOpenInventory()) { //상점 오픈
			if (_inven->getOpenShop()) {
				_inven->closeShop();
				_stopCharacter = false;
			}
			else {
				_inven->openShop();
				_stopCharacter = true;
			}
		}
		if (KEYMANAGER->isOnceKeyDown('3')) //강제로 클리어상태로 전환
		{
			_ss = CLEAR;
			SOUNDMANAGER->stop("스테이지1");
		}

		_inven->update();
	}
}

void stage1::render()
{
	IMAGEMANAGER->findImage("스테이지_00")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("스테이지_00_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	_knife->render();
	_enemy->render();
	_boss00->render();
	_stone->render();

	_mainPlayer->render();
	//유아이박스는 메인게임에다 그냥 고정박아버림 // 병철
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(rc1).x, CAMERAMANAGER->CameraRelativePoint(rc1).y, 100, 100);
	
	_inven->render();

	IMAGEMANAGER->findImage("검은화면")->alphaRender(getMemDC(), 0, 0, 255-_alpha);

}

void stage1::characterMovement() {

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (CAMERAMANAGER->getCameraCondition() != CAMERA_EFFECT)
		{
			if (CAMERAMANAGER->getCameraCondition() == CAMERA_FREE)
			{
				CAMERAMANAGER->cameraMove(false, 0);
				currentRC->bottom -= 5;
				currentRC->top -= 5;
			}
			else
			{
				currentRC->bottom -= 5;
				currentRC->top -= 5;
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (CAMERAMANAGER->getCameraCondition() != CAMERA_EFFECT)
		{
			if (CAMERAMANAGER->getCameraCondition() == CAMERA_FREE)
			{
				CAMERAMANAGER->cameraMove(false, 0);
				currentRC->bottom += 5;
				currentRC->top += 5;
			}
			else {
				currentRC->bottom += 5;
				currentRC->top += 5;
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (CAMERAMANAGER->getCameraCondition() != CAMERA_EFFECT)
		{
			if (CAMERAMANAGER->getCameraCondition() == CAMERA_FREE)
			{
				CAMERAMANAGER->cameraMove(true, 0);
				currentRC->left -= 5;
				currentRC->right -= 5;
			}
			else
			{
				if (currentRC->left <= 0)
				{
					currentRC->left += 5;
					currentRC->right += 5;
				}
				currentRC->left -= 5;
				currentRC->right -= 5;
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (CAMERAMANAGER->getCameraCondition() != CAMERA_EFFECT)
		{
			if (CAMERAMANAGER->getCameraCondition() == CAMERA_FREE)
			{
				CAMERAMANAGER->cameraMove(true, 0);
				currentRC->left += 5;
				currentRC->right += 5;
			}
			else
			{
				if (currentRC->right >= 3456)
				{
					currentRC->left -= 5;
					currentRC->right -= 5;
				}
				currentRC->left += 5;
				currentRC->right += 5;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		currentRC = &rc1;
		CAMERAMANAGER->setCameraAim(currentRC);
		CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);

	}

	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	}

	_enemy->update();
	_mainPlayer->update();

	/*if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SCENEMANAGER->changeScene("스테이지01");
	}*/
}

void stage1::makeEnemy(){

	/*
	카메라 특정 지점일때 몬스터 생성
	첫 웨이브가 나왔냐 && 카메라가 특정 지점에 왔냐
	if (!firstWave && 카메라가 특정지점이냐)
	{

	쫄따구 1마리 생성
	_em -> setMinion()

	카메라 고정 추가(기성아 부탁한다)


	}

	첫 웨이브는 나왔는데 에너미 매니져의 크기가 0이다 --> 몹 다죽임
	else if(firstWave && _em.size() == 0)
	{

	카메라 다시 이동(기성아 부탁한다)

	}

	두번째 웨이브가 나왔냐 && 카메라가 특정 지점이냐
	if(!secondWave && 카메라가 특정지점이냐)
	{
	정예몹 1마리 생성
	_em -> setPick()

	카메라 고정 추가(이것도 부탁해)
	}

	//두번째 웨이브는 나왔는데 에너미 매니져의 크기가 0이다 --> 몹 다죽임
	else if(secondWave && _em.size() == 0)
	{

	카메라 다시 이동(기성아 부탁한다)

	}

	*/
}