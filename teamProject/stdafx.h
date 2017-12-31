#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             

#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "collision.h"
#include "imageManager.h"
#include "timeManager.h"
#include "soundManager.h"
#include "txtData.h"
#include "effectManager.h"
#include "iniDataManager.h"
#include "sceneManager.h"
#include "keyAniManager.h"
#include "zOrderManager.h"
#include "cameraManager.h"


using namespace std;
using namespace HEXA_UTIL;

//=====================================
// ## 디파인 ## 17.09.29 ##
//=====================================

#define WINNAME		(LPTSTR)(TEXT("Hexa API"))
#define WINSTARTX	50
#define WINSTARTY	50
#define WINSIZEX	1152	
#define WINSIZEY	648
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

//기성 추가
//#define BACKGROUNDSIZEX 3456
//#define BACKGROUNDSIZEY 648

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define INIDATA iniDataManager::getSingleton()
#define ZORDERMANAGER zOrderManager::getSingleton()
#define CAMERAMANAGER  cameraManager::getSingleton()

//=============================================================
// ## 17.10.18 ## Macro ##
//=============================================================

#define SAFE_DELETE(p) {if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL;}}


//=====================================
// ## extern ## 17.10.12 ##
//=====================================

extern HINSTANCE _hInstance;	
extern HWND	_hWnd;			
extern POINT _ptMouse;

static enum stageState
{
	READY,		//알파값을 위한 준비모드(재호 추가)
	MOVING,
	FIGHTING,
	CLEAR
};