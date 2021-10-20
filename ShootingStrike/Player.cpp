#include "Player.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "BitmapManager.h"
#include "GameDataManager.h"
#include "Bridge.h"
#include "NormalBullet.h"
#include "MathManager.h"
#include "SpawnManager.h"
#include "Enemy.h"
#include "Background.h"
#include "GuideBullet.h"

Player::Player()
	: life(0)
	, damage(0)
	, level(0)
	, isSpawing(false)
	, bReSpawn(false)
	, isDied(false)
	, oldPosition(Vector3())
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	Super::Initialize();

	pImage = BitmapManager::GetInstance()->GetImage(eImageKey::PLAYER);
	tagName = eTagName::PLAYER_FLIGHT1;	

	transInfo.Position = Vector3(WINDOWS_WIDTH * 0.5f, WINDOWS_HEIGHT * 0.5f);
	transInfo.Scale = Vector3(42.0f, 47.0f);

	collider.Position = Vector3(transInfo.Position.x + 3, transInfo.Position.y);
	collider.Scale = Vector3(12.0f, 12.0f);

	key = eObjectKey::PLAYER;
	status = eObjectStatus::DEACTIVATED;
	collisionType = eCollisionType::ELLIPSE;
	oldPosition = transInfo.Position;
	bGenerateCollisionEvent = true;

	bulletScript.Initialize();

	life = 3;
	damage = 1;
	level = 1;

	isSpawing = false;
	isDied = false;

	speed = 3.0f;

	cantAccessInputTimer = 0;
	cantAccessInputDurationTime = 0;
	invincibleTimer = 0;
	invicibleDurationTime = 0;
}

void Player::Update()
{
	Super::Update();

	// ** 현재 플레이어 상태 체크
	CheckStatus();
		
	if ( isSpawing )
	{
		// ** 이동 속도
		float moveSpeed = 0.5f;
		
		// ** 멈출 위치
		Background* pStageBackground = static_cast<Background*>(
			ObjectManager::GetInstance()->FindObjectWithTag(eTagName::STAGE_MAIN_BKG));
		float stopPositionY = (pStageBackground->GetPosition().y + (pStageBackground->GetScale().y * 0.5f)) - 100;

		// ** 화면 아래에서부터 일정 위치까지 서서히 올라오도록
		if ( transInfo.Position.y - moveSpeed > stopPositionY )
		{
			transInfo.Position.y -= moveSpeed;
			
		}
		// ** 멈출 위치에 도달
		else
		{
			// ** Spawn 관련 플래그 모두 비활성화 및 키 입력 가능하도록 설정
			transInfo.Position.y = stopPositionY;
			isSpawing = false;
			bReSpawn = false;
			bCantAccessInput = false;
		}
	}

	// ** 키 입력이 막힌 상태가 아니라면
	if ( !bCantAccessInput )
	{
		#ifdef GAME_DEBUG_MODE
		// _Debug_
		if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_ENTER, eKeyInputState::DOWN) )
		{
			level++;
		}
		#endif // GAME_DEBUG_MODE

		if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_LEFT, eKeyInputState::PRESSED) )
		{
			transInfo.Position.x -= 3;
		}
		if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_UP, eKeyInputState::PRESSED) )
		{
			transInfo.Position.y -= 3;
		}
		if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_RIGHT, eKeyInputState::PRESSED) )
		{
			transInfo.Position.x += 3;
		}
		if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_DOWN, eKeyInputState::PRESSED) )
		{
			transInfo.Position.y += 3;
		}

		// ** 미사일 발사
		if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_SPACE, eKeyInputState::PRESSED) )
		{
			static ULONGLONG fireTime = 0; 
			int fireDelay = 100;

			if ( fireTime + fireDelay < GetTickCount64() )
			{
				fireTime = GetTickCount64();

				Fire(level, damage);
			}
		}
	}

	// ** Direction 저장
	transInfo.Direction = MathManager::GetDirection(oldPosition, transInfo.Position);

	// ** Stage 전장을 벗어났는지 체크
	CheckPositionInBkgBoundary();

	// ** 직전 위치 정보 저장
	oldPosition = transInfo.Position;

	// ** 충돌체 갱신
	SetCollider(Vector3(transInfo.Position.x + 1, transInfo.Position.y), Vector3(12.0f, 12.0f));

	// ** Bullet Spawn Pattern Script 실행
	bulletScript.Run();

	return;
}

