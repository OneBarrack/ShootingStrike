#include "BossAngelEnemy.h"
#include "Object.h"
#include "BitmapManager.h"
#include "SpawnManager.h"
#include "InputManager.h"

BossAngelEnemy::BossAngelEnemy()
	: AnimType(AnimationType::DEFAULT)
{
}

BossAngelEnemy::~BossAngelEnemy()
{
	Release();
}


void BossAngelEnemy::Initialize()
{
	Key = eBridgeKey::ENEMY_BOSS;

	AnimType = AnimationType::DEFAULT;
}

void BossAngelEnemy::Update()
{
	// ** Owner의 데이터를 받아옴
	ReceiveInfoFromOwner();

	static int PatternIndex = 0;
	static int ActiveCount = 0;	
	static ULONGLONG ActiveTime = GetTickCount64();

	if ( CheckKeyInputState(eInputKey::KEY_LBUTTON, eKeyInputState::DOWN) )
	{
		PatternIndex = 1;
		ActiveCount = 1;
		ActiveTime = GetTickCount64();
	}

	switch ( PatternIndex )
	{
		case 1:
		{
			int MaxActiveCount = 50;

			// ** Level 만큼 총알 숫자를 늘리고, 상방 기준 총알 간 간격에 대한 각도를 설정하여
			// ** 부채꼴 형태로 발사되도록 한다.
			// ** angleGap : 총알간 간격 각도

			int AngleGap = 30;
			if ( ActiveTime + 50 < GetTickCount64() )
			{				
				int BulletCount = 360 / AngleGap;				
				for ( int i = 0; i < BulletCount; ++i )
				{
					// ** 상방 기준 현재 각도
					int Angle = AngleGap * i + (ActiveCount * 7);

					// ** Bullet의 TransInfo 설정
					Transform BulletTransInfo;
					BulletTransInfo.Position = TransInfo.Position;
					BulletTransInfo.Scale = Vector3(10.0f, 10.0f);
					BulletTransInfo.Direction = Vector3(cosf(Angle * PI / 180), -sinf(Angle * PI / 180));

					// ** Bullet의 Speed 설정
					float BulletSpeed = 3.0f;

					// ** Bullet Spawn
					SpawnManager::SpawnBullet(pOwner, BulletTransInfo, BulletSpeed, 1, eBulletFiringType::NORMAL);
				}
								
				ActiveTime = GetTickCount64();
				++ActiveCount;
			}
			if ( MaxActiveCount < ActiveCount )
			{
				PatternIndex = 0;
			}
			break;
		}
		default:
			ActiveTime = 0;
			break;
	}

	//TransInfo.Position.x += TransInfo.Direction.x * Speed;
	//TransInfo.Position.y += TransInfo.Direction.y * Speed;

	// ** Owner로 가공된 데이터 전달
	SendInfoToOwner();
}


void BossAngelEnemy::Render(HDC _hdc)
{
	if ( !pImage )
		return;

	switch ( AnimType )
	{
		case AnimationType::DEFAULT:	PlayAnimDefault(_hdc);	 break;
		case AnimationType::ATTACK1:	PlayAnimAttack1(_hdc);	 break;
		case AnimationType::ATTACK2:	PlayAnimAttack2(_hdc);	 break;
		case AnimationType::ATTACK3:	PlayAnimAttack3(_hdc);	 break;
		case AnimationType::EVOLUTION:	PlayAnimEvolution(_hdc); break;
		case AnimationType::ATTACKED: break;
		default:
			break;
	}	
}

void BossAngelEnemy::Release()
{

}

void BossAngelEnemy::PlayAnimDefault(HDC _hdc)
{
	static ULONGLONG Time = GetTickCount64();
	static int Offset = 0;
	int MaxSegmentCount = 6; // ** 해당 라인에서 분할된 이미지 수
	int Delay = 200;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * Offset),
		(int)(pImage->GetSegmentationScale().y * static_cast<int>(AnimType)),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(147, 187, 236));

	// ** Delay 시간 주기로 Offset 증가
	if ( Time + Delay < GetTickCount64() )
	{
		if ( ++Offset == MaxSegmentCount )
			Offset = 0;

		Time = GetTickCount64();
	}
	
}

void BossAngelEnemy::PlayAnimAttack1(HDC _hdc)
{
	static ULONGLONG Time = GetTickCount64();
	static int Offset = 0;
	static bool bRepeatSection = false; // ** 일정 구간이 반복되고 있는 타이밍인지
	int MaxSegmentCount = 6;			// ** 해당 라인에서 분할된 이미지 수	
	int Delay = 200;

	// ** Ready 타이밍
	static ULONGLONG ReadyTime = 0;
	int ReadyDurationTime = 1000;
	int ReadySectionStart = 0;
	int ReadySectionEnd = 1;

	// ** Fire 타이밍
	static ULONGLONG FireTime = 0;
	int FireDurationTime = 2000;
	int FireSectionStart = 2;
	int FireSectionEnd = 5;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * Offset),
		(int)(pImage->GetSegmentationScale().y * static_cast<int>(AnimType)),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(147, 187, 236));

	// ** Ready 시작 구간 진입
	if ( !bRepeatSection && Offset == ReadySectionStart )
	{
		// ** Ready 시작 타임 설정
		ReadyTime = GetTickCount64();
	}

	// ** Fire 시작 구간 진입
	if ( !bRepeatSection && Offset == FireSectionStart )
	{
		// ** Fire 시작 타임 설정
		FireTime = GetTickCount64();
	}

	// ** Ready 종료 구간 진입
	if ( Offset == ReadySectionEnd )
	{
		// ** 구간 반복 스타트
		bRepeatSection = true;

		// ** Ready 구간반복 지속시간이 끝났는지 체크
		if ( ReadyTime + ReadyDurationTime < GetTickCount64() )
		{
			// ** 구간 반복 종료
			bRepeatSection = false;

			// ** 구간을 넘김 ( 종료지점의 다음 Offset으로 설정 )
			Offset = ReadySectionEnd + 1;
		}
	}
	// ** Fire 종료 구간 진입
	else if ( Offset == FireSectionEnd )
	{
		// ** 구간 반복 스타트
		bRepeatSection = true;

		// ** Fire 구간반복 지속시간이 끝났는지 체크
		if ( FireTime + FireDurationTime < GetTickCount64() )
		{
			// ** 구간 반복 종료
			bRepeatSection = false;

			// ** 마지막 구간이므로 Offset을 가장 처음으로 리셋
			Offset = 0;
		}
		else
		{
			// ** 반복을 위해 Fire 스타트 지점으로 리셋
			Offset = FireSectionStart;
		}
	}
	// ** 반복구간 종료지점이 아니라면
	else
	{
		// ** Delay 시간 주기로 Offset 증가
		if ( Time + Delay < GetTickCount64() )
		{
			++Offset;

			Time = GetTickCount64();
		}
	}
}

void BossAngelEnemy::PlayAnimAttack2(HDC _hdc)
{
}

void BossAngelEnemy::PlayAnimAttack3(HDC _hdc)
{
}

void BossAngelEnemy::PlayAnimEvolution(HDC _hdc)
{
}
