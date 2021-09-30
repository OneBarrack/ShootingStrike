#include "BossAngelEnemy.h"
#include "Object.h"
#include "BitmapManager.h"
#include "SpawnManager.h"
#include "InputManager.h"

BossAngelEnemy::BossAngelEnemy()
	: AnimType(AnimationType::DEFAULT)
	, bLoopPlayAnim(false)
{
}

BossAngelEnemy::~BossAngelEnemy()
{
	
}


void BossAngelEnemy::Initialize()
{
	Key = eBridgeKey::ENEMY_BOSS;

	AnimType = AnimationType::DEFAULT;
	bLoopPlayAnim = false;
}

void BossAngelEnemy::Update()
{
	// ** Owner의 데이터를 받아옴
	ReceiveInfoFromOwner();

	static int PatternIndex = 0;
	static int ActiveCount = 0;	
	static ULONGLONG ActiveTime = GetTickCount64();

	// _Debug_
	if ( CheckKeyInputState(eInputKey::KEY_LBUTTON, eKeyInputState::DOWN) )
	{
		PatternIndex = 1;
		ActiveCount = 1;
		ActiveTime = GetTickCount64();

		static int TypeIndex = 0;
		if ( TypeIndex == static_cast<int>(AnimationType::EVOLUTION) )
			TypeIndex = 0;
		else
			TypeIndex++;
			
		PlayAnimation(static_cast<AnimationType>(TypeIndex), false);
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

	static AnimationType OldAnimType = AnimationType::DEFAULT;
	static ULONGLONG Time = GetTickCount64();
	static int Offset = 0;
	bool bFinishPlay = false;

	// ** 이전에 그리던 Animation과 현재 Animation이 다를때,
	// ** 즉 새로운 Animation이 플레이 되는 시점에 초기화
	if ( OldAnimType != AnimType )
	{
		OldAnimType = AnimType;
		Time = GetTickCount64();
		Offset = 0;		
	}

	switch ( AnimType )
	{
		case AnimationType::DEFAULT:	PlayAnimDefault(_hdc, Time, Offset);	break;
		case AnimationType::ATTACK1:	PlayAnimAttack1(_hdc, Time, Offset);	break;
		case AnimationType::ATTACK2:	PlayAnimAttack2(_hdc, Time, Offset);	break;
		case AnimationType::ATTACK3:	PlayAnimAttack3(_hdc, Time, Offset);	break;
		case AnimationType::EVOLUTION:	PlayAnimEvolution(_hdc, Time, Offset);	break;
		case AnimationType::ATTACKED: break;
		default:
			break;
	}
}

void BossAngelEnemy::Release()
{

}

void BossAngelEnemy::PlayAnimation(AnimationType _AnimType, bool _bLoop)
{
	AnimType = _AnimType;
	bLoopPlayAnim = _bLoop;
}

void BossAngelEnemy::PlayAnimDefault(HDC _hdc, ULONGLONG& _Time, int& _Offset)
{
	int MaxSegmentCount = 6; // ** 해당 라인에서 분할된 이미지 수
	int Delay = 200;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * _Offset),
		(int)(pImage->GetSegmentationScale().y * static_cast<int>(AnimType)),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(147, 187, 236));

	// ** Delay 시간 주기로 Offset 증가
	if ( _Time + Delay < GetTickCount64() )
	{
		// ** Default는 항상 Loop 상태이므로 Offset을 0으로 세팅
		if ( ++_Offset == MaxSegmentCount )
			_Offset = 0;

		_Time = GetTickCount64();
	}	
}