void Player::Render(HDC _hdc)
{
	Super::Render(_hdc);

	// ** 스폰 중
	if ( isSpawing )
	{
		RenderSpawn(_hdc);		
		return;
	}

	// ** 죽음
	if ( isDied )
	{		
		return;
	}		

	// ** 일반 출력
	RenderPlayer(_hdc);	
}

void Player::Fire(int _power, int _damage)
{
	Object* pObject = nullptr;
	Bridge* pBridge = nullptr;

	// ** Bullet 간격 각도
	int bulletGap = 15;

	// ** 가장 좌측 Bullet의 x Offet
	int startBulletOffsetX = static_cast<int>(-bulletGap * 0.5 * (_power - 1));

	switch ( _power )
	{
		case 1:
		{
			// ** Bullet의 TransInfo 설정
			Transform bulletTransInfo;
			bulletTransInfo.Position.x = transInfo.Position.x;
			bulletTransInfo.Position.y = transInfo.Position.y - (transInfo.Scale.y * 0.5f);
			bulletTransInfo.Scale = Vector3(15.0f, 15.0f);
			bulletTransInfo.Direction = Vector3(0.0f, -1.0f);

			// ** Bullet의 Speed 설정
			float bulletSpeed = 10.0f;

			// ** Bullet Spawn
			pObject = SpawnManager::SpawnBullet(this, bulletTransInfo, bulletSpeed, _damage, eBridgeKey::BULLET_NORMAL);
			pObject->SetImageOffsetOrder(Point(1, 2));
			break;
		}
		case 2:
		{
			int bulletGap = 15;
			int startBulletOffset = static_cast<int>(-bulletGap * 0.5 * (_power - 1));

			for ( int i = 0; i < 2; ++i )
			{
				// ** 상방 기준 현재 각도
				int bulletOffset = startBulletOffset + (bulletGap * i);

				// ** Bullet의 TransInfo 설정
				Transform bulletTransInfo;
				bulletTransInfo.Position.x = transInfo.Position.x - bulletOffset;
				bulletTransInfo.Position.y = transInfo.Position.y - (transInfo.Scale.y * 0.5f);
				bulletTransInfo.Scale = Vector3(15.0f, 15.0f);
				bulletTransInfo.Direction = Vector3(0.0f, -1.0f);

				// ** Bullet의 Speed 설정
				float bulletSpeed = 10.0f;

				// ** Bullet Spawn
				pObject = SpawnManager::SpawnBullet(this, bulletTransInfo, bulletSpeed, _damage, eBridgeKey::BULLET_NORMAL);
				pObject->SetImageOffsetOrder(Point(1, 2));
			}
			break;
		}
		case 3:
		{
			// ** 3개의 Bullet 발사
			for ( int i = 0; i < 3; ++i )
			{
				// ** 상방 기준 현재 각도
				int bulletOffset = startBulletOffsetX + (bulletGap * i);

				// ** Bullet의 TransInfo 설정
				Transform bulletTransInfo;
				bulletTransInfo.Position.x = transInfo.Position.x - bulletOffset;												

				// ** 좌측과 우측 Bullet의 Position은 센터기준 살짝 뒤로 잡는다
				if ( i == 0 || i == 2 ) // ** 좌/우
					bulletTransInfo.Position.y = transInfo.Position.y - (transInfo.Scale.y * 0.3f);
				else // ** 센터
					bulletTransInfo.Position.y = transInfo.Position.y - (transInfo.Scale.y * 0.5f);
							
				bulletTransInfo.Scale = Vector3(15.0f, 15.0f);
				bulletTransInfo.Direction = Vector3(0.0f, -1.0f);

				// ** Bullet의 Speed 설정
				float bulletSpeed = 10.0f;

				// ** Bullet Spawn
				pObject = SpawnManager::SpawnBullet(this, bulletTransInfo, bulletSpeed, _damage, eBridgeKey::BULLET_NORMAL);
				pObject->SetImageOffsetOrder(Point(1, 2));
			}			
			break;
		}
		case 4:
		{
			// ** 4개의 Bullet 발사
			for ( int i = 0; i < 4; ++i )
			{
				// ** 상방 기준 현재 각도
				int bulletOffset = startBulletOffsetX + (bulletGap * i);

				// ** Bullet의 TransInfo 설정
				Transform bulletTransInfo;
				bulletTransInfo.Position.x = transInfo.Position.x - bulletOffset;

				// ** 좌측과 우측 Bullet의 Position은 센터기준 살짝 뒤로 잡는다
				if ( i == 0 || i == 3 ) // ** 좌/우
					bulletTransInfo.Position.y = transInfo.Position.y - (transInfo.Scale.y * 0.3f);
				else // ** 센터
					bulletTransInfo.Position.y = transInfo.Position.y - (transInfo.Scale.y * 0.5f);

				bulletTransInfo.Scale = Vector3(15.0f, 15.0f);
				bulletTransInfo.Direction = Vector3(0.0f, -1.0f);

				// ** Bullet의 Speed 설정
				float bulletSpeed = 10.0f;

				// ** Bullet Spawn
				pObject = SpawnManager::SpawnBullet(this, bulletTransInfo, bulletSpeed, _damage, eBridgeKey::BULLET_NORMAL);
				pObject->SetImageOffsetOrder(Point(1, 2));
			}
			break;
		}
		case 5:
		{
			// ** 4개의 Bullet 발사
			for ( int i = 0; i < 4; ++i )
			{
				// ** 상방 기준 현재 각도
				int bulletOffset = startBulletOffsetX + (bulletGap * i);

				// ** Bullet의 TransInfo 설정
				Transform bulletTransInfo;
				bulletTransInfo.Position.x = transInfo.Position.x - bulletOffset;

				// ** 좌측과 우측 Bullet의 Position은 센터기준 살짝 뒤로 잡는다
				if ( i == 0 || i == 3 ) // ** 좌/우
					bulletTransInfo.Position.y = transInfo.Position.y - (transInfo.Scale.y * 0.3f);
				else // ** 센터
					bulletTransInfo.Position.y = transInfo.Position.y - (transInfo.Scale.y * 0.5f);

				bulletTransInfo.Scale = Vector3(15.0f, 15.0f);
				bulletTransInfo.Direction = Vector3(0.0f, -1.0f);

				// ** Bullet의 Speed 설정
				float bulletSpeed = 10.0f;

				// ** Bullet Spawn
				pObject = SpawnManager::SpawnBullet(this, bulletTransInfo, bulletSpeed, _damage, eBridgeKey::BULLET_NORMAL);
				pObject->SetImageOffsetOrder(Point(1, 2));
			}

			// ** 좌우로 Guide Bullet 생성
			{
				static ULONGLONG guideBulletSpawnTime = 0;
				int guideBulletSpawnDelay = 500;

				float bulletSpeed = 3.0f;

				if ( guideBulletSpawnTime + guideBulletSpawnDelay < GetTickCount64() )
				{
					guideBulletSpawnTime = GetTickCount64();

					// ** Delay Time과 이후 필요한 방향, 속도, 최대속도, 가속도 설정
					int guideDelay = 200;
					Vector3 directionAfterDelay = Vector3(0.0, -1.0f);
					float speedAfterDelay = 1.0f;
					float maxSpeed = 10.0f;
					float accelerationAfterDelay = 0.3f;					

					// ** Bullet의 TransInfo 설정
					Transform bulletTransInfo;
					bulletTransInfo.Position.x = transInfo.Position.x - (transInfo.Scale.x * 0.5f);
					bulletTransInfo.Position.y = transInfo.Position.y;
					bulletTransInfo.Scale = Vector3(15.0f, 15.0f);
					bulletTransInfo.Direction = Vector3(-1.0f, 0.0f);

					// ** Bullet Spawn
					pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BULLET_GUIDE);
					static_cast<GuideBullet*>(pBridge)->SetDelay(directionAfterDelay, speedAfterDelay, maxSpeed, accelerationAfterDelay, guideDelay);
					static_cast<GuideBullet*>(pBridge)->SetLoopGuide(true);

					pObject = SpawnManager::SpawnBullet(this, bulletTransInfo, bulletSpeed, _damage, pBridge);
					pObject->SetImageOffsetOrder(Point(0, 1));

					// ** Bullet의 TransInfo 설정
					bulletTransInfo.Position.x = transInfo.Position.x + (transInfo.Scale.x * 0.5f);
					bulletTransInfo.Position.y = transInfo.Position.y;
					bulletTransInfo.Scale = Vector3(15.0f, 15.0f);
					bulletTransInfo.Direction = Vector3(1.0f, 0.0f);

					// ** Bullet Spawn
					pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BULLET_GUIDE);
					static_cast<GuideBullet*>(pBridge)->SetDelay(directionAfterDelay, speedAfterDelay, maxSpeed, accelerationAfterDelay, guideDelay);
					static_cast<GuideBullet*>(pBridge)->SetLoopGuide(true);

					pObject = SpawnManager::SpawnBullet(this, bulletTransInfo, bulletSpeed, _damage, pBridge);
					pObject->SetImageOffsetOrder(Point(0, 1));
				}
			}
			break;
		}
	}
}

