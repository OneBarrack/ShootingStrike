#include "Prototype.h"

#include "Background.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyHole.h"
#include "HammerEffect.h"
#include "ButtonUI.h"
#include "ScoreUI.h"

#include "BasicBkg.h"
#include "ScrollHorizontalBkg.h"
#include "ScrollVerticalBkg.h"
#include "BossEnemy.h"
#include "NormalBullet.h"
#include "GuideBullet.h"

Prototype::Prototype()
{

}

Prototype::~Prototype()
{

}


void Prototype::CreatePrototype()
{
	// Create Object Prototype
	ObjectPrototypeList[eObjectKey::BACKGROUND]		= new Background;
	ObjectPrototypeList[eObjectKey::PLAYER]			= new Player;
	ObjectPrototypeList[eObjectKey::ENEMY]			= new Enemy;
	ObjectPrototypeList[eObjectKey::BULLET]			= new Bullet;
	ObjectPrototypeList[eObjectKey::UI_BUTTON]		= new ButtonUI;
	ObjectPrototypeList[eObjectKey::UI_SCORE]		= new ScoreUI;
	
	ObjectPrototypeList[eObjectKey::FOREGROUND]  = ObjectPrototypeList[eObjectKey::BACKGROUND];

	// Create Bridge Prototype
	BridgePrototypeList[eBridgeKey::BACKGROUND_BASIC]			  = new BasicBkg;
	BridgePrototypeList[eBridgeKey::BACKGROUND_SCROLL_HORIZONTAL] = new ScrollHorizontalBkg;
	BridgePrototypeList[eBridgeKey::BACKGROUND_SCROLL_VERTICAL]	  = new ScrollVerticalBkg;
	BridgePrototypeList[eBridgeKey::ENEMY_BOSS]					  = new BossEnemy;
	BridgePrototypeList[eBridgeKey::BULLET_NORMAL]				  = new NormalBullet;
	BridgePrototypeList[eBridgeKey::BULLET_GUIDE]				  = new GuideBullet;
}

Object* Prototype::FindPrototypeObject(eObjectKey _Key)
{
	map<eObjectKey, Object*>::iterator iter = ObjectPrototypeList.find(_Key);

	if (iter == ObjectPrototypeList.end())
	{
		//ERROR_MESSAGE("복사 생성할 객체 원형이 없습니다.", _Key);
		
		Sleep(500);
		return nullptr;
	}

	return iter->second;
}

Bridge* Prototype::FindPrototypeBridge(eBridgeKey _Key)
{
	map<eBridgeKey, Bridge*>::iterator iter = BridgePrototypeList.find(_Key);

	if ( iter == BridgePrototypeList.end() )
	{
		//ERROR_MESSAGE("복사 생성할 객체 원형이 없습니다.", _Key);

		Sleep(500);
		return nullptr;
	}

	return iter->second;
}
