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

Player::Player()
	: pPlayerImage(nullptr)
	, HP(0)
	, Damage(0)
	, Level(0)
	, FiringType(eBulletFiringType::NORMAL)
	, bSpawing(false)
	, bAttacking(false)
	, bTakeDamage(false)
	, bDied(false)
	, Frame(0)
	, OldPosition(Vector3())
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	Super::Initialize();

	pPlayerImage = BitmapManager::GetInstance()->GetImage(eImageKey::PLAYER);
	TagName = eTagName::PLAYER;

	TransInfo.Position = Vector3(WindowsWidth * 0.5f, WindowsHeight * 0.5f);
	TransInfo.Scale = Vector3(42.0f, 47.0f);

	Collider.Position = TransInfo.Position;
	Collider.Scale = TransInfo.Scale;

	Key = eObjectKey::PLAYER;
	Status = eObjectStatus::DEACTIVATED;
	CollisionType = eCollisionType::RECT;
	OldPosition = TransInfo.Position;
	bGenerateCollisionEvent = true;

	HP = 3;
	Damage = 1;
	Level = 1;
	FiringType = eBulletFiringType::NORMAL;

	bSpawing = false;
	bAttacking = false;
	bTakeDamage = false;
	bDied = false;

	Speed = 3.0f;
	Frame = 0;
	

	Offset = Vector3(95.0f, -85.0f);
}

void Player::Update()
{
	Super::Update();

	// ** 수정 작업 필요

	Frame++;

	if ( bDied )
	{
		HP = 3;
		Level = 1;
		bDied = false;
		bSpawing = true;
	}

	// ** 스폰 중
	if ( bSpawing )
	{
		bGenerateCollisionEvent = false;
	}
	else
	{
		bGenerateCollisionEvent = true;
		// ** 공격중
		if ( bAttacking )
		{
			// ...
		}

		#ifdef GAME_DEBUG_MODE
		// _Debug_
		if ( CheckKeyInputState(eInputKey::KEY_ENTER, eKeyInputState::DOWN) )
		{
			Level++;
		}
		#endif // GAME_DEBUG_MODE

		if ( CheckKeyInputState(eInputKey::KEY_LEFT, eKeyInputState::PRESSED) )
		{
			TransInfo.Position.x -= 3;
		}
		if ( CheckKeyInputState(eInputKey::KEY_UP, eKeyInputState::PRESSED) )
		{
			TransInfo.Position.y -= 3;
		}
		if ( CheckKeyInputState(eInputKey::KEY_RIGHT, eKeyInputState::PRESSED) )
		{
			TransInfo.Position.x += 3;
		}
		if ( CheckKeyInputState(eInputKey::KEY_DOWN, eKeyInputState::PRESSED) )
		{
			TransInfo.Position.y += 3;
		}

		// ** 미사일 발사
		if ( CheckKeyInputState(eInputKey::KEY_SPACE, eKeyInputState::DOWN) )
		{
			Fire(FiringType, Level, Damage);
		}
		else
		{
			bAttacking = false;
		}
	}

	// ** Direction 저장
	TransInfo.Direction = MathManager::GetDirection(OldPosition, TransInfo.Position);

	// ** 직전 위치 정보 저장
	OldPosition = TransInfo.Position;

	// ** 충돌체 갱신
	Collider = TransInfo;

	return;
}

void Player::Render(HDC _hdc)
{
	Super::Render(_hdc);

	// ** 스폰 중
	if ( bSpawing )
	{
		if ( RenderSpawn(_hdc) )			
			bSpawing = false;

		return;
	}

	// ** 죽음
	if ( bDied )
	{		
		return;
	}
		
	// ** 피해를 입었을 시
	if ( bTakeDamage )
	{

	}

	// ** 일반 출력
	RenderPlayer(_hdc);	
}