void Player::ApplyDamage(Object* _pTarget, int _damage)
{
	// ** 데미지를 가함
	switch ( _pTarget->GetKey() )
	{
		case eObjectKey::ENEMY:
		{
			Enemy* pEnemy = static_cast<Enemy*>(_pTarget);
			pEnemy->TakeDamage(_damage);
			
			// ** Enemy가 죽었다면 DeathPoint, Hit만 했다면 HitPoint Score를 받아온다.			
			int score = pEnemy->IsDead() ? pEnemy->GetDeathPoint() : pEnemy->GetHitPoint();
			GameDataManager::GetInstance()->AddScore(score);
			break;
		}		
		default:
			break;
	}	
}

void Player::TakeDamage(int _damage)
{
	// ** 현재 플레이어는 HP가 없고 한방에 터짐. Life만 감소
	
	// Die
	if ( !isDied )
	{
		life--;
		Die();
	}
}

void Player::Spawn()
{
	isSpawing = true;
	status = eObjectStatus::ACTIVATED;

	// ** 스타트 위치 설정
	Background* pStageBackground = static_cast<Background*>(
		ObjectManager::GetInstance()->FindObjectWithTag(eTagName::STAGE_MAIN_BKG));
			
	transInfo.Position.x = pStageBackground->GetPosition().x;
	transInfo.Position.y = (pStageBackground->GetPosition().y + (pStageBackground->GetScale().y * 0.5f)) + 30;

	// ** 키 입력을 막음
	bCantAccessInput = true;
	cantAccessInputTimer = GetTickCount64();
	cantAccessInputDurationTime = 5000; // 스폰이 종료되면 키 입력 가능해지므로 여기서는 넉넉히 잡아둔다 

	// ** 무적 설정
	isInvicible = true;
	invincibleTimer = GetTickCount64();
	invicibleDurationTime = 5500;
}

