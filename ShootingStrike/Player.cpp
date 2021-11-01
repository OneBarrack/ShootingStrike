#include "Player.h"
#include "Bridge.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "BitmapManager.h"
#include "GameDataManager.h"
#include "SoundManager.h"
#include "NormalBullet.h"
#include "MathManager.h"
#include "SpawnManager.h"
#include "Enemy.h"
#include "Item.h"
#include "Background.h"
#include "GuideBullet.h"
#include "Bullet.h"

Player::Player()
	: damage(0)
	, life(0)
	, maxLife(0)
	, power(0)
	, maxPower(0)
	, bomb(0)
	, maxBomb(0)
	, isSpawing(false)
	, bReSpawn(false)
	, isDied(false)
	, isInvicible(false)
	, bCantAccessInput(false)
	, oldPosition(Vector3())
	, cantAccessInputTimer(0)
	, cantAccessInputDurationTime(0)
	, invincibleTimer(0)
	, invicibleDurationTime(0)
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

	objectKey = eObjectKey::PLAYER;
	objectStatus = eObjectStatus::DEACTIVATED;
	collisionType = eCollisionType::ELLIPSE;
	oldPosition = transInfo.Position;
	bGenerateCollisionEvent = true;

	bulletScript.Initialize();

	damage = 1;
	life = 3;
	maxLife = 10;
	power = 1;
	maxPower = 5;
	bomb = 2;
	maxBomb = 2;

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
	if ( life == 0 )
		return;

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
		if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_Z, eKeyInputState::PRESSED) )
		{
			static ULONGLONG fireTime = 0; 
			int fireDelay = 100;

			if ( fireTime + fireDelay < GetTickCount64() )
			{
				fireTime = GetTickCount64();

				Fire(power, damage);
			}
		}

		// ** Bomb Skill 발동
		if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_X, eKeyInputState::DOWN) )
		{
			static ULONGLONG bombTime = 0;
			int bombDelay = 1500;

			if ( bombTime + bombDelay < GetTickCount64() )
			{
				bombTime = GetTickCount64();

				ActivateBomb();
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
	if ( life == 0 )
		return;

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

void Player::PowerUp(bool _bMax)
{	
	++power;

	if ( _bMax || maxPower < power )
		power = maxPower;
}

void Player::PowerDown(bool _bMin)
{
	--power;

	if ( _bMin || power < 1 )
		power = 1;
}

void Player::LifeUp(bool _bMax)
{
	life++;

	if ( _bMax || maxLife < life )
		life = maxLife;
}

void Player::LifeDown(bool _bMin)
{
	--life;

	if ( _bMin || life < 0 )
		life = 0;
}

void Player::BombUp(bool _bMax)
{
	bomb++;

	if ( _bMax || maxBomb < bomb )
		bomb = maxBomb;
}

void Player::BombDown(bool _bMin)
{
	--bomb;

	if ( _bMin || bomb < 0 )
		bomb = 0;
}

void Player::Fire(int _power, int _damage)
{
	// ** Play Player Fire Sound
	SoundManager::GetInstance()->Play(eSoundKey::EFFECT_PLAYER_FIRE);

	Object* pObject = nullptr;
	Bridge* pBridge = nullptr;	

	switch ( _power )
	{
		case 1:
		{
			// ** 한 번에 발사될 Normal Bullet 개수
			int normalBulletCount = 1;

			// ** Bullet 간격 각도
			int bulletGap = 15;

			// ** 가장 좌측 Bullet의 x Offet
			int startBulletOffsetX = static_cast<int>(-bulletGap * 0.5 * (normalBulletCount - 1));

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
			// ** 한 번에 발사될 Normal Bullet 개수
			int normalBulletCount = 2;

			// ** Bullet 간격 각도
			int bulletGap = 15;

			// ** 가장 좌측 Bullet의 x Offet
			int startBulletOffsetX = static_cast<int>(-bulletGap * 0.5 * (normalBulletCount - 1));

			// ** 2개의 Normal Bullet 발사
			for ( int i = 0; i < normalBulletCount; ++i )
			{
				// ** 상방 기준 현재 각도
				int bulletOffset = startBulletOffsetX + (bulletGap * i);

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
			// ** 한 번에 발사될 Normal Bullet 개수
			int normalBulletCount = 3;

			// ** Bullet 간격 각도
			int bulletGap = 15;

			// ** 가장 좌측 Bullet의 x Offet
			int startBulletOffsetX = static_cast<int>(-bulletGap * 0.5 * (normalBulletCount - 1));

			// ** 3개의 Noamal Bullet 발사
			for ( int i = 0; i < normalBulletCount; ++i )
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
			// ** 한 번에 발사될 Normal Bullet 개수
			int normalBulletCount = 4;

			// ** Bullet 간격 각도
			int bulletGap = 15;

			// ** 가장 좌측 Bullet의 x Offet
			int startBulletOffsetX = static_cast<int>(-bulletGap * 0.5 * (normalBulletCount - 1));

			// ** 4개의 Normal Bullet 발사
			for ( int i = 0; i < normalBulletCount; ++i )
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
			// ** 한 번에 발사될 Normal Bullet 개수
			int normalBulletCount = 4;

			// ** Bullet 간격 각도
			int bulletGap = 15;

			// ** 가장 좌측 Bullet의 x Offet
			int startBulletOffsetX = static_cast<int>(-bulletGap * 0.5 * (normalBulletCount - 1));

			// ** 4개의 Normal Bullet 발사
			for ( int i = 0; i < normalBulletCount; ++i )
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

void Player::ActivateBomb(bool _bPlayAnimation)
{
	// ** Bomb가 남아있다면
	if ( bomb > 0 )
	{
		// ** Play Bomb Sound
		SoundManager::GetInstance()->Play(eSoundKey::EFFECT_PLAYER_BOMB);

		// ** Player의 Bullet과 None/Boss Enemy를 제외한 Bullet들을 모두 Coin Item으로 변환시킨다.
		
		// ** 모든 Enemy를 탐색한다.
		list<Object*> enemyList = ObjectManager::GetInstance()->GetObjectList(eObjectKey::ENEMY);
		for ( Object* pEnemy : enemyList )
		{
			// ** Boss Enemy가 아닌 Enemy라면 
			if ( static_cast<Enemy*>(pEnemy)->GetEnemyType() != eEnemyType::NONE &&
				static_cast<Enemy*>(pEnemy)->GetEnemyType() != eEnemyType::ENEMY_BOSS_ANGEL )
			{
				// ** Bullet을 Coin Item으로 변환시킨다.
				Bridge* pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ITEM_GO_TO_PLAYER);
				Object* pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ITEM);
				pObject->SetPosition(pEnemy->GetPosition());
				pObject->SetScale(20.0f, 20.0f);
				pObject->SetDirection(Vector3(0.0f, -1.0f));
				pObject->SetSpeed(3.0f);
				pObject->SetAcceleration(0.1f);
				pObject->SetBridge(pBridge);
				static_cast<Item*>(pObject)->SetItemType(eItemType::COIN);
				static_cast<Enemy*>(pEnemy)->Die();
			}
		}

		// ** 모든 Bullet을 탐색한다.
		list<Object*> bulletList = ObjectManager::GetInstance()->GetObjectList(eObjectKey::BULLET);
		for ( Object* pBullet : bulletList )
		{
			// ** Player의 Bullet이 아니라면 
			if ( static_cast<Bullet*>(pBullet)->GetOwner()->GetKey() != eObjectKey::PLAYER )
			{
				// ** Bullet을 Coin Item으로 변환시킨다.
				Bridge* pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ITEM_GO_TO_PLAYER);
				Object* pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ITEM);
				pObject->SetPosition(pBullet->GetPosition());
				pObject->SetScale(20.0f, 20.0f);
				pObject->SetDirection(Vector3(0.0f, -1.0f));
				pObject->SetSpeed(3.0f);
				pObject->SetAcceleration(0.1f);
				pObject->SetBridge(pBridge);
				static_cast<Item*>(pObject)->SetItemType(eItemType::COIN);

				pBullet->SetStatus(eObjectStatus::DESTROYED);
			}
		}

		// ** Bomb 감소
		BombDown();
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
			
			int score = 0;

			// ** Enemy가 죽었다면 DeathPoint, Hit만 했다면 HitPoint Score를 받아온다.
			if ( pEnemy->IsDied() )
			{
				score = pEnemy->GetDeathPoint();

				// ** Enemy가 Boss 였다면
				if ( pEnemy->GetEnemyType() == eEnemyType::ENEMY_BOSS_ANGEL )
				{
					// ** Bomb Skill을 애니메이션 없이 발동시켜 
					// ** 남아있는 Bullet들을 Coin으로 처리하여 정리한다.
					BombUp();
					ActivateBomb(false);
				}
			}
			else
			{
				score = pEnemy->GetHitPoint();
			}
			
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
		Die();
	}
}

void Player::Spawn()
{
	isSpawing = true;
	
	// ** 플레이어 오브젝트 활성화 및 충돌 활성화
	SetStatus(eObjectStatus::ACTIVATED);
	bGenerateCollisionEvent = true;

	// ** Power, Bomb 초기화
	PowerDown(true);
	BombUp(true);

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
	// ** Play player die sound
	SoundManager::GetInstance()->Play(eSoundKey::EFFECT_PLAYER_DIE);

	// ** bDied flag true 세팅
	isDied = true;

	// ** 충돌 비활성화
	bGenerateCollisionEvent = false;

	// ** Life 감소
	LifeDown();

	// ** 폭발 이펙트 스폰
	Transform explosionTransInfo;
	explosionTransInfo.Position = transInfo.Position;
	explosionTransInfo.Scale = transInfo.Scale * 2.0f;
	SpawnManager::SpawnEffect(explosionTransInfo, eBridgeKey::EFFECT_EXPLOSION);

	// ** 보스 단계에서 죽은 것이라면 Power Max Item 스폰
	if ( ObjectManager::GetInstance()->FindObjectWithTag(eTagName::ENEMY_BOSS) )
	{
		Bridge* pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ITEM_BOUNCE_ON_WALL);
		Object* pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ITEM);
		pObject->SetPosition(transInfo.Position);
		pObject->SetScale(Vector3(40.0f, 40.0f));
		pObject->SetSpeed(2.0f);
		pObject->SetBridge(pBridge);
		static_cast<Item*>(pObject)->SetItemType(eItemType::POWER_MAX);
	}
}

