#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	:m_bIsDead(false)
	, m_fSpeed(0.f)
	, m_fAngle(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}


CGameObject::~CGameObject()
{
}


void CGameObject::UpdateRect_GameObject()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.iCY >> 1));

	if (m_fAngle > 360) {
		m_fAngle -= 360;
	}

	if (m_fAngle < -360) {
		m_fAngle += 360;
	}
}

void CGameObject::Set_Pos(float fX, float fY)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
}

void CGameObject::Set_Angle(float fDegree)
{
	 m_fAngle = fDegree; 
}

const RECT& CGameObject::Get_Rect() const
{
	return m_tRect;
}

const INFO& CGameObject::Get_Info() const
{
	return m_tInfo;
}

const bool & CGameObject::CheckOutofFrame() const
{
	if (FRAMELEFT > m_tInfo.fX || m_tInfo.fX > FRAMERIGHT
		|| FRAMEBOTTOM< m_tInfo.fY || FRAMETOP>m_tInfo.fY) {
		return true;
	}

	return false;
}

const float & CGameObject::Get_Angle() const
{
	return m_fAngle;
}

void CGameObject::Push_Object(float fX, float fY)
{
	m_tInfo.fX += fX;
	m_tInfo.fY += fY;
}
