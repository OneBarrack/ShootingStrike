#include "Player.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "BitmapManager.h"
#include "Bullet.h"


Player::Player()
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	TransInfo.Position = Vector3(WindowsWidth / 2, WindowsHeight / 2);
	TransInfo.Scale = Vector3(482.0f, 424.0f);

	Collider.Position = Vector3(TransInfo.Position.x, TransInfo.Position.y - 20.0f);
	Collider.Scale = Vector3(120.0f, 60.0f);

	Key = eObjectKey::PLAYER;
	Status = eObjectStatus::ACTIVATED;
	CollisionType = eCollisionType::RECT;

	Speed = 3.0f;

	Drop = false;
	bJump = false;

	Frame = 0;
	OldPositionY = 0.0f;
	JumpSpeed = 8.0f;
	JumpTime = 0.0f;

	Offset = Vector3(95.0f, -85.0f);
}

int Player::Update()
{
	TransInfo.Position = InputManager::GetInstance()->GetMousePosition();
	Collider.Position = InputManager::GetInstance()->GetMousePosition();

	DWORD dwKey = InputManager::GetInstance()->GetKeyInfo().Key;

	//if (dwKey & KEY_LBUTTON)
	//	Frame = 1;
	//else
	//	Frame = 0;

	return 0;
}

void Player::Render(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		TransInfo.Position.x,
		TransInfo.Position.y,
		75,
		81,
		BitmapManager::GetInstance()->GetMemDC(eImageKey::PLAYER),
		30,
		0,
		40,
		43,
		RGB(0, 91, 127));

	//TransparentBlt(_hdc, // ** 최종 출력 위치
	//	TransInfo.Position.x - (TransInfo.Scale.x / 2) + Offset.x,
	//	TransInfo.Position.y - (TransInfo.Scale.y / 2) + Offset.y,
	//	TransInfo.Scale.x,
	//	TransInfo.Scale.y,
	//	BitmapManager::GetInstance()->GetMemDC(eImageKey::HAMMER),
	//	TransInfo.Scale.x * Frame,
	//	0,
	//	TransInfo.Scale.x,
	//	TransInfo.Scale.y,
	//	RGB(255, 0, 255));
}

void Player::Release()
{
	
}

void Player::OnCollision(Object* _pObject)
{
}

void Player::Jump()
{
	if (bJump)
		return;

	bJump = true;
	OldPositionY = TransInfo.Position.y;
	JumpTime = 0.0f;
} 