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
	pBulletImage = BitmapManager::GetInstance()->GetImage(eImageKey::PROJECTILE);
	BulletImageScale = Vector3(230.0f, 230.0f);
	BulletRenderScale = Vector3(10.0f, 10.0f);

	Speed = 3.0f;

	DrawKey = "NormalBullet";
}

void GuideBullet::Update(Transform& _rTransInfo)
{
	CalcGuideDirection(_rTransInfo);

	_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
	_rTransInfo.Position.y += _rTransInfo.Direction.y * Speed;
}


void GuideBullet::Render(HDC _hdc)
{
	if ( pBulletImage )
		RenderBullet(_hdc);
}

void GuideBullet::Release()
{

}

void GuideBullet::CalcGuideDirection(Transform& _rTransInfo)
{
	Object* Target = FindTarget(_rTransInfo.Position);

	if ( Target )
		_rTransInfo.Direction = MathManager::GetDirection(_rTransInfo.Position, Target->GetPosition());
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
		(int)(pOwner->GetPosition().x - (BulletRenderScale.x * 0.5f)),
		(int)(pOwner->GetPosition().y - (BulletRenderScale.y * 0.5f)),
		(int)BulletRenderScale.x,
		(int)BulletRenderScale.y,
		pBulletImage->GetMemDC(),
		(int)BulletImageScale.x,
		0,
		(int)BulletImageScale.x,
		(int)BulletImageScale.y,
		RGB(255, 0, 255));
}
