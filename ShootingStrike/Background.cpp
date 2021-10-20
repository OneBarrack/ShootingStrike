#include "Background.h"
#include "Bridge.h"

Background::Background(bool _isForeBkg)
	: mapProgressRatio(0.0f)
	, isForeBkg(_isForeBkg)
{
}

Background::~Background()
{	
}


void Background::Initialize()
{
	Super::Initialize();

	if ( isForeBkg ) 
		objectKey = eObjectKey::FOREGROUND;
	else
		objectKey = eObjectKey::BACKGROUND;
	
	objectStatus = eObjectStatus::ACTIVATED;
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
