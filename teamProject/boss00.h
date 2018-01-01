#pragma once
#include "gameNode.h"
#include "enemy.h"

enum BOSSDIRECTION
{
	//������
	BOSSDIRECTION_RIGHT_STOP,				//����
	BOSSDIRECTION_RIGHT_MOVE,				//�ɾ
	BOSSDIRECTION_RIGHT_RUN,				//�޸���
	BOSSDIRECTION_RIGHT_ONE_JAB,			//��µ����
	BOSSDIRECTION_RIGHT_TWO_JAB,			//��µ����
	BOSSDIRECTION_RIGHT_JUMP_ATTACK,		//��������
	BOSSDIRECTION_RIGHT_HIT,				//���ݴ���
	BOSSDIRECTION_RIGHT_HIT2,				//�����ɸ��°��ݴ���
	BOSSDIRECTION_RIGHT_CROUCH,			//������
	BOSSDIRECTION_RIGHT_CROUCH_HIT,		//�����ϰ��ĵ巯����
	BOSSDIRECTION_RIGHT_CROUCH_THROW,		//�����ϰ���������
	BOSSDIRECTION_RIGHT_DOWN,				//������
	BOSSDIRECTION_RIGHT_COMBO_DOWN,		//���Ӱ��ݸ°�����
	BOSSDIRECTION_RIGHT_DOWN_STAND,		//�������� �Ͼ
	BOSSDIRECTION_RIGHT_DOWN_FOREVER,		//�������� ����
	BOSSDIRECTION_RIGHT_STONE_UP,			//���� �������
	BOSSDIRECTION_RIGHT_STONE_UP_MOVE,		//���� ��������
	BOSSDIRECTION_RIGHT_STONE_THROW,		//���� ����
	BOSSDIRECTION_RIGHT_KNIFE_UP,			//Į ����
	BOSSDIRECTION_RIGHT_KNIFE_THROW,		//Į ����


	//����									  //
	BOSSDIRECTION_LEFT_STOP,				//����
	BOSSDIRECTION_LEFT_MOVE,				//�ɾ
	BOSSDIRECTION_LEFT_RUN,				//�޸���
	BOSSDIRECTION_LEFT_ONE_JAB,			//��µ����
	BOSSDIRECTION_LEFT_TWO_JAB,			//��µ����
	BOSSDIRECTION_LEFT_JUMP_ATTACK,		//��������
	BOSSDIRECTION_LEFT_HIT,				//���ݴ���
	BOSSDIRECTION_LEFT_HIT2,				//�����ɸ��°��ݴ���
	BOSSDIRECTION_LEFT_CROUCH,				//������
	BOSSDIRECTION_LEFT_CROUCH_HIT,			//�����ϰ��ĵ巯����
	BOSSDIRECTION_LEFT_CROUCH_THROW,		//�����ϰ���������
	BOSSDIRECTION_LEFT_DOWN,				//������
	BOSSDIRECTION_LEFR_COMBO_DOWN,			//���Ӱ��ݸ°�����
	BOSSDIRECTION_LEFT_DOWN_STAND,			//�������� �Ͼ
	BOSSDIRECTION_LEFT_DOWN_FOREVER,		//�������� ����
	BOSSDIRECTION_LEFT_STONE_UP,			//���� �������
	BOSSDIRECTION_LEFT_STONE_UP_MOVE,		//���� ��������
	BOSSDIRECTION_LEFT_STONE_THROW,		//���� ����
	BOSSDIRECTION_LEFT_KNIFE_UP,			//Į����
	BOSSDIRECTION_LEFT_KNIFE_THROW,		//Į����

	//����
	BOSSDIRECTION_Clime,					//��ٸ�
	BOSSDIRECTION_RIGHT_DEAD				//������
};


class boss00 : public enemy
{
private:
	BOSSDIRECTION _BossDirection;


	//�̹����� ��ġ���� ��Ʈ�� HP����
	/*
	image* _imageEnemy;				//�̹���
	RECT _rcEnemy;				//��Ʈ
	RECT _CollircEnemy;			//�浹��Ʈ
	int _HP;					//ü��
	int _maxHP;					//�ִ�ü��
	int _speed;					//�ӵ�
	int _x, _y;					//xy��
	float _ZMove;				//z����
	float _jump, _Gravity;		//����,�߷�

	animation* _enemyMotion;
	*/
	



public:
	boss00();
	~boss00();


	virtual HRESULT init(POINT point);
	//virtual void release();
	//virtual void update();
	//virtual void render();
	virtual void collision();


	//�ݹ��Լ��� ����

	static void rightAttack(void* obj);
	static void rightJumpAttack(void* obj);
	static void leftAttack(void* obj);
	static void leftJumpAttack(void* obj);

	/*virtual ENEMYDIRECTION getEnemyDirection(void) { return _BossDirection; }
	virtual void setEnemyDirection(ENEMYDIRECTION direction) { _BossDirection; }*/

	////���׹� ���¿� ���� �����ڿ� �����ڰ���?
	//BOSSDIRECTION getEnemyDirection(void) { return _BossDirection; }
	//void setEnemyDirection(BOSSDIRECTION direction) { _BossDirection = direction; }

	////���׹��� ��ǿ� ���� �����ڿ� �����ڰ���?
	//animation* getBossMotion(void) { return _BossMotion; }
	//void getBossMotion(animation* ani) { _BossMotion = ani; }
};

