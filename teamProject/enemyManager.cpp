#include "stdafx.h"
#include "enemyManager.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{

}
HRESULT enemyManager::init()
{


	return S_OK;
}

void enemyManager::release()
{

}

void enemyManager::update()
{
	
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); /*++_viEnemy*/)
	{
		if (KEYMANAGER->isToggleKey('7'))
		{
			(*_viEnemy)->update();
		}
		ZORDERMANAGER->addZOrder(*_viEnemy, (*_viEnemy)->getCollircEnemy().bottom);
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			removeEnemy(0);
			continue;
			//_vEnemy.clear();
		}
		else ++_viEnemy;
		
		//else ++_viEnemy;
	}

	

	//_mini->update();
	
	deadEnemy();
	traceCharacter();

	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		_vEnemy[0]->setHP(_vEnemy[0]->getHP() - 10);
	}

}
void enemyManager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}

	if (_vEnemy.size() == 0) return;


	setColorRect(getMemDC(), _vEnemy[0]->getCollircEnemy(), 20, 30, 90);

	showIntData(getMemDC(), "첫번째 적 Y좌표 : %d", _vEnemy[0]->getCenterY(), 700, 40);
	showIntData(getMemDC(), "첫번째 적 상태(0번 패트롤, 2번 추적, 4번 공격, 5번 맞음 : %d", _vEnemy[0]->getIsTracePlayer(), 700, 60);
	showFloatData(getMemDC(), "각도 3.14가 180도 : %0.2f ",_vEnemy[0]->getTraceAngle(),700,80);
	///_mini->render();

}

//쫄따구
void enemyManager::setMinion(POINT point, int stageCout)
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
void enemyManager::setBoss(POINT point, int stageCout)
{
	enemy* temp;
	temp = new boss00;
	temp->init(point, stageCout);

	_vEnemy.push_back(temp);
}

//적 사망시 제거
void enemyManager::removeEnemy(int arrNum)
{
	ZORDERMANAGER->allClear();
	if (_stageNum == 1)
	{
		_stage1->dropMoney(PointMake(_vEnemy[arrNum]->getAbsoluteX(), _vEnemy[arrNum]->getAbsoluteY()), 20);
	
	}
	else if (_stageNum == 2)
	{
		_stage2->dropMoney(PointMake(_vEnemy[arrNum]->getAbsoluteX(), _vEnemy[arrNum]->getAbsoluteY()), 20);
	}
	SAFE_DELETE(_vEnemy[arrNum]);
	_viEnemy = _vEnemy.erase(_vEnemy.begin() + arrNum);

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
		if (_vEnemy[i]->getIsDead()) return;

		if (getDistance(_vEnemy[i]->getCenterX(), _vEnemy[i]->getCenterY(), _mainPlayer->getCenterX(), _mainPlayer->getCenterY()) < 300) {

			if (_vEnemy[i]->getIsAttack()) return;			//적이 공격상태이면 추적 금지
			if (_vEnemy[i]->getIsHitted()) return;

			if (getDistance(_vEnemy[i]->getCenterX(), _vEnemy[i]->getCenterY(), _mainPlayer->getCenterX(), _mainPlayer->getCenterY()) < 80) {
				
				if (_vEnemy[i]->getCurrentStage() != 2) {
					_vEnemy[i]->setTraceAngle(getAngle(_vEnemy[i]->getCenterX(), _vEnemy[i]->getCenterY(), _mainPlayer->getCenterX(), _mainPlayer->getCenterY()));
				}
				_vEnemy[i]->setIsTracePlayer(4);

				if (_vEnemy[i]->getTraceAngle() <= getDegree(188) && _vEnemy[i]->getTraceAngle() >= getDegree(172)) {
					_vEnemy[i]->setIsAttack(true);			//공격해라
					_vEnemy[i]->setIsTracePlayer(2);		//다시 한번 이야기 하지만 0번이 패트롤 상태 1번이 추격, 2번이 공격
					_mainPlayer->hurt(1, _vEnemy[i]->getCenterX());
				}
				else if (_vEnemy[i]->getTraceAngle() <= getDegree(10) && _vEnemy[i]->getTraceAngle() >= getDegree(0)) {
					_vEnemy[i]->setIsAttack(true);			//공격해라
					_vEnemy[i]->setIsTracePlayer(2);
					_mainPlayer->hurt(1, _vEnemy[i]->getCenterX());
				}
				else if (_vEnemy[i]->getTraceAngle() <= getDegree(360) && _vEnemy[i]->getTraceAngle() >= getDegree(350)) {
					_vEnemy[i]->setIsAttack(true);			//공격해라
					_vEnemy[i]->setIsTracePlayer(2);
					_mainPlayer->hurt(1, _vEnemy[i]->getCenterX());
				}
				
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
void enemyManager::setStage1MemoryAddressLink(stage1* stage1, int stageNum){
	_stage1 = stage1; _stageNum = stageNum;
}
void enemyManager::setStage2MemoryAddressLink(stage2* stage2, int stageNum){
	_stage2 = stage2; _stageNum = stageNum;
}
//void enemyManager::setStage3MemoryAddressLink(stage3* stage3, int stageNum){
//	_stage3 = stage3; _stageNum = stageNum;
//}


void enemyManager::deadEnemy() {
	for (int i = 0; i < _vEnemy.size(); ++i) {
		if (_vEnemy.size() == 0) return;

		if (_vEnemy[i]->getHP() < 0) {

			if (_vEnemy[i]->getDeleteEnemy()) {
				removeEnemy(i);
				break;
			}

			_vEnemy[i]->setIsTracePlayer(3);
			_vEnemy[i]->setIsDead(true);

			break;
		}
	}
}