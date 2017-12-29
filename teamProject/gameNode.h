#pragma once
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);
///����� �߰�
static image* _backBuffer2 = IMAGEMANAGER->addImage("backBuffer2", WINSIZEX, WINSIZEY);

class character;

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

protected:
	character* _mainPlayer;

public:
	virtual HRESULT init();		//�ʱ�ȭ �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();		//�޸� ���� �Լ�
	virtual void update();		//���� �Լ�
	virtual void render();		//�׷��ִ� �Լ�(a.k.a WM_PAINT)

	virtual void setMainPlayer(character* mainPlayer) {}
	virtual character* getMainPlayer(){ return _mainPlayer; }

	//����� ������
	image* getBackBuffer() { return _backBuffer; }
	///����� 2������
	image* getBackBuffer2() { return _backBuffer2; }
	
	//�޸�DC ������
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

