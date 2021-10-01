#include "Background.h"
#include "Bridge.h"

Background::Background()
{
}

Background::~Background()
{	
}


void Background::Initialize()
{
	Super::Initialize();

	Key = eObjectKey::BACKGROUND;
	Status = eObjectStatus::ACTIVATED;
	CollisionType = eCollisionType::NONE;
	bGenerateCollisionEvent = false;

	pBridge = nullptr;
}

void Background::Update()
{	
	Super::Update();

	// ** 충돌체 갱신
	SetCollider(TransInfo);
}

void Background::Render(HDC _hdc)
{
	Super::Render(_hdc);
}

void Background::Release()
{
	Super::Release();
}

void Background::OnCollision(Object* _pObject)
{
}
