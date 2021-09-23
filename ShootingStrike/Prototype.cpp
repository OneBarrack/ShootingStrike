#include "Prototype.h"

#include "Background.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyHole.h"
#include "HammerEffect.h"
#include "Button.h"

Prototype::Prototype()
{

}

Prototype::~Prototype()
{

}


void Prototype::CreatePrototype()
{
	Transform TransInfo;

	PrototypeList[eObjectKey::BACKGROUND]	= new Background;
	PrototypeList[eObjectKey::PLAYER]		= new Player;
	PrototypeList[eObjectKey::ENEMY]		= new Enemy;
	PrototypeList[eObjectKey::BULLET]		= new Bullet;
	PrototypeList[eObjectKey::BUTTON]		= new Button;
}

Object* Prototype::FindPrototypeObject(eObjectKey _Key)
{
	map<eObjectKey, Object*>::iterator iter = PrototypeList.find(_Key);

	if (iter == PrototypeList.end())
	{
		//ERROR_MESSAGE("복사 생성할 객체 원형이 없습니다.", _Key);
		
		Sleep(500);
		return nullptr;
	}

	return iter->second;
}
