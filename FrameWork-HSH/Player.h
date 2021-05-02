#pragma once
#include "GameObject.h"

class CPlayer final:
	public CGameObject
{
	explicit CPlayer();
	list<CGameObject*>* m_pBulletList;
	list<CGameObject*>* m_pShieldList;
	list<CGameObject*>* m_pTrackingBulletList;

	LINEINFO m_tGun;

public:
	virtual ~CPlayer();
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

	static CGameObject* Create();
	void Set_BulletList(list<CGameObject*>* pBulletList);
	void Set_ShieldtList(list<CGameObject*>* pShieldList);
	void Set_TrackingBulletList(list<CGameObject*>* pTrackingBulletList);
	void Update_GunInfo();


};

