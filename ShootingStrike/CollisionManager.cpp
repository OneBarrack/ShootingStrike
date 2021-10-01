#include "CollisionManager.h"

bool CollisionManager::IsCollision(Object* _pObj1, Object* _pObj2)
{
	eCollisionType collisionType1 = _pObj1->GetCollisionType();
	eCollisionType collisionType2 = _pObj2->GetCollisionType();

	if ( collisionType1 == eCollisionType::ELLIPSE && collisionType2 == eCollisionType::ELLIPSE )
	{
		return EllipseCollision(_pObj1, _pObj2);
	}
	else if ( collisionType1 == eCollisionType::RECT && collisionType2 == eCollisionType::RECT )
	{
		return RectCollision(_pObj1, _pObj2);
	}
	else if ( collisionType1 == eCollisionType::ELLIPSE && collisionType2 == eCollisionType::RECT )
	{
		return EllipseRectCollision(_pObj1, _pObj2);
	}
	else if ( collisionType1 == eCollisionType::RECT && collisionType2 == eCollisionType::ELLIPSE )
	{
		return EllipseRectCollision(_pObj2, _pObj1);
	}

	return false;
}

bool CollisionManager::EllipseCollision(Object* _pObj1, Object* _pObj2)
{
	// ** 플레이어 충돌체 반지름과 Target 충돌체 반지름의 합을 구함.
	float radiusSum = (_pObj1->GetColliderScale().x * 0.5f) + (_pObj2->GetColliderScale().x * 0.5f);

	// ** 거리를 구하는 공식
	// ** 먼저 기준 Object와 Target Object의 x, y 값을 구함.

	//**    /| 
	//**   / |
	//**  /  | y
	//** /___|
	//**   x
	float deltaX = _pObj1->GetColliderPosition().x - _pObj2->GetColliderPosition().x;
	float deltaY = _pObj1->GetColliderPosition().y - _pObj2->GetColliderPosition().y;
	float distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	return (radiusSum > distance);
}

bool CollisionManager::EllipseCollision(Transform _TransInfo1, Transform _TransInfo2)
{
	// ** 플레이어의 반지름과 Target의 반지름의 합을 구함.
	float RadiusSum = (_TransInfo1.Scale.x * 0.5f) + (_TransInfo2.Scale.x * 0.5f);

	// ** 거리를 구하는 공식
	// ** 먼저 기준 Object와 Target Object의 x, y 값을 구함.

	//**    /| 
	//**   / |
	//**  /  | y
	//** /___|
	//**   x
	float DeltaX = _TransInfo1.Position.x - _TransInfo2.Position.x;
	float DeltaY = _TransInfo1.Position.y - _TransInfo2.Position.y;
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
	
	//return ((_pObj1->GetColliderPosition().x + (_pObj1->GetColliderScale().x * 0.5f)) > (_pObj2->GetColliderPosition().x - (_pObj2->GetColliderScale().x * 0.5f)) &&
	//	(_pObj1->GetColliderPosition().y + (_pObj1->GetColliderScale().y * 0.5f)) > (_pObj2->GetColliderPosition().y - (_pObj2->GetColliderScale().y * 0.5f)) &&
	//	(_pObj1->GetColliderPosition().x - (_pObj1->GetColliderScale().x * 0.5f)) < (_pObj2->GetColliderPosition().x + (_pObj2->GetColliderScale().x * 0.5f)) &&
	//	(_pObj1->GetColliderPosition().y - (_pObj1->GetColliderScale().y * 0.5f)) < (_pObj2->GetColliderPosition().y + (_pObj2->GetColliderScale().y * 0.5f)));

	return RectCollision(_pObj1->GetColliderF(), _pObj2->GetColliderF());
}

bool CollisionManager::RectCollision(RECT _rect1, RECT _rect2)
{
	return (_rect1.left < _rect2.right && _rect1.top < _rect2.bottom&&
		_rect2.left < _rect1.right && _rect2.top < _rect1.bottom);
}

bool CollisionManager::RectCollision(RectF _rect1, RectF _rect2)
{
	return (_rect1.Left < _rect2.Right && _rect1.Top < _rect2.Bottom&&
		_rect2.Left < _rect1.Right && _rect2.Top < _rect1.Bottom);
}
bool CollisionManager::IsPointInCircle(float _Cx, float _Cy, float _Cr, float _Px, float _Py)
{
	float deltaX = _Cx - _Px;
	float deltaY = _Cy - _Py;
	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

	return (distance < _Cr);
}

bool CollisionManager::IsPointInCircle(Vector3 _circlePos, float _Cr, Vector3 _pointPos)
{
	float deltaX = _circlePos.x - _pointPos.x;
	float deltaY = _circlePos.y - _pointPos.y;
	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

	return (distance < _Cr);
}

bool CollisionManager::IsPointInRect(RECT _rect, Vector3 _pointPos)
{
	return (_rect.left < _pointPos.x && _pointPos.x < _rect.right &&
		_rect.top < _pointPos.y && _pointPos.y < _rect.bottom);
}

bool CollisionManager::IsPointInRect(RectF _rect, Vector3 _pointPos)
{
	return (_rect.Left < _pointPos.x&& _pointPos.x < _rect.Right&&
		_rect.Top < _pointPos.y&& _pointPos.y < _rect.Bottom);
}

bool CollisionManager::EllipseRectCollision(Object* _pEllipseObj, Object* _pRectObj)
{	
	float ellipseX	   = _pEllipseObj->GetColliderPosition().x;
	float ellipseY     = _pEllipseObj->GetColliderPosition().y;
	float radius       = _pEllipseObj->GetColliderScale().x * 0.5f;
	RectF rectCollider = _pRectObj->GetColliderF();
	
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

	if ( (rectCollider.Left <= ellipseX && ellipseX <= rectCollider.Right) ||
		(rectCollider.Top <= ellipseY && ellipseY <= rectCollider.Bottom) )
	{
		// ** 원의 반지름만큼 확장한 사각형
		RectF expRectCollider = { 
			rectCollider.Left - radius,
			rectCollider.Top - radius,
			rectCollider.Right + radius,
			rectCollider.Bottom + radius
		};

		// ** 확장한 사각형 안에 원의 중심이 들어있다면 충돌
		if ( (expRectCollider.Left < ellipseX && ellipseX < expRectCollider.Right) &&
			(expRectCollider.Top < ellipseY && ellipseY < expRectCollider.Bottom) )
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
		if ( IsPointInCircle(ellipseX, ellipseY, radius, rectCollider.Left, rectCollider.Top)   ||
			IsPointInCircle(ellipseX, ellipseY, radius, rectCollider.Left, rectCollider.Bottom) ||
			IsPointInCircle(ellipseX, ellipseY, radius, rectCollider.Right, rectCollider.Top)   ||
			IsPointInCircle(ellipseX, ellipseY, radius, rectCollider.Right, rectCollider.Bottom) )
		{
			return true;
		}
	}

	return false;
}
