#include "SoundManager.h"
#include "InputManager.h"

SoundManager* SoundManager::pInstance = nullptr;

SoundManager::SoundManager()
	: m_pSystem(nullptr)
	, volume(0.0f)
{
	//UINT		Version;
	//FMOD_RESULT Result;

	// ** FMOD를 생성
	FMOD::System_Create(&m_pSystem);

	// ** 버전 확인
	//m_pSystem->getVersion(&Version);

	// ** 32개의 채널을 갖겠다.
	if ( FMOD_OK != m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr) )
	{
		// ** Error Msg
		cout << "SoundManager::Initialize Error." << endl;
		return;
	}
}

SoundManager::~SoundManager()
{
	Release();
}

void SoundManager::Initialize()
{
	volume = 0.5f;

	SoundManager::GetInstance()->LoadSoundData(eSoundKey::BGM_MENU			, "../Resource/Sound/BGM/Menu.wav", true);
	SoundManager::GetInstance()->LoadSoundData(eSoundKey::BGM_STAGE			, "../Resource/Sound/BGM/Stage.wav", true);
	SoundManager::GetInstance()->LoadSoundData(eSoundKey::BGM_STAGE_BOSS	, "../Resource/Sound/BGM/Stage_Boss.wav", true);
	SoundManager::GetInstance()->LoadSoundData(eSoundKey::BGM_STAGE_CLEAR	, "../Resource/Sound/BGM/Stage_Clear.wav");
	SoundManager::GetInstance()->LoadSoundData(eSoundKey::BGM_GAMEOVER		, "../Resource/Sound/BGM/GameOver.wav");
	SoundManager::GetInstance()->LoadSoundData(eSoundKey::EFFECT_PLAYER_FIRE, "../Resource/Sound/Effect/PlayerFire.wav");
	SoundManager::GetInstance()->LoadSoundData(eSoundKey::EFFECT_PLAYER_BOMB, "../Resource/Sound/Effect/PlayerBomb.wav");
	SoundManager::GetInstance()->LoadSoundData(eSoundKey::EFFECT_PLAYER_DIE	, "../Resource/Sound/Effect/PlayerDie.wav");
	SoundManager::GetInstance()->LoadSoundData(eSoundKey::EFFECT_GET_ITEM	, "../Resource/Sound/Effect/GetItem.wav");
	SoundManager::GetInstance()->LoadSoundData(eSoundKey::EFFECT_EXPLOSION	, "../Resource/Sound/Effect/Explosion.wav");	
	SoundManager::GetInstance()->LoadSoundData(eSoundKey::EFFECT_WARNING	, "../Resource/Sound/Effect/Warning.wav");
	SoundManager::GetInstance()->LoadSoundData(eSoundKey::EFFECT_BOSS_FIRE	, "../Resource/Sound/Effect/BossFire.wav", true);
}

SoundInfo* SoundManager::GetSoundInfo(eSoundKey _key)
{
	SoundInfo* pSoundInfo = nullptr;

	if ( _key != eSoundKey::ALL )
	{
		// ** 사운드 탐색
		map<eSoundKey, SoundInfo*>::iterator iter = soundList.find(_key);
		if ( iter != soundList.end() )
		{
			pSoundInfo = iter->second;
		}
	}

	return pSoundInfo;
}

void SoundManager::LoadSoundData(eSoundKey _key, const char* _fileName, bool _bLoop)
{
	SoundInfo* pSoundInfo = GetSoundInfo(_key);
	if ( !pSoundInfo )
	{
		pSoundInfo = new SoundInfo;

		FMOD_MODE loopMode;
		if ( _bLoop )	loopMode = FMOD_LOOP_NORMAL;
		else 			loopMode = FMOD_LOOP_OFF;

		if ( FMOD_OK != m_pSystem->createSound(_fileName, loopMode, 0, &pSoundInfo->soundObj) )
		{
			// ** Error Msg
			cout << "SoundManager::LoadSoundData Error." << endl;
			return;
		}

		pSoundInfo->channelId = 0;
		pSoundInfo->soundObj->setMusicChannelVolume(pSoundInfo->channelId, 0.5f);

		soundList.insert(make_pair(_key, pSoundInfo));
	}
}

void SoundManager::Update()
{
	m_pSystem->update();

	if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_PLUS, eKeyInputState::DOWN) )
		SoundManager::GetInstance()->VolumeUp();

	if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_MINUS, eKeyInputState::DOWN) )
		SoundManager::GetInstance()->VolumeDown();
}