void Player::CheckStatus()
{
	// ** 죽었을 시
	if ( isDied )
	{
		// ** 체력과 레벨 초기화		
		power = 1;

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
		// ** 일정 딜레이 후 무적 해제
		if ( invincibleTimer + invicibleDurationTime < GetTickCount64() )
		{
			isInvicible = false;
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

	cout << "pos: " << transInfo.Position.x << ", " << transInfo.Position.y << endl;
	cout << "boundary: " << bkgBoundary.Left << ", " << bkgBoundary.Top 
		<< ", " << bkgBoundary.Right << ", " << bkgBoundary.Bottom << endl;
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
	// ** Item 과 충돌 시
	if ( _pObject->GetKey() == eObjectKey::ITEM )
	{
		eItemType itemType = static_cast<Item*>(_pObject)->GetItemType();
		if ( itemType != eItemType::NONE )
		{
			SoundManager::GetInstance()->Play(eSoundKey::EFFECT_GET_ITEM);
			switch ( itemType )
			{
				case eItemType::POWER_MAX: PowerUp(true); break;
				case eItemType::POWER_UP:  PowerUp();	  break;
				case eItemType::LIFE_UP:   LifeUp();	  break;
				case eItemType::COIN: GameDataManager::GetInstance()->AddScore(258); break;
			}
		}
	}
}