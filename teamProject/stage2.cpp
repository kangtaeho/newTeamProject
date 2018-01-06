#include "stdafx.h"
#include "stage2.h"


stage2::stage2() //절대값같은 수치는 여기서 초기화, 이미지의 크기처럼 무언가를 받아서 초기화 해야한다면 init에서
	: _alpha(0),
	_ss(READY),
	_rc1(RectMakeCenter(760, 2280, 100, 100)), //카메라의 렉트 좌표
	_rc2(RectMakeCenter(760, 2280, 100, 100)),
	_rc3(RectMakeCenter(760, 2280, 100, 100)),
	_playerStartPoint(PointMake(760, 2310)), //스테이지 2 플레이어 시작좌표
	_currentRC(&_rc1),
	_firstWave(false),
	_secondWave(false),
	_thirdWave(false),
	_boatSwitchOn(false),	//배랑 충돌했냐 ??
	_elevatorSwitchOn(false)//엘베랑 충돌했냐??
{
}

stage2::~stage2()
{
}

HRESULT stage2::init()
{
	
	addImage();			//이미지 add
	initialization();	//변수 new 및 init
	singletonInit();	//싱글톤 init

	_boatX = 1420;
	_boatY = 2400;

	//_boat->setX(1450);
	//_boat->setY(2400);
	_boatRC = RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight());
	
	//_elevator->setX(5520);
	//_elevator->setY(2186);

	_elevatorX = 5520;
	_elevatorY = 2186;

	_elevatorRC = RectMakeCenter(_elevatorX, _elevatorY, 10, 10);



	_liver->setX(2900);
	_liver->setY(2450);

	_liverAni->start();
	


	return S_OK;
}

void stage2::release()
{

}

