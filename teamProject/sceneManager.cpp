#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{

}

//friend ���� ��, �Լ� Ȥ�� Ŭ������ private���� �׳� ������ ������ ��.
//������ ���� ���̰� �Ǵµ� ��ü���� ����� �����ϰ� �ϴ°� ���� ��� �ƴϸ�
//�����ϸ� �ȵ�

DWORD CALLBACK loadingThread(LPVOID prc)
{
	//�غ��� ���� �̸� �ʱ�ȭ ���ѵд�
	sceneManager::_readyScene->init();

	//�غ�� ���� ��������� ��ü�Ѵ�
	sceneManager::_currentScene = sceneManager::_readyScene;

	//�ε��� ���� ���� �����Ѵ�
	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	return 0;
}

gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadingScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

HRESULT sceneManager::init(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;
	
	return S_OK;
}

void sceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for ( ; miSceneList != _mSceneList.end(); )
	{
		if ( miSceneList->second != NULL )
		{
			if ( miSceneList->second == _currentScene ) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void sceneManager::update(void)	
{
	if ( _currentScene ) _currentScene->update();
}

void sceneManager::render(void)	
{
	if ( _currentScene ) _currentScene->render();
}


//�� �߰� ���� �Լ�
gameNode* sceneManager::addScene(string sceneName, gameNode* scene)				 
{
	//���� ���ٸ� �ΰ� ��ȯ
	if ( !scene ) return NULL;

	//���̸� �� �ش� ���� �ʿ� �ִ´�
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

gameNode* sceneManager::addLoadingScene(string loadingSceneName, gameNode* scene)
{
	//���� ���ٸ� �ΰ� ��ȯ
	if ( !scene ) return NULL;

	//���̸� �� �ش� ���� �ʿ� �ִ´�
	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}


//�� ����
HRESULT sceneManager::changeScene(string sceneName)							
{
	//���ͷ����Ϳ� ã�����ϴ� ���� Ű���� �ְ�
	mapSceneIter find = _mSceneList.find(sceneName);

	//��ã�Ҵٸ� �����ߴٰ� �˸���
	if ( find == _mSceneList.end() ) return E_FAIL;

	//���࿡ ã�� ���� ���� ���� �����ϸ� �ٲ��� �ʴ´�
	if ( find->second == _currentScene ) return S_OK;

	//���� �ٲٷ��� ���� '������'���� �ٲ���ٸ� init�Լ��� ȣ���Ѵ�
	if ( SUCCEEDED(find->second->init()) )
	{
		//���� ��(�ٸ����� �ִٸ�) �ش���� �����ְ�
		if ( _currentScene ) _currentScene->release();
		//�ٲٷ��� ������ ���� �ٲ��ش�
		_currentScene = find->second;

		//�� �κ��� ���߿� ������ �Ը��� ���� �ٲ� �ʿ䰡 �ִ�.
		//���� ������ ���࿡ ��������1���� � DB �ڷḦ �����ϰ�
		//���� �ٲٷ��� �ϸ� ����� ���� ȣ���� �Ǳ⶧����
		//������ �Ѿ���� �ʴ� �����̴�. 

		return S_OK;
	}

	return E_FAIL;
}

//���߿� �� �����غ��� ���� �ſ� �ʷ� ���ߴ�
HRESULT sceneManager::changeScene(string sceneName, string loadingSceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	if ( find == _mSceneList.end() ) return E_FAIL;
	if ( find->second == _currentScene ) return S_OK;

	//�ε��Ϸ��� ���� ã�´�
	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	if ( find == _mLoadingSceneList.end() ) return changeScene(loadingSceneName);

	if ( SUCCEEDED(find->second->init()) )
	{
		if ( _currentScene ) _currentScene->release();

		_loadingScene = findLoading->second;
		_readyScene = find->second;
		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadingThreadID));
	}

	return E_FAIL;
}


