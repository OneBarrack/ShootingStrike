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
#include "TextUI.h"
#include "ProgressBarUI.h"

Stage::Stage() 
	: pPlayer(nullptr)
	, pBackground(nullptr)
	, pLeftSideBackground(nullptr)
	, pRightSideBackground(nullptr)
	, pScoreTextUI(nullptr)
	, pScoreUI(nullptr)
	, pLifeTextUI(nullptr)
	, pLifeUI(nullptr)
	, pBossAngelEnemy(nullptr)
	, pBossEnemyProgressBar(nullptr)
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
	pBackground->SetImage(eImageKey::STAGEBACK);
	pBackground->SetTagName(eTagName::STAGE_MAIN_BKG);
	pBackground->SetPosition(WINDOWS_WIDTH * 0.5f, WINDOWS_HEIGHT * 0.5f);
	pBackground->SetScale(600, WINDOWS_HEIGHT);
	pBackground->SetSpeed(0.5f);
	pBackground->SetBridge(pBridge);
	static_cast<ScrollVerticalBkg*>(pBridge)->StartBottom();
	static_cast<ScrollVerticalBkg*>(pBridge)->ScrollUp();
	static_cast<ScrollVerticalBkg*>(pBridge)->SetLoop(false);
	
	// ** Left Side Background
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BACKGROUND_BASIC);
	pLeftSideBackground = ObjectManager::GetInstance()->NewObject(eObjectKey::FOREGROUND);
	pLeftSideBackground->SetImage(eImageKey::STAGESIDEBACK);
	pLeftSideBackground->SetPosition(((WINDOWS_WIDTH - pBackground->GetScale().x) * 0.5f) * 0.5f, WINDOWS_HEIGHT * 0.5f);
	pLeftSideBackground->SetScale((WINDOWS_WIDTH - pBackground->GetScale().x) * 0.5f, WINDOWS_HEIGHT);
	pLeftSideBackground->SetBridge(pBridge);

	// ** Right Side Background
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BACKGROUND_BASIC); 
	pRightSideBackground = ObjectManager::GetInstance()->NewObject(eObjectKey::FOREGROUND);
	pRightSideBackground->SetImage(eImageKey::STAGESIDEBACK);
	pRightSideBackground->SetImageOffsetOrder(Point(1,0));
	pRightSideBackground->SetPosition(WINDOWS_WIDTH - pLeftSideBackground->GetPosition().x, WINDOWS_HEIGHT * 0.5f);
	pRightSideBackground->SetScale((WINDOWS_WIDTH - pBackground->GetScale().x) * 0.5f, WINDOWS_HEIGHT);
	pRightSideBackground->SetBridge(pBridge);

	// ** EnemyBoss
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_BOSS);
	pBossAngelEnemy = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
	pBossAngelEnemy->SetImage(eImageKey::ANGEL);
	pBossAngelEnemy->SetTagName(eTagName::ENEMY_BOSS);
	pBossAngelEnemy->SetPosition(pBackground->GetPosition().x, pBackground->GetScale().y * 0.3f);
	pBossAngelEnemy->SetScale(224.0f, 320.0f);
	static_cast<Enemy*>(pBossAngelEnemy)->SetMaxHP(50);
	static_cast<Enemy*>(pBossAngelEnemy)->SetHP(50);
	static_cast<Enemy*>(pBossAngelEnemy)->SetHitPoint(10);
	static_cast<Enemy*>(pBossAngelEnemy)->SetDeathPoint(5000);
	pBossAngelEnemy->SetBridge(pBridge);

	// ** Score Text UI
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_TEXT);
	pScoreTextUI = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
	pScoreTextUI->SetPosition(pRightSideBackground->GetPosition().x, 30.0f);
	pScoreTextUI->SetScale(pRightSideBackground->GetScale().x - 30.0f, 20.0f);
	pScoreTextUI->SetBridge(pBridge);
	static_cast<TextUI*>(pBridge)->SetText("SCORE", 25);

	// ** Score UI
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_SCORE);
	pScoreUI = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
	pScoreUI->SetPosition(pRightSideBackground->GetPosition().x, 65.0f);
	pScoreUI->SetScale(pRightSideBackground->GetScale().x - 20.0f, 27.0f);
	pScoreUI->SetBridge(pBridge);
	
	// ** Life Text UI
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_TEXT);
	pLifeTextUI = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
	pLifeTextUI->SetPosition(pRightSideBackground->GetPosition().x, 120.0f);
	pLifeTextUI->SetScale(pRightSideBackground->GetScale().x - 30.0f, 20.0f);
	pLifeTextUI->SetBridge(pBridge);
	static_cast<TextUI*>(pBridge)->SetText("LIFE", 23);

	// ** Life UI
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_LIFE);
	pLifeUI = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
	pLifeUI->SetPosition(pRightSideBackground->GetPosition().x, 163.0f);
	pLifeUI->SetScale(pRightSideBackground->GetScale().x - 20.0f, 50.0f);
	pLifeUI->SetBridge(pBridge);

	// ** Boss Enemy HP ProgressBar UI
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_PROGRESSBAR);
	pBossEnemyProgressBar = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
	pBossEnemyProgressBar->SetPosition(WINDOWS_WIDTH * 0.5f, 30.0f);
	pBossEnemyProgressBar->SetScale(pBackground->GetScale().x - 30.0f, 50.0f);
	pBossEnemyProgressBar->SetBridge(pBridge);

	// ** Map Progress UI
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_MAP_PROGRESS);
	pMapProgress = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
	pMapProgress->SetPosition(50.0f, WINDOWS_HEIGHT * 0.5f);
	pMapProgress->SetScale(40.0f, 500.0f);
	pMapProgress->SetBridge(pBridge);

	/******* Stage Start *******/
	Start();	
}

