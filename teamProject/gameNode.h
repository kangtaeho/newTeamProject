#pragma once
#include "image.h"


static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class character;
class inventory;

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;


protected:
	character* _mainPlayer;
	inventory* _inven;

	POINT		_playerStartPoint;

public:
	virtual HRESULT init();		//초기화 함수
	virtual HRESULT init(bool managerInit);
	virtual void release();		//메모리 해제 함수
	virtual void update();		//연산 함수
	virtual void render();		//그려주는 함수(a.k.a WM_PAINT)

	virtual void setMainPlayer(character* mainPlayer) {}
	virtual character* getMainPlayer(){ return _mainPlayer; }

	virtual void setInventory(inventory* inven){}
	virtual inventory* getInventory(){ return _inven; }

	//백버퍼 접근자
	image* getBackBuffer() { return _backBuffer; }
	
	//메모리DC 접근자
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

