#include "GameDebugManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "GameDataManager.h"
#include "Object.h"
#include "Bridge.h"

GameDebugManager* GameDebugManager::pInstance = nullptr;

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
	// ** F8을 누르면 Debug 모드가 실행되도록
	if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_F8, eKeyInputState::DOWN) )
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
	RECT textBoundary;
	textBoundary.left = 0;
	textBoundary.top = 0;
	textBoundary.right = 500;
	textBoundary.bottom = WINDOWS_HEIGHT;

	int FPS = GameDataManager::GetInstance()->GetFPS();
	auto enemyList = ObjectManager::GetInstance()->GetObjectList(eObjectKey::ENEMY);
	auto bulletList = ObjectManager::GetInstance()->GetObjectList(eObjectKey::BULLET);
	Vector3 playerPos = ObjectManager::GetInstance()->GetPlayer()->GetPosition();
	
	string tempStr = "";
	tempStr += "FPS : " + to_string(FPS) + "\n";
	tempStr += "Enemy Count : " + to_string(enemyList.size()) + "\n";		
	tempStr += "Bullet Count : " + to_string(bulletList.size()) + "\n";
	tempStr += "Player Position : " + to_string(playerPos.x) + " " + to_string(playerPos.y);
	
	wstring resultStr = wstring(tempStr.begin(), tempStr.end());
	DrawText(_hdc, resultStr.c_str(), resultStr.length(), &textBoundary, DT_LEFT | DT_WORDBREAK);
}

void GameDebugManager::DrawCollisionBoundary(HDC _hdc)
{
	auto enableObjectList = ObjectManager::GetInstance()->GetEnableObjectList();
	auto enableBridgeList = ObjectManager::GetInstance()->GetEnableBridgeList();

	for ( map<eObjectKey, list<Object*>>::iterator iter = enableObjectList->begin();
		iter != enableObjectList->end(); ++iter )
	{
		for ( list<Object*>::iterator iter2 = iter->second.begin();
			iter2 != iter->second.end(); ++iter2 )
		{
			Object* pObject = *iter2;
			switch ( pObject->GetCollisionType() )
			{
				// ** 사각형:빨간색, 원:파란색 선으로 표시
				case eCollisionType::RECT: 
					RenderManager::DrawRect(_hdc, pObject->GetCollider(), RGB(255, 0, 0)); 
					break;
				case eCollisionType::ELLIPSE: 
					RenderManager::DrawEllipse(_hdc, pObject->GetCollider(), RGB(0, 0, 255)); 
					break;
			}
		}
	}
}
