#pragma once
#include "gameNode.h"
#include "item.h"
#include "knife.h"
<<<<<<< HEAD
#include "enemy.h"
=======
#include "stone.h"
>>>>>>> d91d087382d8938c79086f37a8ccdb79a060cacf
class stage1 : public gameNode
{

private:

	RECT rc1;
	RECT* currentRC;

	item* _knife; // Į ���������� ������
<<<<<<< HEAD
	enemy* _enemy;

=======
	item* _stone; // �̴ϵ����� ����
>>>>>>> d91d087382d8938c79086f37a8ccdb79a060cacf
public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();
};