void SoundManager::Play(eSoundKey _key)
{
	if ( _key == eSoundKey::ALL )
		return;

	// ** 사운드 탐색
	SoundInfo* pSoundInfo = GetSoundInfo(_key);

	// ** 만약 찾는 사운드가 없다면
	if ( !pSoundInfo )
	{
		// ** Error Msg
		// ** 사운드 데이터가 없다는 메시지를 띄운 후 종료시킴
		cout << "SoundManager::OnPlaySound - Sound data does not exits." << endl;
		return;
	}

	// ** 사운드를 재생 시킴
	if ( FMOD_OK != m_pSystem->playSound(pSoundInfo->soundObj, 0, false, &pSoundInfo->soundChannel) )
	{
		cout << "SoundManager::OnPlaySound - playSound Error." << endl;
		return;
	}

	pSoundInfo->soundChannel->setVolume(volume);
}

void SoundManager::Pause(eSoundKey _key)
{
	if ( _key == eSoundKey::ALL )
	{
		// ** 전체 사운드
		for ( map<eSoundKey, SoundInfo*>::iterator iter = soundList.begin();
			iter != soundList.end(); ++iter )
		{
			iter->second->soundChannel->setPaused(true);
		}
	}
	else
	{
		// ** 사운드 탐색
		SoundInfo* pSoundInfo = GetSoundInfo(_key);
		if ( pSoundInfo )
		{
			pSoundInfo->soundChannel->setPaused(true);
		}
	}
}

void SoundManager::Resume(eSoundKey _key)
{
	if ( _key == eSoundKey::ALL )
	{
		// ** 전체 사운드
		for ( map<eSoundKey, SoundInfo*>::iterator iter = soundList.begin();
			iter != soundList.end(); ++iter )
		{
			iter->second->soundChannel->setPaused(false);
		}
	}
	else
	{
		// ** 사운드 탐색
		SoundInfo* pSoundInfo = GetSoundInfo(_key);
		if ( pSoundInfo )
		{
			pSoundInfo->soundChannel->setPaused(false);
		}
	}
}

void SoundManager::Stop(eSoundKey _key)
{
	if ( _key == eSoundKey::ALL )
	{
		// ** 전체 사운드
		for ( map<eSoundKey, SoundInfo*>::iterator iter = soundList.begin();
			iter != soundList.end(); ++iter )
		{
			iter->second->soundChannel->stop();
		}
	}
	else
	{
		// ** 사운드 탐색
		SoundInfo* pSoundInfo = GetSoundInfo(_key);
		if ( pSoundInfo )
		{
			pSoundInfo->soundChannel->stop();
		}
	}
}

void SoundManager::Release()
{
	for ( map<eSoundKey, SoundInfo*>::iterator iter = soundList.begin();
		iter != soundList.end(); )
	{
		SoundInfo* pSoundInfo = iter->second;
		pSoundInfo->soundObj->release();
		::Safe_Delete(pSoundInfo);

		soundList.erase(iter++);
	}
	soundList.clear();

	m_pSystem->release();
	m_pSystem->close();
}

void SoundManager::VolumeUp()
{	
	if ( volume < SOUND_VOLUME_MAX )
	{
		volume += SOUND_VOLUME;
		SetVolume();
	}
}

void SoundManager::VolumeDown()
{
	if ( volume > SOUND_VOLUME_MIN )
	{
		volume -= SOUND_VOLUME;
		SetVolume();
	}
}

void SoundManager::SetVolume()
{
	for ( map<eSoundKey, SoundInfo*>::iterator iter = soundList.begin();
		iter != soundList.end(); ++iter )
	{
		iter->second->soundChannel->setVolume(volume);
	}
}

bool SoundManager::IsPlaying(eSoundKey _key)
{
	bool isPlaying = false;

	if ( _key == eSoundKey::ALL )
	{
		for ( map<eSoundKey, SoundInfo*>::iterator iter = soundList.begin();
			iter != soundList.end(); ++iter )
		{
			// 하나라도 재생중이면 true 리턴
			iter->second->soundChannel->isPlaying(&isPlaying);
			if ( isPlaying )
			{
				break;
			}
		}
	}
	else
	{
		SoundInfo* pSoundInfo = GetSoundInfo(_key);
		if ( pSoundInfo )
		{
			pSoundInfo->soundChannel->isPlaying(&isPlaying);
		}
	}

	return isPlaying;
}