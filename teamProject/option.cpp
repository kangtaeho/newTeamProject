#include "stdafx.h"
#include "option.h"
#include "gameNode.h"


option::option()
	:_isOpenOption(false),
	_onBgm(true),
	_onEffect(true),
	_currentSelectY(0)
{
}


option::~option()
{
}

HRESULT option::init(){

	_blackWindow = IMAGEMANAGER->addImage("���â",WINSIZEX,WINSIZEY);
	_optionBmp = IMAGEMANAGER->addImage("�ɼ�â", "./images/option.bmp", 250, 250, true, RGB(255, 0, 255));
	_bgmBmp = IMAGEMANAGER->addImage("���on", "./images/button01_1.bmp", 100, 40, true, RGB(255, 0, 255));
	_effectBmp = IMAGEMANAGER->addImage("ȿ����on", "./images/button02_1.bmp", 100, 40, true, RGB(255, 0, 255));
	_bgmProgBmp = IMAGEMANAGER->addImage("��ݻ�������", "./images/prograssBar.bmp", 450, 8, true, RGB(255, 0, 255));
	_effectProgBmp = IMAGEMANAGER->addImage("ȿ������������", "./images/prograssBar.bmp", 450, 8, true, RGB(255, 0, 255));
	_bgmProgButtonBmp = IMAGEMANAGER->addImage("���������ư", "./images/button03.bmp", 24, 24, true, RGB(255, 0, 255));
	_effectProgButtonBmp = IMAGEMANAGER->addImage("ȿ��������ư", "./images/button03.bmp", 24, 24, true, RGB(255, 0, 255));
	_optionSelectBmp = IMAGEMANAGER->addImage("�ɼǼ��ù�", "./images/optionSelect.bmp",100, 40, true, RGB(255, 0, 255));
	_closeOptionBmp = IMAGEMANAGER->addImage("������", "./images/button04.bmp", 100, 40, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���off", "./images/button01_0.bmp", 100, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ȿ����off", "./images/button02_0.bmp", 100, 40, true, RGB(255, 0, 255));

	_selectOption[0].x = WINSIZEX / 2 - _optionBmp->getWidth() / 2 + 75;
	_selectOption[0].y = WINSIZEY / 2 - _optionBmp->getHeight() / 2 + 70;
	_selectOption[1].x = WINSIZEX / 2 - _optionBmp->getWidth() / 2 + 75;
	_selectOption[1].y = WINSIZEY / 2 - _optionBmp->getHeight() / 2 + 130;
	_selectOption[2].x = WINSIZEX / 2 - _optionBmp->getWidth() / 2 + 75;
	_selectOption[2].y = WINSIZEY / 2 - _optionBmp->getHeight() / 2 + 190;

	return S_OK;

}

void option::release(){

}

void option::update(){
	if (_isOpenOption) {

		if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
			_currentSelectY--;
			if (_currentSelectY < 0) _currentSelectY = 0;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
			_currentSelectY++;
			if (_currentSelectY > 2) _currentSelectY = 2;
		}

		if (KEYMANAGER->isOnceKeyDown('Z')) {
			switch (_currentSelectY) {
				case 0:
					if (_onBgm) {
						_onBgm = false;
						_bgmBmp = IMAGEMANAGER->findImage("���off");
					}
					else {
						_onBgm = true;
						_bgmBmp = IMAGEMANAGER->findImage("���on");
					}
				break;

				case 1:
					if (_onEffect) {
						_onEffect = false;
						_bgmBmp = IMAGEMANAGER->findImage("ȿ����off");
					}
					else {
						_onEffect = true;
						_bgmBmp = IMAGEMANAGER->findImage("ȿ����o");
					}
				break;

				case 2:
					_isOpenOption = false;
				break;
			}
		}

		bgmSystem();
		effectSystem();
	}
}

void option::render(){

	if (!_isOpenOption) return;

	_blackWindow->alphaRender(_gameNode->getMemDC(), 80);

	_optionBmp->render(_gameNode->getMemDC(), WINSIZEX / 2 - _optionBmp->getWidth() / 2,
								   WINSIZEY / 2 - _optionBmp->getHeight() / 2);

	_bgmBmp->render(_gameNode->getMemDC(), WINSIZEX / 2 - _optionBmp->getWidth() / 2 + 75,
								WINSIZEY / 2 - _optionBmp->getHeight() / 2 + 70);

	_effectBmp->render(_gameNode->getMemDC(), WINSIZEX / 2 - _optionBmp->getWidth() / 2 + 75,
								   WINSIZEY / 2 - _optionBmp->getHeight() / 2 + 130);

	_closeOptionBmp->render(_gameNode->getMemDC(), _selectOption[2].x, _selectOption[2].y);

	_optionSelectBmp->render(_gameNode->getMemDC(), _selectOption[_currentSelectY].x, _selectOption[_currentSelectY].y);

}

void option::bgmSystem() {
	if (!_onBgm) {
		SOUNDMANAGER->pause(SOUNDMANAGER->getCurrentBgmKey());
	}
	else {
		SOUNDMANAGER->resume(SOUNDMANAGER->getCurrentBgmKey());
	}
}

void option::effectSystem() {

}