void stage2::update()
{


	//스테이지가 호출되어 레디상태일경우 알파값 덧셈
	if (_ss == READY)
	{
		_mainPlayer->setX(760);
		_mainPlayer->setY(2280);
		_mainPlayer->setStage(IMAGEMANAGER->findImage("스테이지_01_red"), 2);
		if (_alpha < 255)
			_alpha += 5;
		//알파값 최대면 움직이기 가능
		else
			_ss = MOVING;
	}
	else if (_ss == CLEAR)
	{
		if (_alpha >0)
			_alpha -= 5;
		else
		{
			SCENEMANAGER->changeScene("3스테이지대화");
			SOUNDMANAGER->stop("스테이지2");
		}
	}
	//스테이지가 준비 or 클리어 상태가 아닐때만 조작 가능
	else if (_ss != READY || _ss != CLEAR)
	{
		if (KEYMANAGER->isOnceKeyDown('1') && !_inven->getOpenShop()) { //인벤토리 오픈
			if (_inven->getOpenInventory()) {
				_inven->closeInventory();
				_stopCharacter = false;
			}
			else {
				_inven->openInventory();
				_stopCharacter = true;
			}
		}

		if (KEYMANAGER->isOnceKeyDown('2') && !_inven->getOpenInventory()) { //상점 오픈
			if (_inven->getOpenShop()) {
				_inven->closeShop();
				_stopCharacter = false;
			}
			else {
				_inven->openShop();
				_stopCharacter = true;
			}
		}
		//3키 입력시 강제 클리어전환
		if (KEYMANAGER->isOnceKeyDown('3'))
		{
			_ss = CLEAR; //보스 디지면 클리어로 전환 
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (CAMERAMANAGER->getCameraCondition() != CAMERA_EFFECT)
			{
				if (CAMERAMANAGER->getCameraCondition() == CAMERA_FREE)
				{
					CAMERAMANAGER->cameraMove(false, 0);
					//_currentRC->bottom -= 5;
					//_currentRC->top -= 5;
				}
				else
				{
					//_currentRC->bottom -= 5;
					//_currentRC->top -= 5;
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
					//_currentRC->bottom += 5;
					//_currentRC->top += 5;
				}
				else {
					//_currentRC->bottom += 5;
					//_currentRC->top += 5;
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
					//_currentRC->left -= 5;
					//_currentRC->right -= 5;
				}
				else if (CAMERAMANAGER->getCameraCondition() == CAMERA_STAGE2)
				{
					CAMERAMANAGER->stage2CameraFollow(true, -5);
					//_currentRC->left -= 5;
					//_currentRC->right -= 5;
				}
				else
				{
					//if (_currentRC->left <= 0)
					//{
					//	_currentRC->left += 5;
					//	_currentRC->right += 5;
					//}
					//_currentRC->left -= 5;
					//_currentRC->right -= 5;
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
					//_currentRC->left += 5;
					//_currentRC->right += 5;
				}
				else if (CAMERAMANAGER->getCameraCondition() == CAMERA_STAGE2)
				{
					CAMERAMANAGER->stage2CameraFollow(true, 5);
					//_currentRC->left += 5;
					//_currentRC->right += 5;
				}
				else
				{
					//if (_currentRC->right >= 5795)
					//{
					//	_currentRC->left -= 5;
					//	_currentRC->right -= 5;
					//}
					//_currentRC->left += 5;
					//_currentRC->right += 5;
				}
			}
		}

		//카메라 위치보정을 위해 에이밍으로 바꾼후 스테이지2 카메라로 변경
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
			_currentRC = &_rc1;
			CAMERAMANAGER->setCameraAim(_currentRC);
			CAMERAMANAGER->setCameraCondition(CAMERA_STAGE2);
		}
		//호로록
		if (KEYMANAGER->isOnceKeyDown('G'))
		{
			CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
			_currentRC = &_rc1;
			CAMERAMANAGER->setCameraAim(_currentRC);
			
		}

		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
		}

		//if (KEYMANAGER->isOnceKeyDown('P'))
		//{
		//	SCENEMANAGER->changeScene("스테이지00"); 
		//}
		RECT temp;
		//보트 무브
		if (IntersectRect(&temp, &_rc1, &_boatRC))
		{
			_boatSwitchOn = true;
		}

		if (_boatSwitchOn && _boatRC.right < 5230)
		{
			boatMove();
		}
		else if (_boatSwitchOn && _boatRC.right >= 5200)
		{
			_boatSwitchOn = false;
		}


		//엘베무브 
		if (IntersectRect(&temp, &_rc1, &_elevatorRC))
		{
			_elevatorSwitchOn = true;
		}

		if (_elevatorSwitchOn && _elevatorRC.top > 140)
		{
			elevatorMove();
		}

		//강 프레임 도는 시간
		_liverAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);

		
		_em->update();

		for (int i = 0; i < _vItem.size(); i++)
		{
			_vItem[i]->update();
		}

		makeEnemy();

	}
	_rc1 = RectMakeCenter(_mainPlayer->getX() /*- 30*/, _mainPlayer->getY()+25/* - 30*/, 100, 100);
	_rc2 = RectMakeCenter(_mainPlayer->getX(), 2280, 100, 100);
	_rc3 = RectMakeCenter(_mainPlayer->getX(), _mainPlayer->getY() + 25, 100, 100);
	if (!_boatSwitchOn)
	{
		_mainPlayer->update();
	}
}

void stage2::render()
{
	draw();
}
void stage2::dropMoney(POINT point, int won)				//돈 드랍 함수 몬스터가 죽었을경우 이것 호출하면 됩니다.
{
	item* tempMoney = new money;
	tempMoney->init(point, won);

	_vItem.push_back(tempMoney);
}

