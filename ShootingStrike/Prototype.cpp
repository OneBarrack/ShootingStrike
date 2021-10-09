#include "Prototype.h"

#include "Background.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyHole.h"
#include "HammerEffect.h"
#include "Effect.h"
#include "UserInterface.h"

#include "BasicBkg.h"
#include "ScrollHorizontalBkg.h"
#include "ScrollVerticalBkg.h"
#include "BossAngelEnemy.h"
#include "NormalBullet.h"
#include "GuideBullet.h"
#include "GoTargetAfterDelayBullet.h"
#include "SpreadAfterDelayBullet.h"
#include "ButtonUI.h"
#include "ScoreUI.h"
#include "TextUI.h"
#include "LifeUI.h"
#include "ProgressBarUI.h"
#include "ExplosionEffect.h"
#include "HitEffect.h"

Prototype::Prototype()
{

}

Prototype::~Prototype()
{

}


void Prototype::CreatePrototype()
{
	// Create Object Prototype
	objectPrototypeList[eObjectKey::BACKGROUND]	= new Background;
	objectPrototypeList[eObjectKey::PLAYER]		= new Player;
	objectPrototypeList[eObjectKey::ENEMY]		= new Enemy;
	objectPrototypeList[eObjectKey::BULLET]		= new Bullet;	
	objectPrototypeList[eObjectKey::UI]			= new UserInterface;
	objectPrototypeList[eObjectKey::EFFECT]		= new Effect;
	objectPrototypeList[eObjectKey::FOREGROUND] = objectPrototypeList[eObjectKey::BACKGROUND];

	// Create Bridge Prototype
	bridgePrototypeList[eBridgeKey::BACKGROUND_BASIC]			  = new BasicBkg;
	bridgePrototypeList[eBridgeKey::BACKGROUND_SCROLL_HORIZONTAL] = new ScrollHorizontalBkg;
	bridgePrototypeList[eBridgeKey::BACKGROUND_SCROLL_VERTICAL]	  = new ScrollVerticalBkg;
	bridgePrototypeList[eBridgeKey::ENEMY_BOSS]					  = new BossAngelEnemy;
	bridgePrototypeList[eBridgeKey::BULLET_NORMAL]				  = new NormalBullet;
	bridgePrototypeList[eBridgeKey::BULLET_GUIDE]				  = new GuideBullet;
	bridgePrototypeList[eBridgeKey::BULLET_GO_TARGET_AFTER_DELAY] = new GoTargetAfterDelayBullet;
	bridgePrototypeList[eBridgeKey::BULLET_SPREAD_AFTER_DELAY]	  = new SpreadAfterDelayBullet;
	bridgePrototypeList[eBridgeKey::UI_BUTTON]					  = new ButtonUI;
	bridgePrototypeList[eBridgeKey::UI_SCORE]					  = new ScoreUI;
	bridgePrototypeList[eBridgeKey::UI_TEXT]					  = new TextUI;
	bridgePrototypeList[eBridgeKey::UI_LIFE]					  = new LifeUI;
	bridgePrototypeList[eBridgeKey::UI_PROGRESSBAR]				  = new ProgressBarUI;
	bridgePrototypeList[eBridgeKey::EFFECT_EXPLOSION]			  = new ExplosionEffect;
	bridgePrototypeList[eBridgeKey::EFFECT_HIT]					  = new HitEffect;
}

Object* Prototype::FindPrototypeObject(eObjectKey _key)
{
	map<eObjectKey, Object*>::iterator iter = objectPrototypeList.find(_key);

	if (iter == objectPrototypeList.end())
	{
		//ERROR_MESSAGE("복사 생성할 객체 원형이 없습니다.", _Key);
		
		Sleep(500);
		return nullptr;
	}

	return iter->second;
}

Bridge* Prototype::FindPrototypeBridge(eBridgeKey _key)
{
	map<eBridgeKey, Bridge*>::iterator iter = bridgePrototypeList.find(_key);

	if ( iter == bridgePrototypeList.end() )
	{
		//ERROR_MESSAGE("복사 생성할 객체 원형이 없습니다.", _Key);

		Sleep(500);
		return nullptr;
	}

	return iter->second;
}
