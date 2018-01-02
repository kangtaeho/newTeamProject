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

	POINT value;
	value.x = 2400;
	value.y = 400;
	_mini = new minion01;
	_mini->init(value);

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


	_mini->update();



}
void enemyManager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}

	showFloatData(getMemDC(), "x ��ǥ : %0.2f", _mini->getX(), 800, 20);
	
	showIntData(getMemDC(), "ī��Ʈ �����ϰ�� �ֳ�? : %d", _mini->getCountMove(), 800, 40);
	
	_mini->render();
}

//�̵���
void enemyManager::setMinion(void)
{


}
//����
void enemyManager::setPick(void)
{

}

//����
void enemyManager::setBoss(void)
{
	enemy* temp;
	temp = new boss00;

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