void stage2::makeEnemy()									//몬스터 생성 함수
{
	
	/*카메라 특정 지점일때 몬스터 생성
	첫 웨이브가 나왔냐 && 카메라가 특정 지점에 왔냐*/
	if (!_firstWave)
	{
		_firstWave = true;
		//쫄따구 2마리 생성
		_em->setMinion(PointMake(700, 2350), 2);
		_em->setMinion1(PointMake(550, 2350), 2);

		//카메라 고정 추가(기성아 부탁한다) 추가
		//CAMERAMANAGER->setCameraCondition(CAMERA_FREE);

	}

	//첫 웨이브는 나왔는데 에너미 매니져의 크기가 0이다 --> 몹 다죽임
	else if (_firstWave && _em->getVMinion().size() == 0)
	{

		//카메라 다시 이동(기성아 부탁한다) 추가
		CAMERAMANAGER->backGroundSizeSetting(5795, 2593);
		_currentRC = &_rc2;
		CAMERAMANAGER->setCameraAim(_currentRC);
		CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);



	}

	//두번째 웨이브가 나왔냐 && 카메라가 특정 지점이냐
	if (!_secondWave && _firstWave&&_em->getVMinion().size() == 0 && _currentRC->right >= 5200)
	{
		//쫄따구1 정예몹 1마리 생성
		_secondWave = true;
		_em->setMinion2(PointMake(5700, 2350), 2);
		_em->setPick(PointMake(5700, 2350), 2);
		CAMERAMANAGER->setCameraCondition(CAMERA_FREE);




	}

	//두번째 웨이브는 나왔는데 에너미 매니져의 크기가 0이다 --> 몹 다죽임
	else if (_secondWave && _em->getVMinion().size() == 0)
	{

		//카메라 다시 이동(기성아 부탁한다) 추가
		CAMERAMANAGER->backGroundSizeSetting(5795, 2593);

		_currentRC = &_rc1;
		CAMERAMANAGER->setCameraAim(_currentRC);
		CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);

	}

	//if (!_thirdWave && _secondWave&&_em->getVMinion().size() == 0&& _currentRC->top<= 140)
	//{
	////쫄따구1 정예몹 1마리 생성
	////	_em->setBoss(PointMake(4864, 70), 2);


	//_currentRC = &_rc2;
	//CAMERAMANAGER->setCameraAim(_currentRC);
	//CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	//}

	//세번째 웨이브는 나왔는데 에너미 매니져의 크기가 0이다 --> 몹 다죽임
	//else if(_thirdWave && _em.size() == 0)
	//{

	////카메라 다시 이동(기성아 부탁한다) 추가
	//currentRC = &rc1;
	//CAMERAMANAGER->setCameraAim(currentRC);
	//CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	//}

	
}

void stage2::characterMovement()							//캐릭터 키매지저를 관리하는 함수
{

}

