#pragma once
#include "singletonBase.h"
#include <map>

#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class soundManager : public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**>			arrSounds;
	typedef map<string, Sound**>::iterator	arrSoundsIter;
	typedef map<string, Channel**>			arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;
	
private:
	map<string, int> _listSounds;
	map<string, int>::iterator _listSoundsIter;

	System*		_system;
	Sound**		_sound;
	Channel**	_channel;

	arrSounds	_mTotalSounds;

public:
	soundManager();
	~soundManager();

	HRESULT init(void);
	void release(void);
	void update(void);

	void addSound(string keyName, string soundName, bool bgm, bool loop);
	
	void play(string keyName, float volume = 1.0f); //0.0 ~ 1.0f
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);
	
	//사운드 이벤트 처리용
	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

};

