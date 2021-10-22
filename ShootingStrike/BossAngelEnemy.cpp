#include "BossAngelEnemy.h"
#include "Object.h"
#include "Enemy.h"
#include "BitmapManager.h"
#include "SpawnManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "Background.h"
#include "MathManager.h"

BossAngelEnemy::BossAngelEnemy()
	: pBackground(nullptr)
	, curPhase(1)
	, animType(eBossAnimationType::DEFAULT)
	, bLoopPlayAnim(false)
	, prevActionCompleteTime(0)
	, actionState(eActionState::READY)
{
}

BossAngelEnemy::~BossAngelEnemy()
{
	
}


void BossAngelEnemy::Initialize()
{
	Super::Initialize();

	key = eBridgeKey::ENEMY_BOSS;

	curPhase = 1;
	animType = eBossAnimationType::DEFAULT;
	isSpawing = true;
	bLoopPlayAnim = false;

	pBackground = static_cast<Background*>(
		ObjectManager::GetInstance()->FindObjectWithTag(eTagName::STAGE_MAIN_BKG));
	spawnStartPos.x = pBackground->GetPosition().x;
	spawnStartPos.y = (pBackground->GetPosition().y - (pBackground->GetScale().y * 0.5f));
	spawnDestPos.x = spawnStartPos.x;
	spawnDestPos.y = (pBackground->GetPosition().y - (pBackground->GetScale().y * 0.5f)) + 150;

	prevActionCompleteTime = GetTickCount64();
	actionState = eActionState::READY;

	InitActionInfo();
}

void BossAngelEnemy::Update()
{
	// ** Owner의 데이터를 받아옴
	ReceiveInfoFromOwner();

	Super::Update();	
	
	// Phase 체크
	CheckPhase();

	// 스폰 중
	if ( isSpawing )
	{
		static bool bSpawnStart = true;

		// ** Spawn이 시작될 때 Spawn Start 위치로 이동 시킨다
		if ( bSpawnStart )
		{
			// ** 스폰중일 시 무적상태 (충돌 비활성화)
			static_cast<Enemy*>(pOwner)->SetGenerateCollisionEvent(false);

			transInfo.Position.x = spawnStartPos.x;
			transInfo.Position.y = spawnStartPos.y;
			transInfo.Direction = MathManager::GetDirection(spawnStartPos, spawnDestPos);

			bSpawnStart = false;
		}

		// ** 이동 속도
		float moveSpeed = 0.5f;

		// ** 화면 위에서부터 일정 위치까지 서서히 내려가도록
		if ( transInfo.Position.y + moveSpeed < spawnDestPos.y )
		{
			transInfo.Position.x += transInfo.Direction.x * moveSpeed;
			transInfo.Position.y += transInfo.Direction.y * moveSpeed;
		}
		// ** 멈출 위치에 도달
		else
		{
			// ** spawnDestPos로 위치 설정 및 Direction 0,0 로 변경
			transInfo.Position = spawnDestPos;
			transInfo.Direction = Vector3(0.0f, 0.0f);
			isSpawing = false;
			bSpawnStart = true;

			prevActionCompleteTime = GetTickCount64();

			// ** 스폰이 끝나면 충돌을 활성화 시켜준다
			static_cast<Enemy*>(pOwner)->SetGenerateCollisionEvent(true);
		}
	}
	else
	{
		// ** Action Info가 있으면 수행
		if ( !actionInfos.empty() )
		{
			eActionType actionType = actionInfos.front().first;
			float delay = actionInfos.front().second;		

			switch ( actionState )
			{
				case eActionState::READY:
					if ( prevActionCompleteTime + delay < GetTickCount64() )
					{
						Action(actionType);
						actionState = eActionState::WORKING;
					}
					break;
				case eActionState::WORKING:
					Action(actionType);
					break;
				case eActionState::END:
					prevActionCompleteTime = GetTickCount64();
					actionInfos.pop();

					actionState = eActionState::READY;
					break;
			}
		}
		else
		{
			// ** Action Info가 없으면 초기화 패턴 반복
			InitActionInfo();
		}
	}

	// 충돌체 조정
	collider.Position = Vector3(transInfo.Position.x, transInfo.Position.y + (transInfo.Scale.y * 0.2f));
	collider.Scale = Vector3(transInfo.Scale.x * 0.4f, transInfo.Scale.y * 0.5f);

	// ** Owner로 가공된 데이터 전달
	SendInfoToOwner();

	bulletScript.Run();
}