void stage2::addImage()									//이미기 추가해주는 함수 이후 이미지는 여기서 add하는걸로
{
	_liver = IMAGEMANAGER->addFrameImage("강물", "./images/liver_2frame.bmp", 11590, 126, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("스테이지_01", "./images/02_stage00.bmp", 5795, 2593, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스테이지_01_red", "./images/02_stage00_red.bmp", 5795, 2593, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("검은화면", "./images/backWindow.bmp", 1152, 648, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쪽배_red", "./images/boat_red.bmp", 527, 75, true, RGB(255, 0, 255));

	_boat = IMAGEMANAGER->addImage("쪽배", "./images/boat.bmp", 527, 75, true, RGB(255, 0, 255));
	_elevator = IMAGEMANAGER->addImage("엘레베이터", "./images/elevator.bmp", 210, 260, true, RGB(255, 0, 255));



	
}
void stage2::initialization()								//변수들 new선언 및 init 해주는 함수 이후 new 및 init은 여기서 하는걸로
{

	//강 애니메이션
	_liverAni = new animation;
	_liverAni->init(_liver->getWidth(), _liver->getHeight(), _liver->getFrameWidth(), _liver->getFrameHeight());
	_liverAni->setDefPlayFrame(true, true);
	_liverAni->setFPS(1);


	_mainPlayer = new character;
	_mainPlayer->init();

	_inven = new inventory;
	_inven->init();

	_em = new enemyManager;
	_em->init();

	_em->setCharacterMemoryAddressLink(_mainPlayer);
	_em->setStage2MemoryAddressLink(this,2);
}
void stage2::singletonInit()								//init에서 싱글톤들 세팅해주는 함수 이후 세팅은 여기서 하는걸로		  
{
	CAMERAMANAGER->backGroundSizeSetting(1152, 2593);
	CAMERAMANAGER->setCameraCondition(CAMERA_STAGE2);
	CAMERAMANAGER->setCameraAim(&_rc1);

	SOUNDMANAGER->play("스테이지2", 0.5f);
}
void stage2::draw()									//그려주는 함수 이후 렌더는 여기서 하는걸로								
{

	IMAGEMANAGER->findImage("엘레베이터")->render(getMemDC(),
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_elevatorX, _elevatorY, _elevator->getWidth(), _elevator->getHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_elevatorX, _elevatorY, _elevator->getWidth(), _elevator->getHeight())).y);



	IMAGEMANAGER->findImage("스테이지_01")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("스테이지_01_red")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);



	//엘레베이터 rc 작은거 충돌용
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_elevatorRC).x, CAMERAMANAGER->CameraRelativePoint(_elevatorRC).y, 10, 10);
	RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rc1).x, CAMERAMANAGER->CameraRelativePoint(_rc1).y, 100, 100);


	
	
	//쪽배
	_boat->render(getMemDC(),
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).y);
	
	//쪽배 픽셀충돌 컬러
	IMAGEMANAGER->findImage("쪽배_red")->render(getMemDC(),
	CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).x,
	CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).y);

	//쪽배 렉트 충돌용
	//RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_boatRC).x, CAMERAMANAGER->CameraRelativePoint(_boatRC).y, _boat->getWidth(), _boat->getHeight());


	_liver->aniRender(getMemDC(), 
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_liver->getX(), _liver->getY(), _liver->getFrameWidth(), _liver->getFrameHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_liver->getX(), _liver->getY(), _liver->getFrameWidth(), _liver->getFrameHeight())).y, _liverAni); 
	
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render();
	}

	_mainPlayer->render();
	_em->render();

	//RectangleMakeCenter(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_mainPlayer->getRect()).x,
	//	CAMERAMANAGER->CameraRelativePoint(_mainPlayer->getUnderBarRect()).y,100,100 );

	/*Rectangle(getMemDC(), _mainPlayer->getUnderBarRect().left, _mainPlayer->getUnderBarRect().top, 
		_mainPlayer->getUnderBarRect().right, _mainPlayer->getUnderBarRect().bottom);*/
	
	//이 검은화면이 제밀 밑에 있도록 코드쳐주세요~~
	IMAGEMANAGER->findImage("검은화면")->alphaRender(getMemDC(), 0, 0, 255 - _alpha);
}

void stage2::boatMove()
{
	
	_boatX += 5;
	_boatRC.left += 5;
	_boatRC.right += 5;

	_currentRC->left += 5;
	_currentRC->right += 5;
	
	_mainPlayer->MakeRightStop(_mainPlayer);
	_mainPlayer->setX(_mainPlayer->getX() + 5);
	_mainPlayer->setY(_boatRC.top-90);
	_mainPlayer->UpdateRect();
	
	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	_currentRC = &_rc1;
	CAMERAMANAGER->setCameraAim(_currentRC);
	

}

void stage2::elevatorMove() 
{
	_elevatorY -= 5;

	_elevatorRC.top -= 5;
	_elevatorRC.bottom -= 5;

	_currentRC->top -= 5;
	_currentRC->bottom -= 5;

	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	_currentRC = &_rc1;
	CAMERAMANAGER->setCameraAim(_currentRC);
}