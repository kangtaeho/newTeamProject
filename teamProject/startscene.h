#pragma once
#include "gameNode.h"
class startscene :
	public gameNode
{
	//ȭ��ǥ�� ��ŸƮ���� �ɼ�����
	bool _index;
public:
	startscene();
	~startscene();

	HRESULT init();
	void release();
	void update();
	void render();

};

