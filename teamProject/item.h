#pragma once
#include "gameNode.h"

enum tagItemType{
	POTION,		//���� �Ҹ�ǰ
	THROW		//��ô �Ҹ�ǰ(�� object)
};
class item :
	public gameNode
{
private:
	image* _itemImage;		//������ �̹���
	float _x, _y;			//������ ��ǥ
	tagItemType	_itemType;	//������ ����
	int _itemEffect;		//������ ȿ��(��ô -> ������ & ���� -> ȸ��)
	int _price;				//������ ����


public:
	item();
	~item();

	
	HRESULT init();

	
	//������Ʈ(��ô)��		�̹��� Ű,    �̹��� �����̸�,   ����,     ����,   ��ǥ			������  *** �������� �ƴ� �׳� �̹����� ������!!!!
	HRESULT init(string strKey, const char* fileName, int width, int height, int frameX, int frameY, POINT point, int itemEffect);

	//����(����)��		�̹��� Ű,    �̹��� �����̸�,   ����,     ����,           ��ǥ		ȸ����			����  *** �������� �ƴ� �׳� �̹����� ������!!!!
	HRESULT init(string strKey, const char* fileName, int width, int height, int frameX, int frameY, POINT point, int itemEffect, int price);

	void release();
	void update();
	void render();

	//������ ��ǥ ���� (��ô�� ���)
	void setPoint(POINT point){ _x = point.x; _y = point.y; }	
	
	//������ ȿ�� ��������(��ô������ : ������, ���� : ȸ����)
	int getItemEffect(){
		return _itemEffect;
	}

};

