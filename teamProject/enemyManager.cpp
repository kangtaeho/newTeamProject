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

	showFloatData(getMemDC(), "x 좌표 : %0.2f", _mini->getX(), 800, 20);
	
	showIntData(getMemDC(), "카운트 증가하고는 있냐? : %d", _mini->getCountMove(), 800, 40);
	
	_mini->render();
}

//쫄따구
void enemyManager::setMinion(void)
{


}
//정예
void enemyManager::setPick(void)
{

}

//보스
void enemyManager::setBoss(void)
{
	enemy* temp;
	temp = new boss00;

	_vEnemy.push_back(temp);
}

//적 사망시 제거
void enemyManager::removeEnemy(int arrNum)
{
	SAFE_DELETE(_vEnemy[arrNum]);
	_vEnemy.erase(_vEnemy.begin() + arrNum);
}

//돈 습득시 제거
void enemyManager::removeItem(int arrNum)
{

}
//fight!!
void enemyManager::collision(void)
{

}