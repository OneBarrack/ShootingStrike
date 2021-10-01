#include "Stage.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyHole.h"
#include "HammerEffect.h"
#include "ObjectFactory.h"
#include "CollisionManager.h"
#include "Background.h"
#include "BasicBkg.h"
#include "ScrollVerticalBkg.h"
#include "BitmapManager.h"
#include "SpawnManager.h"

Stage::Stage() 
	: pPlayer(nullptr)
	, pBackground(nullptr)
	, pLeftSideBackground(nullptr)
	, pRightSideBackground(nullptr)
{

}

Stage::~Stage()
{
	Release();
}

void Stage::Initialize()
{
	Bridge* pBridge = nullptr;

	// ** Player
	pPlayer = ObjectManager::GetInstance()->GetPlayer();

	// ** Main Scrolling Background
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BACKGROUND_SCROLL_VERTICAL);
	pBackground = ObjectManager::GetInstance()->NewObject(eObjectKey::BACKGROUND);
	pBackground->SetBridge(pBridge);
	pBackground->SetImage(eImageKey::STAGEBACK);
	pBackground->SetTagName(eTagName::STAGE_MAIN_BKG);
	pBackground->SetPosition(WINDOWS_WIDTH * 0.5f, WINDOWS_HEIGHT * 0.5f);
	pBackground->SetScale(600, WINDOWS_HEIGHT);
	pBackground->SetSpeed(0.5f);
	static_cast<ScrollVerticalBkg*>(pBridge)->StartBottom();
	static_cast<ScrollVerticalBkg*>(pBridge)->ScrollUp();
	
	// ** Left Side Background
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BACKGROUND_BASIC);
	pLeftSideBackground = ObjectManager::GetInstance()->NewObject(eObjectKey::FOREGROUND);
	pLeftSideBackground->SetBridge(pBridge);
	pLeftSideBackground->SetImage(eImageKey::STAGESIDEBACK);
	pLeftSideBackground->SetPosition(((WINDOWS_WIDTH - pBackground->GetScale().x) * 0.5f) * 0.5f, WINDOWS_HEIGHT * 0.5f);
	pLeftSideBackground->SetScale((WINDOWS_WIDTH - pBackground->GetScale().x) * 0.5f, WINDOWS_HEIGHT);

	// ** Right Side Background
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BACKGROUND_BASIC); 
	pRightSideBackground = ObjectManager::GetInstance()->NewObject(eObjectKey::FOREGROUND);
	pRightSideBackground->SetBridge(pBridge);
	pRightSideBackground->SetImage(eImageKey::STAGESIDEBACK);
	pRightSideBackground->SetImageOffsetOrder(Point(1,0));
	pRightSideBackground->SetPosition(WINDOWS_WIDTH - pLeftSideBackground->GetPosition().x, WINDOWS_HEIGHT * 0.5f);
	pRightSideBackground->SetScale(pLeftSideBackground->GetScale());

	// ** EnemyBoss
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_BOSS);
	pBossAngelEnemy = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
	pBossAngelEnemy->SetBridge(pBridge);
	pBossAngelEnemy->SetImage(eImageKey::ANGEL);
	pBossAngelEnemy->SetTagName(eTagName::ENEMY_BOSS);
	pBossAngelEnemy->SetPosition(pBackground->GetPosition().x, pBackground->GetScale().y * 0.3f);
	pBossAngelEnemy->SetScale(224.0f, 320.0f);
	static_cast<Enemy*>(pBossAngelEnemy)->SetHitPoint(10);
	static_cast<Enemy*>(pBossAngelEnemy)->SetDeathPoint(5000);

	// ** Score UI
	pScoreUI = ObjectManager::GetInstance()->NewObject(eObjectKey::UI_SCORE);
	pScoreUI->SetPosition(WINDOWS_WIDTH - 200.0f, 45.0f);
	pScoreUI->SetScale(125.0f, 25.0f);

	// ** Spawn Player
	SpawnManager::SpawnPlayer();
}

void Stage::Update()
{
	ObjectManager::GetInstance()->Update();
}

void Stage::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);
}

void Stage::Release()
{
	if ( pBackground )			ObjectManager::GetInstance()->RecallObject(pBackground);
	if ( pLeftSideBackground )	ObjectManager::GetInstance()->RecallObject(pLeftSideBackground);
	if ( pRightSideBackground ) ObjectManager::GetInstance()->RecallObject(pRightSideBackground);
	if ( pScoreUI )				ObjectManager::GetInstance()->RecallObject(pScoreUI);
	if ( pBossAngelEnemy )		ObjectManager::GetInstance()->RecallObject(pBossAngelEnemy);
}