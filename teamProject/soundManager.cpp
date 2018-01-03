#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
{
}


soundManager::~soundManager()
{

}

HRESULT soundManager::init(void)
{
	//FMOD SOUND 엔진시스템 초기화
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);
	memset(_channel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);

	_currentBgm = "keyName";

	return S_OK;
}

void soundManager::release(void)
{

}

void soundManager::update(void)	
{

}


void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if ( loop )
	{
		if ( bgm )
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		if ( bgm )
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
	}

	_listSounds.insert(make_pair(keyName, _mTotalSounds.size()));
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}


void soundManager::play(string keyName, float volume) //0.0 ~ 1.0f
{
	arrSoundsIter iter = _mTotalSounds.begin();

	for ( iter; iter != _mTotalSounds.end(); ++iter)
	{
		if ( keyName == iter->first )
		{
			_listSoundsIter = _listSounds.find(keyName);
			_system->playSound(FMOD_CHANNEL_FREE, _sound[_listSoundsIter->second], false, &_channel[_listSoundsIter->second]);

			_channel[_listSoundsIter->second]->setVolume(volume);

			break;
		}
	}

}

void soundManager::stop(string keyName)	 
{
	arrSoundsIter iter = _mTotalSounds.begin();

	for ( iter; iter != _mTotalSounds.end(); ++iter)
	{
		if ( keyName == iter->first )
		{
			_listSoundsIter = _listSounds.find(keyName);
			_channel[_listSoundsIter->second]->stop();
			break;
		}
	}

}

void soundManager::pause(string keyName) 
{
	arrSoundsIter iter = _mTotalSounds.begin();

	for ( iter; iter != _mTotalSounds.end(); ++iter )
	{
		if ( keyName == iter->first )
		{
			_listSoundsIter = _listSounds.find(keyName);
			_channel[_listSoundsIter->second]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	for ( iter; iter != _mTotalSounds.end(); ++iter )
	{
		if ( keyName == iter->first )
		{
			_listSoundsIter = _listSounds.find(keyName);
			_channel[_listSoundsIter->second]->setPaused(false);
			break;
		}
	}
}


//사운드 이벤트 처리용
bool soundManager::isPlaySound(string keyName) 
{
	bool isPlay;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for ( iter; iter != _mTotalSounds.end(); ++iter, count++ )
	{
		if ( keyName == iter->first )
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for ( iter; iter != _mTotalSounds.end(); ++iter, count++ )
	{
		if ( keyName == iter->first )
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}
