#include "Player.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "BitmapManager.h"
#include "Bridge.h"
#include "NormalBullet.h"
#include "MathManager.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	TransInfo.Position = Vector3(WindowsWidth / 2, WindowsHeight / 2);
	TransInfo.Scale = Vector3(42.0f, 47.0f);

	Collider.Position = Vector3(TransInfo.Position.x, TransInfo.Position.y);
	Collider.Scale = Vector3(42.0f, 47.0f);

	Key = eObjectKey::PLAYER;
	Status = eObjectStatus::DEACTIVATED;
	CollisionType = eCollisionType::RECT;
	OldPosition = TransInfo.Position;

	HP = 3;

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
	Frame++;

	if ( bDied )
	{
		
	}

	if ( HP <= 0 )
		return;

	if ( bSpawing )
	{
		
	}
	else if ( bAttacking )
	{

	}
	else
	{
		//TransInfo.Position = InputManager::GetInstance()->GetMousePosition();
		//Collider.Position = InputManager::GetInstance()->GetMousePosition();
		// ** _DEBUG_
		if ( CheckKeyInputStatus(eInputKey::KEY_ENTER, eKeyInputStatus::DOWN) )
		{
			Spawn();
		}

		if ( CheckKeyInputStatus(eInputKey::KEY_LEFT, eKeyInputStatus::PRESSED) )
		{
			TransInfo.Position.x -= 3;
		}
		if ( CheckKeyInputStatus(eInputKey::KEY_UP, eKeyInputStatus::PRESSED) )
		{
			TransInfo.Position.y -= 3;
		}
		if ( CheckKeyInputStatus(eInputKey::KEY_RIGHT, eKeyInputStatus::PRESSED) )
		{
			TransInfo.Position.x += 3;
		}
		if ( CheckKeyInputStatus(eInputKey::KEY_DOWN, eKeyInputStatus::PRESSED) )
		{
			TransInfo.Position.y += 3;
		}

		if ( CheckKeyInputStatus(eInputKey::KEY_SPACE, eKeyInputStatus::DOWN) )
		{
			Bridge* pBridge = new NormalBullet;
			ObjectManager::GetInstance()->TakeObject(eObjectKey::BULLET, TransInfo.Position, pBridge);
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

	// ** 플레이어가 화면 밖으로 나가지 않도록 처리	
	CheckPositionInsideScreen();

	return;
}

void Player::Render(HDC _hdc)
{
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
		bDied = false;
		//return;
	}
		
	// ** 피해를 입었을 시
	if ( bTakeDamage )
	{

	}

	// ** 일반 출력
	RenderPlayer(_hdc);	
}

void Player::TakeDamage()
{
	bTakeDamage = true;

	return;
}

void Player::CheckPositionInsideScreen()
{
	float Offset = 22.0f;
	float StageScaleX = 600.0f;
	
	RECT ScreenRect;
	ScreenRect.left   = (LONG)((WindowsWidth / 2) - (StageScaleX / 2));
	ScreenRect.top	  = 0;
	ScreenRect.right  = (LONG)((WindowsWidth / 2) + (StageScaleX / 2));
	ScreenRect.bottom = WindowsHeight;
		
	// ** 좌
	if ( (LONG)TransInfo.Position.x < ScreenRect.left + Offset )
		TransInfo.Position.x = ScreenRect.left + Offset;

	// ** 우
	if ( (LONG)TransInfo.Position.x > ScreenRect.right - Offset )
		TransInfo.Position.x = ScreenRect.right - Offset;

	// ** 상
	if ( (LONG)TransInfo.Position.y < Offset )
		TransInfo.Position.y = Offset;

	// ** 하
	if ( (LONG)TransInfo.Position.y > WindowsHeight - Offset )
		TransInfo.Position.y = WindowsHeight - Offset;
}

bool Player::RenderSpawn(HDC _hdc)
{
	// ** 화면 아래에서부터 일정 위치까지 서서히 올라오도록 그림	
	static float MovePositionY = WindowsHeight + 30;

	float MoveSpeed = 0.5f;
	float StopPositionY = WindowsHeight - 100;
	Vector3 ImagePosition = Vector3(42.0f, 0.0f);

	TransInfo.Position.x = WindowsWidth / 2;
	TransInfo.Position.y = MovePositionY;

	TransparentBlt(_hdc, 
		(int)(TransInfo.Position.x - TransInfo.Scale.x / 2),
		(int)(TransInfo.Position.y - TransInfo.Scale.y / 2),
		(int)TransInfo.Scale.x,
		(int)TransInfo.Scale.y,
		BitmapManager::GetInstance()->GetMemDC(eImageKey::PLAYER),
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
	Vector3 ImagePosition = Vector3(0.0f, TransInfo.Scale.y * (Frame % 2 + 1));

	// ** Direction으로 방향을 체크하여 해당하는 이미지 포지션 적용
	if ( TransInfo.Direction.x < 0.0f )		 ImagePosition.x = 0.0f;  // ** Left
	else if ( TransInfo.Direction.x > 0.0f ) ImagePosition.x = 84.0f; // ** Right
	else									 ImagePosition.x = 42.0f; // ** None(Center)

	TransparentBlt(_hdc,
		(int)TransInfo.Position.x - (int)TransInfo.Scale.x / 2,
		(int)TransInfo.Position.y - (int)TransInfo.Scale.y / 2,
		(int)TransInfo.Scale.x,
		(int)TransInfo.Scale.y,
		BitmapManager::GetInstance()->GetMemDC(eImageKey::PLAYER),
		(int)ImagePosition.x,
		(int)ImagePosition.y,
		(int)TransInfo.Scale.x,
		(int)TransInfo.Scale.y,
		RGB(255, 0, 255));
}

void Player::Release()
{
	
}

void Player::OnCollision(Object* _pObject)
{
}