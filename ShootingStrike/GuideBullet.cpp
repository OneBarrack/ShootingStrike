#include "GuideBullet.h"
#include "Object.h"
#include "ObjectManager.h"
#include "BitmapManager.h"
#include "MathManager.h"

GuideBullet::GuideBullet()
{
}

GuideBullet::~GuideBullet()
{
}


void GuideBullet::Initialize()
{
	if ( pOwner )
		ReceiveInfoFromOwner();

	key = eBridgeKey::BULLET_GUIDE;

	speed = 3.0f;
}

void GuideBullet::Update()
{
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
	if ( pImage )
		RenderBullet(_hdc);
}

void GuideBullet::Release()
{

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

	// ** 상대되는 Object의 List를 받아온다
	eObjectKey OwnerObjectKey = pOwner->GetKey();
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

	// ** 모든 오브젝트의 추가작업이 끝나면 가장 첫번째에 있는 오브젝트를 반환한다.
	return findTargetList.begin()->second;
}

void GuideBullet::RenderBullet(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		(int)(transInfo.Position.x - (transInfo.Scale.x * 0.5f)),
		(int)(transInfo.Position.y - (transInfo.Scale.y * 0.5f)),
		(int)transInfo.Scale.x,
		(int)transInfo.Scale.y,
		pImage->GetMemDC(),
		(int)transInfo.Scale.x,
		0,
		(int)transInfo.Scale.x,
		(int)transInfo.Scale.y,
		RGB(255, 0, 255));
}
