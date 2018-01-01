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





}
void enemyManager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}
}

//ÂÌµû±¸
void enemyManager::setMinion(void)
{


}
//Á¤¿¹
void enemyManager::setPick(void)
{

}
//º¸½º
void enemyManager::setBoss(void)
{
	enemy* temp;
	temp = new boss00;

	_vEnemy.push_back(temp);
}

//Àû »ç¸Á½Ã Á¦°Å
void enemyManager::removeEnemy(int arrNum)
{
	SAFE_DELETE(_vEnemy[arrNum]);
	_vEnemy.erase(_vEnemy.begin() + arrNum);
}
//µ· ½Àµæ½Ã Á¦°Å
void enemyManager::removeItem(int arrNum)
{

}
//fight!!
void enemyManager::collision(void)
{

}