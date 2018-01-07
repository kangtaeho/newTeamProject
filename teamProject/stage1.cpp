#include "stdafx.h"
#include "stage1.h"


//변수값 초기화는 여기서
stage1::stage1()	//절대값같은 수치는 여기서 초기화, 이미지의 크기처럼 무언가를 받아서 초기화 해야한다면 init에서
	:_alpha(0),							//알파 초기화
	_firstWave(false),					//처음 웨이브
	_secondWave(false),					//두번째 웨이브
	_stopCharacter(false),	//캐릭터가 멈췄니? (인벤토리 킬때 사용)
	_rc1(RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100)),	// 병철아!!!!! 여기꺼 수정하면된다 시작위치
	_DOORRC(RectMakeCenter(3225, 230, 10, 10)),
	_currentRC(&_rc1),
	_ss(READY),
	_isOpenDoor(false)
{

}


stage1::~stage1()
{
}

HRESULT stage1::init()
{
	addImage();	//사용할 이미지들 추가
	
	_door->setX(3225);
	_door->setY(258);
	
	

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
	//_vItem.push_back(_knife);
	//_vItem.push_back(_bigStone);

	_rc1 = RectMake(_mainPlayer->getRect().left, _mainPlayer->getRect().top, 100, 100);
	_currentRC = &_rc1;

	singletonInit();

	
	


	
	//몬스터 생성은 이런식으로(이후에 makeEnemy 함수에서 생성)
	//_em->setBoss(PointMake(3000,300));

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
			/*_mainPlayer->setX(760);
			_mainPlayer->setY(2310);
			_mainPlayer->UpdateRect();*/
			SCENEMANAGER->changeScene("스테이지01");
			SOUNDMANAGER->stop("스테이지1");
			SOUNDMANAGER->play("스테이지2", 0.5f);
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

		
		//if (KEYMANAGER->isOnceKeyDown('3')) //강제로 클리어상태로 전환
		//{
		//	_ss = CLEAR; 		
		//}
		

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
	}

	_doorAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);

	if (_ss == CLEAR)
	{
		if (!_isOpenDoor)
		{
			_doorAni->start();
			_isOpenDoor = true;
		}
	
	}



	
}

void stage1::render()
{
	draw();
}