void Stage::Update()
{
	ObjectManager::GetInstance()->Update();

	int bossMaxHP = static_cast<Enemy*>(pBossAngelEnemy)->GetMaxHP();
	int bossHP = static_cast<Enemy*>(pBossAngelEnemy)->GetHP();
	static_cast<ProgressBarUI*>(pBossEnemyProgressBar->GetBridgeObject())->SetValue(bossHP, bossMaxHP);
}

void Stage::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);
}

void Stage::Release()
{
	if ( pBackground )	
		ObjectManager::GetInstance()->RecallObject(pBackground);
	pBackground = nullptr;

	if ( pLeftSideBackground )	 
		ObjectManager::GetInstance()->RecallObject(pLeftSideBackground);
	pLeftSideBackground = nullptr;

	if ( pRightSideBackground )  
		ObjectManager::GetInstance()->RecallObject(pRightSideBackground);
	pRightSideBackground = nullptr;

	if ( pScoreUI )				 
		ObjectManager::GetInstance()->RecallObject(pScoreUI);
	pScoreUI = nullptr;

	if ( pScoreTextUI )
		ObjectManager::GetInstance()->RecallObject(pScoreTextUI);
	pScoreTextUI = nullptr;

	if ( pLifeTextUI )			
		ObjectManager::GetInstance()->RecallObject(pLifeTextUI);
	pLifeTextUI = nullptr;

	if ( pLifeUI )				
		ObjectManager::GetInstance()->RecallObject(pLifeUI);
	pLifeUI = nullptr;

	if ( pBossAngelEnemy )		 
		ObjectManager::GetInstance()->RecallObject(pBossAngelEnemy);
	pBossAngelEnemy = nullptr;

	if ( pBossEnemyProgressBar )
		ObjectManager::GetInstance()->RecallObject(pBossEnemyProgressBar);
	pBossEnemyProgressBar = nullptr;

	if ( pMapProgress )
		ObjectManager::GetInstance()->RecallObject(pMapProgress);
	pMapProgress = nullptr;
}

void Stage::Start()
{
	// ** Player ½ºÆù
	SpawnManager::SpawnPlayer();

	// ...
}