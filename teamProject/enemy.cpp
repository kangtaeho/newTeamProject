#include "stdafx.h"
#include "enemy.h"
#include "stage1.h"

enemy::enemy()
{
}


enemy::~enemy()
{
}



HRESULT enemy::init(POINT point, int currentStage  )
{
	_x = point.x;
	_y = point.y;
	_countMove = 0;
	return S_OK;

}

void enemy::release()
{


}

void enemy::update()
{

	//카메라확인겸 움직이는지 확인중
	//_x = (_rcEnemy.left + _rcEnemy.right) / 2;
	//_y = (_rcEnemy.top + _rcEnemy.bottom) / 2;

	//여기 모르겠음
	//if (_x < _backgroundsizex-300) _speed = 3;
	//if (_x > _backgroundsizex+300) _speed = -3;

	//_x -= _speed;
	//_rcEnemy = RectMakeCenter(_x, _y, 100, 100);

	          switch (_enemyDirection)
	          {
	          case ENEMYDIRECTION_RIGHT_STOP:
	          	break;
	          case ENEMYDIRECTION_RIGHT_MOVE:
	          	break;
	          case ENEMYDIRECTION_RIGHT_RUN:
	          	break;
	          case ENEMYDIRECTION_RIGHT_ONE_JAB:
	          	break;
	          case ENEMYDIRECTION_RIGHT_TWO_JAB:
	          	break;
	          case ENEMYDIRECTION_RIGHT_JUMP_ATTACK:
	          	break;
	          case ENEMYDIRECTION_RIGHT_HIT:
	          	break;
	          case ENEMYDIRECTION_RIGHT_HIT2:
	          	break;
	          case ENEMYDIRECTION_RIGHT_CROUCH:
	          	break;
	          case ENEMYDIRECTION_RIGHT_CROUCH_HIT:
	          	break;
	          case ENEMYDIRECTION_RIGHT_CROUCH_THROW:
	          	break;
	          case ENEMYDIRECTION_RIGHT_DOWN:
	          	break;
	          case ENEMYDIRECTION_RIGHT_COMBO_DOWN:
	          	break;
	          case ENEMYDIRECTION_RIGHT_DOWN_STAND:
	          	break;
	          case ENEMYDIRECTION_RIGHT_DOWN_FOREVER:
	          	break;
	          case ENEMYDIRECTION_RIGHT_STONE_UP:
	          	break;
	          case ENEMYDIRECTION_RIGHT_STONE_UP_MOVE:
	          	break;
	          case ENEMYDIRECTION_RIGHT_STONE_THROW:
	          	break;
	          case ENEMYDIRECTION_RIGHT_KNIFE_UP:
	          	break;
	          case ENEMYDIRECTION_RIGHT_KNIFE_THROW:
	          	break;
	          case ENEMYDIRECTION_LEFT_STOP:
	          	break;
	          case ENEMYDIRECTION_LEFT_MOVE:
	          	break;
	          case ENEMYDIRECTION_LEFT_RUN:
	          	break;
	          case ENEMYDIRECTION_LEFT_ONE_JAB:
	          	break;
	          case ENEMYDIRECTION_LEFT_TWO_JAB:
	          	break;
	          case ENEMYDIRECTION_LEFT_JUMP_ATTACK:
	          	break;
	          case ENEMYDIRECTION_LEFT_HIT:
	          	break;
	          case ENEMYDIRECTION_LEFT_HIT2:
	          	break;
	          case ENEMYDIRECTION_LEFT_CROUCH:
	          	break;
	          case ENEMYDIRECTION_LEFT_CROUCH_HIT:
	          	break;
	          case ENEMYDIRECTION_LEFT_CROUCH_THROW:
	          	break;
	          case ENEMYDIRECTION_LEFT_DOWN:
	          	break;
	          case ENEMYDIRECTION_LEFR_COMBO_DOWN:
	          	break;
	          case ENEMYDIRECTION_LEFT_DOWN_STAND:
	          	break;
	          case ENEMYDIRECTION_LEFT_DOWN_FOREVER:
	          	break;
	          case ENEMYDIRECTION_LEFT_STONE_UP:
	          	break;
	          case ENEMYDIRECTION_LEFT_STONE_UP_MOVE:
	          	break;
	          case ENEMYDIRECTION_LEFT_STONE_THROW:
	          	break;
	          case ENEMYDIRECTION_LEFT_KNIFE_UP:
	          	break;
	          case ENEMYDIRECTION_LEFT_KNIFE_THROW:
	          	break;
	          case ENEMYDIRECTION_Clime:
	          	break;

	          default:
	          	break;
	          }



 ////////////////////////////////////보스/////////////////////////////////

			  switch (_bossDirection)
			  {
			  case BOSSDIRECTION_RIGHT_STOP:
				  break;
			  case BOSSDIRECTION_RIGHT_MOVE:
				  break;
			  case BOSSDIRECTION_RIGHT_ONE_JAB:
				  break;
			  case BOSSDIRECTION_RIGHT_TWO_JAB:
				  break;
			  case BOSSDIRECTION_RIGHT_HIT:
				  break;
			  case BOSSDIRECTION_RIGHT_HIT2:
				  break;
			  case BOSSDIRECTION_RIGHT_DOWN:
				  break;
			  case BOSSDIRECTION_RIGHT_COMBO_DOWN:
				  break;
			  case BOSSDIRECTION_RIGHT_DOWN_STAND:
				  break;
			  case BOSSDIRECTION_LEFT_STOP:
				  break;
			  case BOSSDIRECTION_LEFT_MOVE:
				  break;
			  case BOSSDIRECTION_LEFT_ONE_JAB:
				  break;
			  case BOSSDIRECTION_LEFT_TWO_JAB:
				  break;
			  case BOSSDIRECTION_LEFT_HIT:
				  break;
			  case BOSSDIRECTION_LEFT_HIT2:
				  break;
			  case BOSSDIRECTION_LEFT_DOWN:
				  break;
			  case BOSSDIRECTION_LEFT_COMBO_DOWN:
				  break;
			  case BOSSDIRECTION_LEFT_DOWN_STAND:
				  break;
			  case BOSSDIRECTION_DEAD:
				  break;
			  default:
				  break;
			  }

	enemyMove();

	_rcEnemy = RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
	_CollircEnemy = RectMakeCenter(CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x + _imageEnemy->getFrameWidth() / 2,
		CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y + _imageEnemy->getFrameHeight() / 2 -50, 75, 75); //충돌렉트

	_enemyCenterX = CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x + _imageEnemy->getFrameWidth() / 2;
	_enemyCenterY = CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y + _imageEnemy->getFrameHeight() / 2;

	KEYANIMANAGER->update();

}

