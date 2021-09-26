#include "GuideBullet.h"
#include "Object.h"
#include "ObjectManager.h"
#include "BitmapManager.h"
#include "MathManager.h"

GuideBullet::GuideBullet() 
	: pBulletImage(nullptr)
	, BulletImageScale(Vector3())
{
	Initialize();
}

GuideBullet::~GuideBullet()
{
	Release();
}


void GuideBullet::Initialize()
{
	pBulletImage = BitmapManager::GetInstance()->GetImage(eImageKey::PROJECTILE);
	BulletImageScale = Vector3(230.0f, 230.0f);

	Speed = 3.0f;
}

void GuideBullet::Update()
{
	// ** Owner의 데이터를 받아옴
	ReceiveInfo();

	CalcGuideDirection(TransInfo.Position, TransInfo.Direction);

	TransInfo.Position.x += TransInfo.Direction.x * Speed;
	TransInfo.Position.y += TransInfo.Direction.y * Speed;

	// ** Owner로 가공된 데이터 전달
	SendInfo();
}


void GuideBullet::Render(HDC _hdc)
{
	if ( pBulletImage )
		RenderBullet(_hdc);
}

void GuideBullet::Release()
{

}

void GuideBullet::CalcGuideDirection(Vector3 _Pos, Vector3& _rDirection)
{
	// ** 가장 가까운 적 탐색
	Object* Target = FindTarget(_Pos);

	// ** 찾았다면 해당 적 방향으로 Direction 갱신
	if ( Target )
		_rDirection = MathManager::GetDirection(_Pos, Target->GetPosition());
}

Object* GuideBullet::FindTarget(Vector3 _Pos)
{
	list<Object*> ObjectList; 

	// ** 상대되는 Object의 List를 받아온다
	eObjectKey OwnerObjectKey = pOwner->GetKey();
	switch ( OwnerObjectKey )
	{
		case eObjectKey::PLAYER:
			ObjectList = ObjectManager::GetInstance()->GetObjectList(eObjectKey::ENEMY);
			break;
		case eObjectKey::ENEMY:
			ObjectList = ObjectManager::GetInstance()->GetObjectList(eObjectKey::PLAYER);
			break;
		default:
			break;
	}	

	// ** 멀티맵을 만든다. Key = 거리, value = Object
	multimap<float, Object*> FindTargetList;

	// ** 모든 적 유닛리스트를 돌면서 확인한다.
	for ( Object* TargetObject : ObjectList )
	{
		// ** Current 와 Target 의 거리를 구해서 멀티맵에 추가한다.
		float Distance = MathManager::GetDistance(_Pos, TargetObject->GetPosition());		
		FindTargetList.insert(make_pair(Distance,TargetObject));
	}

	// ** 만약에 리스트에 아무것도 없다면....
	if ( FindTargetList.empty() )
		return nullptr;

	// ** 모든 오브젝트의 추가작업이 끝나면 가장 첫번째에 있는 오브젝트를 반환한다.
	return FindTargetList.begin()->second;
}

void GuideBullet::RenderBullet(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		(int)(TransInfo.Position.x - (TransInfo.Scale.x * 0.5f)),
		(int)(TransInfo.Position.y - (TransInfo.Scale.y * 0.5f)),
		(int)TransInfo.Scale.x,
		(int)TransInfo.Scale.y,
		pBulletImage->GetMemDC(),
		(int)TransInfo.Scale.x,
		0,
		(int)TransInfo.Scale.x,
		(int)TransInfo.Scale.y,
		RGB(255, 0, 255));
}
