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

	DOOR = IMAGEMANAGER->addFrameImage("스테이지1_문", "./images/door.bmp", 460, 155, 3, 1, true, RGB(255, 0, 255));
	DOOR->setX(3225);
	DOOR->setY(258);




	DOOR->setFrameX(0);
	DOORRC = RectMakeCenter(3225, 190, 10, 10);

	//DOORRC = RectMakeCenter(1000, 300, 200, 200);

	
	//알파값,웨이브정보 초기화
	_alpha = _firstWave = _secondWave = 0;

	// 스테이지상태
	// 기존 moving 에서 ready로 수정
	_ss = READY;

	//카메라 렉트
	//rc1 = RectMakeCenter(50, 300 , 100, 100);
	rc1 = RectMakeCenter(3225, 300, 100, 100); //렉트 문앞에다 놨음
	currentRC = &rc1;

	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	CAMERAMANAGER->setCameraAim(&rc1);

	//칼추가 //병철
	_knife = new knife;
	_knife->init(PointMake(1000, 350));

	//에너미 추가...중  //수빈

	/*_minion00 = new minion00;
	_minion00->init(PointMake(300 , 300 ));*/

	_boss00 = new boss00;
	_boss00->init(PointMake(500,300));

	_minion00 = new minion00;
	_minion00->init(PointMake(800, 300));

	_minion01 = new minion01;
	_minion01->init(PointMake(500, 500));

	//_minion02 = new minion02;
	//_minion02->init(PointMake(800, 500));

	//미니돌덩이 //병철
	_stone = new stone;
	_stone->init(PointMake(2000, 450));

	_bigStone = new bigStone;
	_bigStone->init(PointMake(2000, 380));

	_mainPlayer = new character;
	_mainPlayer->init();

	_inven = new inventory;
	_inven->init();

	_stopCharacter = false;

	_em = new enemyManager;
	_em->init();

	//아이템 벡터에 돌, 칼 추가
	_vItem.push_back(_stone);
	_vItem.push_back(_knife);
	_vItem.push_back(_bigStone);

	SOUNDMANAGER->play("스테이지1",0.5f);
	SOUNDMANAGER->setCurrentBgmKey("스테이지1");

	return S_OK;
}

void stage1::release()
{
}

void stage1::update()
{
	RECT temp;
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
	//스테이지 상태가 다음맵으로 넘어가는경우

	//else if (_ss == CLEAR)
	//{															
	//	//알파값 감소시켜 검은화면 나타나면서						   
	//	if (_alpha >0)											
	//		_alpha -= 5;										
	//	//알파값이 0이 되면 다음 스테이지							 
	//	else													
	//SCENEMANAGER->changeScene("스테이지01");
	//}

	//스테이지 상태가 레디나 클리어가 아닐때만 모든 행동 가능하도록 // 문에 닿지 않았을때 추가 
	else if (_ss ==  MOVING || (_ss == CLEAR && !IntersectRect(&temp, &rc1, &DOORRC)))
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
			
			
		}
		

		if (KEYMANAGER->isOnceKeyDown('4')) //강제로 돈드랍
		{
			dropMoney(PointMake(200,200),10);
		}
		if (KEYMANAGER->isOnceKeyDown('5')) //오브젝트 강제로 날라가는 상태로 변경
		{
			for (int i = 0; i < _vItem.size(); i++)
			{
				_vItem[i]->setState(true);
			}
		}
		_inven->update();
		for (int i = 0; i < _vItem.size(); i++)
		{
			_vItem[i]->update();
		}
		
		
	}

	//RECT temp;
	if (IntersectRect(&temp, &rc1, &DOORRC) && _ss == CLEAR) //클리어 상태에서 문에 닿았을때 다음씬으로 넘겨라 //병철
	{

		if (_alpha >0)
			_alpha -= 5;
		//알파값이 0이 되면 다음 스테이지							 
		else
			SCENEMANAGER->changeScene("스테이지01");
			SOUNDMANAGER->stop("스테이지1");
	}
}

void stage1::render()
{
	IMAGEMANAGER->findImage("스테이지_00")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("스테이지_00_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	//_knife->render();
	//_minion00->render();
	_boss00->render();
	_minion00->render();
	_minion01->render();
	//_minion02->render();
	//_stone->render();

	_mainPlayer->render();
	
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(rc1).x, CAMERAMANAGER->CameraRelativePoint(rc1).y, 100, 100);

	


		IMAGEMANAGER->findImage("스테이지1_문")->frameRender(getMemDC(), 
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(DOOR->getX(), DOOR->getY(), DOOR->getFrameWidth(), DOOR->getFrameHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(DOOR->getX(), DOOR->getY(), DOOR->getFrameWidth(), DOOR->getFrameHeight())).y, DOOR->getFrameX(), DOOR->getFrameY());

	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(DOORRC).x, CAMERAMANAGER->CameraRelativePoint(DOORRC).y, 10, 10);
	_inven->render();

	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render();
	}

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
				currentRC->bottom -= 10;
				currentRC->top -= 10;
			}
			else
			{
				currentRC->bottom -= 10;
				currentRC->top -= 10;
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
				currentRC->bottom += 10;
				currentRC->top += 10;
			}
			else {
				currentRC->bottom += 10;
				currentRC->top += 10;
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
				currentRC->left -= 10;
				currentRC->right -= 10;
			}
			else
			{
				if (currentRC->left <= 0)
				{
					currentRC->left += 10;
					currentRC->right += 10;
				}
				currentRC->left -= 10;
				currentRC->right -= 10;
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
				currentRC->left += 10;
				currentRC->right += 10;
			}
			else
			{
				if (currentRC->right >= 3456)
				{
					currentRC->left -= 10;
					currentRC->right -= 10;
				}
				currentRC->left += 10;
				currentRC->right += 10;
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

	//_minion00->update();
	_boss00->update();
	_minion00->update();
	_minion01->update();
	//_minion02->update();
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
//돈 드랍 함수			어디에        얼마냐
void stage1::dropMoney(POINT point, int won){

	item* tempMoney = new money;
	tempMoney->init(point, won);

	_vItem.push_back(tempMoney);

}