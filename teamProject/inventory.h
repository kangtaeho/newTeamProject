#pragma once
#include "gameNode.h"
#include "orangePotion.h"
#include "redPotion.h"
#include "whitePotion.h"

class inventory:public gameNode
{
private:

public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();

	void getItem();						//æ∆¿Ã≈∆¿ª ¡÷ø¸¿ª ∂ß

};

