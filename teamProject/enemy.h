#pragma once
#include "gameNode.h"


//���׹� ���¼��� (�� �߰� �ɼ��� ����)
//enum ENEMYDIRECTION
//{
//	//������
//	ENEMYDIRECTION_RIGHT_STOP,				//����
//	ENEMYDIRECTION_RIGHT_MOVE,				//�ɾ
//	ENEMYDIRECTION_RIGHT_RUN,				//�޸���
//	ENEMYDIRECTION_RIGHT_ONE_JAB,			//��µ����
//	ENEMYDIRECTION_RIGHT_TWO_JAB,			//��µ����
//	ENEMYDIRECTION_RIGHT_JUMP_ATTACK,		//��������
//	ENEMYDIRECTION_RIGHT_HIT,				//���ݴ���
//	ENEMYDIRECTION_RIGHT_HIT2,				//�����ɸ��°��ݴ���
//	ENEMYDIRECTION_RIGHT_CROUCH,			//������
//	ENEMYDIRECTION_RIGHT_CROUCH_HIT,		//�����ϰ��ĵ巯����
//	ENEMYDIRECTION_RIGHT_CROUCH_THROW,		//�����ϰ���������
//	ENEMYDIRECTION_RIGHT_DOWN,				//������
//	ENEMYDIRECTION_RIGHT_COMBO_DOWN,		//���Ӱ��ݸ°�����
//	ENEMYDIRECTION_RIGHT_DOWN_STAND,		//�������� �Ͼ
//	ENEMYDIRECTION_RIGHT_DOWN_FOREVER,		//�������� ����
//	ENEMYDIRECTION_RIGHT_STONE_UP,			//���� �������
//	ENEMYDIRECTION_RIGHT_STONE_UP_MOVE,		//���� ��������
//	ENEMYDIRECTION_RIGHT_STONE_THROW,		//���� ����
//	ENEMYDIRECTION_RIGHT_KNIFE_UP,			//Į ����
//	ENEMYDIRECTION_RIGHT_KNIFE_THROW,		//Į ����
//											
//	//����									  //
//	ENEMYDIRECTION_LEFT_STOP,				//����
//	ENEMYDIRECTION_LEFT_MOVE,				//�ɾ
//	ENEMYDIRECTION_LEFT_RUN,				//�޸���
//	ENEMYDIRECTION_LEFT_ONE_JAB,			//��µ����
//	ENEMYDIRECTION_LEFT_TWO_JAB,			//��µ����
//	ENEMYDIRECTION_LEFT_JUMP_ATTACK,		//��������
//	ENEMYDIRECTION_LEFT_HIT,				//���ݴ���
//	ENEMYDIRECTION_LEFT_HIT2,				//�����ɸ��°��ݴ���
//	ENEMYDIRECTION_LEFT_CROUCH,				//������
//	ENEMYDIRECTION_LEFT_CROUCH_HIT,			//�����ϰ��ĵ巯����
//	ENEMYDIRECTION_LEFT_CROUCH_THROW,		//�����ϰ���������
//	ENEMYDIRECTION_LEFT_DOWN,				//������
//	ENEMYDIRECTION_LEFR_COMBO_DOWN,			//���Ӱ��ݸ°�����
//	ENEMYDIRECTION_LEFT_DOWN_STAND,			//�������� �Ͼ
//	ENEMYDIRECTION_LEFT_DOWN_FOREVER,		//�������� ����
//	ENEMYDIRECTION_LEFT_STONE_UP,			//���� �������
//	ENEMYDIRECTION_LEFT_STONE_UP_MOVE,		//���� ��������
//	ENEMYDIRECTION_LEFT_STONE_THROW,		//���� ����
//	ENEMYDIRECTION_LEFT_KNIFE_UP,			//Į����
//	ENEMYDIRECTION_LEFT_KNIFE_THROW,		//Į����
//
//	//����
//	ENEMYDIRECTION_Clime					//��ٸ�
//};


class enemy : public gameNode
{
protected:
	//
	//ENEMYDIRECTION _enemyDirection;


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


	virtual HRESULT init(/*const char* imageName,*/POINT point);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void collision();


	//�ݹ��Լ��� ����

	static void rightAttack(void* obj);
	static void rightJumpAttack(void* obj);
	static void leftAttack(void* obj);
	static void leftJumpAttack(void* obj);

	//���׹� ���¿� ���� �����ڿ� �����ڰ���?
	/*virtual ENEMYDIRECTION getEnemyDirection(void) {  }
	virtual void setEnemyDirection(ENEMYDIRECTION direction) { }*/
	//
	////���׹��� ��ǿ� ���� �����ڿ� �����ڰ���?
	animation* getEnemyMotion(void) { return _enemyMotion; }
	void setEnemyMotion(animation* ani) { _enemyMotion = ani; }
};

//���� �ݹ��Լ��� �ʿ��� ��ǵ��̶���� �׷��� ���ؾߵɱ
//�� �߰��ؾߵɰ� ���������