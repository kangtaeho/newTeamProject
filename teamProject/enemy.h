#pragma once
#include "gameNode.h"


//���׹� ���¼��� (�� �߰� �ɼ��� ����)

class stage1;

//���
enum ENEMYDIRECTION
{
	
	//������
	ENEMYDIRECTION_RIGHT_STOP,				//����
	ENEMYDIRECTION_RIGHT_MOVE,				//�ɾ
	ENEMYDIRECTION_RIGHT_RUN,				//�޸���
	ENEMYDIRECTION_RIGHT_ONE_JAB,			//��µ����
	ENEMYDIRECTION_RIGHT_TWO_JAB,			//��µ����
	ENEMYDIRECTION_RIGHT_JUMP_ATTACK,		//��������
	ENEMYDIRECTION_RIGHT_HIT,				//���ݴ���
	ENEMYDIRECTION_RIGHT_HIT2,				//�����ɸ��°��ݴ���
	ENEMYDIRECTION_RIGHT_CROUCH,			//������
	ENEMYDIRECTION_RIGHT_CROUCH_HIT,		//�����ϰ��ĵ巯����
	ENEMYDIRECTION_RIGHT_CROUCH_THROW,		//�����ϰ���������
	ENEMYDIRECTION_RIGHT_DOWN,				//������
	ENEMYDIRECTION_RIGHT_COMBO_DOWN,		//���Ӱ��ݸ°�����
	ENEMYDIRECTION_RIGHT_DOWN_STAND,		//�������� �Ͼ
	ENEMYDIRECTION_RIGHT_DOWN_FOREVER,		//�������� ����
	ENEMYDIRECTION_RIGHT_STONE_UP,			//���� �������
	ENEMYDIRECTION_RIGHT_STONE_UP_MOVE,		//���� ��������
	ENEMYDIRECTION_RIGHT_STONE_THROW,		//���� ����
	ENEMYDIRECTION_RIGHT_KNIFE_UP,			//Į ����
	ENEMYDIRECTION_RIGHT_KNIFE_THROW,		//Į ����
											
	//����									  //
	ENEMYDIRECTION_LEFT_STOP,				//����
	ENEMYDIRECTION_LEFT_MOVE,				//�ɾ
	ENEMYDIRECTION_LEFT_RUN,				//�޸���
	ENEMYDIRECTION_LEFT_ONE_JAB,			//��µ����
	ENEMYDIRECTION_LEFT_TWO_JAB,			//��µ����
	ENEMYDIRECTION_LEFT_JUMP_ATTACK,		//��������
	ENEMYDIRECTION_LEFT_HIT,				//���ݴ���
	ENEMYDIRECTION_LEFT_HIT2,				//�����ɸ��°��ݴ���
	ENEMYDIRECTION_LEFT_CROUCH,				//������
	ENEMYDIRECTION_LEFT_CROUCH_HIT,			//�����ϰ��ĵ巯����
	ENEMYDIRECTION_LEFT_CROUCH_THROW,		//�����ϰ���������
	ENEMYDIRECTION_LEFT_DOWN,				//������
	ENEMYDIRECTION_LEFR_COMBO_DOWN,			//���Ӱ��ݸ°�����
	ENEMYDIRECTION_LEFT_DOWN_STAND,			//�������� �Ͼ
	ENEMYDIRECTION_LEFT_DOWN_FOREVER,		//�������� ����
	ENEMYDIRECTION_LEFT_STONE_UP,			//���� �������
	ENEMYDIRECTION_LEFT_STONE_UP_MOVE,		//���� ��������
	ENEMYDIRECTION_LEFT_STONE_THROW,		//���� ����
	ENEMYDIRECTION_LEFT_KNIFE_UP,			//Į����
	ENEMYDIRECTION_LEFT_KNIFE_THROW,		//Į����

	//����
	ENEMYDIRECTION_Clime				//��ٸ�

};


//����
enum BOSSDIRECTION
{
	//������
	BOSSDIRECTION_RIGHT_STOP,				//����
	BOSSDIRECTION_RIGHT_MOVE,				//�ɾ
	BOSSDIRECTION_RIGHT_ONE_JAB,			//��µ����
	BOSSDIRECTION_RIGHT_TWO_JAB,			//��µ����
	BOSSDIRECTION_RIGHT_HIT,				//���ݴ���
	BOSSDIRECTION_RIGHT_HIT2,				//�����ɸ��°��ݴ���
	BOSSDIRECTION_RIGHT_DOWN,				//������
	BOSSDIRECTION_RIGHT_COMBO_DOWN,			//���Ӱ��ݸ°�����
	BOSSDIRECTION_RIGHT_DOWN_STAND,			//�������� �Ͼ

											
	//����									  //
	BOSSDIRECTION_LEFT_STOP,				//����
	BOSSDIRECTION_LEFT_MOVE,				//�ɾ
	BOSSDIRECTION_LEFT_ONE_JAB,				//��µ����
	BOSSDIRECTION_LEFT_TWO_JAB,				//��µ����
	BOSSDIRECTION_LEFT_HIT,					//���ݴ���
	BOSSDIRECTION_LEFT_HIT2,				//�����ɸ��°��ݴ���
	BOSSDIRECTION_LEFT_DOWN,				//������
	BOSSDIRECTION_LEFT_COMBO_DOWN,			//���Ӱ��ݸ°�����
	BOSSDIRECTION_LEFT_DOWN_STAND,			//�������� �Ͼ

