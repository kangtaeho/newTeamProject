#include "stdafx.h"
#include "cameraManager.h"


cameraManager::cameraManager()
{
}


cameraManager::~cameraManager()
{

}


//ī�޶� �ʱ� ����
HRESULT cameraManager::init()
{
	backGroundSizeSetting(_backgroundsizex, _backgroundsizey);

	_cameraCondition = CAMERA_FREE;
	_aim = NULL;
	return S_OK;
}
void cameraManager::release(void)
{

}

//ī�޶� UPDATE() gameNode�� update()���� ����ȴ�.
void cameraManager::update(void)
{
	switch (_cameraCondition)
	{
	case CAMERA_AIMING:
		cameraFollow();
		break;
	case CAMERA_EFFECT:
		cameraEffecting();
		break;
	}


}

//�Ű������� �޴� RECT�� �߽����� ī�޶� �̵���Ű�� �Լ�
void cameraManager::setCameraAim(RECT * rc)
{
	if (_cameraCondition == CAMERA_AIMING) _aim = rc;

	int centerX, centerY;
	centerX = (rc->left + rc->right) / 2;
	centerY = (rc->top + rc->bottom) / 2;

	_camera.x = centerX - WINSIZEX / 2;
	_camera.y = centerY - WINSIZEY / 2;

	cameraRevision();
}


//�Ű������� ���� RC�� ���� ī�޶���� ���ʿ� �ִ��� �Ǵ��Ͽ� TRUE�� FALSE�� ��ȯ�ϴ� �Լ�
bool cameraManager::isInCamera(RECT rc)
{
	if (rc.right > _camera.x && rc.left<_camera.x - WINSIZEX
		&& rc.bottom > _camera.y && rc.top < _camera.y - WINSIZEY) return true;
	else return false;
}

//ī�޶� ȭ�� ������ ���� �� �������ִ� �Լ�
void cameraManager::cameraRevision()
{
	if (_camera.x < 0)
	{
		_camera.x = 0;
	}
	else if (_camera.x > _backgroundsizex - WINSIZEX)
	{
		_camera.x = _backgroundsizex - WINSIZEX;
	}

	if (_camera.y < 0)
	{
		_camera.y = 0;
	}
	else if (_camera.y > _backgroundsizey - WINSIZEY)
	{
		_camera.y = _backgroundsizey - WINSIZEY;
	}
}

//����Ʈ�� �ְ������ �����Լ� EFFECT ����, ����, �ð�(��)
void cameraManager::setEffect(int effectIndex, float strong, float time)
{
	if (_cameraCondition != CAMERA_EFFECT)
		_prevCameraCondition = _cameraCondition;
	_cameraCondition = CAMERA_EFFECT;
	_effectIndex = effectIndex;
	_maxEffectT = time * 60;
	_strong = strong;
	_effectT = 0;
	originX = _camera.x;
	originY = _camera.y;
}

//����Ʈ �Լ� _cameraCondition �� CAMERA_EFFECT�϶� ����ȴ�.
void cameraManager::cameraEffecting()
{


	switch (_effectIndex)
	{
	case EFFECT_SIN:
		_camera.x = originX + _strong * sinf(_effectT);
		_camera.y = originY + _strong * sinf(_effectT);
		break;
	}
	//cameraRevision();
	_effectT++;

	cameraRevision();

	if (_effectT > _maxEffectT)
	{
		_cameraCondition = _prevCameraCondition;
	}

}

void cameraManager::backGroundSizeSetting(int x, int y)
{

	_backgroundsizex = x;
	_backgroundsizey = y;
	//�ʱ� ī�޶� ��ġ ��� ũ���� �߾����� ����
	//_camera.x = _backgroundsizex / 2 - WINSIZEX / 2;
	//_camera.y = _backgroundsizey / 2 - WINSIZEY / 2;
	
}

void cameraManager::cameraMove(bool isX, float speed)
{
	if (_cameraCondition == CAMERA_FREE)
	{
		if (isX) _camera.x += speed;
		else _camera.y += speed;

		cameraRevision();
	}
}

void cameraManager::cameraFollow()
{
	int centerX, centerY;
	centerX = (_aim->left + _aim->right) / 2;
	centerY = (_aim->top + _aim->bottom) / 2;

	_camera.x = centerX - WINSIZEX / 2;
	_camera.y = centerY - WINSIZEY / 2;

	cameraRevision();
}
