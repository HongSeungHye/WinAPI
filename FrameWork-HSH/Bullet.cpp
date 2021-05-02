#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}

CBullet::~CBullet()
{

}

int CBullet::Ready_GameObject()
{
	m_tInfo.iCX = 10;
	m_tInfo.iCY = 10;
	m_fSpeed = 6.f;
	return 0;
}

int CBullet::Update_GameObject()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle * DEG2RAD) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * DEG2RAD) * m_fSpeed;

	return OBJ_NOEVENT;
}

void CBullet::Late_Update_GameObject()
{
	CGameObject::UpdateRect_GameObject();
	m_bIsDead = CGameObject::CheckOutofFrame();
}
void  CBullet::Render_GameObject(HDC hDC) 
{
	CGameObject::UpdateRect_GameObject();
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}

void CBullet::Release_GameObject()
{
	
}

CGameObject * CBullet::Create(float fX, float fY, float fDegree)
{
	CGameObject* pInstance = new CBullet;
	if (0 > pInstance->Ready_GameObject())
	{
		delete pInstance;
		pInstance = nullptr;
		return pInstance;
	}

	pInstance->Set_Pos(fX, fY);
	pInstance->Set_Angle(fDegree);
	return pInstance;
}

