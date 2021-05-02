#pragma once
#include "GameObject.h"
class CMonster final:
	public CGameObject
{
	//DIRECTION::DIR m_eDirection;
	CGameObject* m_pTarget;
	explicit CMonster();
public:
	virtual ~CMonster();

	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;

	static CGameObject* Create(float fX, float fY);
	//void SetDirection(DIRECTION::DIR direction);
	void Set_Target(CGameObject* pTarget);


};

