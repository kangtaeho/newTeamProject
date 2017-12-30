#pragma once
#include "gameNode.h"


//���׹� ���¼��� (�� �߰� �ɼ��� ����)
enum ENEMYDIRECTION
{
	//������
	ENEMYDIRECTION_RIGHT_STOP,				//����
	ENEMYDIRECTION_RIGHT_MOVE,				//�ɾ
	ENEMYDIRECTION_RIGHT_RUN,				//�޸���
	ENEMYDIRECTION_RIGHT_ATTACK,			//����
	ENEMYDIRECTION_RIGHT_JUMP_ATTACK,		//��������
	ENEMYDIRECTION_RIGHT_HIT,				//����
	ENEMYDIRECTION_RIGHT_CROUCH,			//������
	ENEMYDIRECTION_RIGHT_CROUCH_HIT,		//�����ϰ��ĵ巯����
	ENEMYDIRECTION_RIGHT_CROUCH_THROW,		//�����ϰ���������
	ENEMYDIRECTION_RIGHT_DOWN,				//������
	ENEMYDIRECTION_RIGHT_DOWN_STAND,		//�������� �Ͼ
	ENEMYDIRECTION_RIGHT_DOWN_FOREVER,		//�������� ����
	ENEMYDIRECTION_RIGHT_SOMETHING_THROW,	//���𰡸� ����
											//
	//����								  /	 /
	ENEMYDIRECTION_LEFT_STOP,				//����
	ENEMYDIRECTION_LEFT_MOVE,				//�ɾ
	ENEMYDIRECTION_LEFT_RUN,				//�޸���
	ENEMYDIRECTION_LEFT_ATTACK,				//����
	ENEMYDIRECTION_LEFT_JUMP_ATTACK,		//��������
	ENEMYDIRECTION_LEFT_HIT,				//����
	ENEMYDIRECTION_LEFT_CROUCH,				//������
	ENEMYDIRECTION_LEFT_CROUCH_HIT,			//�����ϰ��ĵ巯����
	ENEMYDIRECTION_LEFT_CROUCH_THROW,		//�����ϰ���������
	ENEMYDIRECTION_LEFT_DOWN,				//������
	ENEMYDIRECTION_LEFT_DOWN_STAND,			//�������� �Ͼ
	ENEMYDIRECTION_LEFT_DOWN_FOREVER,		//�������� ����
	ENEMYDIRECTION_LEFT_SOMETHING_THROW		//���𰡸� ����
};


class enemy : public gameNode
{
private:
	ENEMYDIRECTION _enemyDirection;


	//�̹����� ��ġ���� ��Ʈ�� HP����
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



public:
	enemy();
	~enemy();


	HRESULT init(POINT point);
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

