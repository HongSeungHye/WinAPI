#pragma once
#include "GameObject.h"

class CShield final :
	public CGameObject
{
	CGameObject* m_pTarget;
	float m_fDist;
	explicit CShield();
public:
	virtual ~CShield();
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

	static CGameObject* Create(CGameObject* pTarget);
	void Set_Target(CGameObject* pTarget);
};

