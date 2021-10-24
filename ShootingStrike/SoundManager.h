#pragma once
#include "Headers.h"

class SoundManager
{
private:
	static SoundManager* pInstance;
public:
	static SoundManager* GetInstance()
	{
		if ( pInstance == nullptr )
			pInstance = new SoundManager;

		return pInstance;
	}

private:
	FMOD::System* m_pSystem;
	map<eSoundKey, SoundInfo*> soundList;

	float volume;

public:
	void Initialize();	
	void Update();
	void Release();

	void Play(eSoundKey _key);
	void Pause(eSoundKey _key);
	void Resume(eSoundKey _key);
	void Stop(eSoundKey _key);
	void VolumeUp();
	void VolumeDown();

	bool IsPlaying(eSoundKey _key);

private:
	SoundInfo* GetSoundInfo(eSoundKey _key);
	void LoadSoundData(eSoundKey _key, const char* _fileName, bool _bLoop = false);
	void SetVolume();

private:
	SoundManager();
public:
	~SoundManager();
};

/*
프로젝트 - 속성 - VC++ 디렉터리
 - 포함 디렉터리(inluce) - 편집 - FMOD폴더 - api폴더 - core -  inc폴더
 - 라이브러리 디렉터리(library) - api폴더 - core - lib - x86폴더

include.h -> #pragma comment(lib, "fmod_vc.lib")

lib x86 폴더 내 fmod.dll 복사 - 프로젝트 경로에 바로 붙여넣기

*/
