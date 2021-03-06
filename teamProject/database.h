#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

//배에 속성
class elements
{
public:
	const char* name;
	int currentHP;
	int maxHP;
	float angle;
	float accelaration;
	float maxSpeed;

	elements() {};
	~elements() {};
};

class database : public singletonBase<database>
{
private:
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;

	typedef map<string, elements*> arrElement;
	typedef map<string, elements*>::iterator iterElement;

private:
	arrElement _mTotalElement;
	float _angle;

public:
	HRESULT init();
	void release();

	void loadDatabase(string name);

	//속성(스탯)에 대한 접근자
	elements* getElementData(string str) { return _mTotalElement.find(str)->second; }

	//설정자
	void setElementDataCurrentHP(string str, float ch);
	void setElementDataMaxHP(string str, float mh);
	void setElementDataAngle(string str, float a);
	void setElementDataAccelaration(string str, float accel);
	void setElementDataMaxSpeed(string str, float ms);

	void setAngle(float angle) { _angle = angle; }
	float getAngle() { return _angle; }




	database();
	~database();
};

