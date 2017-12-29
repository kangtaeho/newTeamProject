#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
{
}


selectScene::~selectScene()
{

}

HRESULT selectScene::init()
{
	_btnSceneChange = new button;
	_btnSceneChange->init("¹öÆ°", WINSIZEX / 2, WINSIZEY / 2,
		PointMake(0, 1), PointMake(0, 0), cbSceneChange);

	_btnAngleDown = new button;
	_btnAngleDown->init("¹öÆ°", WINSIZEX / 2 - 200, WINSIZEY / 2 + 200,
		PointMake(0, 1), PointMake(0, 0), cbangleDown);

	_btnAngleUp = new button;
	_btnAngleUp->init("¹öÆ°", WINSIZEX / 2 + 200, WINSIZEY / 2 + 200,
		PointMake(0, 1), PointMake(0, 0), cbAngleUp);

	//==================================================================
	_action = new action;
	_action->init();

	_actionImage = IMAGEMANAGER->findImage("bullet");
	_actionImage->setX(WINSIZEX / 2);
	_actionImage->setY(WINSIZEY / 2);


	_action->moveTo(_actionImage, 50, 50, 10.0f);

	return S_OK;
}

void selectScene::release()
{

}

void selectScene::update() 
{
	

	_btnSceneChange->update();
	_btnAngleDown->update();
	_btnAngleUp->update();
	_action->update();
}

void selectScene::render() 
{
	_btnSceneChange->render();
	_btnAngleDown->render();
	_btnAngleUp->render();

	char str[128];

	sprintf(str, "¿©±ä ¼¿·ºÆ®¾À");
	TextOut(getMemDC(), WINSIZEX / 2, 100, str, strlen(str));

	_actionImage->render(getMemDC(), _actionImage->getX(), _actionImage->getY());

}

void selectScene::cbSceneChange()
{
	
	SCENEMANAGER->changeScene("½ºÅ¸¾À");
}

void selectScene::cbAngleUp()
{
	DATABASE->setElementDataAngle("battle", DATABASE->getElementData("battle")->angle += 0.2f);
}

void selectScene::cbangleDown()
{
	DATABASE->setElementDataAngle("battle", DATABASE->getElementData("battle")->angle -= 0.2f);
}