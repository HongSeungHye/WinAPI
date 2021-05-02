#include "stdafx.h"
#include "ScrewBullet.h"


CScrewBullet::CScrewBullet() :
	m_pTarget{ nullptr }
	, m_fDist{ 0.f }
	, m_fRevAngle{ 0.f }
	, m_fRevDist{ 0.f }
	,m_fRevSpeed{0.f}
{
	ZeroMemory(&m_tOrigin, sizeof(m_tOrigin));
}


CScrewBullet::~CScrewBullet()
{
	Release_GameObject();
}

int CScrewBullet::Ready_GameObject()
{
	m_tInfo.iCX = 10;
	m_tInfo.iCY = 10;
	m_fRevSpeed = 15.f;
	m_fRevDist = 15.f;
	m_fSpeed = 1.f;
	return 0;
}

int CScrewBullet::Update_GameObject()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	//직선으로 이동 
	m_tOrigin.x += cosf(m_fAngle * DEG2RAD) * m_fSpeed;
	m_tOrigin.y -= sinf(m_fAngle * DEG2RAD) * m_fSpeed;

	return OBJ_NOEVENT;
}

void CScrewBullet::Late_Update_GameObject()
{
	//공전 
	m_fRevAngle += m_fRevSpeed;
	m_tInfo.fX = m_tOrigin.x + cosf(m_fRevAngle *DEG2RAD) * m_fRevDist;
	m_tInfo.fY = m_tOrigin.y - sinf(m_fRevAngle *DEG2RAD) * m_fRevDist;

	m_bIsDead = CGameObject::CheckOutofFrame();

}

void CScrewBullet::Render_GameObject(HDC hDC)
{
	CGameObject::UpdateRect_GameObject();
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CScrewBullet::Release_GameObject()
{
}

CGameObject * CScrewBullet::Create(float startfX, float startfY, float fAngle)
{
	CGameObject* pInstance = new CScrewBullet;
	if (0 > pInstance->Ready_GameObject())
	{
		Safe_Delete(pInstance);
		return pInstance;
	}
	static_cast<CScrewBullet*>(pInstance)->Set_Origin(startfX,startfY,fAngle);
	return pInstance;
}

void CScrewBullet::Set_Origin(float startfX, float startfY, float fAngle)
{
	m_tOrigin.x = startfX;
	m_tOrigin.y = startfY;
	m_fAngle = fAngle;
}
