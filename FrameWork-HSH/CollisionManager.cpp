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
	// é�� 1. �������� ���� ���ض�! 
	float fRadiusSum = float((pDstInfo->iCX >> 1) + (pSrcInfo->iCX >> 1));
	// ��Ÿ����� ����  = a2 + b2 = c2 �̴� �� ǥ���ϱ� ���� ���� �������� �������� �������� �ϵ��� �̷��� ?
	// ���ϲ���. 
	// é�� 2. �غ��� ���̸� ������. 
	float a = pDstInfo->fX - pSrcInfo->fX;
	float b = pDstInfo->fY - pSrcInfo->fY;
	//é�� 3. �غ��� ���̷� �Ÿ��� ������! 
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
	//1.���� �߽��� �簢���� ���ԵǴ°��
	// ���� �߽�> �簢��.left && �����߽�> �簢��.bottom 
	// ���� �߽�< �簢��.right && �����߽�< �簢��.top 
	// 
	//2.���� �߽��� �簢�� �� �𼭸��� �ִ� ��� 
	// �簢���� �𼭸��� ���� ���ԵǴ��� 
	//3. ���� �߽��� �簢�� ���� �ִ� ���
	// ���� ����: x���̳� y ���� ������ �簢���� �� ������ ���̰� x ���̳� y ���� �簢��
	//�������� ���� ���������� ������ ����



	return false;
}

