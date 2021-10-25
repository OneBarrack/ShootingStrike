#include "Stage.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "SoundManager.h"
#include "Player.h"
#include "Enemy.h"
#include "WarningEffect.h"
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
#include "MathManager.h"
#include "BounceOnWallItem.h"

Stage::Stage() 
	: frame(0)
	, startTime(0)
	, currentTime(0)
	, bSpawnedBossEnemy(false)
	, bStageClear(false)
	, bGameOver(false)
	, pPlayer(nullptr)
	, pStageDummyEnemy(nullptr)
	, pBackground(nullptr)
	, pLeftSideBackground(nullptr)
	, pRightSideBackground(nullptr)
	, pPlayTimeTextUI(nullptr)
	, pScoreTextUI(nullptr)
	, pScoreUI(nullptr)
	, pLifeTextUI(nullptr)
	, pLifeUI(nullptr)
	, pGameOverUI(nullptr)
	, pGameClearUI(nullptr)
	, pBombTextUI(nullptr)
	, pBombUI(nullptr)
	, pBossAngelEnemy(nullptr)
	, pBossEnemyProgressBar(nullptr)	
	, pMapProgress(nullptr)
{

}

Stage::~Stage()
{
	Release();
}

void Stage::Initialize()
{
	/******* Stage Start *******/
	isStartingScene = true;

	// ** Init Frame
	frame = 1;

	// ** Init Stage Time 
	startTime = GetTickCount64();
	currentTime = GetTickCount64();

	// ** Init spawned boss enemy
	bSpawnedBossEnemy = false;

	// ** Stage clear state
	bStageClear = false;
	bGameOver = false;

	// ***** Start Init Objects ***** //
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
	static_cast<ScrollVerticalBkg*>(pBridge)->SetLoop(2);
		
	// ** 스테이지 내 Bullet 생성을 위한 Dummy Enemy. 비활성화 상태로 둔다
	pStageDummyEnemy = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
	pStageDummyEnemy->SetStatus(eObjectStatus::DEACTIVATED);

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

	// ** Play Time Text UI
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_TEXT);
	pPlayTimeTextUI = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
	pPlayTimeTextUI->SetPosition(
		pBackground->GetPosition().x - (pBackground->GetScale().x * 0.05f),
		pBackground->GetPosition().y - (pBackground->GetScale().y * 0.45f));
	pPlayTimeTextUI->SetScale(100.0f, 50.0f);
	pPlayTimeTextUI->SetBridge(pBridge);
	static_cast<TextUI*>(pBridge)->SetText("00:00:00", 20);

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

	// ** Bomb Text UI
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_TEXT);
	pBombTextUI = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
	pBombTextUI->SetPosition(pRightSideBackground->GetPosition().x, 210.0f);
	pBombTextUI->SetScale(pRightSideBackground->GetScale().x - 30.0f, 20.0f);
	pBombTextUI->SetBridge(pBridge);
	static_cast<TextUI*>(pBridge)->SetText("BOMB", 23);

	// ** Bomb UI
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_BOMB);
	pBombUI = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
	pBombUI->SetPosition(pRightSideBackground->GetPosition().x, 253.0f);
	pBombUI->SetScale(pRightSideBackground->GetScale().x - 20.0f, 50.0f);
	pBombUI->SetBridge(pBridge);

	// ** Map Progress UI
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_MAP_PROGRESS);
	pMapProgress = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
	pMapProgress->SetPosition(50.0f, WINDOWS_HEIGHT * 0.5f);
	pMapProgress->SetScale(40.0f, 500.0f);
	pMapProgress->SetBridge(pBridge);	

	// ***** End Init Objects ***** //

	// ** Initialized Enemy Spawn Pattern Script
	enemyScript.Initialize();

	// ** Initialized Enemy Spawn Pattern Timings.
	InitEnemySpawnPatternTimings();

	// ** Spawn Player
	SpawnManager::SpawnPlayer();

	// ** Play BGM Sound
	SoundManager::GetInstance()->Play(eSoundKey::BGM_STAGE);
}

