#include "stdafx.h"
#include "enemyManager.h"


enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{

}
HRESULT enemyManager::init()
{

	/*POINT value;
	value.x = 2400;
	value.y = 400;
	_mini = new minion01;
	_mini->init(value);*/

	return S_OK;
}

void enemyManager::release()
{

}

void enemyManager::update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_vEnemy.clear();
	}
	//_mini->update();



}
void enemyManager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}

	//showFloatData(getMemDC(), "x ��ǥ : %0.2f", _mini->getX(), 800, 20);
	//
	//showIntData(getMemDC(), "ī��Ʈ �����ϰ�� �ֳ�? : %d", _mini->getCountMove(), 800, 40);
	
	///_mini->render();
}

//�̵���
void enemyManager::setMinion(POINT point,int stageCout)
{
	enemy* temp;
	temp = new minion00;
	temp->init(point, stageCout);

	_vEnemy.push_back(temp);

}
void enemyManager::setMinion1(POINT point, int stageCout)
{
	enemy* temp;
	temp = new minion01;
	temp->init(point, stageCout);

	_vEnemy.push_back(temp);
}
void enemyManager::setMinion2(POINT point, int stageCout)
{
	enemy* temp;
	temp = new minion02;
	temp->init(point, stageCout);

	_vEnemy.push_back(temp);
}
//����
void enemyManager::setPick(POINT point, int stageCout)
{
	enemy* temp;
	temp = new minion02;
	temp->init(point, stageCout);

	_vEnemy.push_back(temp);
}

//����
void enemyManager::setBoss(POINT point,int stageCout)
{
	enemy* temp;
	temp = new boss00;
	temp->init(point);

	_vEnemy.push_back(temp);
}

//�� ����� ����
void enemyManager::removeEnemy(int arrNum)
{
	SAFE_DELETE(_vEnemy[arrNum]);
	_vEnemy.erase(_vEnemy.begin() + arrNum);
}

//�� ����� ����
void enemyManager::removeItem(int arrNum)
{

}
//fight!!
void enemyManager::collision(void)
{

}