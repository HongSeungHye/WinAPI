#pragma once
class CGameObject;
class CCollisionManager
{
	CCollisionManager();
	~CCollisionManager();

	static bool Check_Sphere(const INFO* pDstInfo, const INFO* pSrcInfo);
	static bool Check_Rect(const RECT* pDstRect, const RECT* pSrcRect);
	static bool Check_SphAndRec(list<CGameObject*>* plistSph, list<CGameObject*>* plistRec);

public:
	static void Collision_Rect(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc);
	static void Collision_Sphere(list<CGameObject*>* plistDest, list<CGameObject*>* plistSrc);
	static void Collision_SphAndRec(list<CGameObject*>* plistSph, list<CGameObject*>* plistRec);

};

