#include "GameDebugManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "GameDataManager.h"
#include "Object.h"
#include "Bridge.h"

GameDebugManager* GameDebugManager::Instance = nullptr;

GameDebugManager::GameDebugManager()
	: bDebugMode(eDebugMode::NONE)
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
		if ( bDebugMode == eDebugMode::ALL )
		{
			bDebugMode = eDebugMode::NONE;
		}
		else
		{
			bDebugMode = static_cast<eDebugMode>(static_cast<int>(bDebugMode) + 1);
		}
	}
}

void GameDebugManager::Render(HDC _hdc)
{
	if ( bDebugMode == eDebugMode::NONE ) 
		return;

	if ( bDebugMode == eDebugMode::PRINT_TEXTINFO || bDebugMode == eDebugMode::ALL ) 
		PrintTextForGameInfo(_hdc);

	if ( bDebugMode == eDebugMode::DRAW_COLLISION || bDebugMode == eDebugMode::ALL ) 
		DrawCollisionBoundary(_hdc);
}

void GameDebugManager::Release()
{	
}

void GameDebugManager::PrintTextForGameInfo(HDC _hdc)
{
	RECT TextBoundary;
	TextBoundary.left = 0;
	TextBoundary.top = 0;
	TextBoundary.right = 500;
	TextBoundary.bottom = WindowsHeight;

	int FPS = GameDataManager::GetInstance()->GetFPS();
	auto EnemyList = ObjectManager::GetInstance()->GetObjectList(eObjectKey::ENEMY);
	auto BulletList = ObjectManager::GetInstance()->GetObjectList(eObjectKey::BULLET);
	Vector3 PlayerPos = ObjectManager::GetInstance()->GetPlayer()->GetPosition();
	
	string TempStr = "";
	TempStr += "FPS : " + to_string(FPS) + "\n";
	TempStr += "Enemy Count : " + to_string(EnemyList.size()) + "\n";		
	TempStr += "Bullet Count : " + to_string(BulletList.size()) + "\n";
	TempStr += "Player Position : " + to_string(PlayerPos.x) + " " + to_string(PlayerPos.y);
	
	wstring ResultStr = wstring(TempStr.begin(), TempStr.end());
	DrawText(_hdc, ResultStr.c_str(), ResultStr.length(), &TextBoundary, DT_LEFT | DT_WORDBREAK);
}

void GameDebugManager::DrawCollisionBoundary(HDC _hdc)
{
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
