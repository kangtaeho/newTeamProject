#include "stdafx.h"
#include "stage1.h"


//변수값 초기화는 여기서
stage1::stage1()	//절대값같은 수치는 여기서 초기화, 이미지의 크기처럼 무언가를 받아서 초기화 해야한다면 init에서
:_alpha(0),							//알파 초기화
_firstWave(false),					//처음 웨이브
_secondWave(false),					//두번째 웨이브
_stopCharacter(false),				//캐릭터가 멈췄니? (인벤토리 킬때 사용)
_rc1(RectMakeCenter(3225, 300, 100, 100)),	// 병철아!!!!! 여기꺼 수정하면된다 시작위치
_DOORRC(RectMakeCenter(3225, 190, 10, 10)),
_currentRC(&_rc1),
_ss(READY)
{

}


stage1::~stage1()
{
}

HRESULT stage1::init()
{
	addImage();	//사용할 이미지들 추가
	
	_DOOR->setX(3225);
	_DOOR->setY(258);
	_DOOR->setFrameX(0);
	

	// 스테이지상태
	// 기존 moving 에서 ready로 수정
	//_ss = READY;

	//카메라 렉트
	//rc1 = RectMakeCenter(50, 300 , 100, 100);
	//_rc1 = RectMakeCenter(3225, 300, 100, 100); //렉트 문앞에다 놨음
	//_currentRC = &_rc1;
	
	initialization();	//각종 변수 new 및 init 선언
	
	//아이템 벡터에 돌, 칼 추가
	_vItem.push_back(_stone);
	_vItem.push_back(_knife);
	_vItem.push_back(_bigStone);

	singletonInit();

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

	else if (IntersectRect(&temp, &_rc1, &_DOORRC) && _ss == CLEAR) //클리어 상태에서 문에 닿았을때 다음씬으로 넘겨라 //병철
	{

		if (_alpha >0) 
			_alpha -= 5;
		//알파값이 0이 되면 다음 스테이지							 
		else
		{
			SCENEMANAGER->changeScene("스테이지01");
			SOUNDMANAGER->stop("스테이지1");
		}
	}

	//스테이지 상태가 레디나 클리어가 아닐때만 모든 행동 가능하도록 // 문에 닿지 않았을때 추가 
	else if (_ss == MOVING || (_ss == CLEAR && !IntersectRect(&temp, &_rc1, &_DOORRC)))
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

	_em->update();
}

void stage1::render()
{
	draw();
}

