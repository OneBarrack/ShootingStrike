#include "ScoreUI.h"
#include "GameDataManager.h"
#include "CollisionManager.h"
#include "BitmapManager.h"

ScoreUI::ScoreUI()
	: pScoreImage(nullptr)
	, pNumberImage(nullptr)
	, NumberList(queue<int>())
{

}

ScoreUI::~ScoreUI()
{	
}


void ScoreUI::Initialize()
{
	pScoreImage = BitmapManager::GetInstance()->GetImage(eImageKey::SCORE);
	pNumberImage = BitmapManager::GetInstance()->GetImage(eImageKey::NUMBER);

	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(0.0f, 0.0f);

	Collider.Position = TransInfo.Position;
	Collider.Scale = TransInfo.Scale;

	Key = eObjectKey::UI_SCORE;
	Status = eObjectStatus::ACTIVATED;
	CollisionType = eCollisionType::NONE;

	bGenerateCollisionEvent = false;
}

void ScoreUI::Update()
{
	MakeScoreNumberList();

	// ** 충돌체 갱신
	Collider = TransInfo;
}

void ScoreUI::Render(HDC _hdc)
{
	if ( !pScoreImage || !pNumberImage )
		return;

	// ** Score
	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(TransInfo.Position.x - TransInfo.Scale.x),
		int(TransInfo.Position.y - TransInfo.Scale.y),
		int(TransInfo.Scale.x),
		int(TransInfo.Scale.y),
		pScoreImage->GetMemDC(),
		0,
		0,
		int(pScoreImage->GetScale().x),
		int(pScoreImage->GetScale().y),
		RGB(255, 0, 255));

	// ** Number
	// ** 뒤에서부터 그리기 위해 Offset을 역순으로 루프
	for ( int Offset = 9; Offset >= 0; --Offset )
	{
		int Num = 0; 

		// ** NumberList의 숫자를 뽑아 차례대로 뒤에서부터 그리고, 
		// ** 숫자가 더 이상 없다면 0으로 채운다
		if ( !NumberList.empty() )
		{
			Num = NumberList.front();
			NumberList.pop();
		}
		
		TransparentBlt(_hdc, // ** 최종 출력 위치
			int((TransInfo.Position.x - TransInfo.Scale.x) + ((pNumberImage->GetSegmentationScale().x + 15) * Offset)),
			int(TransInfo.Position.y),
			int(pNumberImage->GetSegmentationScale().x + 13),
			int(TransInfo.Scale.y),
			pNumberImage->GetMemDC(),
			int(pNumberImage->GetSegmentationScale().x * Num),
			0,
			int(pNumberImage->GetSegmentationScale().x),
			int(pNumberImage->GetScale().y),
			RGB(255, 0, 255));
	}
}

void ScoreUI::Release()
{

}

void ScoreUI::OnCollision(Object* _pObject)
{

}

void ScoreUI::MakeScoreNumberList()
{
	int Score = GameDataManager::GetInstance()->GetScore();
	while ( Score > 0 )
	{
		int iTemp = int(Score % 10);
		Score /= 10;

		NumberList.push(iTemp);
	}
}