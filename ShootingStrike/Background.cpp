#include "Background.h"
#include "Bridge.h"

Background::Background()
	: mapProgressRatio(0.0f)
{
}

Background::~Background()
{	
}


void Background::Initialize()
{
	Super::Initialize();

	key = eObjectKey::BACKGROUND;
	status = eObjectStatus::ACTIVATED;
	collisionType = eCollisionType::NONE;
	bGenerateCollisionEvent = false;
	mapProgressRatio = 0.0f;

	pBridge = nullptr;
}

void Background::Update()
{	
	Super::Update();

	// ** 충돌체 갱신
	SetCollider(transInfo);
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
