#pragma once
#include "gameNode.h"

enum tagItemType{
	POTION,		//물약 소모품
	THROW,		//투척 소모품(맵 object)
	MONEY		//돈
};
class item :
	public gameNode
{
protected:
	image* _itemImage;		//아이템 이미지
	float _x, _y;			//아이템 중점좌표
	tagItemType	_itemType;	//아이템 종류
	int _itemEffect;		//아이템 효과(투척 -> 데미지 & 물약 -> 회복 & 돈->획득량)
	int _price;				//아이템 가격
	int _count;				//들고있는 갯수

public:
	item();
	~item();

	//좌표가 필요없는 상점아이템 초기화
	virtual HRESULT init();
	//좌표가 필요한 오브젝트, 돈 초기화
	virtual HRESULT init(POINT point);
	virtual void release();
	virtual void update();
	virtual void render();

	//아이템 좌표 설정 (투척시 사용)
	void setPoint(POINT point){ _x = point.x; _y = point.y; }		
	RECT getItemRC() { return RectMakeCenter(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight()); }

	//아이템 효과 가져오기(투척아이템 : 데미지, 물약 : 회복량)
	int getItemEffect(){return _itemEffect;}

	//물약 이미지는 이걸 통해 그리면 됨
	image*	getItemImage(){ return _itemImage; }

	//물약 소지 갯수 변경 및 가져오기(사용시 인수값 = -1)
	void setCount(int count) { _count = count; }
	int getCount(){ return _count; }

	//가격 가져오기
	int getPrice(){ return _price; }


};

