#include "GoToPlayerItem.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "MathManager.h"
#include "GameDataManager.h"

GoToPlayerItem::GoToPlayerItem()
	: guideTime(0)
	, guideDelayTime(0)
	, bGuidePlayer(false)
{

}

GoToPlayerItem::~GoToPlayerItem()
{
}


void GoToPlayerItem::Initialize()
{
	Super::Initialize();

	key = eBridgeKey::ITEM_GO_TO_PLAYER;

	guideTime = GetTickCount64();
	guideDelayTime = 1000;

	bGuidePlayer = false;
}

void GoToPlayerItem::Update()
{
	Super::Update();

	ReceiveInfoFromOwner();

	// 유도중이지 않을때는 속도를 줄이고 유도중일때 속도를 높인다.
	if ( !bGuidePlayer )
	{
		speed -= acceleration;
	}
	else
	{
		speed += (acceleration * 2.0f);
	}


	// ** speed가 0가 되는 시점부터 플레이어 유도 시작
	if ( speed <= 0.0f )
	{
		bGuidePlayer = true;
		speed = 0.0f;
	}

	// ** Player 위치로 유도
	if ( bGuidePlayer )
		CalcGuideDirectionForPlayer(transInfo.Position, transInfo.Direction);

	// ** 일정 시간(guideDelayTime)이 지나면
	//if ( guideTime + guideDelayTime < GetTickCount64() )
	//{
	//	// ** Player 위치로 유도
	//	CalcGuideDirectionForPlayer(transInfo.Position, transInfo.Direction);
	//}

	transInfo.Position.x += transInfo.Direction.x * speed;
	transInfo.Position.y += transInfo.Direction.y * speed;

	collider = transInfo;

	SendInfoToOwner();
}

void GoToPlayerItem::Render(HDC _hdc)
{
	Super::Render(_hdc);
	
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
		case eItemType::COIN:
			segmentationOffset = Point(GameDataManager::GetInstance()->GetFrame() % 7, 1);
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

void GoToPlayerItem::Release()
{
	Super::Release();
}

void GoToPlayerItem::CalcGuideDirectionForPlayer(Vector3 _pos, Vector3& _rDirection)
{
	// ** 플레이어 탐색
	Object* pPlayer = ObjectManager::GetInstance()->GetPlayer();

	// ** 찾았다면 해당 적 방향으로 Direction 갱신
	if ( pPlayer )
		_rDirection = MathManager::GetDirection(_pos, pPlayer->GetPosition());
}