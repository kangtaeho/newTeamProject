#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

//gameNode Ŭ������ ���漱������!
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;	//���� ��
	static gameNode* _loadingScene;	//�ε� ��
	static gameNode* _readyScene;	//��� ��(�ε��� ������ �ٲ� ���̶����)

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadingThreadID;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�� �߰� ���� �Լ�
	gameNode* addScene(string sceneName, gameNode* scene);
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//�� ����
	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);

	friend DWORD CALLBACK loadingThread(LPVOID prc);



	sceneManager();
	~sceneManager();
};