void BossAngelEnemy::Render(HDC _hdc)
{
	Super::Render(_hdc);
	if ( !pImage )
		return;

	static eBossAnimationType oldAnimType = eBossAnimationType::DEFAULT;
	static ULONGLONG time = GetTickCount64();
	static int offset = 0;
	bool bFinishPlay = false;

	// ** 이전에 그리던 Animation과 현재 Animation이 다를때,
	// ** 즉 새로운 Animation이 플레이 되는 시점에 초기화
	if ( oldAnimType != animType )
	{
		oldAnimType = animType;
		time = GetTickCount64();
		offset = 0;		
	}

	switch ( animType )
	{
		case eBossAnimationType::DEFAULT:	PlayAnimDefault(_hdc, time, offset);	break;
		case eBossAnimationType::ATTACK1:	PlayAnimAttack1(_hdc, time, offset);	break;
		case eBossAnimationType::ATTACK2:	PlayAnimAttack2(_hdc, time, offset);	break;
		case eBossAnimationType::ATTACK3:	PlayAnimAttack3(_hdc, time, offset);	break;
		case eBossAnimationType::EVOLUTION:	PlayAnimEvolution(_hdc, time, offset);	break;
		case eBossAnimationType::ATTACKED: break;
		default:
			break;
	}
}

void BossAngelEnemy::Release()
{
	Super::Release();
}

void BossAngelEnemy::PlayAnimation(eBossAnimationType _AnimType, bool _bLoop)
{
	animType = _AnimType;
	bLoopPlayAnim = _bLoop;
}

void BossAngelEnemy::PlayAnimDefault(HDC _hdc, ULONGLONG& _time, int& _offset)
{
	int maxSegmentCount = 6; // ** 해당 라인에서 분할된 이미지 수
	int delay = 200;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * _offset),
		(int)(pImage->GetSegmentationScale().y * static_cast<int>(animType)),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(147, 187, 236));

	// ** Delay 시간 주기로 Offset 증가
	if ( _time + delay < GetTickCount64() )
	{
		// ** Default는 항상 Loop 상태이므로 Offset을 0으로 세팅
		if ( ++_offset == maxSegmentCount )
			_offset = 0;

		_time = GetTickCount64();
	}	
}

void BossAngelEnemy::PlayAnimAttack1(HDC _hdc, ULONGLONG& _time, int& _offset)
{
	static bool bRepeatSection = false; // ** 일정 구간이 반복되고 있는 타이밍인지
	int maxSegmentCount = 6;			// ** 해당 라인에서 분할된 이미지 수	
	int delay = 200;

	// ** Ready 타이밍
	static ULONGLONG readyTime = 0;
	int readyDurationTime = 1000;
	int readySectionStart = 0;
	int readySectionEnd = 1;

	// ** Fire 타이밍
	static ULONGLONG fireTime = 0;
	int fireDurationTime = 2000;
	int fireSectionStart = 2;
	int fireSectionEnd = maxSegmentCount - 1;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * _offset),
		(int)(pImage->GetSegmentationScale().y * static_cast<int>(animType)),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(147, 187, 236));

	// ** Delay 시간 주기로 Offset 적용
	if ( _time + delay < GetTickCount64() )
	{
		_time = GetTickCount64();

		// ** Ready 시작 구간 진입
		if ( !bRepeatSection && _offset == readySectionStart )
		{
			// ** Ready 시작 타임 설정
			readyTime = GetTickCount64();
		}

		// ** Fire 시작 구간 진입
		if ( !bRepeatSection && _offset == fireSectionStart )
		{
			// ** Fire 시작 타임 설정
			fireTime = GetTickCount64();
		}

		// ** Ready 종료 구간 진입
		if ( _offset == readySectionEnd )
		{
			// ** 구간 반복 스타트
			bRepeatSection = true;

			// ** Ready 구간반복 지속시간이 끝났는지 체크
			if ( readyTime + readyDurationTime < GetTickCount64() )
			{
				// ** 구간 반복 종료
				bRepeatSection = false;

				// ** 구간을 넘김 ( 종료지점의 다음 Offset으로 설정 )
				_offset = readySectionEnd + 1;
			}
		}
		// ** Fire 종료 구간 진입
		else if ( _offset == fireSectionEnd )
		{
			// ** 구간 반복 스타트
			bRepeatSection = true;

			// ** Fire 구간반복 지속시간이 끝났는지 체크
			if ( fireTime + fireDurationTime < GetTickCount64() )
			{
				// ** 구간 반복 종료
				bRepeatSection = false;

				// ** Loop중이라면 Offset을 다시 0으로 세팅하고 아니라면 Default Animation을 Play 시킨다 
				if ( bLoopPlayAnim )
					_offset = 0;
				else
					PlayAnimation(eBossAnimationType::DEFAULT, true);
			}
			else
			{
				// ** 반복을 위해 Fire 스타트 지점으로 리셋
				_offset = fireSectionStart;
			}
		}
		// ** 반복구간 종료지점이 아니라면
		else
		{
			// Offset 증가
			++_offset;
		}
	}
}

