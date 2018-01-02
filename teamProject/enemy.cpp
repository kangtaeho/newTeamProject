#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}



HRESULT enemy::init(/*const char* imageName,*/POINT point)
{





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


	//_rcEnemy = RectMakeCenter(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());

	_enemyMotion->start();
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

	_imageEnemy->aniRender(getMemDC(), _rcEnemy.left, _rcEnemy.top, _enemyMotion);
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



//ENEMY01  이미지