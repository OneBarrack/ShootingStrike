#include "Item.h"
#include "BitmapManager.h"

Item::Item()
	: itemType(eItemType::NONE)
{

}

Item::~Item()
{
}


void Item::Initialize()
{
	Super::Initialize();

	objectKey = eObjectKey::ITEM;
	objectStatus = eObjectStatus::ACTIVATED;
	collisionType = eCollisionType::RECT;

	bGenerateCollisionEvent = true;
	pImage = BitmapManager::GetInstance()->GetImage(eImageKey::ITEM);

	itemType = eItemType::NONE;
}

void Item::Update()
{
	Super::Update();
}

void Item::Render(HDC _hdc)
{
	Super::Render(_hdc);
}

void Item::Release()
{
	Super::Release();
}

void Item::OnCollision(Object* _pObject)
{
	if ( _pObject->GetKey() == eObjectKey::PLAYER )
		SetStatus(eObjectStatus::DESTROYED);
}