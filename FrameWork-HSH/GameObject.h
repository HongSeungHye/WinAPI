#pragma once
class CGameObject abstract
{
protected:
	INFO m_tInfo;
	float m_fSpeed;
	RECT m_tRect;
	int m_iDirection;
	bool m_bIsDead;
	float m_fAngle;

public:
	explicit CGameObject();
	virtual ~CGameObject();

	virtual int Ready_GameObject()=0;
	virtual int Update_GameObject()=0;
	virtual void Late_Update_GameObject() =0;
	virtual void Render_GameObject(HDC hDC)=0;
	virtual void Release_GameObject() = 0;

	void UpdateRect_GameObject();
	void Set_Pos(float fX, float fY);
	void Set_Dead() { m_bIsDead = true; }
	void Set_Angle(float fDegree);
	const RECT& Get_Rect() const;
	const INFO& Get_Info() const;
	const bool& CheckOutofFrame() const;
	const float& Get_Angle() const;
	void Push_Object(float fX, float fY);

};