void enemy::render()
{

	//에네미rc
	//RectangleMake(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x, CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y, 100, 100);
	
	//되는지 실험중

	//IMAGEMANAGER->findImage("enemy01")->frameRender(getMemDC(),
	//	CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight())).x,
	//	CAMERAMANAGER->CameraRelativePoint(RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight())).y, 0, 0);
	

	setColorRect(getMemDC(), _CollircEnemy, 200, 20, 20);

	_imageEnemy->aniRender(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x, 
									   CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y-50, 
									   _enemyMotion);


}


//여기서부터 콜백함수
void enemy::rightAttack(void * obj)
{

}

void enemy::rightJumpAttack(void * obj)
{

}

void enemy::leftAttack(void * obj)
{

}

void enemy::leftJumpAttack(void * obj)
{

}

void enemy::collision()
{

}

void enemy::enemyMove() {
	_countMove++;

	switch (_currentStage) {
		case 1:

			
			switch (_isTracePlayer) {
			case 0: // 패트롤 상태

				if (_countMove < 100) { //랜덤으로 움직인다
					if (_countMove == 1) _enemyMotion->start();
					_x += _rndDirX;
					_y += _rndDirY;;
				}
				else if (_countMove >= 100 && _countMove < 150) {

					if (_countMove == 100) {
						_rndDirX = rndDirection(RND->getInt(3));
						_rndDirY = rndDirection(RND->getInt(3));
						_rndTum = RND->getFromIntTo(50, 120);
						_rndTum2 = RND->getFromIntTo(280, 320);

						if (_rndDirX == 1) {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[0]);
						}
						else {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[1]);
						}
					}

					if (_countMove == 149) {

						if (_rndDirX == 1) {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[4]);
							_enemyMotion->start();
						}
						else {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[5]);
							_enemyMotion->start();
						}
					}
				}
				else if (_countMove >= 150 && _countMove < 150 + _rndTum) {

					_x += _rndDirX;
					_y += _rndDirY;

				}
				else if (_countMove >= 150 + _rndTum && _countMove < _rndTum2) {

					if (_countMove == 250) {
						_rndDirX = rndDirection(RND->getInt(3));
						_rndDirY = rndDirection(RND->getInt(3));

						if (_rndDirX == 1) {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[0]);
						}
						else {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[1]);
						}
					}


					if (_countMove == _rndTum2 - 1) {

						if (_rndDirX == 1) {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[4]);
							_enemyMotion->start();
						}
						else {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[5]);
							_enemyMotion->start();
						}

					}
				}
				else {
					_countMove = 0;
					_rndTum = RND->getFromIntTo(50, 120);
					_rndTum2 = RND->getFromIntTo(280, 320);
				}

				if (_y > 482) {
					_rndDirY = -1;
				}
				else if (_y < 337) {
					_rndDirY = 1;
				}

				break;

			case 1: // 플레이어 발견

				_x += cosf(_traceAngle) * 1.2f;
				_y += -sinf(_traceAngle) * 1.2f;

				if (cosf(_traceAngle) * 1.2f > 0) {
					_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[4]);
					if (_isRight) _enemyMotion->start();		//오른쪽 발견
					_isRight = false;
					_isLeft = true;
				}
				else {
					_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[5]);
					if (_isLeft) _enemyMotion->start();
					_isRight = true;
					_isLeft = false;
				}

				break;

			case 2: // 플레이어 공격

				_countAttack++;

				if (!_isRight&&_isLeft) {
					_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[6]);
				}
				else {
					_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[7]);
				}

				if (!_attackAniStart) _enemyMotion->start();
				_attackAniStart = true;

				if (_countAttack % 20 == 0) {
					_attackAniStart = false;
					_isAttack = false;
					_countAttack = 0;
				}

				break;

			case 3: // 몹 죽음

				if (_HP == 0)
				{
					if (!_isRight&&_isLeft) {
						_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[10]);
					}
					else {
						_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[11]);
					}

					if (!_dieAniStart) _enemyMotion->start();
					_dieAniStart = true;
				}

				break;

			case 4:	 //접근하고 나서 플레이어와 각도 설정

			
				if (_isRight) {
					if (_traceAngle > getDegree(180)) {
						_y += 1.0f;
					}
					else {
						_y -= 1.0f;
					}
				
				}
				else {
					if (_traceAngle > getDegree(0)) {
						_y += 1.0f;
					}
					else if(_traceAngle < getDegree(360)){
						_y -= 1.0f;
					}
					else {
						_y -= 1.0f;
					}
				}	

				break;
			}

		case 2:

			switch (_isTracePlayer) {
			case 0: // 패트롤 상태

				if (_countMove < 100) { //랜덤으로 움직인다
					if (_countMove == 1) _enemyMotion->start();
					if (_rndDirX == 0) _rndDirX = -1;
					_x += _rndDirX;
				}
				else if (_countMove >= 100 && _countMove<150) {

					if (_countMove == 100) {
						_rndDirX = rndDirection(RND->getInt(3));
						_rndDirY = rndDirection(RND->getInt(3));
						_rndTum = RND->getFromIntTo(50, 120);
						_rndTum2 = RND->getFromIntTo(280, 320);

						if (_rndDirX == 1) {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[0]);
						}
						else {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[1]);
						}
					}

					if (_countMove == 149) {

						if (_rndDirX == 1) {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[4]);
							_enemyMotion->start();
						}
						else {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[5]);
							_enemyMotion->start();
						}
					}
				}
				else if (_countMove >= 150 && _countMove<150 + _rndTum) {
					if (_rndDirX == 0) _rndDirX = 1;
					_x += _rndDirX;

				}
				else if (_countMove >= 150 + _rndTum && _countMove<_rndTum2) {

					if (_countMove == 150 + _rndTum) {
						_rndDirX = rndDirection(RND->getInt(3));
						_rndDirY = rndDirection(RND->getInt(3));

						if (_rndDirX == 1) {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[0]);
						}
						else {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[1]);
						}
					}


					if (_countMove == _rndTum2 - 1) {

						if (_rndDirX == 1) {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[4]);
							_enemyMotion->start();
						}
						else {
							_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[5]);
							_enemyMotion->start();
						}

					}
				}
				else {
					_countMove = 0;
					_rndTum = RND->getFromIntTo(50, 120);
					_rndTum2 = RND->getFromIntTo(280, 320);
				}

				break;

			case 1: // 플레이어 발견

				_x += cosf(_traceAngle) * 1.2f;

				if (cosf(_traceAngle) * 1.2f > 0) {
					_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[4]);
					if (_isRight) _enemyMotion->start();
					_isRight = false;
					_isLeft = true;
				}
				else {
					_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[5]);
					if (_isLeft) _enemyMotion->start();
					_isRight = true;
					_isLeft = false;
				}

				break;

			case 2: // 플레이어 공격

				_countAttack++;

				if (!_isRight&&_isLeft) {
					_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[6]);
				}
				else {
					_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[7]);
				}

				if (!_attackAniStart) _enemyMotion->start();
				_attackAniStart = true;

				if (_countAttack % 20 == 0) {
					_attackAniStart = false;
					_isAttack = false;
					_countAttack = 0;
				}

				break;
			}
	
		break;

	}
}

int enemy::rndDirection(int value) {
	switch (value) {
	case 0:
		return -1;
		break;

	case 1:
		return 0;
		break;

	case 2:
		return 1;
		break;
	}
}

