#pragma once
#include "GameObject.h"
class CScrewBullet :
	public CGameObject
{
	CGameObject* m_pTarget;
	float m_fDist;
	POINT m_tOrigin;
	float m_fRevAngle;
	float m_fRevDist; 
	float m_fRevSpeed;

	explicit CScrewBullet();


public:

	virtual ~CScrewBullet();
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

	static CGameObject* Create(float startfX, float startfY, float fAngle);
	void Set_Origin(float startfX, float startfY, float fAngle);

};

