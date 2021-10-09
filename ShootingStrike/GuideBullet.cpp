#include "GuideBullet.h"
#include "Object.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include "BitmapManager.h"
#include "MathManager.h"

GuideBullet::GuideBullet()
	: distToTarget(0.0f)
{
}

GuideBullet::~GuideBullet()
{
}


void GuideBullet::Initialize()
{
	Super::Initialize();

	key = eBridgeKey::BULLET_GUIDE;

	speed = 3.0f;

	distToTarget = 0.0f;
}

void GuideBullet::Update()
{
	Super::Update();

	// ** Owner의 데이터를 받아옴
	ReceiveInfoFromOwner();

	CalcGuideDirection(transInfo.Position, transInfo.Direction);

	transInfo.Position.x += transInfo.Direction.x * speed;
	transInfo.Position.y += transInfo.Direction.y * speed;

	// ** Owner로 가공된 데이터 전달
	SendInfoToOwner();
}


void GuideBullet::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( pImage )
		RenderBullet(_hdc);
}

void GuideBullet::Release()
{
	Super::Release();
}

void GuideBullet::CalcGuideDirection(Vector3 _pos, Vector3& _rDirection)
{
	// ** 가장 가까운 적 탐색
	Object* target = FindTarget(_pos);

	// ** 찾았다면 해당 적 방향으로 Direction 갱신
	if ( target )
		_rDirection = MathManager::GetDirection(_pos, target->GetPosition());
}

Object* GuideBullet::FindTarget(Vector3 _pos)
{
	list<Object*> objectList; 

	// ** 현 Bullet의 Owner를 체크하여 상대되는 Object에 대한 리스트를 받아온다
	eObjectKey OwnerObjectKey = static_cast<Bullet*>(pOwner)->GetOwner()->GetKey();
	switch ( OwnerObjectKey )
	{
		case eObjectKey::PLAYER:
			objectList = ObjectManager::GetInstance()->GetObjectList(eObjectKey::ENEMY);
			break;
		case eObjectKey::ENEMY:
			objectList = ObjectManager::GetInstance()->GetObjectList(eObjectKey::PLAYER);
			break;
		default:
			break;
	}	

	// ** 멀티맵을 만든다. Key = 거리, value = Object
	multimap<float, Object*> findTargetList;

	// ** 모든 적 유닛리스트를 돌면서 확인한다.
	for ( Object* TargetObject : objectList )
	{
		// ** Current 와 Target 의 거리를 구해서 멀티맵에 추가한다.
		float distance = MathManager::GetDistance(_pos, TargetObject->GetPosition());		
		findTargetList.insert(make_pair(distance,TargetObject));
	}

	// ** 만약에 리스트에 아무것도 없다면....
	if ( findTargetList.empty() )
		return nullptr;
		
	// ** 가장 첫번째에 있 (가장 가까운) 오브젝트와의 거리 저장
	distToTarget = findTargetList.begin()->first;

	// ** 모든 오브젝트의 추가작업이 끝나면 가장 첫번째에 있는 오브젝트를 반환한다.
	return findTargetList.begin()->second;
}

void GuideBullet::RenderBullet(HDC _hdc)
{
	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pOwner->GetImage()->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * pOwner->GetImageOffsetOrder().x),
		(int)(pImage->GetSegmentationScale().y * pOwner->GetImageOffsetOrder().y),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(255, 0, 255));
}
