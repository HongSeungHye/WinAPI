#include "stdafx.h"
#include "TrackingBullet.h"


CTrackingBullet::CTrackingBullet()
{
}


CTrackingBullet::~CTrackingBullet()
{
}

int CTrackingBullet::Ready_GameObject()
{
	m_tInfo.iCX = 10;
	m_tInfo.iCY = 10;
	m_fSpeed = 3.f;
	return 0;
}

int CTrackingBullet::Update_GameObject()
{
	if (m_pTarget == nullptr || m_bIsDead)
		return OBJ_DEAD;

	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	fX += 1;
	fY += 1;
	float fDist = sqrtf(fX * fX + fY * fY);

	m_fAngle = acosf(fX / fDist); //acosf는 라디안값을 리턴한다. 
	if (m_pTarget->Get_Info().fY > m_tInfo.fY) {
		//m_fAngle *= -1.f;  아래와 같은 이야기
		m_fAngle = (PI * 2) - m_fAngle;
	}

	m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle)* m_fSpeed; 

	return OBJ_NOEVENT;
}

void CTrackingBullet::Late_Update_GameObject()
{
	CGameObject::UpdateRect_GameObject();
	m_bIsDead = CGameObject::CheckOutofFrame();
}

void CTrackingBullet::Render_GameObject(HDC hDC)
{
	CGameObject::UpdateRect_GameObject();
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}

void CTrackingBullet::Release_GameObject()
{
}

CGameObject * CTrackingBullet::Create(float fX, float fY)
{
	CGameObject* pInstance = new CTrackingBullet;
	if (0 > pInstance->Ready_GameObject())
	{
		delete pInstance;
		pInstance = nullptr;
		return pInstance;
	}

	pInstance->Set_Pos(fX, fY);

	return pInstance;
}

void CTrackingBullet::Set_Target(CGameObject * pTarget)
{
	m_pTarget = pTarget;
}
