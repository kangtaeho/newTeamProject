#pragma once
#include "singletonBase.h"
#include <map>




//ī�޶� ���°�
#define CAMERA_FREE 0 //ī�޶� �����Ӱ� �̵��� �� ����
#define CAMERA_AIMING 1 //ī�޶� aim ���� ������ rc�� ����
#define CAMERA_EFFECT 2 //ī�޶� ��鸲, ȿ�� ó��
#define CAMERA_MOVING 3 //ī�޶� �̵�ó��
#define CAMERA_STAGE2 4 //2�������� ī�޶� �̵� ���� 
//����Ʈ

//#define EFFECT_POWF 0
#define EFFECT_SIN 1
//#define EFFECT_SINPOWF 2
//#define EFFECT_SINPOWF2 3



class cameraManager : public singletonBase<cameraManager>
{
private:


	RECT * _aim;

	POINT _camera;

	int _cameraCondition;
	int _prevCameraCondition;

	int _effectIndex;
	float originX, originY;
	float _strong;
	float _effectT, _maxEffectT;

	int _backgroundsizex;
	int _backgroundsizey;

public:
	cameraManager();
	~cameraManager();

	HRESULT init(void);
	void release(void);
	void update(void);



	// �ش��ϴ� rc�� ī�޶� �����մϴ�.
	void setCameraAim(RECT* rc);

	// object�� ī�޶� ȭ�� ���ʿ� �ִ��� �˾Ƴ��ϴ�.
	bool isInCamera(RECT rc);

	void cameraMove(bool isX, float speed);

	void cameraFollow();

	void stage2CameraFollow(bool isX, float speed);


	// CAMERA_FREE, CAMERA_AIMING, CAMERA_EFFEICTING, CAMERA_MOVING�� ī�޶� ���¸� �����մϴ�.
	void setCameraCondition(int cameraCondition) { _cameraCondition = cameraCondition; }

	//ī�޶� ȭ��� ��ǥ�� ��ȯ�մϴ�.
	POINT CameraRelativePoint(RECT rc) { return { rc.left - _camera.x, rc.top - _camera.y }; }


	//ī�޶� ��ġ�� ����� �����Ѵ�.
	void cameraRevision();

	// ī�޶� ����Ʈ ���� EFFECT_SIN,..., ����, �ð�(��)
	void setEffect(int effectIndex, float strong, float time);

	//ī�޶� ������
	void cameraEffecting();

	void backGroundSizeSetting(int x, int y);
	int getBackGroundSizeX(){ return _backgroundsizex; }

	int getCameraCondition() { return _cameraCondition; }

	POINT getCameraPoint() { return _camera; }
};