void Player::ReSpawn()
{
	bReSpawn = true;
	Spawn();
}

void Player::Die()
{
	// ** bDied flag true 세팅
	isDied = true;

	// ** 폭발 이펙트 스폰
	Transform explosionTransInfo;
	explosionTransInfo.Position = transInfo.Position;
	explosionTransInfo.Scale = transInfo.Scale * 2.0f;
	SpawnManager::SpawnEffect(explosionTransInfo, eBridgeKey::EFFECT_EXPLOSION);
}

void Player::CheckStatus()
{
	// ** 죽었을 시
	if ( isDied )
	{
		// ** 체력과 레벨 초기화		
		level = 1;

		// ** 리 스폰
		isDied = false;
		ReSpawn();
	}	

	// ** 키 입력이 막혔을 시
	if ( bCantAccessInput )
	{
		// ** 일정 딜레이 후 키 입력 허용
		if ( cantAccessInputTimer + cantAccessInputDurationTime < GetTickCount64() )
		{
			bCantAccessInput = false;
		}
	}

	// ** 무적일 시 
	if ( isInvicible )
	{
		// ** 충돌 비활성화
		bGenerateCollisionEvent = false;
		
		// ** 일정 딜레이 후 무적 해제 및 충돌 활성화
		if ( invincibleTimer + invicibleDurationTime < GetTickCount64() )
		{
			isInvicible = false;
			bGenerateCollisionEvent = true;
		}		
	}
}

