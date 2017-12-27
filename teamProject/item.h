#pragma once
#include "gameNode.h"

enum tagItemType{
	POTION,		//물약 소모품
	THROW		//투척 소모품(맵 object)
};
class item :
	public gameNode
{
private:
	image* _itemImage;		//아이템 이미지
	float _x, _y;			//아이템 좌표
	tagItemType	_itemType;	//아이템 종류
	int _itemEffect;		//아이템 효과(투척 -> 데미지 & 물약 -> 회복)
	int _price;				//아이템 가격


public:
	item();
	~item();

	
	HRESULT init();

	
	//오브젝트(투척)용		이미지 키,    이미지 파일이름,   넓이,     높이,   좌표			데미지  *** 프레임이 아닌 그냥 이미지로 만들어둠!!!!
	HRESULT init(string strKey, const char* fileName, int width, int height, int frameX, int frameY, POINT point, int itemEffect);

	//상점(물약)용		이미지 키,    이미지 파일이름,   넓이,     높이,           좌표		회복량			가격  *** 프레임이 아닌 그냥 이미지로 만들어둠!!!!
	HRESULT init(string strKey, const char* fileName, int width, int height, int frameX, int frameY, POINT point, int itemEffect, int price);

	void release();
	void update();
	void render();

	//아이템 좌표 설정 (투척시 사용)
	void setPoint(POINT point){ _x = point.x; _y = point.y; }	
	
	//아이템 효과 가져오기(투척아이템 : 데미지, 물약 : 회복량)
	int getItemEffect(){
		return _itemEffect;
	}

};