void stage1::characterMovement() {

	ZORDERMANAGER->allClear();
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (CAMERAMANAGER->getCameraCondition() != CAMERA_EFFECT)
		{
			if (CAMERAMANAGER->getCameraCondition() == CAMERA_FREE)
			{
				CAMERAMANAGER->cameraMove(false, 0);
				_currentRC->bottom -= 4;
				_currentRC->top -= 4;
			}
			else
			{
				_currentRC->bottom -= 4;
				_currentRC->top -= 4;
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
				_currentRC->bottom += 4;
				_currentRC->top += 4;
			}
			else {
				_currentRC->bottom += 4;
				_currentRC->top += 4;
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
				_currentRC->left -= 4;
				_currentRC->right -= 4;
			}
			else
			{
				if (_currentRC->left <= 0)
				{
					_currentRC->left += 4;
					_currentRC->right += 4;
				}
				_currentRC->left -= 4;
				_currentRC->right -= 4;
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
				_currentRC->left += 4;
				_currentRC->right += 4;
			}
			else
			{
				if (_currentRC->right >= 3456)
				{
					_currentRC->left -= 4;
					_currentRC->right -= 4;
				}
				_currentRC->left += 4;
				_currentRC->right += 4;
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
	_rc1 = RectMake(_mainPlayer->getX() - 30, _mainPlayer->getY() - 30, 100, 100);
	_mainPlayer->update();

	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->update();

		ZORDERMANAGER->addZOrder(_vItem[i], _vItem[i]->getItemRC().bottom);
	}
	makeEnemy();
	enemyItemCollision();
	playerItemCollisioin();

		_em->update();
	
	ZORDERMANAGER->addZOrder(_mainPlayer, _mainPlayer->getZOrderY());
	//ZORDERMANAGER->addZOrder(_stone, _stone->getItemRC().bottom);
	/*if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SCENEMANAGER->changeScene("스테이지01");
	}*/
}
void stage1::makeEnemy() {


	//카메라 특정 지점일때 몬스터 생성
	//첫 웨이브가 나왔냐 && 카메라가 특정 지점에 왔냐
	if (!_firstWave /*&& CAMERAMANAGER->getCameraPoint().x >=2070*/)
	{
		_firstWave = true;
		CAMERAMANAGER->backGroundSizeSetting(2070, 648);
	//쫄따구 1마리 생성\


		_em->setMinion1(PointMake(1500, 400),1);
		//_em->setMinion(PointMake(1000, 400));
		//_em->setMinion2(PointMake(1200, 400));
	//_em->getVMinion()[0]->setStageMemoryLink(this);
	//카메라 고정 추가(기성아 부탁한다) 추가 
	//CAMERAMANAGER->setCameraCondition(CAMERA_FREE);

	}


	else if (_firstWave && _em->getVMinion().size() == 0)
	{
		CAMERAMANAGER->backGroundSizeSetting(3456, 648);
		//_em->setMinion1(PointMake(1500, 300));
	////카메라 다시 이동(기성아 부탁한다) 추가
		_currentRC = &_rc1;
		CAMERAMANAGER->setCameraAim(_currentRC);
		CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	}

	////두번째 웨이브가 나왔냐 && 카메라가 특정 지점이냐
	if (!_secondWave && _firstWave &&_em->getVMinion().size() == 0 /*&& 카메라가 특정지점이냐*/)
	{
		////정예몹 1마리 생성
		_secondWave = true;
		_em->setPick(PointMake(3000, 400),1);
	//_em->getVMinion()[0]->setStageMemoryLink(this);
	////카메라 고정 추가(이것도 부탁해) 추가
	//CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
		//_em->getVMinion()[0]->setStageMemoryLink(this);
		////카메라 고정 추가(이것도 부탁해) 추가
		//CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	}

	////두번째 웨이브는 나왔는데 에너미 매니져의 크기가 0이다 --> 몹 다죽임
	else if (_secondWave && _em->getVMinion().size() == 0)
	{
		CAMERAMANAGER->backGroundSizeSetting(3456, 648);
		//카메라 다시 이동(기성아 부탁한다) 추가 
		_currentRC = &_rc1;
		CAMERAMANAGER->setCameraAim(_currentRC);
		CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
		_ss = CLEAR;
	}

	

	
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

	_door = IMAGEMANAGER->addFrameImage("스테이지1_문", "./images/door.bmp", 460, 155, 3, 1, false, RGB(255, 0, 255));
	
	
}

void stage1::initialization()
{

	//칼추가 //병철
	//_knife = new knife;
	//_knife->init(PointMake(1000, 350));


	_doorAni = new animation;
	_doorAni->init(_door->getWidth(), _door->getHeight(), _door->getFrameWidth(), _door->getFrameHeight());
	_doorAni->setDefPlayFrame(false, false);
	_doorAni->setFPS(1);
	_stone = new stone;
	_stone->init(PointMake(2000, 450));

	//_bigStone = new bigStone;
	//_bigStone->init(PointMake(2000, 380));

	_mainPlayer = new character;
	_mainPlayer->init();
	_mainPlayer->setStage(IMAGEMANAGER->findImage("스테이지_00_red"), 1);

	_inven = new inventory;
	_inven->init();

	_em = new enemyManager;
	_em->init();

	_inven->setMainPlayerMemoryLink(_mainPlayer);
	_mainPlayer->SetMemoryEnemyManager(_em);
	_em->setCharacterMemoryAddressLink(_mainPlayer);
	_em->setStage1MemoryAddressLink(this,1);
}

void stage1::singletonInit(){
	CAMERAMANAGER->backGroundSizeSetting(3456, 648);

	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	CAMERAMANAGER->setCameraAim(&_rc1);

	SOUNDMANAGER->play("스테이지1", 0.5f);
	SOUNDMANAGER->setCurrentBgmKey("스테이지1");

	ZORDERMANAGER->addZOrder(_mainPlayer, _mainPlayer->getZOrderY());
}

void stage1::draw(){
	IMAGEMANAGER->findImage("스테이지_00")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);	
	if (KEYMANAGER->isToggleKey('8'))
	IMAGEMANAGER->findImage("스테이지_00_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	_door->aniRender(getMemDC(),
								CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_door->getX(), _door->getY(), _door->getFrameWidth(), _door->getFrameHeight())).x,
								CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_door->getX(), _door->getY(), _door->getFrameWidth(), _door->getFrameWidth())).y, _doorAni);
	
	ZORDERMANAGER->paintZOrder();
	_inven->render();


	//알파렌더를 위한 검은화면 렌더
	IMAGEMANAGER->findImage("검은화면")->alphaRender(getMemDC(), 0, 0, 255 - _alpha);

}
void stage1::enemyItemCollision(){

	//몬스터가 없으면 확인할 필요없다.
	if (_em->getVMinion().size() == 0) return;
	//아이템이 없으면 확인할 필요없다.
	if (_vItem.size() == 0) return;

	for (int i = 0; i < _em->getVMinion().size(); i++)
	{
		for (int j = 0; j < _vItem.size(); j++)
		{
			//돈타입이면 체크 넘긴다.
			if (_vItem[j]->getItemType() == 2) continue;

			//드랍상태면 넘긴다.
			if (_vItem[j]->getState() == 0) continue;

			//그 외 아이템이면서 날라가는 상태면 충돌체크
			RECT temp;
			if (IntersectRect(&temp, &_vItem[j]->getItemRC(), &_em->getVMinion()[i]->getCollircEnemy()))
			{
				_em->getVMinion()[i]->setIsTracePlayer(5);
				_em->getVMinion()[i]->setHP(-_vItem[j]->getItemEffect());				
				_em->getVMinion()[i]->setIsHitted(true);
			}
		}
	}
}
void stage1::playerItemCollisioin(){
	//아이템이 없으면 확인할 필요없다.
	if (_vItem.size() == 0) return;
	
	for (int i = 0; i < _vItem.size(); /*++i*/)
	{
		RECT temp;
		if (IntersectRect(&temp, &_mainPlayer->getRect(), &_vItem[i]->getAbsoluteRC()))
		{
			//돈타입이면 소지금 올려주고 
			if (_vItem[i]->getItemType() == 2)
			{
				ZORDERMANAGER->allClear();
				_inven->setCurrentMoney(_vItem[i]->getItemEffect());
				SAFE_DELETE(_vItem[i]);
				_vItem.erase(_vItem.begin() + i);
				continue;
			}
			//투척가능타입이면
			else if (_vItem[i]->getItemType() == 1)
			{
				//이미 무언가 들고 있는 상태면
				if (_mainPlayer->getIsHanded())
				{
					++i;
					continue;
				}
				_mainPlayer->setIsItemCollision(true);
				_mainPlayer->setItem(_vItem[i]);
				if (i == 0) //돌, 칼 큰돌
				{
					_mainPlayer->setItemType(0);
				}
				if (i == 1) //돌, 칼 큰돌
				{
					_mainPlayer->setItemType(1);
				}
				if (i == 2) //돌, 칼 큰돌
				{
					_mainPlayer->setItemType(2);
				}
				break;
			}
			++i;
		}
		else
		{
			//아이템 들고있으면 밑에 진행안함
			if (_mainPlayer->getIsHanded())
			{
				++i;
				continue;
			}

			_mainPlayer->setIsItemCollision(false);
			++i;
		}

	}
	
}