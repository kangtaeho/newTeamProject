#include "stdafx.h"
#include "stage2.h"


stage2::stage2() //절대값같은 수치는 여기서 초기화, 이미지의 크기처럼 무언가를 받아서 초기화 해야한다면 init에서
: _alpha(0),
_ss(READY),
_rc1(RectMakeCenter(560, 2286, 100, 100)), //카메라의 렉트 좌표
_playerStartPoint(PointMake(760, 2310)), //스테이지 2 플레이어 시작좌표
_currentRC(&_rc1),
_firstWave(false),
_secondWave(false),
_thirdWave(false)
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

	_boatX = 1450;
	_boatY = 2400;

	//_boat->setX(1450);
	//_boat->setY(2400);
	_boatRC = RectMakeCenter(_boatX, _boatY, 527, 75);
	
	//_elevator->setX(5520);
	//_elevator->setY(2186);

	_elevatorX = 5520;
	_elevatorY = 2186;

	_elevatorRC = RectMakeCenter(_elevatorX, _elevatorY, 10, 10);

	_elevatorSwitchOn = false;

	_liver->setX(0);
	_liver->setY(2450);

	_frameX = _frameCount = 0;
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
					_currentRC->bottom -= 5;
					_currentRC->top -= 5;
				}
				else
				{
					_currentRC->bottom -= 5;
					_currentRC->top -= 5;
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
					_currentRC->bottom += 5;
					_currentRC->top += 5;
				}
				else {
					_currentRC->bottom += 5;
					_currentRC->top += 5;
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
					_currentRC->left -= 5;
					_currentRC->right -= 5;
				}
				else if (CAMERAMANAGER->getCameraCondition() == CAMERA_STAGE2)
				{
					CAMERAMANAGER->stage2CameraFollow(true, -5);
					_currentRC->left -= 5;
					_currentRC->right -= 5;
				}
				else
				{
					if (_currentRC->left <= 0)
					{
						_currentRC->left += 5;
						_currentRC->right += 5;
					}
					_currentRC->left -= 5;
					_currentRC->right -= 5;
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
					_currentRC->left += 5;
					_currentRC->right += 5;
				}
				else if (CAMERAMANAGER->getCameraCondition() == CAMERA_STAGE2)
				{
					CAMERAMANAGER->stage2CameraFollow(true, 5);
					_currentRC->left += 5;
					_currentRC->right += 5;
				}
				else
				{
					if (_currentRC->right >= 5795)
					{
						_currentRC->left -= 5;
						_currentRC->right -= 5;
					}
					_currentRC->left += 5;
					_currentRC->right += 5;
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

		if (KEYMANAGER->isOnceKeyDown('P'))
		{
			SCENEMANAGER->changeScene("스테이지00"); 
		}
	}
	

	//엘베무브 보트 무브
	RECT temp;
	if (IntersectRect(&temp, &_rc1, &_elevatorRC)) 
	{
		_elevatorSwitchOn = true;
	}

	if (_elevatorSwitchOn && _elevatorRC.top > 140)
	{
		elevatorMove();
		_elevatorRC.top -= 5;
		_elevatorRC.bottom -= 5;

		_currentRC->top -= 5;
		_currentRC->bottom -= 5;

		CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
		_currentRC = &_rc1;
		CAMERAMANAGER->setCameraAim(_currentRC);
	}
	
	//boatMove(); 
	_frameCount++;
	if (_frameCount % 10 == 0)
	{
		_frameX++;
		if (_frameX > _liver->getMaxFrameX()) _frameX = 0;
	}
	
	_mainPlayer->update();
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
	/*
	카메라 특정 지점일때 몬스터 생성
	첫 웨이브가 나왔냐 && 카메라가 특정 지점에 왔냐
	if (!_firstWave && 카메라가 특정지점이냐)
	{

	쫄따구 2마리 생성
	_em -> setMinion()
	_em -> setMinion2()

	카메라 고정 추가(기성아 부탁한다) 추가
	CAMERAMANAGER->setCameraCondition(CAMERA_FREE);

	}

	첫 웨이브는 나왔는데 에너미 매니져의 크기가 0이다 --> 몹 다죽임
	else if(_firstWave && _em.size() == 0)
	{

	카메라 다시 이동(기성아 부탁한다) 추가
	currentRC = &rc1;
	CAMERAMANAGER->setCameraAim(currentRC);
	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	}

	두번째 웨이브가 나왔냐 && 카메라가 특정 지점이냐
	if(!_secondWave && 카메라가 특정지점이냐)
	{
	쫄따구1 정예몹 1마리 생성
	_em -> setMinion2()
	_em -> setPick()
	

	카메라 고정 추가(이것도 부탁해) 추가
	CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	}

	//두번째 웨이브는 나왔는데 에너미 매니져의 크기가 0이다 --> 몹 다죽임
	else if(_secondWave && _em.size() == 0)
	{

	카메라 다시 이동(기성아 부탁한다) 추가
	currentRC = &rc1;
	CAMERAMANAGER->setCameraAim(currentRC);
	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	}

	if(!_thirdWave && 카메라가 특정지점이냐)
	{
	쫄따구1 정예몹 1마리 생성
	_em -> setMinion2()
	_em -> setPick()


	카메라 고정 추가(이것도 부탁해) 추가
	CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
	}

	//세번째 웨이브는 나왔는데 에너미 매니져의 크기가 0이다 --> 몹 다죽임
	else if(_thirdWave && _em.size() == 0)
	{

	카메라 다시 이동(기성아 부탁한다) 추가
	currentRC = &rc1;
	CAMERAMANAGER->setCameraAim(currentRC);
	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	}

	*/
}

