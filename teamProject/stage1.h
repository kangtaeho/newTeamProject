#pragma once
#include "gameNode.h"
#include "item.h"
#include "knife.h"
#include "enemy.h"
#include "stone.h"
#include "character.h"
#include "inventory.h"

static enum stageState 
{
	MOVING,
	FIGHTING,
	CLEAR


};

class stage1 : public gameNode
{

private:

	RECT rc1;
	RECT* currentRC;

	item* _knife; // Ä® ½ºÅ×ÀÌÁö·Î °¡Á®¿È
	enemy* _enemy;

	item* _stone; // ¹Ì´Ïµ¹µ¢ÀÌ ¤·¤·


	inventory* _inven;				//ÀÎº¥Åä¸® Å¬·¡½º »ı¼º

	bool _stopCharacter;			//Ä³¸¯ÅÍ°¡ ¸Ø­Ÿ´Ï?(ÀÎº¥Åä¸® ¿­¶§ »ç¿ë)

	stageState _ss;
public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();

	virtual void setMainPlayer(character* mainPlayer) { _mainPlayer = mainPlayer; }
	virtual character* getMainPlayer(){ return _mainPlayer; }

	void characterMovement();							//Ä³¸¯ÅÍ Å°¸ÅÁöÀú¸¦ °ü¸®ÇÏ´Â ÇÔ¼ö
};

