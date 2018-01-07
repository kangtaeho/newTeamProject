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
		
		(*_viEnemy)->update();
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

	if (_vEnemy.size() == 0) return;
	//showFloatData(getMemDC(), "x ��ǥ : %0.2f", _mini->getX(), 800, 20);
	//
	showIntData(getMemDC(), "ī��Ʈ �����ϰ�� �ֳ�? : %d", _vEnemy[0]->getCountHitted(), 800, 40);
	showIntData(getMemDC(), "ī��Ʈ �����ϰ�� �ֳ�? : %d", _vEnemy[0]->getIsTracePlayer(), 800, 60);
	///_mini->render();

}

//�̵���
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
//����
void enemyManager::setPick(POINT point, int stageCout)
{
	enemy* temp;
	temp = new minion02;
	temp->init(point, stageCout);

	_vEnemy.push_back(temp);
}

//����
void enemyManager::setBoss(POINT point, int stageCout)
{
	enemy* temp;
	temp = new boss00;
	temp->init(point);

	_vEnemy.push_back(temp);
}

//�� ����� ����
void enemyManager::removeEnemy(int arrNum)
{
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

//�� ����� ����
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

		if (getDistance(_vEnemy[i]->getCenterX(), _vEnemy[i]->getCenterY(), _mainPlayer->getCenterX(), _mainPlayer->getCenterY()) < 300) {

			if (_vEnemy[i]->getIsAttack()) return;			//���� ���ݻ����̸� ���� ����
			if (_vEnemy[i]->getIsHitted()) return;

			if (getDistance(_vEnemy[i]->getCenterX(), _vEnemy[i]->getCenterY(), _mainPlayer->getCenterX(), _mainPlayer->getCenterY()) < 80) {

				_vEnemy[i]->setIsTracePlayer(4);
				_vEnemy[i]->setTraceAngle(getAngle(_vEnemy[i]->getCenterX(), _vEnemy[i]->getCenterY(), _mainPlayer->getCenterX(), _mainPlayer->getCenterY()));

				if (_vEnemy[i]->getTraceAngle() <= getDegree(185) && _vEnemy[i]->getTraceAngle() >= getDegree(175)) {
					_vEnemy[i]->setIsAttack(true);			//�����ض�
					_vEnemy[i]->setIsTracePlayer(2);		//�ٽ� �ѹ� �̾߱� ������ 0���� ��Ʈ�� ���� 1���� �߰�, 2���� ����
				}
				else if (_vEnemy[i]->getTraceAngle() <= getDegree(10) && _vEnemy[i]->getTraceAngle() >= getDegree(0)) {
					_vEnemy[i]->setIsAttack(true);			//�����ض�
					_vEnemy[i]->setIsTracePlayer(2);
				}
				else if (_vEnemy[i]->getTraceAngle() < getDegree(360) && _vEnemy[i]->getTraceAngle() >= getDegree(355)) {
					_vEnemy[i]->setIsAttack(true);			//�����ض�
					_vEnemy[i]->setIsTracePlayer(2);
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