void BossAngelEnemy::PlayAnimAttack2(HDC _hdc, ULONGLONG& _time, int& _offset)
{
	static bool bRepeatSection = false; // ** 일정 구간이 반복되고 있는 타이밍인지
	int maxSegmentCount = 5;			// ** 해당 라인에서 분할된 이미지 수	
	int delay = 200;
	
	// ** Ready 타이밍
	static ULONGLONG readyTime = 0;
	int readyDurationTime = 1000;
	int readySectionStart = 0;
	int readySectionEnd = 1;

	// ** Fire 타이밍
	static ULONGLONG fireTime = 0;
	int fireDurationTime = 2000;
	int fireSectionStart = 2;
	int fireSectionEnd = maxSegmentCount - 1;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * _offset),
		(int)(pImage->GetSegmentationScale().y * static_cast<int>(animType)),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(147, 187, 236));

	// ** Delay 시간 주기로 Offset 적용
	if ( _time + delay < GetTickCount64() )
	{
		_time = GetTickCount64();

		// ** Ready 시작 구간 진입
		if ( !bRepeatSection && _offset == readySectionStart )
		{
			// ** Ready 시작 타임 설정
			readyTime = GetTickCount64();
		}

		// ** Fire 시작 구간 진입
		if ( !bRepeatSection && _offset == fireSectionStart )
		{
			// ** Fire 시작 타임 설정
			fireTime = GetTickCount64();
		}

		// ** Ready 종료 구간 진입
		if ( _offset == readySectionEnd )
		{
			// ** 구간 반복 스타트
			bRepeatSection = true;

			// ** Ready 구간반복 지속시간이 끝났는지 체크
			if ( readyTime + readyDurationTime < GetTickCount64() )
			{
				// ** 구간 반복 종료
				bRepeatSection = false;

				// ** 구간을 넘김 ( 종료지점의 다음 Offset으로 설정 )
				_offset = readySectionEnd + 1;
			}
		}
		// ** Fire 종료 구간 진입
		else if ( _offset == fireSectionEnd )
		{
			// ** 구간 반복 스타트
			bRepeatSection = true;

			// ** Fire 구간반복 지속시간이 끝났는지 체크
			if ( fireTime + fireDurationTime < GetTickCount64() )
			{
				// ** 구간 반복 종료
				bRepeatSection = false;

				// ** Loop중이라면 Offset을 다시 0으로 세팅하고 아니라면 Default Animation을 Play 시킨다 
				if ( bLoopPlayAnim )
					_offset = 0;
				else
					PlayAnimation(eBossAnimationType::DEFAULT, true);
			}
			else
			{
				// ** 반복을 위해 Fire 스타트 지점으로 리셋
				_offset = fireSectionStart;
			}
		}
		// ** 반복구간 종료지점이 아니라면
		else
		{
			// Offset 증가
			++_offset;
		}
	}
}

