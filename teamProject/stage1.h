#pragma once
#include "gameNode.h"
#include "item.h"
#include "knife.h"
#include "enemy.h"
#include "stone.h"
class stage1 : public gameNode
{

private:

	RECT rc1;
	RECT* currentRC;

	item* _knife; // Į ���������� ������
	enemy* _enemy;

	item* _stone; // �̴ϵ����� ����
public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();
};

