#pragma once
#include "gameNode.h"
#include "enemy.h"

//���׹� ���¼��� (�� �߰� �ɼ��� ����)
//enum ENEMYDIRECTION
//{
//	������
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
//	����									  //
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
//	����
//	ENEMYDIRECTION_Clime,					//��ٸ�
//	BOSSDIRECTION_DEAD
//};


class minion00 : public enemy
{
private:
	//ENEMYDIRECTION _EnemyDirection;


	////�̹����� ��ġ���� ��Ʈ�� HP����
	//image* _imageEnemy;				//�̹���
	//RECT _rcEnemy;				//��Ʈ
	//RECT _CollircEnemy;			//�浹��Ʈ
	//int _HP;					//ü��
	//int _maxHP;					//�ִ�ü��
	//int _speed;					//�ӵ�
	//int _x, _y;					//xy��
	//float _ZMove;				//z����
	//float _jump, _Gravity;		//����,�߷�

	//animation* _EnemyMotion;



public:
	minion00();
	~minion00();


	virtual HRESULT init(POINT point, int currentStage = 1);
	//virtual void release();
	//virtual void update();
	//virtual void render();
	 virtual void collision();


	//�ݹ��Լ��� ����

	// static void rightAttack(void* obj);
	// static void rightJumpAttack(void* obj);
	// static void leftAttack(void* obj);
	// static void leftJumpAttack(void* obj);

	//���׹� ���¿� ���� �����ڿ� �����ڰ���?
	//ENEMYDIRECTION getEnemyDirection(void) { return _EnemyDirection; }
	//void setEnemyDirection(ENEMYDIRECTION direction) { _EnemyDirection = direction; }

	//���׹��� ��ǿ� ���� �����ڿ� �����ڰ���?
	//animation* getEnemyMotion(void) { return _EnemyMotion; }
	//void getEnemyMotion(animation* ani) { _EnemyMotion = ani; }
};

