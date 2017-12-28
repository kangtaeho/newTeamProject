#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{

}

//HRESULT == MS����� 
//S_OK
//E_FAIL
//SUCCEDED
HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;



	

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if ( _managerInit )
	{
		//Ÿ�̸� ���� == 0.01
		//SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		SOUNDMANAGER->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		KEYANIMANAGER->init();
		TXTDATA->init();
		INIDATA->init();
		ZORDERMANAGER->init();
		CAMERAMANAGER->init();
		
	}


	return S_OK;
}

void gameNode::release()
{
	if ( _managerInit )
	{
		//KillTimer(_hWnd, 1);
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->releaseSingleton();
		SOUNDMANAGER->releaseSingleton();
		EFFECTMANAGER->releaseSingleton();
		SCENEMANAGER->releaseSingleton();
		KEYANIMANAGER->releaseSingleton();
		TXTDATA->releaseSingleton();
		INIDATA->releaseSingleton();
		ZORDERMANAGER->releaseSingleton();
		CAMERAMANAGER->releaseSingleton();
		
	}

	ReleaseDC(_hWnd, _hdc);
	
}
		
void gameNode::update()	
{
	CAMERAMANAGER->update();
}
	
void gameNode::render()
{

}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
		
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>LOWORD(lParam);
			_ptMouse.y = static_cast<float>HIWORD(lParam);
		break;
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					PostMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
