#pragma once
#include "singletonBase.h"
#include <map>




//카메라 상태값
#define CAMERA_FREE 0 //카메라가 자유롭게 이동할 수 있음
#define CAMERA_AIMING 1 //카메라가 aim 으로 설정된 rc를 따라감
#define CAMERA_EFFECT 2 //카메라 흔들림, 효과 처리
#define CAMERA_MOVING 3 //카메라 이동처리
#define CAMERA_STAGE2 4 //2스테이지 카메라 이동 제어 
//이펙트

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



	// 해당하는 rc로 카메라를 설정합니다.
	void setCameraAim(RECT* rc);

	// object가 카메라 화면 안쪽에 있는지 알아냅니다.
	bool isInCamera(RECT rc);

	void cameraMove(bool isX, float speed);

	void cameraFollow();

	void stage2CameraFollow(bool isX, float speed);


	// CAMERA_FREE, CAMERA_AIMING, CAMERA_EFFEICTING, CAMERA_MOVING로 카메라 상태를 설정합니다.
	void setCameraCondition(int cameraCondition) { _cameraCondition = cameraCondition; }

	//카메라에 화면상 좌표를 반환합니다.
	POINT CameraRelativePoint(RECT rc) { return { rc.left - _camera.x, rc.top - _camera.y }; }


	//카메라가 위치를 벗어나면 보정한다.
	void cameraRevision();

	// 카메라 이펙트 설정 EFFECT_SIN,..., 강도, 시간(초)
	void setEffect(int effectIndex, float strong, float time);

	//카메라 이펙팅
	void cameraEffecting();

	void backGroundSizeSetting(int x, int y);
	int getBackGroundSizeX(){ return _backgroundsizex; }

	int getCameraCondition() { return _cameraCondition; }

	POINT getCameraPoint() { return _camera; }
};