	//����
	BOSSDIRECTION_DEAD						//������
};


class enemy : public gameNode
{
protected:
	//
	ENEMYDIRECTION _enemyDirection;
	BOSSDIRECTION _bossDirection;

	//�̹����� ��ġ���� ��Ʈ�� HP����
	image* _imageEnemy;				//�̹���
	RECT _rcEnemy;					//��Ʈ
	RECT _CollircEnemy;				//�浹��Ʈ
	int _HP;						//ü��
	int _maxHP;						//�ִ�ü��
	int _speed;						//�ӵ�
	float _x, _y;						//xy�� (���� ��ǥ)
	float _ZMove;					//z����
	float _jump, _Gravity;			//����,�߷�

	int _countMove;					//ī��Ʈ ���� (AI ���� �ð�)

	int _rndDirX;					//X���⼳��
	int _rndDirY;					//Y���⼳��
	int _currentStage;				//���� �������� (������ �߿�! ������ 1�� xy�� ����������
									//�������� 2���ʹ� �ȿ����̴ϱ� �׶����� ����ó���� �޶����
									//������ �߿��ϴ�.

	int _rndTum;					//���� ��
	int _rndTum2;					//���� ��2

	float _traceAngle;


	float _enemyCenterX, _enemyCenterY;
	float _playerCenterX, _playerCenterY;

	animation* _enemyMotion;
	animation* _bossMotion;


	string _enemyKeyName[14];

	bool _isItemCollion;			//�������̶� �ε�����
	bool _isGetItemEnemy;			//�������� ������ �ִ� ���ʹ̴�?
	bool _isAttack;					//�÷��̾ �������̴�?
	bool _attackAniStart;			//���� �ִϸ��̼� ������
	bool _hittedAniStart;			//�´� �ִϸ��̼� ������
	bool _dieAniStart;
	
	int _isTracePlayer;				//�÷��̾ ������?
									// 0 �� ��Ʈ�� ���� // 1�� : �÷��� �߰� // 3�� : �÷��̾� ����

	bool _isLeft = true;					//�����Դϱ�?
	bool _isRight = true;

	bool _isHitted;				//�÷��̾� ���� �¾ҽ��ϱ�?

	int _countAttack = 0;				//����ī��Ʈ
	int _countHitted = 0;

	stage1* _stage1;

public:
	enemy();
	~enemy();

	virtual HRESULT init(POINT point, int currentStage = 1);
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

	animation* getBossMotion(void) { return _bossMotion; }
	void setBossMotion(animation* ani) { _bossMotion = ani; }


	void enemyMove();
	int rndDirection(int value);


	bool getIsGetItemEemey() { return _isGetItemEnemy; }

	void setIsTracePlayer(int isTracePlayer) { _isTracePlayer = isTracePlayer; }
	void setTraceAngle(float traceAngle) { _traceAngle= traceAngle; } //���� ���ϱ�
	float getTraceAngle() { return _traceAngle; }

	float getCenterX() { return  CAMERAMANAGER->CameraRelativePoint(_rcEnemy).x + _imageEnemy->getFrameWidth() / 2; }
	float getCenterY() { return  CAMERAMANAGER->CameraRelativePoint(_rcEnemy).y + _imageEnemy->getFrameHeight() / 2; }

	//���� ������ǥ ��ȯ
	float getAbsoluteX(){ return _x; }
	float getAbsoluteY(){ return _y; }


	void setPlayerCenterX(float playerCenterX) { _playerCenterX = playerCenterX; }
	void setPlayerCenterY(float playerCenterY) { _playerCenterY = playerCenterY; }

	int getCountMove() { return _countMove; }

	RECT getCollircEnemy(){ return _CollircEnemy; }
	void setIsItemCollion(bool isItemCollion){ _isItemCollion = isItemCollion; }

	void setStageMemoryLink(stage1* stage1){ _stage1 = stage1; }

	void setIsAttack(bool isAttack) { _isAttack = isAttack; }
	bool getIsAttack() { return _isAttack; }

	void setIsHitted(bool isHitted) { _isHitted = isHitted; }
	bool getIsHitted() { return _isHitted; }


	bool getIsRight() { return _isRight; }
	bool getIsLeft() { return _isLeft; }

	void setHP(int HP) { _HP = HP; }
	int getHP() { return _HP; }

	int getCountHitted() { return _countHitted; }
	int getIsTracePlayer() { return _isTracePlayer; }
};

//���� �ݹ��Լ��� �ʿ��� ��ǵ��̶���� �׷��� ���ؾߵɱ
//�� �߰��ؾߵɰ� ���������