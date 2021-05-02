#pragma once
#include "GameObject.h"
class CTrackingBullet :
	public CGameObject
{
	explicit CTrackingBullet();
	CGameObject* m_pTarget;

public:
	virtual ~CTrackingBullet();
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

	static CGameObject* Create(float fX, float fY);
	void Set_Target(CGameObject* pTarget);

};

