#include "GameDebugManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "Object.h"
#include "Bridge.h"

GameDebugManager* GameDebugManager::Instance = nullptr;

GameDebugManager::GameDebugManager()
	: bDebugMode(false)
{
}

GameDebugManager::~GameDebugManager()
{
}

void GameDebugManager::Initialize()
{
}

void GameDebugManager::Update()
{
	if ( CheckKeyInputState(eInputKey::KEY_F8, eKeyInputState::DOWN) )
	{
		bDebugMode ^= true;
	}
}

void GameDebugManager::Render(HDC _hdc)
{
	if ( !bDebugMode )
		return;

	auto EnableObjectList = ObjectManager::GetInstance()->GetEnableObjectList();
	auto EnableBridgeList = ObjectManager::GetInstance()->GetEnableBridgeList();

	for ( map<eObjectKey, list<Object*>>::iterator iter = EnableObjectList->begin();
		iter != EnableObjectList->end(); ++iter )
	{
		for ( list<Object*>::iterator iter2 = iter->second.begin();
			iter2 != iter->second.end(); ++iter2 )
		{
			Object* pObject = *iter2;
			switch ( pObject->GetCollisionType() )
			{
				// ** 사각형:빨간색, 원:파란색 선으로 표시
				case eCollisionType::RECT: RenderManager::DrawRect(_hdc, pObject->GetCollider(), RGB(255, 0, 0)); break;
				case eCollisionType::ELLIPSE: RenderManager::DrawEllipse(_hdc, pObject->GetCollider(), RGB(0, 0, 255)); break;
			}			
		}
	}
}

void GameDebugManager::Release()
{
}
