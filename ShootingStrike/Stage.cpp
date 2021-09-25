#include "Stage.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "EnemyHole.h"
#include "HammerEffect.h"
#include "ObjectFactory.h"
#include "CollisionManager.h"
#include "ScrollVerticalBkg.h"
#include "StageSideBackground.h"
#include "BitmapManager.h"
#include "SpawnManager.h"

Stage::Stage() 
	: pPlayer(nullptr)
	, pBackground(nullptr)
	, pSideBackground(nullptr)
{

}

Stage::~Stage()
{
	Release();
}

void Stage::Initialize()
{
	// ** Player
	pPlayer = ObjectManager::GetInstance()->GetPlayer();

	// ** Main Scrolling Background
	Bridge* pBridge = new ScrollVerticalBkg;
	pBackground = ObjectManager::GetInstance()->TakeObject(eObjectKey::BACKGROUND, pBridge);
	pBackground->SetImage(BitmapManager::GetInstance()->GetImage(eImageKey::STAGEBACK));
	pBackground->SetSpeed(0.5f);

	Transform StageBkgTransInfo;
	StageBkgTransInfo.Position = Vector3(WindowsWidth * 0.5f, WindowsHeight * 0.5f);
	StageBkgTransInfo.Scale = Vector3(600.0f, 5527.0f);
	pBackground->SetTransInfo(StageBkgTransInfo);

	Transform StageBkgCollider;
	StageBkgCollider.Position = StageBkgTransInfo.Position;
	StageBkgCollider.Scale = Vector3(600.0f, WindowsHeight);
	pBackground->SetCollider(StageBkgCollider);

	// ** Side Background
	pBridge = new StageSideBackground;
	pSideBackground = ObjectManager::GetInstance()->TakeObject(eObjectKey::FOREGROUND, pBridge);

	// ** Spawn Player
	SpawnManager::SpawnPlayer();
}

void Stage::Update()
{
	ObjectManager::GetInstance()->Update();

	// ** 해당 오브젝트들이 메인 Background 내부를 벗어났는지 체크
	CheckPositionInBkgBoundary(eObjectKey::PLAYER);
	CheckPositionInBkgBoundary(eObjectKey::ENEMY);
	CheckPositionInBkgBoundary(eObjectKey::BULLET);
}

void Stage::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);
}

void Stage::Release()
{
	if ( pBackground )
	{
		pBackground->Release();
		ObjectManager::GetInstance()->RecallObject(pBackground);	
	}
}

void Stage::CheckPositionInBkgBoundary(eObjectKey _ObjectKey)
{
	// ** Stage의 바운더리
	RectF ScreenRect = pBackground->GetColliderF();

	// ** Key에 해당하는 Object List를 받아옴
	list<Object*> ObjectList = ObjectManager::GetInstance()->GetObjectList(_ObjectKey);

	// ** List를 돌며 Position 체크
	for ( Object* pObject : ObjectList )
	{
		// ** Object의 Position과 
		Vector3 ObjectPosition = pObject->GetPosition();		

		float Offset = 0.0f;
		switch ( pObject->GetKey() )
		{
			case eObjectKey::PLAYER:
				// ** 테두리 경계선 기준에 몸체가 잘리지 않게 하기 위한 Offset 값
				Offset = 22.0f;

				// ** 좌
				if ( ObjectPosition.x < ScreenRect.Left + Offset )
					ObjectPosition.x = ScreenRect.Left + Offset;
				// ** 우
				if ( ObjectPosition.x > ScreenRect.Right - Offset )
					ObjectPosition.x = ScreenRect.Right - Offset;
				// ** 상
				if ( ObjectPosition.y < ScreenRect.Top - Offset )
					ObjectPosition.y = ScreenRect.Top - Offset;
				// ** 하
				if ( ObjectPosition.y > ScreenRect.Bottom - Offset )
					ObjectPosition.y = ScreenRect.Bottom - Offset;

				// ** 계산된 Position을 다시 플레이어에 세팅
				pObject->SetPosition(ObjectPosition);

				break;
			case eObjectKey::ENEMY:
				[[fallthrough]];
			case eObjectKey::BULLET:
				// ** Stage 바운더리를 넓힐 여유분 길이의 Offset
				Offset = 0.0f;

				// ** Stage 바운더리를 Offset 만큼 넓힌다
				ScreenRect.Left   -= Offset;
				ScreenRect.Top    -= Offset;
				ScreenRect.Right  += Offset;
				ScreenRect.Bottom += Offset;

				// ** Stage의 바운더리 내 Object Position이 위치하지 않으면 Destroy
				if ( !CollisionManager::IsPointInRect(ScreenRect, ObjectPosition) )
				{
					pObject->SetStatus(eObjectStatus::DESTROYED);
				}
				break;
			default:
				break;
		}
	}
}