void Stage::Update()
{
	// ** 현재 진행 시간 갱신
	currentTime = GetTickCount64();
	
	// ** 일정 시간마다 무작위로 Bullet을 스폰시키기 위한 Time 변수와 Delay
	static ULONGLONG bulletSpawnTime = GetTickCount64();
	int bulletSpawnDelay;
	
	// ** 아직 스테이지 클리어 되지 않았다면
	if ( !bStageClear )
	{
		// ** 1초간격으로 시간마다 무작위로 Bullet을 스폰시킨다. 
		// ** (위쪽의 랜덤한 위치에서 생성되어 아래쪽 랜덤한 위치로 이동하는 Bullet 생성)
		bulletSpawnDelay = 1000;		
		if ( bulletSpawnTime + bulletSpawnDelay < GetTickCount64() )
		{
			bulletSpawnTime = GetTickCount64();
			
			Vector3 startPos;
			startPos.x = pBackground->GetPosition().x - (pBackground->GetScale().x * 0.5f) + (rand() % static_cast<int>(pBackground->GetScale().x));
			startPos.y = pBackground->GetPosition().y - (pBackground->GetScale().y * 0.5f);

			Vector3 destPos;
			destPos.x = pBackground->GetPosition().x - (pBackground->GetScale().x * 0.5f) + (rand() % static_cast<int>(pBackground->GetScale().x));
			destPos.y = pBackground->GetPosition().y + (pBackground->GetScale().y * 0.3f);

			Transform bulletTransInfo;
			bulletTransInfo.Position = startPos;
			bulletTransInfo.Direction = MathManager::GetDirection(startPos, destPos);
			bulletTransInfo.Scale = Vector3(10.0f, 10.0f);

			// ** Bullet의 Speed 설정
			float bulletSpeed = 2.0f;

			// ** Bullet Spawn
			SpawnManager::SpawnBullet(pStageDummyEnemy, bulletTransInfo, bulletSpeed, 1, eBridgeKey::BULLET_NORMAL);
		}
	}	
	
	// ** Play Time
	if ( pPlayTimeTextUI )
	{
		static_cast<TextUI*>(pPlayTimeTextUI->GetBridgeObject())->SetText(
			GameDataManager::GetInstance()->GetPlayTimeStrFormat(), 20);
	}

	// ** 맵 진행도
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

	// ** 맵 진행도가 90%가 넘어가면 보스 소환
	if ( mapProgressPercentage > 90.0f && !bSpawnedBossEnemy )
	{
		bSpawnedBossEnemy = true;

		// ** Stop play all sound
		SoundManager::GetInstance()->Stop(eSoundKey::ALL);

		// ** Play warning / stage boss sound
		SoundManager::GetInstance()->Play(eSoundKey::EFFECT_WARNING);
		SoundManager::GetInstance()->Play(eSoundKey::BGM_STAGE_BOSS);

		Bridge* pBridge;

		// ** EnemyBoss
		pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_BOSS);
		pBossAngelEnemy = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
		pBossAngelEnemy->SetImage(eImageKey::ENEMY_ANGEL);
		pBossAngelEnemy->SetTagName(eTagName::ENEMY_BOSS);
		pBossAngelEnemy->SetScale(224.0f, 320.0f);
		pBossAngelEnemy->SetBridge(pBridge);
		static_cast<Enemy*>(pBossAngelEnemy)->SetEnemyType(eEnemyType::ENEMY_BOSS_ANGEL);			
		static_cast<Enemy*>(pBossAngelEnemy)->Spawn();

		// ** Boss Enemy HP ProgressBar UI
		pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_PROGRESSBAR);
		pBossEnemyProgressBar = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
		pBossEnemyProgressBar->SetPosition(WINDOWS_WIDTH * 0.5f, 30.0f);
		pBossEnemyProgressBar->SetScale(pBackground->GetScale().x - 30.0f, 50.0f);
		pBossEnemyProgressBar->SetBridge(pBridge);

		// ** Warning Effect
		pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::EFFECT_WARNING);
		Object* pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::EFFECT);
		pObject->SetImage(eImageKey::FADEBACK_RED);
		pObject->SetPosition(WINDOWS_WIDTH * 0.5f, WINDOWS_HEIGHT * 0.25f);
		pObject->SetScale(382.0f, 100.0f);
		pObject->SetBridge(pBridge);
	}

	// ** 보스가 스폰 되었다면
	if ( bSpawnedBossEnemy )
	{		
		Object* pBossEnemy = ObjectManager::GetInstance()->FindObjectWithTag(eTagName::ENEMY_BOSS);

		// ** 보스가 생존중이면
		if ( pBossEnemy )
		{
			// ** 보스 체력 프로그래스 바 갱신
			int bossMaxHP = static_cast<Enemy*>(pBossEnemy)->GetMaxHP();
			int bossHP = static_cast<Enemy*>(pBossEnemy)->GetHP();
			static_cast<ProgressBarUI*>(pBossEnemyProgressBar->GetBridgeObject())->SetValue(bossHP, bossMaxHP);
		}
		// ** 보스가 죽은상태라면
		else
		{
			// ** 보스 체력 프로그래스 바 삭제
			if ( pBossEnemyProgressBar )
			{
				pBossEnemyProgressBar->SetStatus(eObjectStatus::DESTROYED);
				pBossEnemyProgressBar = nullptr;
			}

			// ** 게임 클리어 UI를 띄움
			if ( !bStageClear )
			{
				bStageClear = true;

				// ** Stop play all sound
				SoundManager::GetInstance()->Stop(eSoundKey::ALL);

				// ** Play stage clear sound
				SoundManager::GetInstance()->Play(eSoundKey::BGM_STAGE_CLEAR);

				// ** GameClear UI
				Bridge* pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_GAMECLEAR);
				pGameClearUI = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
				pGameClearUI->SetPosition(pBackground->GetPosition());
				pGameClearUI->SetScale(pBackground->GetScale());
				pGameClearUI->SetBridge(pBridge);
			}
		}
	}

	// ** Player Life가 0이면 GameOver UI를 띄움
	if ( static_cast<Player*>(pPlayer)->GetLife() == 0 )
	{
		if ( !bGameOver )
		{
			bGameOver = true;

			// ** Stop play all sound
			SoundManager::GetInstance()->Stop(eSoundKey::ALL);

			// ** Play game over sound
			SoundManager::GetInstance()->Play(eSoundKey::BGM_GAMEOVER);

			// ** GameOver UI
			Bridge* pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_GAMEOVER);
			pGameOverUI = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
			pGameOverUI->SetPosition(pBackground->GetPosition());
			pGameOverUI->SetScale(pBackground->GetScale());
			pGameOverUI->SetBridge(pBridge);
		}
	}

	++frame;

	enemyScript.Run();

	ObjectManager::GetInstance()->Update();
}

