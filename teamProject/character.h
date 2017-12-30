#pragma once
#include "gameNode.h"

#define CHARASPEED 4;
#define CHARAJUMP 8;

enum CHARA {
	CHARA_RIGHT_STOP,
	CHARA_LEFT_STOP,
	CHARA_RIGHT_MOVE,
	CHARA_LEFT_MOVE,
	CHARA_RIGHT_LAND,
	CHARA_LEFT_LAND,
	CHARA_RIGHT_PUNCH_ONE,
	CHARA_RIGHT_PUNCH_TWO,
	CHARA_LEFT_PUNCH_ONE,
	CHARA_LEFT_PUNCH_TWO,
	CHARA_RIGHT_KICK,
	CHARA_LEFT_KICK,
	CHARA_RIGHT_HEAD,
	CHARA_LEFT_HEAD,
	CHARA_RIGHT_UPPER,
	CHARA_LEFT_UPPER,
	CHARA_RIGHT_HIGHKICK,
	CHARA_LEFT_HIGHKICK,
	CHARA_RIGHT_BACKBLOW,
	CHARA_LEFT_BACKBLOW,
	CHARA_RIGHT_HOLD,
	CHARA_LEFT_HOLD,
	CHARA_RIGHT_JUMP,
	CHARA_LEFT_JUMP,
	CHARA_RIGHT_MOVE_JUMP,
	CHARA_LEFT_MOVE_JUMP,
	CHARA_RIGHT_BACKKICK,
	CHARA_LEFT_BACKKICK,
	CHARA_RIGHT_DRILL,
	CHARA_LEFT_DRILL,
	CHARA_STAIR,
	CHARA_RIGHT_HIT,
	CHARA_LEFT_HIT,
	CHARA_RIGHT_STRIKED,
	CHARA_LEFT_STRIKED,
	CHARA_RIGHT_DOWN,
	CHARA_LEFT_DOWN,
	CHARA_RIGHT_JUMP_KICK,
	CHARA_LEFT_JUMP_KICK,
	CHARA_RIGHT_ATT,
	CHARA_LEFT_ATT,
};

class character : public gameNode
{
private:
	float _x, _y;
	float _StartX, _StartY;//������ ���ƿ� ����
	float _Zmove;//���� �̵���
	float _JP, _gravity;//����, �߷�
	int _HP, _maxHP;//����, ����
	bool _isRight;//������?

	RECT _rc;//������ ��Ʈ
	RECT _colliRect;//��ſ� ��Ʈ

	CHARA _state;//���°�
	animation * _motion;//���
	image * _image;

public:
	character();
	~character();
	HRESULT init();
	void release();
	void update();
	void render();

	//��Ʈ�ֽ�ȭ�Լ�
	void RectUpdate();

	RECT getRect() { return _colliRect; }
	float getX() { return _x; }
	void setX(float X) { _x = X; }
	float getY() { return _y; }
	void setY(float Y) { _y = Y; }

	//���°� HIT�� �ٲ�� ������
	void hurt(int damage);
	//���°� STRIKED�� �ٲ�� ������ ������
	//x���� Ŭ���� ���� �������� ���������� ������
	void strike(int damage, float x);

	static void MakeRightStop(void* obj);
	static void MakeLeftStop(void* obj);
	static void MakeRightFall(void* obj);
	static void MakeLeftFall(void* obj);
	static void MakeRightHold(void* obj);
	static void MakeLeftHold(void* obj);
	static void MakeRightDrill(void* obj);
	static void MakeLeftDrill(void* obj);
	static void MakeRightLand(void* obj);
	static void MakeLeftLand(void* obj);

	//ĳ���� ����������,������
	CHARA getState() { return _state; }
	void setState(CHARA C) { _state = C; }

	//ĳ���� ���������,������
	animation * getMotion() { return _motion; }
	void setMotion(animation * ani) { _motion = ani; }

	//�����Ŀ� ����
	void setJP(float J) { _JP = J; }

	//�����̵�����
	void ZmoveOn() { _Zmove = CHARASPEED; }

	//�����̵��Ұ���
	void ZmoveOff() { _Zmove = 0; };

	//��Ʈ�ֽ�ȭ
	void UpdateRect();
};