void BossAngelEnemy::PlayAnimAttack3(HDC _hdc, ULONGLONG& _time, int& _offset)
{
	static bool bRepeatSection = false; // ** 일정 구간이 반복되고 있는 타이밍인지
	int maxSegmentCount = 6;			// ** 해당 라인에서 분할된 이미지 수	
	int delay = 200;

	// ** Ready 타이밍
	static ULONGLONG readyTime = 0;
	int readyDurationTime = 1000;
	int readySectionStart = 0;
	int readySectionEnd = 1;

	// ** Fire 타이밍
	static ULONGLONG fireTime = 0;
	int fireDurationTime = 2000;
	int fireSectionStart = 2;
	int fireSectionEnd = maxSegmentCount - 1;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * _offset),
		(int)(pImage->GetSegmentationScale().y * static_cast<int>(animType)),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(147, 187, 236));

	// ** Delay 시간 주기로 Offset 적용
	if ( _time + delay < GetTickCount64() )
	{
		_time = GetTickCount64();

		// ** Ready 시작 구간 진입
		if ( !bRepeatSection && _offset == readySectionStart )
		{
			// ** Ready 시작 타임 설정
			readyTime = GetTickCount64();
		}

		// ** Fire 시작 구간 진입
		if ( !bRepeatSection && _offset == fireSectionStart )
		{
			// ** Fire 시작 타임 설정
			fireTime = GetTickCount64();
		}

		// ** Ready 종료 구간 진입
		if ( _offset == readySectionEnd )
		{
			// ** 구간 반복 스타트
			bRepeatSection = true;

			// ** Ready 구간반복 지속시간이 끝났는지 체크
			if ( readyTime + readyDurationTime < GetTickCount64() )
			{
				// ** 구간 반복 종료
				bRepeatSection = false;

				// ** 구간을 넘김 ( 종료지점의 다음 Offset으로 설정 )
				_offset = readySectionEnd + 1;
			}
		}
		// ** Fire 종료 구간 진입
		else if ( _offset == fireSectionEnd )
		{
			// ** 구간 반복 스타트
			bRepeatSection = true;

			// ** Fire 구간반복 지속시간이 끝났는지 체크
			if ( fireTime + fireDurationTime < GetTickCount64() )
			{
				// ** 구간 반복 종료
				bRepeatSection = false;

				// ** Loop중이라면 Offset을 다시 0으로 세팅하고 아니라면 Default Animation을 Play 시킨다 
				if ( bLoopPlayAnim )
					_offset = 0;
				else
					PlayAnimation(eBossAnimationType::DEFAULT, true);
			}
			else
			{
				// ** 반복을 위해 Fire 스타트 지점으로 리셋
				_offset = fireSectionStart;
			}
		}
		// ** 반복구간 종료지점이 아니라면
		else
		{
			// Offset 증가
			++_offset;
		}
	}
}

void BossAngelEnemy::PlayAnimEvolution(HDC _hdc, ULONGLONG& _time, int& _offset)
{
	int maxSegmentCount = 8; // ** 해당 라인에서 분할된 이미지 수
	int delay = 200;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * _offset),
		(int)(pImage->GetSegmentationScale().y * static_cast<int>(animType)),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(147, 187, 236));

	// ** Delay 시간 주기로 Offset 증가
	if ( _time + delay < GetTickCount64() )
	{
		if ( ++_offset == maxSegmentCount )
		{
			// ** Loop중이라면 Offset을 다시 0으로 세팅하고 아니라면 Default Animation을 Play 시킨다 
			if ( bLoopPlayAnim ) 
				_offset = 0;
			else
				PlayAnimation(eBossAnimationType::DEFAULT, true);
		}
		_time = GetTickCount64();
	}
}

void BossAngelEnemy::PlayAnimAttacked(HDC _hdc, ULONGLONG& _time, int& _offset)
{
	int maxSegmentCount = 1; // ** 해당 라인에서 분할된 이미지 수
	int delay = 200;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * _offset),
		(int)(pImage->GetSegmentationScale().y * static_cast<int>(animType)),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(147, 187, 236));

	// ** Delay 시간 주기로 Offset 증가
	if ( _time + delay < GetTickCount64() )
	{
		// ** Default는 항상 Loop 상태이므로 Offset을 0으로 세팅
		if ( ++_offset == maxSegmentCount )
		{
			if ( bLoopPlayAnim )
				_offset = 0;
			else
				PlayAnimation(eBossAnimationType::DEFAULT, true);
		}

		_time = GetTickCount64();
	}
}

void BossAngelEnemy::InitActionInfo()
{
	// ** Move info 초기화
	if ( pOwner )
	{
		static_cast<Enemy*>(pOwner)->InitMoveInfo();
	}

	// ** Action Info 초기화
	actionInfos = queue<pair<eActionType, float>>();	

	vector<float> delayTimes = { 3000.0f, 2000.0f, 1000.0f };

	actionInfos.push(make_pair(eActionType::MOVE_SPAWN_POS, 0.0f));
	actionInfos.push(make_pair(eActionType::FIRE_FALLDOWN_BACK_AND_FORTH, delayTimes[curPhase - 1]));
	actionInfos.push(make_pair(eActionType::FIRE_TRIANGLE, delayTimes[curPhase - 1]));
	actionInfos.push(make_pair(eActionType::FIRE_DIAMOND, delayTimes[curPhase - 1]));
	actionInfos.push(make_pair(eActionType::FIRE_MULTI_SPIN, delayTimes[curPhase - 1]));
}

