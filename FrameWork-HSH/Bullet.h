#pragma once
#include "GameObject.h"
class CBullet: public CGameObject
{
	//DIRECTION::DIR m_eDirection;
	explicit CBullet();
public:

	virtual ~CBullet();

	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

	//static CGameObject* Create(float fX, float fY, DIRECTION::DIR eDir);
	static CGameObject* Create(float fX, float fY, float fDegree);
	//void SetDirection(DIRECTION::DIR direction);
};

