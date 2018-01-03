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
	virtual HRESULT init();		//�ʱ�ȭ �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();		//�޸� ���� �Լ�
	virtual void update();		//���� �Լ�
	virtual void render();		//�׷��ִ� �Լ�(a.k.a WM_PAINT)

	virtual void setMainPlayer(character* mainPlayer) {}
	virtual character* getMainPlayer(){ return _mainPlayer; }

	virtual void setInventory(inventory* inven){}
	virtual inventory* getInventory(){ return _inven; }

	//����� ������
	image* getBackBuffer() { return _backBuffer; }
	
	//�޸�DC ������
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

