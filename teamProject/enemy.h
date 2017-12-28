#pragma once
#include "gameNode.h"


//���׹� ���¼��� (�� �߰� �ɼ��� ����)
enum ENEMYDIRECTION
{
	//������
	ENEMYDIRECTION_RIGHT_STOP,			  //�����ʸ���
	ENEMYDIRECTION_RIGHT_MOVE,			  //�����ʿ�����
	ENEMYDIRECTION_RIGHT_RUN,			  //�����ʴ޸�
	ENEMYDIRECTION_RIGHT_ATTACK,		  //�����ʰ���
	ENEMYDIRECTION_RIGHT_JUMP_ATTACK,     //��������������
	ENEMYDIRECTION_RIGHT_HIT,			  //�����ʹٶ󺸸鼭 ����
	ENEMYDIRECTION_RIGHT_CROUCH,		  //�����ʿ��� ����
	ENEMYDIRECTION_RIGHT_CROUCH_HIT,	  //�����ʿ��� ������ ����
	ENEMYDIRECTION_RIGHT_CROUCH_THROW,	  //���������� ������
	ENEMYDIRECTION_RIGHT_DOWN,			  //������
	ENEMYDIRECTION_RIGHT_DOWN_STAND,	  //�������ٰ� �Ͼ
	ENEMYDIRECTION_RIGHT_DOWN_FOREVER,	  //������ ����
	ENEMYDIRECTION_RIGHT_SOMETHING_THROW, //���𰡸� ����

	//����
	ENEMYDIRECTION_LEFT_STOP,				//���ʸ���
	ENEMYDIRECTION_LEFT_MOVE,				//���ʿ�����
	ENEMYDIRECTION_LEFT_RUN,				//���ʴ޸�
	ENEMYDIRECTION_LEFT_ATTACK,				//���ʰ���
	ENEMYDIRECTION_LEFT_JUMP_ATTACK,		//������������
	ENEMYDIRECTION_LEFT_HIT,				//���ʹٶ󺸸鼭 ����
	ENEMYDIRECTION_LEFT_CROUCH,				//���ʿ��� ����
	ENEMYDIRECTION_LEFT_CROUCH_HIT,			//���ʿ��� ������ ����
	ENEMYDIRECTION_LEFT_CROUCH_THROW,		//�������� ������
	ENEMYDIRECTION_LEFT_DOWN,				//�������� ������
	ENEMYDIRECTION_LEFT_DOWN_STAND,			//�������ٰ� �Ͼ
	ENEMYDIRECTION_LEFT_DOWN_FOREVER,		//������ ����
	ENEMYDIRECTION_LEFT_SOMETHING_THROW		//���𰡸� ����
};


class enemy : public gameNode
{
private:
	ENEMYDIRECTION _enemyDirection;


	//�̹����� ��ġ���� ��Ʈ�� HP����
	image* _image;
	float _x, _y;
	RECT _rc;
	int _currentHP;


	animation* _enemyMotion;



public:
	enemy();
	~enemy();


	HRESULT init();
	void release();
	void update();
	void render();


	//�ݹ��Լ��� ����

	static void rightAttack(void* obj);
	static void rightJumpAttack(void* obj);
	static void leftAttack(void* obj);
	static void leftJumpAttack(void* obj);

	//���׹� ���¿� ���� �����ڿ� �����ڰ���?
	ENEMYDIRECTION getEnemyDirection(void) { return _enemyDirection; }
	void setEnemyDirection(ENEMYDIRECTION direction) { _enemyDirection = direction; }

	//���׹��� ��ǿ� ���� �����ڿ� �����ڰ���?
	animation* getEnemyMotion(void) { return _enemyMotion; }
	void setEnemyMotion(animation* ani) { _enemyMotion = ani; }
};

