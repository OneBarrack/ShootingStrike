#include "GuideBullet.h"
#include "Object.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include "BitmapManager.h"
#include "MathManager.h"

GuideBullet::GuideBullet()
	: distToTarget(0.0f)
	, bLoopGuide(true)
	, bGuideEnd(false)
	, hasDelay(false)
	, time(0)
	, delay(0)
	, speedAfterDelay(0.0f)
	, accelerationAfterDelay(0.0f)
	, maxSpeed(0.0f)
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

	bLoopGuide = true;
	bGuideEnd = false;
	hasDelay = false;
	time = 0;
	delay = 0;
	directionAfterDelay = Vector3();
	speedAfterDelay = 0.0f;
	accelerationAfterDelay = 0.0f;
	maxSpeed = 10.0f;
}

void GuideBullet::Update()
{
	Super::Update();

	// ** Owner의 데이터를 받아옴
	ReceiveInfoFromOwner();

	// ** Delay가 있다면
	if ( hasDelay )
	{
		// ** Delay가 지나면 Delay 이후 설정될 값들을 적용 후 hasDelay를 false로 변경
		if ( time + delay < GetTickCount64() )
		{
			transInfo.Direction = directionAfterDelay;
			speed = speedAfterDelay;
			pOwner->SetAcceleration(accelerationAfterDelay);
			hasDelay = false;
		}
	}	

	// ** Delay가 종료되고 GuideEnd가 false라면 유도 진행
	if ( !hasDelay && !bGuideEnd )
	{
		CalcGuideDirection(transInfo.Position, transInfo.Direction);
		
		// ** 무한 유도가 아니라면 1회 유도 후 Guide를 중지한다.
		if ( !bLoopGuide )
			bGuideEnd = true;
	}

	// ** Speed 설정
	speed += pOwner->GetAcceleration();
	if ( speed > maxSpeed )
		speed = maxSpeed;

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

void GuideBullet::SetLoopGuide(bool _bLoopGuide)
{
	bLoopGuide = _bLoopGuide;
	bGuideEnd = false;
}

void GuideBullet::SetDelay(Vector3 _directionAfterDelay, float _speed, float _maxSpeed, float _acceleration, int _delay)
{
	hasDelay = true;
	time = GetTickCount64();
	delay = _delay;

	directionAfterDelay = _directionAfterDelay;
	speedAfterDelay = _speed;
	accelerationAfterDelay = _acceleration;
	maxSpeed = _maxSpeed;
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
	// ** 타겟이 되는 Object와 Key
	Object* targetObject = nullptr;
	eObjectKey targetObjectKey;

	// ** 현 Bullet의 Owner를 체크하여 상대되는 Object에 대한 리스트를 받아온다
	eObjectKey ownerObjectKey = static_cast<Bullet*>(pOwner)->GetOwner()->GetKey();	
	switch ( ownerObjectKey )
	{
		case eObjectKey::PLAYER:
			targetObjectKey = eObjectKey::ENEMY;			
			break;
		case eObjectKey::ENEMY:
			targetObjectKey = eObjectKey::PLAYER;
			break;
		default:
			targetObjectKey = eObjectKey::NONE;
			break;
	}	

	if ( targetObjectKey != eObjectKey::NONE )
	{
		list<Object*> objectList = ObjectManager::GetInstance()->GetObjectList(targetObjectKey);

		// ** 멀티맵을 만든다. Key = 거리, value = Object
		multimap<float, Object*> findTargetList;

		// ** 모든 적 유닛리스트를 돌면서 확인한다.
		for ( Object* TargetObject : objectList )
		{
			// ** 활성화 되었고 Collision event가 작동하는 Object에 대해서 동작
			if ( TargetObject->GetStatus() == eObjectStatus::ACTIVATED && 
				TargetObject->IsGeneratedCollisionEvent() )
			{
				// ** Current 와 Target 의 거리를 구해서 멀티맵에 추가한다.
				float distance = MathManager::GetDistance(_pos, TargetObject->GetPosition());
				findTargetList.insert(make_pair(distance, TargetObject));
			}
		}

		// ** 만약에 리스트에 아무것도 없다면....
		if ( findTargetList.empty() )
			return nullptr;

		// ** 가장 첫번째에 있 (가장 가까운) 오브젝트와의 거리 저장
		distToTarget = findTargetList.begin()->first;

		// ** 모든 오브젝트의 추가작업이 끝나면 가장 첫번째에 있는 오브젝트를 반환한다.
		targetObject = findTargetList.begin()->second;
	}

	return targetObject;
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