void BossAngelEnemy::PlayAnimAttack1(HDC _hdc, ULONGLONG& _Time, int& _Offset)
{
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
	int FireSectionEnd = MaxSegmentCount - 1;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * _Offset),
		(int)(pImage->GetSegmentationScale().y * static_cast<int>(AnimType)),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(147, 187, 236));

	// ** Ready 시작 구간 진입
	if ( !bRepeatSection && _Offset == ReadySectionStart )
	{
		// ** Ready 시작 타임 설정
		ReadyTime = GetTickCount64();
	}

	// ** Fire 시작 구간 진입
	if ( !bRepeatSection && _Offset == FireSectionStart )
	{
		// ** Fire 시작 타임 설정
		FireTime = GetTickCount64();
	}

	// ** Ready 종료 구간 진입
	if ( _Offset == ReadySectionEnd )
	{
		// ** 구간 반복 스타트
		bRepeatSection = true;

		// ** Ready 구간반복 지속시간이 끝났는지 체크
		if ( ReadyTime + ReadyDurationTime < GetTickCount64() )
		{
			// ** 구간 반복 종료
			bRepeatSection = false;

			// ** 구간을 넘김 ( 종료지점의 다음 Offset으로 설정 )
			_Offset = ReadySectionEnd + 1;
		}
	}
	// ** Fire 종료 구간 진입
	else if ( _Offset == FireSectionEnd )
	{
		// ** 구간 반복 스타트
		bRepeatSection = true;

		// ** Fire 구간반복 지속시간이 끝났는지 체크
		if ( FireTime + FireDurationTime < GetTickCount64() )
		{
			// ** 구간 반복 종료
			bRepeatSection = false;

			// ** Loop중이라면 Offset을 다시 0으로 세팅하고 아니라면 Default Animation을 Play 시킨다 
			if ( bLoopPlayAnim )
				_Offset = 0;
			else
				PlayAnimation(AnimationType::DEFAULT, true);
		}
		else
		{
			// ** 반복을 위해 Fire 스타트 지점으로 리셋
			_Offset = FireSectionStart;
		}
	}
	// ** 반복구간 종료지점이 아니라면
	else
	{
		// ** Delay 시간 주기로 Offset 증가
		if ( _Time + Delay < GetTickCount64() )
		{
			++_Offset;

			_Time = GetTickCount64();
		}
	}
}

void BossAngelEnemy::PlayAnimAttack2(HDC _hdc, ULONGLONG& _Time, int& _Offset)
{
	static bool bRepeatSection = false; // ** 일정 구간이 반복되고 있는 타이밍인지
	int MaxSegmentCount = 5;			// ** 해당 라인에서 분할된 이미지 수	
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
	int FireSectionEnd = MaxSegmentCount - 1;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * _Offset),
		(int)(pImage->GetSegmentationScale().y * static_cast<int>(AnimType)),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(147, 187, 236));

	// ** Ready 시작 구간 진입
	if ( !bRepeatSection && _Offset == ReadySectionStart )
	{
		// ** Ready 시작 타임 설정
		ReadyTime = GetTickCount64();
	}

	// ** Fire 시작 구간 진입
	if ( !bRepeatSection && _Offset == FireSectionStart )
	{
		// ** Fire 시작 타임 설정
		FireTime = GetTickCount64();
	}

	// ** Ready 종료 구간 진입
	if ( _Offset == ReadySectionEnd )
	{
		// ** 구간 반복 스타트
		bRepeatSection = true;

		// ** Ready 구간반복 지속시간이 끝났는지 체크
		if ( ReadyTime + ReadyDurationTime < GetTickCount64() )
		{
			// ** 구간 반복 종료
			bRepeatSection = false;

			// ** 구간을 넘김 ( 종료지점의 다음 Offset으로 설정 )
			_Offset = ReadySectionEnd + 1;
		}
	}
	// ** Fire 종료 구간 진입
	else if ( _Offset == FireSectionEnd )
	{
		// ** 구간 반복 스타트
		bRepeatSection = true;

		// ** Fire 구간반복 지속시간이 끝났는지 체크
		if ( FireTime + FireDurationTime < GetTickCount64() )
		{
			// ** 구간 반복 종료
			bRepeatSection = false;

			// ** Loop중이라면 Offset을 다시 0으로 세팅하고 아니라면 Default Animation을 Play 시킨다 
			if ( bLoopPlayAnim )
				_Offset = 0;
			else
				PlayAnimation(AnimationType::DEFAULT, true);
		}
		else
		{
			// ** 반복을 위해 Fire 스타트 지점으로 리셋
			_Offset = FireSectionStart;
		}
	}
	// ** 반복구간 종료지점이 아니라면
	else
	{
		// ** Delay 시간 주기로 Offset 증가
		if ( _Time + Delay < GetTickCount64() )
		{
			++_Offset;

			_Time = GetTickCount64();
		}
	}
}

