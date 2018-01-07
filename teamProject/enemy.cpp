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

	//setColorRect(getMemDC(), _CollircEnemy, 200, 20, 20);

	_imageEnemy->aniAlphaRender(getMemDC(), CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x, 
									   CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y-50, 
									   _enemyMotion,_alphaValue);
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

				if (!_isRight&&_isLeft) {
					if (_rndAttackStyle == 0) {
						_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[6]);
					}
					else {
						_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[14]);
					}
				}
				else {
					if (_rndAttackStyle == 0) {
						_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[7]);
					}
					else {
						_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[15]);
					}
				}

				if (!_attackAniStart) _enemyMotion->start();
				_attackAniStart = true;

				_countAttack++;
				if (_countAttack % 25 == 0) {
					_attackAniStart = false;
					_isAttack = false;
					_countAttack = 0;
					_rndAttackStyle = RND->getInt(2);
				}

				break;

			case 3: // 몹 죽음
				if (_alphaValue <= 0) {
					_deleteEnemy = true;
					break;
				} 
				
					if (!_isRight&&_isLeft) {
						_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[10]);
					}
					else {
						_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[11]);
					}

					if (!_dieAniStart) _enemyMotion->start();
					_dieAniStart = true;
					_alphaValue-=5;

				break;

			case 4:	 //접근하고 나서 플레이어와 각도 설정

				if (_isRight) {
					if (_traceAngle > getDegree(180)) {
						_y += 1.0f;
						if (_y >= 480) _y = 480;
					}
					else {
						_y -= 1.0f;
						if (_y <= 337) _y = 337;
					}

				}
				else {
					if (_traceAngle > getDegree(0)) {
						_y += 1.0f;
						if (_y >= 480) _y = 480;
					}
					else if (_traceAngle < getDegree(360)) {
						_y -= 1.0f;
						if (_y <= 337) _y = 337;
					}
					else {
						_y -= 1.0f;
						if (_y <= 337) _y = 337;
					}
				}

				break;

			case 5:
				_countHitted++;

				if (_traceAngle > getDegree(90) && _traceAngle < getDegree(270)) {
					_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[13]);
				}
				else {
					_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[12]);
				}
				
				if (!_hittedAniStart) _enemyMotion->start();
				_hittedAniStart = true;
				
				if (_countHitted % 50 == 0) {
					_hittedAniStart = false;
					_isHitted = false;
					_countHitted = 0;
					_isTracePlayer = 2;
				}
				
				break;

			}

			break;

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

			case 3: // 몹 죽음
				if (_alphaValue <= 0) {
					_deleteEnemy = true;
					break;
				}

				if (!_isRight&&_isLeft) {
					_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[10]);
				}
				else {
					_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[11]);
				}

				if (!_dieAniStart) _enemyMotion->start();
				_dieAniStart = true;
				_alphaValue -= 5;

				break;

			case 4:

				if (!_isRight&&_isLeft) {
					_traceAngle = getDegree(0);
				}
				else {
					_traceAngle = getDegree(1);
				}

				break;

			case 5:
				_countHitted++;

				if (_traceAngle > getDegree(90) && _traceAngle < getDegree(270)) {
					_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[13]);
				}
				else {
					_enemyMotion = KEYANIMANAGER->findAnimation(_enemyKeyName[12]);
				}

				if (!_hittedAniStart) _enemyMotion->start();
				_hittedAniStart = true;

				if (_countHitted % 50 == 0) {
					_hittedAniStart = false;
					_isHitted = false;
					_countHitted = 0;
					_isTracePlayer = 2;
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

