#include "stdafx.h"
#include "stage1.h"


stage1::stage1()
{

}


stage1::~stage1()
{
}

HRESULT stage1::init()
{
	IMAGEMANAGER->addImage("��������_00", "./images/01_stage00.bmp", 3456, 648, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����̹ڽ�", "./images/ui_box.bmp", 1152, 144, true, RGB(255, 0, 255));

	return S_OK;
}

void stage1::release()
{
}

void stage1::update()
{
}

void stage1::render()
{
	IMAGEMANAGER->findImage("��������_00")->render(getMemDC(),0,0);

	//��ö�߰� //�����̹ڽ� ī�޶� ���� �ȹ��� ��ġ���� // 20121227 7:45
	IMAGEMANAGER->findImage("�����̹ڽ�")->render(getMemDC(), 0, WINSIZEY - IMAGEMANAGER->findImage("�����̹ڽ�")->getHeight());
}
