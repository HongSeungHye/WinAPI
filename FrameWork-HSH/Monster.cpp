#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	CMonster::Release_GameObject();
}

int CMonster::Ready_GameObject()
{
	m_fSpeed = 0.5f;
	m_tInfo.iCX = 50;
	m_tInfo.iCY = 50;
	return 0;
}

int CMonster::Update_GameObject()
{
	if (m_pTarget ==nullptr|| m_bIsDead)
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

	//switch (m_eDirection)
	//{
	//case DIRECTION::UP:
	//	m_tInfo.fY -= m_fSpeed;
	//	if (FRAMETOP <= m_tRect.top) {
	//		m_eDirection = DIRECTION::DOWN;
	//	}
	//	break;
	//case DIRECTION::DOWN:
	//	m_tInfo.fY += m_fSpeed;
	//	if (FRAMEBOTTOM <= m_tRect.bottom) {
	//		m_eDirection = DIRECTION::UP;
	//	}
	//	break;
	//case DIRECTION::LEFT:
	//	m_tInfo.fX -= m_fSpeed;
	//	if (FRAMELEFT >= m_tRect.left) {
	//		m_eDirection = DIRECTION::RIGHT;
	//	}
	//	break;
	//case DIRECTION::RIGHT:
	//	m_tInfo.fX += m_fSpeed;
	//	if (FRAMERIGHT <= m_tRect.right) {
	//		m_eDirection = DIRECTION::LEFT;
	//	}
	//	break;
	//default:
	//	break;
	//}

	return OBJ_NOEVENT;
}

void CMonster::Late_Update_GameObject()
{
}

void CMonster::Render_GameObject(HDC hDC)
{
	CGameObject::UpdateRect_GameObject();
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release_GameObject()
{
}

CGameObject * CMonster::Create(float fX, float fY)
{
	CGameObject* pInstance = new CMonster;
	if (0 > pInstance->Ready_GameObject())
	{
		delete pInstance;
		pInstance = nullptr;
		return pInstance;
	}

	pInstance->Set_Pos(fX, fY);
	//static_cast<CMonster*>(pInstance)->SetDirection(eDir);

	return pInstance;
}

//void CMonster::SetDirection(DIRECTION::DIR direction)
//{
//	m_eDirection = direction;
//}


void CMonster::Set_Target(CGameObject* pTarget) {
	m_pTarget = pTarget;
}