void BossAngelEnemy::Action(eActionType _ActionType)
{
	Vector3 bkgPos = pBackground->GetPosition();
	Vector3 bkgScale = pBackground->GetScale();
	
	static ULONGLONG actionTime = GetTickCount64();
	static int moveCount = 0;
	
	switch ( _ActionType )
	{
		case eActionType::MOVE_SPAWN_POS:
			if ( actionState == eActionState::READY )
			{
				speed = 0.75f;
				static_cast<Enemy*>(pOwner)->MoveTo(spawnDestPos);

				moveCount = 1;
			
			}
			else // actionState == eActionState::WORKING
			{
				if ( !static_cast<Enemy*>(pOwner)->isMoving() )
					actionState = eActionState::END;
			}
			break;
		case eActionType::FIRE_FALLDOWN_BACK_AND_FORTH:
			if ( actionState == eActionState::READY )
			{
				actionTime = GetTickCount64();
				speed = 3.0f;
				moveCount = 5;

				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x - bkgScale.x * 0.4f, spawnDestPos.y));
				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x + bkgScale.x * 0.4f, spawnDestPos.y));
				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x - bkgScale.x * 0.4f, spawnDestPos.y));
				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x + bkgScale.x * 0.4f, spawnDestPos.y));
				static_cast<Enemy*>(pOwner)->MoveTo(Vector3(spawnDestPos));				

				PlayAnimation(eBossAnimationType::ATTACK1, true);
			}			
			else
			{
				int bulletSpawnDelay = 200;
				if ( actionTime + bulletSpawnDelay < GetTickCount64() )
				{
					actionTime = GetTickCount64();

					float bulletSpeed = 5.0f;

					// 몸체 기준 좌우로 Scale 간격을 두고 5개의 Bullet 발사
					for ( int offset = 0; offset < 5; ++offset )
					{
						Transform bulletTransInfo;
						bulletTransInfo.Direction = Vector3(0.0f, 1.0f);
						bulletTransInfo.Position.x = (collider.Position.x - collider.Scale.x) + ((collider.Scale.x * 0.5f) * offset);
						bulletTransInfo.Position.y = collider.Position.y;
						bulletTransInfo.Scale = Vector3(10.0f, 10.0f);

						// ** Bullet Spawn
						SpawnManager::SpawnBullet(pOwner, bulletTransInfo, bulletSpeed, 1, eBridgeKey::BULLET_NORMAL);
					}
				}

				if ( !static_cast<Enemy*>(pOwner)->isMoving() )
				{
					--moveCount;
					if ( moveCount == 0 )
					{
						actionState = eActionState::END;
						PlayAnimation(eBossAnimationType::DEFAULT, true);
					}
				}
			}
			break;
		case eActionType::FIRE_TRIANGLE:
			if ( actionState == eActionState::READY )
			{
				actionTime = GetTickCount64();
				speed = 3.0f;
				moveCount = 6;

				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x - bkgScale.x * 0.24f, bkgPos.y - bkgScale.y * 0.48f));
				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x + bkgScale.x * 0.24f, bkgPos.y - bkgScale.y * 0.48f));
				static_cast<Enemy*>(pOwner)->MoveTo(Vector3(spawnDestPos));
				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x - bkgScale.x * 0.24f, bkgPos.y - bkgScale.y * 0.48f));
				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x + bkgScale.x * 0.24f, bkgPos.y - bkgScale.y * 0.48f));
				static_cast<Enemy*>(pOwner)->MoveTo(Vector3(spawnDestPos));
				
				

				PlayAnimation(eBossAnimationType::ATTACK1, true);
			}
			else
			{
				int bulletSpawnDelay = 500;
				if ( actionTime + bulletSpawnDelay < GetTickCount64() )
				{
					actionTime = GetTickCount64();

					Transform spawnTransInfo;
					spawnTransInfo.Position = collider.Position;
					spawnTransInfo.Scale = collider.Scale;
					spawnTransInfo.Direction = Vector3(0.0f, 1.0f);

					bulletScript.ReadyToSpawn(pOwner, static_cast<eBulletSpawnPattern>(eBulletSpawnPattern::N_POLYGON_GO), spawnTransInfo, 1, 3);
				}

				if ( !static_cast<Enemy*>(pOwner)->isMoving() )
				{
					--moveCount;
					if ( moveCount == 0 )
					{
						actionState = eActionState::END;
						PlayAnimation(eBossAnimationType::DEFAULT, true);
					}
				}
			}
			break;
		case eActionType::FIRE_DIAMOND:
			if ( actionState == eActionState::READY )
			{
				actionTime = GetTickCount64();
				speed = 3.0f;
				moveCount = 9;

				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x, bkgPos.y));
				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x - bkgScale.x * 0.24f, bkgPos.y - bkgScale.y * 0.24f));
				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x, bkgPos.y - bkgScale.y * 0.48f));
				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x + bkgScale.x * 0.24f, bkgPos.y - bkgScale.y * 0.24f));
				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x, bkgPos.y));
				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x - bkgScale.x * 0.24f, bkgPos.y - bkgScale.y * 0.24f));
				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x, bkgPos.y - bkgScale.y * 0.48f));
				static_cast<Enemy*>(pOwner)->MoveTo(
					Vector3(bkgPos.x + bkgScale.x * 0.24f, bkgPos.y - bkgScale.y * 0.24f));
				static_cast<Enemy*>(pOwner)->MoveTo(Vector3(spawnDestPos));

				PlayAnimation(eBossAnimationType::ATTACK2, true);
			}
			else
			{
				int bulletSpawnDelay = 500;
				if ( actionTime + bulletSpawnDelay < GetTickCount64() )
				{
					actionTime = GetTickCount64();

					Transform spawnTransInfo;
					spawnTransInfo.Position = collider.Position;
					spawnTransInfo.Scale = collider.Scale;
					spawnTransInfo.Direction = Vector3(0.0f, 1.0f);

					bulletScript.ReadyToSpawn(pOwner, static_cast<eBulletSpawnPattern>(eBulletSpawnPattern::N_POLYGON_GO), spawnTransInfo, 1, 4);
				}

				if ( !static_cast<Enemy*>(pOwner)->isMoving() )
				{
					--moveCount;
					if ( moveCount == 0 )
					{
						actionState = eActionState::END;
						PlayAnimation(eBossAnimationType::DEFAULT, true);
					}
				}
			}
			break;
		case eActionType::FIRE_MULTI_SPIN:
			if ( actionState == eActionState::READY )
			{
				actionTime = GetTickCount64();
				speed = 3.0f;
				moveCount = 1;

				static_cast<Enemy*>(pOwner)->MoveTo(Vector3(spawnDestPos));

				Transform spawnTransInfo;
				spawnTransInfo.Position = collider.Position;
				spawnTransInfo.Scale = collider.Scale;
				spawnTransInfo.Direction = Vector3(0.0f, 1.0f);

				bulletScript.ReadyToSpawn(pOwner, static_cast<eBulletSpawnPattern>(eBulletSpawnPattern::MULTI_SPIN_GO), spawnTransInfo, 1);

				PlayAnimation(eBossAnimationType::ATTACK2, true);
			}
			else
			{
				int actionDelayTime = 10000;

				if ( actionTime + actionDelayTime < GetTickCount64() )
				{
					if ( !static_cast<Enemy*>(pOwner)->isMoving() )
					{
						--moveCount;
						if ( moveCount == 0 )
						{
							actionState = eActionState::END;
							PlayAnimation(eBossAnimationType::DEFAULT, true);
						}
					}
				}
			}
			break;
	}
}

void BossAngelEnemy::CheckPhase()
{
	int maxHP = static_cast<Enemy*>(pOwner)->GetMaxHP();
	int HP = static_cast<Enemy*>(pOwner)->GetHP();
	float HpRatio = HP / static_cast<float>(maxHP);

	// 체력이 33% 미만일 시 페이즈 3
	if ( HpRatio < 0.33f )
	{
		curPhase = 3;
	}
	// 체력이 66% 미만일 시 페이즈 2
	else if ( HpRatio < 0.66f )
	{
		curPhase = 2;
	}
	// 기본 페이즈 1
	else
	{
		curPhase = 1;
	}
}
