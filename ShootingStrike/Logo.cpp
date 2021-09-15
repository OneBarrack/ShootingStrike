#include "Logo.h"
#include "Player.h"
#include "Enemy.h"

#include "SceneManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "BitmapManager.h"

Logo::Logo()
{

}

Logo::~Logo()
{

}

void Logo::Initialize()
{
	ObjectManager::GetInstance()->Initialize();

	ObjectManager::GetInstance()->SetPlayer(
		ObjectManager::GetInstance()->TakeObject(eObjectKey::PLAYER));

	BitmapManager::GetInstance()->Initialize();
}

void Logo::Update()
{
	if (GetAsyncKeyState('A'))
		SceneManager::GetInstance()->SetScene(eSCENEID::MENU);
}

void Logo::Render(HDC _hdc)
{
    
}

void Logo::Release()
{

}
