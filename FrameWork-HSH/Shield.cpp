#include "stdafx.h"
#include "Shield.h"


CShield::CShield()
	:m_fDist(0.f)
{
}


CShield::~CShield()
{
	Release_GameObject();
}

int CShield::Ready_GameObject()
{
	m_tInfo.iCX = 10;
	m_tInfo.iCY = 10;
	m_fSpeed = 6.f;
	m_fDist = 120.f;
	return READY_OK;
}

int CShield::Update_GameObject()
{
	if (nullptr == m_pTarget||m_bIsDead)
		return OBJ_DEAD;

	m_fAngle += m_fSpeed;
	float originPX = m_pTarget->Get_Info().fX;
	float originPY = m_pTarget->Get_Info().fY + 70;
	m_tInfo.fX = originPX + cosf(m_fAngle * DEG2RAD) * m_fDist;
	m_tInfo.fY = originPY - sinf(m_fAngle * DEG2RAD) * m_fDist;

	return OBJ_NOEVENT;
}

void CShield::Late_Update_GameObject()
{
}

void CShield::Render_GameObject(HDC hDC)
{
	CGameObject::UpdateRect_GameObject();
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CShield::Release_GameObject()
{
}

CGameObject * CShield::Create(CGameObject* pTarget)
{
	CGameObject* pInstance = new CShield;
	if (0 > pInstance->Ready_GameObject())
	{
		delete pInstance;
		pInstance = nullptr;
		return pInstance;
	}
	static_cast<CShield*>(pInstance)->Set_Target(pTarget);
	return pInstance;
}

void CShield::Set_Target(CGameObject * pTarget)
{
	m_pTarget = pTarget; 
}

