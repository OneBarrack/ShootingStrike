#include "BounceOnWallItem.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "MathManager.h"

BounceOnWallItem::BounceOnWallItem()
	: itemDirection(Vector3(1.0f, 0.0f))
{

}

BounceOnWallItem::~BounceOnWallItem()
{
}


void BounceOnWallItem::Initialize()
{
	Super::Initialize();

	key = eBridgeKey::ITEM_BOUNCE_ON_WALL;

	// ** 0 ~ 359 까지의 각도를 무작위 생성하여 랜덤 방향을 설정한다. ( 360도 = 0도 )
	itemDirection = MathManager::RotateByDegree(itemDirection, static_cast<float>(rand() % 360));
}

void BounceOnWallItem::Update()
{
	Super::Update();

	ReceiveInfoFromOwner();

	CalcDirectionForBounceOnWall(transInfo);

	transInfo.Direction = itemDirection;

	transInfo.Position.x += transInfo.Direction.x * speed;
	transInfo.Position.y += transInfo.Direction.y * speed;

	collider = transInfo;
	
	SendInfoToOwner();	
}

void BounceOnWallItem::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( !pImage )
		return;

	Point segmentationOffset;
	switch ( itemType )
	{
		case eItemType::POWER_MAX:
			segmentationOffset = Point(0, 0);
			break;
		case eItemType::POWER_UP:
			segmentationOffset = Point(1, 0);
			break;		
		case eItemType::LIFE_UP:
			segmentationOffset = Point(2, 0);
			break;
		default:
			// ** 위 ItemType이 아니면 그리지 않는다
			return;
	}

	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		int(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		int(pOwner->GetScale().x),
		int(pOwner->GetScale().y),
		pImage->GetMemDC(),
		int(pImage->GetSegmentationScale().x * segmentationOffset.x),
		int(pImage->GetSegmentationScale().y * segmentationOffset.y),
		int(pImage->GetSegmentationScale().x),
		int(pImage->GetSegmentationScale().y),
		RGB(255, 0, 255));

	//RenderManager::DrawRect(_hdc, pOwner->GetTransInfo(), RGB(255, 228, 0));
}

void BounceOnWallItem::Release()
{
	Super::Release();
}

void BounceOnWallItem::CalcDirectionForBounceOnWall(Transform& _transInfo)
{
	RectF stageBkgCollider = ObjectManager::GetInstance()->FindObjectWithTag(eTagName::STAGE_MAIN_BKG)->GetColliderF();

	if ( _transInfo.Position.x - (_transInfo.Scale.x * 0.5f) < stageBkgCollider.Left )
	{
		_transInfo.Position.x = stageBkgCollider.Left + (_transInfo.Scale.x * 0.5f);
		itemDirection.x *= -1.0f;
	}
	if ( _transInfo.Position.y - (_transInfo.Scale.y * 0.5f) < stageBkgCollider.Top )
	{
		_transInfo.Position.y = stageBkgCollider.Top + (_transInfo.Scale.y * 0.5f);
		itemDirection.y *= -1.0f;
	}
	if ( _transInfo.Position.x + (_transInfo.Scale.x * 0.5f) > stageBkgCollider.Right )
	{
		_transInfo.Position.x = stageBkgCollider.Right - (_transInfo.Scale.x * 0.5f);
		itemDirection.x *= -1.0f;
	}
	if ( _transInfo.Position.y + (_transInfo.Scale.y * 0.5f) > stageBkgCollider.Bottom )
	{
		_transInfo.Position.y = stageBkgCollider.Bottom - (_transInfo.Scale.y * 0.5f);
		itemDirection.y *= -1.0f;
	}
}