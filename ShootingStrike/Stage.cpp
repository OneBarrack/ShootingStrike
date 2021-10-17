#include "Stage.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "RenderManager.h"
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
#include "GameDataManager.h"
#include "GoAndSpinEnemy.h"

Stage::Stage() 
	: frame(0)
	, pPlayer(nullptr)
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
	/******* Stage Start *******/
	bSceneStart = true;

	frame = 1;

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

	// ** Map Progress UI
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_MAP_PROGRESS);
	pMapProgress = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
	pMapProgress->SetPosition(50.0f, WINDOWS_HEIGHT * 0.5f);
	pMapProgress->SetScale(40.0f, 500.0f);
	pMapProgress->SetBridge(pBridge);	

	// ** Initialized Enemy Spawn Pattern Script
	enemyScript.Initialize();

	// ** Initialized Enemy Spawn Pattern Timings.
	InitEnemySpawnPatternTimings();

	// ** Spawn Player
	SpawnManager::SpawnPlayer();
}

void Stage::Update()
{	
	float mapProgressPercentage = GameDataManager::GetInstance()->GetMapProgressRatio() * 100.0f;
	
	// ** Enemy Spawn Pattern 발동 타이밍 정보가 있다면
	while ( !enemySpawnTimings.empty() )
	{
		// ** 발동 타이밍이 현재 맵 진행률과 일치하지 않으면 break
		float spawnTiming = enemySpawnTimings.top().first;
		if ( mapProgressPercentage < spawnTiming )
			break;

		// ** 현재 맵 진행률과 일치하면 패턴 Ready 후 해당 타이밍 정보 pop
		eEnemySpawnPattern spawnPattern = enemySpawnTimings.top().second;
		enemyScript.ReadyToSpawn(pBackground, spawnPattern);
		enemySpawnTimings.pop();
	}

	// ** 맵 진행도가 50%가 넘어가면 보스 소환
	if ( mapProgressPercentage > 50.0f )
	{
		if ( !pBossAngelEnemy )
		{
			Bridge* pBridge;

			// ** EnemyBoss
			pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_BOSS);
			pBossAngelEnemy = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
			pBossAngelEnemy->SetImage(eImageKey::ANGEL);
			pBossAngelEnemy->SetTagName(eTagName::ENEMY_BOSS);
			pBossAngelEnemy->SetScale(224.0f, 320.0f);
			static_cast<Enemy*>(pBossAngelEnemy)->SetMaxHP(50);
			static_cast<Enemy*>(pBossAngelEnemy)->SetHP(50);
			static_cast<Enemy*>(pBossAngelEnemy)->SetHitPoint(10);
			static_cast<Enemy*>(pBossAngelEnemy)->SetDeathPoint(5000);
			pBossAngelEnemy->SetBridge(pBridge);
			static_cast<Enemy*>(pBossAngelEnemy)->Spawn();

			// ** Boss Enemy HP ProgressBar UI
			pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_PROGRESSBAR);
			pBossEnemyProgressBar = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
			pBossEnemyProgressBar->SetPosition(WINDOWS_WIDTH * 0.5f, 30.0f);
			pBossEnemyProgressBar->SetScale(pBackground->GetScale().x - 30.0f, 50.0f);
			pBossEnemyProgressBar->SetBridge(pBridge);
		}

		if ( pBossAngelEnemy && pBossEnemyProgressBar )
		{
			int bossMaxHP = static_cast<Enemy*>(pBossAngelEnemy)->GetMaxHP();
			int bossHP = static_cast<Enemy*>(pBossAngelEnemy)->GetHP();
			static_cast<ProgressBarUI*>(pBossEnemyProgressBar->GetBridgeObject())->SetValue(bossHP, bossMaxHP);
		}
	}

	++frame;

	enemyScript.Run();

	ObjectManager::GetInstance()->Update();
}

void Stage::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);

	if ( bSceneStart && RenderManager::FadeIn(_hdc) )
	{
		bSceneStart = false;
	}

	if ( bSceneEnd && RenderManager::FadeOut(_hdc) )
	{
		bSceneEnd = false;
	}
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

void Stage::InitEnemySpawnPatternTimings()
{
	eEnemySpawnPattern enemySpawnPattern;

	enemySpawnPattern = eEnemySpawnPattern::FALLDOWN_GO_RAND;
	enemySpawnTimings.push(make_pair(4.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(8.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(12.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(16.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(20.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(24.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(28.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(32.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(36.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(40.0f, enemySpawnPattern));

	enemySpawnPattern = eEnemySpawnPattern::FALLDOWN_GO;
	enemySpawnTimings.push(make_pair(10.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(20.0f, enemySpawnPattern));

	enemySpawnPattern = eEnemySpawnPattern::FALLDOWN_GO_AND_SPIN;
	enemySpawnTimings.push(make_pair(60.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(80.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(100.0f, enemySpawnPattern));

	enemySpawnPattern = eEnemySpawnPattern::FALLDOWN_BACK_AND_FORTH;
	enemySpawnTimings.push(make_pair(30.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(40.0f, enemySpawnPattern));

	enemySpawnPattern = eEnemySpawnPattern::FALLDOWN_GO_ACCELERATION_RAND;
	enemySpawnTimings.push(make_pair(60.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(64.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(68.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(72.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(76.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(80.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(84.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(88.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(92.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(96.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(100.0f, enemySpawnPattern));
}