void stage1::characterMovement() {

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (CAMERAMANAGER->getCameraCondition() != CAMERA_EFFECT)
		{
			if (CAMERAMANAGER->getCameraCondition() == CAMERA_FREE)
			{
				CAMERAMANAGER->cameraMove(false, 0);
				_currentRC->bottom -= 10;
				_currentRC->top -= 10;
			}
			else
			{
				_currentRC->bottom -= 10;
				_currentRC->top -= 10;
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
				_currentRC->bottom += 10;
				_currentRC->top += 10;
			}
			else {
				_currentRC->bottom += 10;
				_currentRC->top += 10;
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
				_currentRC->left -= 10;
				_currentRC->right -= 10;
			}
			else
			{
				if (_currentRC->left <= 0)
				{
					_currentRC->left += 10;
					_currentRC->right += 10;
				}
				_currentRC->left -= 10;
				_currentRC->right -= 10;
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
				_currentRC->left += 10;
				_currentRC->right += 10;
			}
			else
			{
				if (_currentRC->right >= 3456)
				{
					_currentRC->left -= 10;
					_currentRC->right -= 10;
				}
				_currentRC->left += 10;
				_currentRC->right += 10;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_currentRC = &_rc1;
		CAMERAMANAGER->setCameraAim(_currentRC);
		CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);

	}

	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	}

	//_boss00->update();
	//_minion00->update();
	//_minion01->update();
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

	카메라 고정 추가(기성아 부탁한다) 추가 
	CAMERAMANAGER->setCameraCondition(CAMERA_FREE);

	}

	첫 웨이브는 나왔는데 에너미 매니져의 크기가 0이다 --> 몹 다죽임
	else if(firstWave && _em.size() == 0)
	{

	카메라 다시 이동(기성아 부탁한다) 추가
	currentRC = &rc1;
	CAMERAMANAGER->setCameraAim(currentRC);
	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	}

	두번째 웨이브가 나왔냐 && 카메라가 특정 지점이냐
	if(!secondWave && 카메라가 특정지점이냐)
	{
	정예몹 1마리 생성
	_em -> setPick()

	카메라 고정 추가(이것도 부탁해) 추가
	CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	}

	//두번째 웨이브는 나왔는데 에너미 매니져의 크기가 0이다 --> 몹 다죽임
	else if(secondWave && _em.size() == 0)
	{

	카메라 다시 이동(기성아 부탁한다) 추가 
	currentRC = &rc1;
	CAMERAMANAGER->setCameraAim(currentRC);
	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	}

	*/
}
//돈 드랍 함수			어디에        얼마냐
void stage1::dropMoney(POINT point, int won){

	item* tempMoney = new money;
	tempMoney->init(point, won);

	_vItem.push_back(tempMoney);

}
void stage1::addImage(){
	IMAGEMANAGER->addImage("스테이지_00", "./images/01_stage00.bmp", 3456, 648, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스테이지_00_red", "./images/01_stage00_red.bmp", 3456, 648, true, RGB(255, 0, 255));
	//레드칠한거 
	IMAGEMANAGER->addImage("검은화면", "./images/backWindow.bmp", 1152, 648, true, RGB(255, 0, 255));

	_DOOR = IMAGEMANAGER->addFrameImage("스테이지1_문", "./images/door.bmp", 460, 155, 3, 1, true, RGB(255, 0, 255));
}

void stage1::initialization(){
	//칼추가 //병철
	_knife = new knife;
	_knife->init(PointMake(1000, 350));

	//에너미 추가...중  //수빈

	//_boss00 = new boss00;
	//_boss00->init(PointMake(500, 300));
	
	//_minion00 = new minion00;
	//_minion00->init(PointMake(800, 300));
	//
	//_minion01 = new minion01;
	//_minion01->init(PointMake(650, 300));
	//
	//_minion02 = new minion02;
	//_minion02->init(PointMake(350, 300));

	//미니돌덩이 //병철
	_stone = new stone;
	_stone->init(PointMake(2000, 450));

	_bigStone = new bigStone;
	_bigStone->init(PointMake(2000, 380));

	_mainPlayer = new character;
	_mainPlayer->init();

	_inven = new inventory;
	_inven->init();

	_em = new enemyManager;
	_em->init();
}

void stage1::singletonInit(){
	CAMERAMANAGER->backGroundSizeSetting(3456, 648);

	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	CAMERAMANAGER->setCameraAim(&_rc1);

	SOUNDMANAGER->play("스테이지1", 0.5f);
	SOUNDMANAGER->setCurrentBgmKey("스테이지1");
}

void stage1::draw(){
	IMAGEMANAGER->findImage("스테이지_00")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("스테이지_00_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);

	//_boss00->render();
	//_minion00->render();
	//_minion01->render();
	//_minion02->render();


	_em->render();
	_mainPlayer->render();

	//카메라 렉트(이후 주석처리를 통해 지우도록!)
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rc1).x, CAMERAMANAGER->CameraRelativePoint(_rc1).y, 100, 100);
	
	IMAGEMANAGER->findImage("스테이지1_문")->frameRender(getMemDC(),
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_DOOR->getX(), _DOOR->getY(), _DOOR->getFrameWidth(), _DOOR->getFrameHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_DOOR->getX(), _DOOR->getY(), _DOOR->getFrameWidth(), _DOOR->getFrameHeight())).y,
		_DOOR->getFrameX(), _DOOR->getFrameY());

	//문 렉트(이후 삭제하도록)
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_DOORRC).x, CAMERAMANAGER->CameraRelativePoint(_DOORRC).y, 10, 10);
	_inven->render();

	//아이템 렌더
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render();
	}

	//알파렌더를 위한 검은화면 렌더
	IMAGEMANAGER->findImage("검은화면")->alphaRender(getMemDC(), 0, 0, 255 - _alpha);
}