void BossAngelEnemy::PlayAnimAttack3(HDC _hdc, ULONGLONG& _Time, int& _Offset)
{
	static bool bRepeatSection = false; // ** 일정 구간이 반복되고 있는 타이밍인지
	int MaxSegmentCount = 4;			// ** 해당 라인에서 분할된 이미지 수	
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
	int FireSectionEnd = MaxSegmentCount - 1;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * _Offset),
		(int)(pImage->GetSegmentationScale().y * static_cast<int>(AnimType)),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(147, 187, 236));

	// ** Ready 시작 구간 진입
	if ( !bRepeatSection && _Offset == ReadySectionStart )
	{
		// ** Ready 시작 타임 설정
		ReadyTime = GetTickCount64();
	}

	// ** Fire 시작 구간 진입
	if ( !bRepeatSection && _Offset == FireSectionStart )
	{
		// ** Fire 시작 타임 설정
		FireTime = GetTickCount64();
	}

	// ** Ready 종료 구간 진입
	if ( _Offset == ReadySectionEnd )
	{
		// ** 구간 반복 스타트
		bRepeatSection = true;

		// ** Ready 구간반복 지속시간이 끝났는지 체크
		if ( ReadyTime + ReadyDurationTime < GetTickCount64() )
		{
			// ** 구간 반복 종료
			bRepeatSection = false;

			// ** 구간을 넘김 ( 종료지점의 다음 Offset으로 설정 )
			_Offset = ReadySectionEnd + 1;
		}
	}
	// ** Fire 종료 구간 진입
	else if ( _Offset == FireSectionEnd )
	{
		// ** 구간 반복 스타트
		bRepeatSection = true;

		// ** Fire 구간반복 지속시간이 끝났는지 체크
		if ( FireTime + FireDurationTime < GetTickCount64() )
		{
			// ** 구간 반복 종료
			bRepeatSection = false;

			// ** Loop중이라면 Offset을 다시 0으로 세팅하고 아니라면 Default Animation을 Play 시킨다 
			if ( bLoopPlayAnim )
				_Offset = 0;
			else
				PlayAnimation(AnimationType::DEFAULT, true);
		}
		else
		{
			// ** 반복을 위해 Fire 스타트 지점으로 리셋
			_Offset = FireSectionStart;
		}
	}
	// ** 반복구간 종료지점이 아니라면
	else
	{
		// ** Delay 시간 주기로 Offset 증가
		if ( _Time + Delay < GetTickCount64() )
		{
			++_Offset;

			_Time = GetTickCount64();
		}
	}
}

void BossAngelEnemy::PlayAnimEvolution(HDC _hdc, ULONGLONG& _Time, int& _Offset)
{
	int MaxSegmentCount = 8; // ** 해당 라인에서 분할된 이미지 수
	int Delay = 200;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * _Offset),
		(int)(pImage->GetSegmentationScale().y * static_cast<int>(AnimType)),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(147, 187, 236));

	// ** Delay 시간 주기로 Offset 증가
	if ( _Time + Delay < GetTickCount64() )
	{
		if ( ++_Offset == MaxSegmentCount )
		{
			// ** Loop중이라면 Offset을 다시 0으로 세팅하고 아니라면 Default Animation을 Play 시킨다 
			if ( bLoopPlayAnim ) 
				_Offset = 0;
			else
				PlayAnimation(AnimationType::DEFAULT, true);
		}
		_Time = GetTickCount64();
	}
}

void BossAngelEnemy::PlayAnimAttacked(HDC _hdc, ULONGLONG& _Time, int& _Offset)
{
	int MaxSegmentCount = 1; // ** 해당 라인에서 분할된 이미지 수
	int Delay = 200;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * _Offset),
		(int)(pImage->GetSegmentationScale().y * static_cast<int>(AnimType)),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(147, 187, 236));

	// ** Delay 시간 주기로 Offset 증가
	if ( _Time + Delay < GetTickCount64() )
	{
		// ** Default는 항상 Loop 상태이므로 Offset을 0으로 세팅
		if ( ++_Offset == MaxSegmentCount )
		{
			if ( bLoopPlayAnim )
				_Offset = 0;
			else
				PlayAnimation(AnimationType::DEFAULT, true);
		}

		_Time = GetTickCount64();
	}
}