void stage2::characterMovement()							//캐릭터 키매지저를 관리하는 함수
{

}

void stage2::addImage()									//이미기 추가해주는 함수 이후 이미지는 여기서 add하는걸로
{
	_liver = IMAGEMANAGER->addFrameImage("강물", "./images/liver_2frame.bmp", 11590, 128, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("스테이지_01", "./images/02_stage00.bmp", 5795, 2593, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스테이지_01_red", "./images/02_stage00_red.bmp", 5795, 2593, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("검은화면", "./images/backWindow.bmp", 1152, 648, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쪽배_red", "./images/boat_red.bmp", 527, 75, true, RGB(255, 0, 255));

	_boat = IMAGEMANAGER->addImage("쪽배", "./images/boat.bmp", 527, 75, true, RGB(255, 0, 255));
	_elevator = IMAGEMANAGER->addImage("엘레베이터", "./images/elevator.bmp", 210, 260, true, RGB(255, 0, 255));



	
}
void stage2::initialization()								//변수들 new선언 및 init 해주는 함수 이후 new 및 init은 여기서 하는걸로
{
	_mainPlayer = new character;
	_mainPlayer->init();

	_inven = new inventory;
	_inven->init();
}
void stage2::singletonInit()								//init에서 싱글톤들 세팅해주는 함수 이후 세팅은 여기서 하는걸로		  
{
	CAMERAMANAGER->backGroundSizeSetting(5795, 2593);
	CAMERAMANAGER->setCameraCondition(CAMERA_FREE);
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


	
	//플레이어가 배에 닿았을때 모든키 제어 불가능하게 해주고
	//배가 플레이어랑 같이 움직여야되는데 //기성씨 8~~ //배아직 안움직임
	IMAGEMANAGER->findImage("쪽배")->render(getMemDC(),
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).y);

	

	IMAGEMANAGER->findImage("쪽배_red")->render(getMemDC(),
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_boatX, _boatY, _boat->getWidth(), _boat->getHeight())).y);

	IMAGEMANAGER->findImage("강물")->frameRender(getMemDC(),
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_liver->getX(), _liver->getY(), _liver->getFrameWidth(), _liver->getFrameHeight())).x,
		CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_liver->getX(), _liver->getY(), _liver->getFrameWidth(), _liver->getFrameHeight())).y, _frameX, 0);

	

	_mainPlayer->render();


	//이 검은화면이 제밀 밑에 있도록 코드쳐주세요~~
	IMAGEMANAGER->findImage("검은화면")->alphaRender(getMemDC(), 0, 0, 255 - _alpha);
}

void stage2::boatMove()
{
	
	_boatX += 5;

}

void stage2::elevatorMove() 
{
	_elevatorY -= 5;
}