void Stage::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);

	if ( isStartingScene && RenderManager::FadeIn(_hdc) )
	{
		isStartingScene = false;
	}

	if ( isEndingScene && RenderManager::FadeOut(_hdc) )
	{
		isEndingScene = false;
	}
}

void Stage::Release()
{	
	SoundManager::GetInstance()->Stop(eSoundKey::ALL);

	if ( pStageDummyEnemy )
		ObjectManager::GetInstance()->RecallObject(pStageDummyEnemy);
	pStageDummyEnemy = nullptr;

	if ( pBackground )	
		ObjectManager::GetInstance()->RecallObject(pBackground);
	pBackground = nullptr;

	if ( pLeftSideBackground )	 
		ObjectManager::GetInstance()->RecallObject(pLeftSideBackground);
	pLeftSideBackground = nullptr;

	if ( pRightSideBackground )  
		ObjectManager::GetInstance()->RecallObject(pRightSideBackground);
	pRightSideBackground = nullptr;

	if ( pPlayTimeTextUI )
		ObjectManager::GetInstance()->RecallObject(pPlayTimeTextUI);
	pPlayTimeTextUI = nullptr;

	if ( pScoreUI )				 
		ObjectManager::GetInstance()->RecallObject(pScoreUI);
	pScoreUI = nullptr;

	if ( pScoreTextUI )
		ObjectManager::GetInstance()->RecallObject(pScoreTextUI);
	pScoreTextUI = nullptr;

	if ( pLifeTextUI )			
		ObjectManager::GetInstance()->RecallObject(pLifeTextUI);
	pLifeTextUI = nullptr;

	if ( pGameOverUI )
		ObjectManager::GetInstance()->RecallObject(pGameOverUI);
	pGameOverUI = nullptr;
	
	if ( pGameClearUI )
		ObjectManager::GetInstance()->RecallObject(pGameClearUI);
	pGameClearUI = nullptr;

	if ( pLifeUI )				
		ObjectManager::GetInstance()->RecallObject(pLifeUI);
	pLifeUI = nullptr;

	if ( pBombUI )
		ObjectManager::GetInstance()->RecallObject(pBombUI);
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

	enemySpawnPattern = eEnemySpawnPattern::DOWN_BACK_AND_FORTH_RED_ELF_2;
	enemySpawnTimings.push(make_pair(5.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(15.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(25.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(35.0f, enemySpawnPattern));

	enemySpawnPattern = eEnemySpawnPattern::DOWN_BACK_AND_FORTH_RED_ELF_4;
	enemySpawnTimings.push(make_pair(20.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(40.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(60.0f, enemySpawnPattern));

	enemySpawnPattern = eEnemySpawnPattern::LEFT_TOP_TO_RIGHT_BOTTOM_SPIN;
	enemySpawnTimings.push(make_pair(30.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(70.0f, enemySpawnPattern));
	
	enemySpawnPattern = eEnemySpawnPattern::RIGHT_TOP_TO_LEFT_BOTTOM_SPIN;
	enemySpawnTimings.push(make_pair(30.0f, enemySpawnPattern));
	enemySpawnTimings.push(make_pair(70.0f, enemySpawnPattern));

	enemySpawnPattern = eEnemySpawnPattern::LEFT_BOTTOM_TO_RIGHT_TOP_SPIN;	
	enemySpawnTimings.push(make_pair(50.0f, enemySpawnPattern));

	enemySpawnPattern = eEnemySpawnPattern::RIGHT_BOTTOM_TO_LEFT_TOP_SPIN;
	enemySpawnTimings.push(make_pair(50.0f, enemySpawnPattern));
}