void Player::CheckPositionInBkgBoundary()
{
	// ** 스폰 중일 때는 체크 x
	if ( isSpawing )
		return;

	// ** Stage 전장 배경
	Object* pBackground = ObjectManager::GetInstance()->FindObjectWithTag(eObjectKey::BACKGROUND, eTagName::STAGE_MAIN_BKG);

	// ** Stage의 바운더리
	RectF bkgBoundary = pBackground->GetColliderF();

	// ** 테두리 경계선 기준에 몸체가 잘리지 않게 하기 위한 Offset 값
	float offset = 22.0f;

	// ** 좌
	if ( transInfo.Position.x < bkgBoundary.Left + offset )
		transInfo.Position.x = bkgBoundary.Left + offset;
	// ** 우
	if ( transInfo.Position.x > bkgBoundary.Right - offset )
		transInfo.Position.x = bkgBoundary.Right - offset;
	// ** 상
	if ( transInfo.Position.y < bkgBoundary.Top + offset )
		transInfo.Position.y = bkgBoundary.Top + offset;
	// ** 하
	if ( transInfo.Position.y > bkgBoundary.Bottom - offset )
		transInfo.Position.y = bkgBoundary.Bottom - offset;
}

void Player::RenderSpawn(HDC _hdc)
{
	if ( !pImage ) 
		return;
	
	// ** 그릴지 말지 판단
	static bool bDraw = true;	
	
	// ** 리스폰 시 캐릭터의 깜빡임을 주기 위한 flicker 시간
	static ULONGLONG flickerTime = GetTickCount64();
	int flickerCycleTime = 200;

	// ** 리스폰일 경우 
	if ( bReSpawn ) 		
	{
		// ** 캐릭터가 깜빡이면서 스폰되도록
		if ( flickerTime + flickerCycleTime < GetTickCount64() )
		{
			flickerTime = GetTickCount64();
			bDraw ^= true;
		}
	}
	else
	{
		bDraw = true;
	}

	// ** Render
	if ( bDraw )
	{
		TransparentBlt(_hdc,
			(int)(transInfo.Position.x - transInfo.Scale.x * 0.5f),
			(int)(transInfo.Position.y - transInfo.Scale.y * 0.5f),
			(int)transInfo.Scale.x,
			(int)transInfo.Scale.y,
			pImage->GetMemDC(),
			(int)pImage->GetSegmentationScale().x,
			(int)0,
			(int)pImage->GetSegmentationScale().x,
			(int)pImage->GetSegmentationScale().y,
			RGB(255, 0, 255));
	}
}

void Player::RenderPlayer(HDC _hdc)
{
	if ( !pImage ) return;

	static POINT segmentOffset = { 0, 0 };

	// ** Direction으로 방향을 체크하여 해당하는 Offset x값 적용
	if ( transInfo.Direction.x < 0.0f )		 segmentOffset.x = 0; // ** Left
	else if ( transInfo.Direction.x > 0.0f ) segmentOffset.x = 2; // ** Right
	else									 segmentOffset.x = 1; // ** None(Center)

	// ** 비행기 뒷편 불꽃 애니메이션을 위해 Offset.y값을 1, 2 무한반복 시킴
	segmentOffset.y = (segmentOffset.y < 2) ? 2 : 1;

	TransparentBlt(_hdc,
		(int)transInfo.Position.x - (int)(transInfo.Scale.x * 0.5f),
		(int)transInfo.Position.y - (int)(transInfo.Scale.y * 0.5f),
		(int)transInfo.Scale.x,
		(int)transInfo.Scale.y,
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * segmentOffset.x),
		(int)(pImage->GetSegmentationScale().y * segmentOffset.y),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(255, 0, 255));
}

void Player::Release()
{
	Super::Release();
}

void Player::OnCollision(Object* _pObject)
{
}