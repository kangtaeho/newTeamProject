#pragma once
#include "gameNode.h"

enum tagItemType{
	POTION,		//���� �Ҹ�ǰ
	THROW,		//��ô �Ҹ�ǰ(�� object)
	MONEY,		//��
};
enum tagItemState{
	DROP,		//������ �ִ� ����	
	THROWING	//�������� �ִ� ����
};
class item :
	public gameNode
{
protected:
	image* _itemImage;			//������ �̹���
	float _x, _y;				//������ ������ǥ
	tagItemType	_itemType;		//������ ����
	tagItemState _itemState;	//������ ����
	int _itemEffect;			//������ ȿ��(��ô -> ������ & ���� -> ȸ�� & ��->ȹ�淮)
	int _price;					//������ ����
	int _count;					//����ִ� ����

	

public:
	item();
	~item();

	//��ǥ�� �ʿ���� ���������� �ʱ�ȭ
	virtual HRESULT init();
	//��ǥ�� �ʿ��� ������Ʈ �ʱ�ȭ
	virtual HRESULT init(POINT point);
	//��ǥ�� �ʿ��ϰ� ���͸��� ����ϴ� ���� �ٸ��� �ϱ� ���� �ʱ�ȭ
	virtual HRESULT init(POINT point, int money);
	virtual void release();
	virtual void update();
	virtual void render();

	//������ ��ǥ ���� (��ô�� ���)
	void setPoint(POINT point){ _x = point.x; _y = point.y; }		
	RECT getItemRC() { return RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight()); }

	//������ ȿ�� ��������(��ô������ : ������, ���� : ȸ����)
	int getItemEffect(){return _itemEffect;}

	//���� �̹����� �̰� ���� �׸��� ��
	image*	getItemImage(){ return _itemImage; }

	//���� ���� ���� ���� �� ��������(���� �μ��� = -1)
	void setCount(int count) { _count = count; }
	int getCount(){ return _count; }

	//���� ��������
	int getPrice(){ return _price; }

	//������ ���� ����
	void setState(bool isThrow){ _itemState = THROWING; }


};

