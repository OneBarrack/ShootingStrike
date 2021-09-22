#include "CollisionManager.h"

bool CollisionManager::IsCollision(Object* _pObj1, Object* _pObj2)
{
	eCollisionType CType1 = _pObj1->GetCollisionType();
	eCollisionType CType2 = _pObj2->GetCollisionType();

	if		( CType1 == eCollisionType::ELLIPSE && CType2 == eCollisionType::ELLIPSE )	return EllipseCollision(_pObj1, _pObj2);
	else if ( CType1 == eCollisionType::RECT	&& CType2 == eCollisionType::RECT )		return RectCollision(_pObj1, _pObj2);	
	else if ( CType1 == eCollisionType::ELLIPSE && CType2 == eCollisionType::RECT )		return EllipseRectCollision(_pObj1, _pObj2);
	else if ( CType1 == eCollisionType::RECT	&& CType2 == eCollisionType::ELLIPSE )	return EllipseRectCollision(_pObj2, _pObj1);
	else return false;
}

bool CollisionManager::EllipseCollision(Object* _pObj1, Object* _pObj2)
{
	// ** 플레이어의 반지름과 Target의 반지름의 합을 구함.
	float RadiusSum = (_pObj1->GetScale().x / 2) + (_pObj2->GetScale().x / 2);

	// ** 거리를 구하는 공식
	// ** 먼저 기준 Object와 Target Object의 x, y 값을 구함.

	//**    /| 
	//**   / |
	//**  /  | y
	//** /___|
	//**   x
	float DeltaX = _pObj1->GetPosition().x - _pObj2->GetPosition().x;
	float DeltaY = _pObj1->GetPosition().y - _pObj2->GetPosition().y;
	float Distance = sqrt((DeltaX * DeltaX) + (DeltaY * DeltaY));

	return (RadiusSum > Distance);
}

bool CollisionManager::EllipseCollision(const Transform& _Temp, const Transform& _Dest)
{
	// ** 플레이어의 반지름과 Target의 반지름의 합을 구함.
	float RadiusSum = (_Temp.Scale.x / 2) + (_Dest.Scale.x / 2);

	// ** 거리를 구하는 공식
	// ** 먼저 기준 Object와 Target Object의 x, y 값을 구함.

	//**    /| 
	//**   / |
	//**  /  | y
	//** /___|
	//**   x
	float DeltaX = _Temp.Position.x - _Dest.Position.x;
	float DeltaY = _Temp.Position.y - _Dest.Position.y;
	float Distance = sqrt((DeltaX * DeltaX) + (DeltaY * DeltaY));

	return (RadiusSum > Distance);
}

bool CollisionManager::RectCollision(Object* _pObj1, Object* _pObj2)
{
	//** vector V1(x, y)
	//**   ↓ 
	//**   |￣￣￣￣| 
	//**   |       |
	//**   |       | 
	//**   |_______| y
	//**         x ↑
	//**         vector V2(x, y)
	return ((_pObj1->GetPosition().x + (_pObj1->GetScale().x / 2)) > (_pObj2->GetPosition().x - (_pObj2->GetScale().x / 2)) &&
		(_pObj1->GetPosition().y + (_pObj1->GetScale().y / 2)) > (_pObj2->GetPosition().y - (_pObj2->GetScale().y / 2)) &&
		(_pObj1->GetPosition().x - (_pObj1->GetScale().x / 2)) < (_pObj2->GetPosition().x + (_pObj2->GetScale().x / 2)) &&
		(_pObj1->GetPosition().y - (_pObj1->GetScale().y / 2)) < (_pObj2->GetPosition().y + (_pObj2->GetScale().y / 2)));
}

bool CollisionManager::RectCollision(RECT _R1, RECT _R2)
{
	return (_R1.left < _R2.right&& _R1.top < _R2.bottom&&
		_R2.left < _R1.right&& _R2.top < _R1.bottom);
}

