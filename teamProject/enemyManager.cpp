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
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_vEnemy.clear();
	}

	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		
		(*_viEnemy)->update();
	}

	

	//_mini->update();

	traceCharacter();

	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		_vEnemy[0]->setHP(_vEnemy[0]->getHP() - 1);
	}

}
void enemyManager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}

	//showFloatData(getMemDC(), "x 좌표 : %0.2f", _mini->getX(), 800, 20);
	//
	//showIntData(getMemDC(), "카운트 증가하고는 있냐? : %d", _mini->getCountMove(), 800, 40);
	
	///_mini->render();
}

//쫄따구
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
//정예
void enemyManager::setPick(POINT point, int stageCout)
{
	enemy* temp;
	temp = new minion02;
	temp->init(point, stageCout);

	_vEnemy.push_back(temp);
}

//보스
void enemyManager::setBoss(POINT point,int stageCout)
{
	enemy* temp;
	temp = new boss00;
	temp->init(point);

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

void enemyManager::traceCharacter() {

	for (int i = 0; i < _vEnemy.size(); ++i) {
		if (_vEnemy.size() == 0) return;

		if (_vEnemy[i]->getHP()<0) _vEnemy[i]->setIsTracePlayer(3);

		if (getDistance(_vEnemy[i]->getCenterX(), _vEnemy[i]->getCenterY(), _mainPlayer->getCenterX(), _mainPlayer->getCenterY()) < 300) {
			
			if (_vEnemy[i]->getIsAttack()) return;			//적이 공격상태이면 추적 금지

			if (getDistance(_vEnemy[i]->getCenterX(), _vEnemy[i]->getCenterY(), _mainPlayer->getCenterX(), _mainPlayer->getCenterY()) < 75) {
			
				_vEnemy[i]->setIsAttack(true);			//공격해라
				_vEnemy[i]->setIsTracePlayer(2);		//다시 한번 이야기 하지만 0번이 패트롤 상태 1번이 추격, 2번이 공격

			}
			
			else {

				_vEnemy[i]->setIsTracePlayer(1);
				_vEnemy[i]->setTraceAngle(getAngle(_vEnemy[i]->getCenterX(), _vEnemy[i]->getCenterY(), _mainPlayer->getCenterX(), _mainPlayer->getCenterY()));

			}

		}
		else {
			_vEnemy[i]->setIsTracePlayer(0);
		}

		
	}

}