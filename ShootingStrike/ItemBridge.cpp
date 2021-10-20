#include "ItemBridge.h"
#include "Item.h"

ItemBridge::ItemBridge()
	: pImage(nullptr)
	, transInfo(Transform())
	, speed(0.0f)
	, acceleration(0.0f)
	, itemType(eItemType::NONE)
{
}

ItemBridge::~ItemBridge()
{
}

void ItemBridge::Initialize()
{
	if ( pOwner )
	{
		pImage = pOwner->GetImage();
		transInfo = pOwner->GetTransInfo();
		speed = pOwner->GetSpeed();
		acceleration = pOwner->GetAcceleration();
		itemType = static_cast<Item*>(pOwner)->GetItemType();
	}
}

void ItemBridge::Update()
{
}

void ItemBridge::Render(HDC _hdc)
{
}

void ItemBridge::Release()
{
	pOwner = nullptr;
	pImage = nullptr;
}

void ItemBridge::ReceiveInfoFromOwner()
{
	if ( pOwner )
	{
		if ( !pImage )
			pImage = pOwner->GetImage();

		transInfo = pOwner->GetTransInfo();
		collider = pOwner->GetCollider();
		speed = pOwner->GetSpeed();
		acceleration = pOwner->GetAcceleration();
		itemType = static_cast<Item*>(pOwner)->GetItemType();
	}
}

void ItemBridge::SendInfoToOwner()
{
	if ( pOwner )
	{
		pOwner->SetTransInfo(transInfo);
		pOwner->SetCollider(collider);
		pOwner->SetSpeed(speed);
		pOwner->SetAcceleration(acceleration);
		static_cast<Item*>(pOwner)->SetItemType(itemType);
	}
}