bool CollisionManager::IsPointInCircle(float _Cx, float _Cy, float _Cr, float _Px, float _Py)
{
	float DeltaX = _Cx - _Px;
	float DeltaY = _Cy - _Py;
	float Distance = sqrt(DeltaX * DeltaX + DeltaY * DeltaY);

	return (Distance < _Cr);
}

bool CollisionManager::IsPointInCircle(Vector3 _CirclePos, float _Cr, Vector3 _PointPos)
{
	float DeltaX = _CirclePos.x - _PointPos.x;
	float DeltaY = _CirclePos.y - _PointPos.y;
	float Distance = sqrt(DeltaX * DeltaX + DeltaY * DeltaY);

	return (Distance < _Cr);
}

bool CollisionManager::IsPointInRect(RECT _Rect, Vector3 _PointPos)
{
	return (_Rect.left < _PointPos.x && _PointPos.x < _Rect.right &&
		_Rect.top < _PointPos.y && _PointPos.y < _Rect.bottom);
}

bool CollisionManager::EllipseRectCollision(Object* _pEllipseObj, Object* _pRectObj)
{	
	float EllipseX	  = _pEllipseObj->GetPosition().x;
	float EllipseY    = _pEllipseObj->GetPosition().y;
	float Radius      = _pEllipseObj->GetScale().x / 2;
	RECT RectCollider = _pRectObj->GetCollider();
	
	//** 가로 세로 위치에 원이 존재한다면
	//** 원의 반지름만큼 사각형을 확장하여 원의 중심이 확장한 사각형 내부에 있는지 확인
	//**          ↓↓
	//**       |        |
	//**       |        |
	//**   ￣￣|￣￣￣￣|￣￣ 
	//** →    |        |    ←
	//** →    |        |    ←
	//**   ____|________|____
	//**       |        |
	//**       |        |
	//**          ↑↑

	if ( (RectCollider.left <= (LONG)EllipseX && (LONG)EllipseX <= RectCollider.right) ||
		(RectCollider.top <= (LONG)EllipseY && (LONG)EllipseY <= RectCollider.bottom) )
	{
		// ** 원의 반지름만큼 확장한 사각형
		RECT ExpRectCollider = { 
			RectCollider.left - (LONG)Radius,
			RectCollider.top - (LONG)Radius,
			RectCollider.right + (LONG)Radius,
			RectCollider.bottom + (LONG)Radius
		};

		// ** 확장한 사각형 안에 원의 중심이 들어있다면 충돌
		if ( (ExpRectCollider.left < (LONG)EllipseX && (LONG)EllipseX < ExpRectCollider.right) &&
			(ExpRectCollider.top < (LONG)EllipseY && (LONG)EllipseY < ExpRectCollider.bottom) )
		{
			return true;
		}
	}
	else
	{
		//** 대각 위치에 위치에 원이 존재한다면
		//** 사각형의 각 꼭지점이 원 안에 들어와 있는지 확인
		//**   ↓              ↓
		//** →    |        |    ←
		//**       |        |    
		//**   ￣￣|￣￣￣￣|￣￣ 
		//**       |        |    
		//**       |        |    
		//**   ____|________|____
		//**       |        |
		//** →    |        |    ←
		//**   ↑              ↑

		// ** 사각형의 좌상단 포인트가 원 안에 있다면 충돌
		if ( IsPointInCircle(EllipseX, EllipseY, Radius, (float)RectCollider.left, (float)RectCollider.top)   ||
			IsPointInCircle(EllipseX, EllipseY, Radius, (float)RectCollider.left, (float)RectCollider.bottom) ||
			IsPointInCircle(EllipseX, EllipseY, Radius, (float)RectCollider.right, (float)RectCollider.top)   ||
			IsPointInCircle(EllipseX, EllipseY, Radius, (float)RectCollider.right, (float)RectCollider.bottom) )
		{
			return true;
		}
	}

	return false;
}
