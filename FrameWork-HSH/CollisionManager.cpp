#include "stdafx.h"
#include "CollisionManager.h"
#include "GameObject.h"


CCollisionManager::CCollisionManager()
{
}


CCollisionManager::~CCollisionManager()
{
}


void CCollisionManager::Collision_Rect(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc)
{
	RECT rc = {};
	for (auto& pDstObject : *plistDest)
	{
		for (auto& pSrcObject : *plistSrc)
		{
			//if (IntersectRect(&rc, &pDstObject->Get_Rect(), &pSrcObject->Get_Rect()))
			if (Check_Rect(&pDstObject->Get_Rect(), &pSrcObject->Get_Rect()))
			{
				pDstObject->Set_Dead();
				pSrcObject->Set_Dead();
			}
		}
	}
}

void CCollisionManager::Collision_Sphere(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc)
{
	for (auto& pDstObject : *plistDest)
	{
		for (auto& pSrcObject : *plistSrc)
		{
			if (Check_Sphere(&pDstObject->Get_Info(), &pSrcObject->Get_Info()))
			{
				pDstObject->Set_Dead();
				pSrcObject->Set_Dead();
			}
		}
	}
}

void CCollisionManager::Collision_SphAndRec(list<CGameObject*>* plistSph, list<CGameObject*>* plistRec)
{
	RECT rc = {};
	for (auto& pDstObject : *plistSph)
	{
		for (auto& pSrcObject : *plistRec)
		{
			if (Check_Rect(&pDstObject->Get_Rect(), &pSrcObject->Get_Rect()))
			{
				float SphereAngle = pDstObject->Get_Angle();
				float x= cosf(SphereAngle * DEG2RAD) * 3.f;
				float y= -sinf(SphereAngle * DEG2RAD) * 3.f;
				pSrcObject->Push_Object(x, y);
			}
		}
	}

}

bool CCollisionManager::Check_Sphere(const INFO * pDstInfo, const INFO * pSrcInfo)
{
	// 챕터 1. 반지름의 합을 구해라! 
	float fRadiusSum = float((pDstInfo->iCX >> 1) + (pSrcInfo->iCX >> 1));
	// 피타고라스의 정리  = a2 + b2 = c2 이다 를 표현하기 위해 밑의 변수명을 그지같이 지은거지 니들은 이러면 ?
	// 죽일꺼야. 
	// 챕터 2. 밑변과 높이를 구하자. 
	float a = pDstInfo->fX - pSrcInfo->fX;
	float b = pDstInfo->fY - pSrcInfo->fY;
	//챕터 3. 밑변과 높이로 거리를 구하자! 
	float c = sqrtf((a * a) + (b * b));

	if (c <= fRadiusSum)
		return true;

	return false;
}

bool CCollisionManager::Check_Rect(const RECT * pDstRect, const RECT * pSrcRect)
{
	if ((pDstRect->left < pSrcRect->right) && (pDstRect->top < pSrcRect->bottom) &&
		(pDstRect->right > pSrcRect->left) && (pDstRect->bottom > pSrcRect->top)) {
		return true;
	}
	return false;
}

bool CCollisionManager::Check_SphAndRec(list<CGameObject*>* plistSph, list<CGameObject*>* plistRec)
{
	//1.원의 중심이 사각형에 포함되는경우
	// 원의 중심> 사각형.left && 원의중심> 사각형.bottom 
	// 원의 중심< 사각형.right && 원의중심< 사각형.top 
	// 
	//2.원의 중심이 사각형 밖 모서리에 있는 경우 
	// 사각형의 모서리가 원에 포함되는지 
	//3. 원의 중심이 사각형 변에 있는 경우
	// 변의 한점: x축이나 y 축의 한축의 사각형과 원 사이의 길이가 x 축이나 y 축의 사각형
	//반지름과 원의 반지름보다 작으면 교차



	return false;
}