void Player::Fire(eBulletFiringType _FiringType, int _Level, int _Damage)
{
	Bridge* pBridge = nullptr;

	switch ( _FiringType )
	{
		case eBulletFiringType::NORMAL:
		{
			// ** Level 만큼 총알 숫자를 늘리고, 상방 기준 총알 간 간격에 대한 각도를 설정하여
			// ** 부채꼴 형태로 발사되도록 한다.
			// ** angleGap : 총알간 간격 각도
			int angleGap = 10;
			int startAngle = 90 - static_cast<int>(angleGap * 0.5 * (_Level - 1));
			
			for ( int i = 0; i < _Level; ++i )
			{
				// ** 상방 기준 현재 각도
				int angle = startAngle + (angleGap * i);

				// ** Bullet의 TransInfo 설정
				Transform BulletTransInfo;
				BulletTransInfo.Position  = TransInfo.Position;
				BulletTransInfo.Scale	  = Vector3(10.0f, 10.0f);
				BulletTransInfo.Direction = Vector3(cosf(angle * PI / 180), -sinf(angle * PI / 180));
				
				// ** Bullet의 Speed 설정
				float BulletSpeed = 3.0f;

				// ** Bullet Spawn
				SpawnManager::SpawnBullet(this, BulletTransInfo, BulletSpeed, _Damage, _FiringType);
			}
			break;
		} 		
		case eBulletFiringType::GUIDE:
			break;
		default:
			break;
	}	
}

void Player::ApplyDamage(Object* _pTarget, int _Damage)
{
	// ** 데미지를 가함
	switch ( _pTarget->GetKey() )
	{
		case eObjectKey::ENEMY:
		{
			Enemy* pEnemy = static_cast<Enemy*>(_pTarget);
			pEnemy->TakeDamage(_Damage);
			
			// ** Enemy가 죽었다면 DeathPoint, Hit만 했다면 HitPoint Score를 받아온다.
			bool aaa = pEnemy->IsDead();
			int Score = pEnemy->IsDead() ? pEnemy->GetDeathPoint() : pEnemy->GetHitPoint();
			GameDataManager::GetInstance()->AddScore(Score);
		}
		break;
	}	
}

void Player::TakeDamage(int _Damage)
{
	HP -= _Damage;
	bTakeDamage = true;

	if ( HP <= 0 )
	{
		HP = 0;
		bDied = true;
	}
}

bool Player::RenderSpawn(HDC _hdc)
{
	if ( !pPlayerImage ) return false;

	// ** 화면 아래에서부터 일정 위치까지 서서히 올라오도록 그림	
	static float MovePositionY = WindowsHeight + 30;

	float MoveSpeed = 0.5f;
	float StopPositionY = WindowsHeight - 100;
	Vector3 ImagePosition = Vector3(42.0f, 0.0f);

	TransInfo.Position.x = WindowsWidth * 0.5f;
	TransInfo.Position.y = MovePositionY;

	TransparentBlt(_hdc, 
		(int)(TransInfo.Position.x - TransInfo.Scale.x * 0.5f),
		(int)(TransInfo.Position.y - TransInfo.Scale.y * 0.5f),
		(int)TransInfo.Scale.x,
		(int)TransInfo.Scale.y,
		pPlayerImage->GetMemDC(),
		(int)ImagePosition.x,
		(int)ImagePosition.y,
		(int)TransInfo.Scale.x,
		(int)TransInfo.Scale.y,
		RGB(255, 0, 255));

	if ( MovePositionY < StopPositionY )
	{
		MovePositionY = WindowsHeight + 30;
		return true;
	}

	MovePositionY -= MoveSpeed;
	return false;
}

void Player::RenderPlayer(HDC _hdc)
{
	if ( !pPlayerImage ) return;

	Vector3 ImagePosition = Vector3(0.0f, TransInfo.Scale.y * (Frame % 2 + 1));

	// ** Direction으로 방향을 체크하여 해당하는 이미지 포지션 적용
	if ( TransInfo.Direction.x < 0.0f )		 ImagePosition.x = 0.0f;  // ** Left
	else if ( TransInfo.Direction.x > 0.0f ) ImagePosition.x = 84.0f; // ** Right
	else									 ImagePosition.x = 42.0f; // ** None(Center)

	TransparentBlt(_hdc,
		(int)TransInfo.Position.x - (int)(TransInfo.Scale.x * 0.5f),
		(int)TransInfo.Position.y - (int)(TransInfo.Scale.y * 0.5f),
		(int)TransInfo.Scale.x,
		(int)TransInfo.Scale.y,
		pPlayerImage->GetMemDC(),
		(int)ImagePosition.x,
		(int)ImagePosition.y,
		(int)TransInfo.Scale.x,
		(int)TransInfo.Scale.y,
		RGB(255, 0, 255));
}

void Player::Release()
{
	Super::Release();
}

void Player::OnCollision(Object* _pObject)
{
}