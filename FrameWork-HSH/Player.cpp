#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "TrackingBullet.h"
CPlayer::CPlayer()
{
	ZeroMemory(&m_tGun, sizeof(LINEINFO));
}


CPlayer::~CPlayer()
{
}

int CPlayer::Ready_GameObject()
{
	m_fSpeed = 5.5f;
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;
	m_tInfo.iCX = 50;
	m_tInfo.iCY = 50;

	m_tGun.iSize = 100;
	m_tGun.fStartX = m_tInfo.fX + 70.f ;
	m_tGun.fStartY= m_tInfo.fY + 35.f;
	m_tGun.fEndX = m_tGun.fStartX + m_tGun.iSize;
	m_tGun.fEndY= m_tInfo.fY + 35.f;

	return 0;
}

int CPlayer::Update_GameObject()
{
	/*
	16비트
	0x0000 아무키도 안눌렸을때
	0x0001 이전에 눌렸을때(눌렀다 뗐을때)
	0x8000 맨앞 8이면 1000 이기때문에 맨앞 1이라 음수다. 현재 눌렸을때 누른순간 
	0x8001 현재 눌리고 있을때 1000 0000 0000 0001
	      
	*/
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		m_fAngle+=m_fSpeed;
	}	
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		m_fAngle -= m_fSpeed;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_tInfo.fX += cosf(m_fAngle*DEG2RAD)*m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle*DEG2RAD)*m_fSpeed;
	}
		
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		m_tInfo.fX -= cosf(m_fAngle * DEG2RAD) * m_fSpeed;
		m_tInfo.fY += sinf(m_fAngle * DEG2RAD)* m_fSpeed;
	}

	if (GetAsyncKeyState('W') & 0x8000) {
		m_pBulletList->
			emplace_back(CBullet::Create(m_tGun.fEndX, m_tGun.fEndY,m_fAngle));
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		m_pShieldList->
			emplace_back(CShield::Create(this));
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		m_pBulletList-> 
			emplace_back(CScrewBullet::Create(m_tGun.fEndX, m_tGun.fEndY, m_fAngle));
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		m_pTrackingBulletList->
			emplace_back(CTrackingBullet::Create(m_tGun.fEndX, m_tGun.fEndY));

	}

		
	Update_GunInfo();
	return 0;
}   

void CPlayer::Late_Update_GameObject()
{

}

void CPlayer::Render_GameObject(HDC hDC)
{
	CGameObject::UpdateRect_GameObject();

	RECT rcEye = {};
	rcEye.left = m_tRect.left+30;
	rcEye.top = m_tRect.top+10;
	rcEye.right = rcEye.left+10;
	rcEye.bottom = rcEye.top+10;

	RECT rcBody = {};
	rcBody.left = m_tRect.left;
	rcBody.top = m_tRect.bottom;
	rcBody.right = m_tRect.right;
	rcBody.bottom = m_tRect.bottom+75;

	RECT rcArm = {};
	rcArm.left = m_tInfo.fX;
	rcArm.top = rcBody.top+5;
	rcArm.right = rcBody.right+40;
	rcArm.bottom = rcBody.top + 20;

	RECT rcHand = {};
	rcHand.left = rcArm.right;
	rcHand.top = rcArm.top;
	rcHand.right = rcArm.right+15;
	rcHand.bottom = rcArm.bottom;

	//RECT rcGunTop = {};
	//rcGunTop.left = rcHand.left + 5;
	//rcGunTop.top = rcHand.top - 10;
	//rcGunTop.right = rcGunTop.left + 30;
	//rcGunTop.bottom = rcGunTop.top + 10;


	RECT rcLeftLeg = {};
	rcLeftLeg.left= rcBody.left;
	rcLeftLeg.top = rcBody.bottom;
	rcLeftLeg.right = LONG((rcBody.right+ rcBody.left)*0.5 );
	rcLeftLeg.bottom = rcBody.bottom + 50;

	RECT rcRIghtLeg = {};
	rcRIghtLeg.left = rcLeftLeg.right;
	rcRIghtLeg.top = rcBody.bottom;
	rcRIghtLeg.right = rcBody.right;
	rcRIghtLeg.bottom = rcBody.bottom + 50;

	RECT rcLeftFoot = {};
	rcLeftFoot.left = rcLeftLeg.left -2;
	rcLeftFoot.top = rcLeftLeg.bottom-5;
	rcLeftFoot.right = rcLeftLeg.right+10;
	rcLeftFoot.bottom = rcLeftFoot.top + 20;

	RECT rcRightFoot = {};
	rcRightFoot.left = rcRIghtLeg.left - 2;
	rcRightFoot.top = rcRIghtLeg.bottom - 5;
	rcRightFoot.right = rcRIghtLeg.right + 10;
	rcRightFoot.bottom = rcRightFoot.top + 20;

	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Ellipse(hDC, rcEye.left, rcEye.top, rcEye.right, rcEye.bottom);


	//입
	MoveToEx(hDC, m_tInfo.fX + 5, m_tInfo.fY + 10, nullptr);
	LineTo(hDC, m_tInfo.fX+5, m_tInfo.fY+10); //선그리기 
	LineTo(hDC, m_tInfo.fX+20, m_tInfo.fY+10);
	
	Rectangle(hDC, rcBody.left, rcBody.top, rcBody.right, rcBody.bottom);
	Rectangle(hDC, rcArm.left, rcArm.top, rcArm.right, rcArm.bottom);

	//총
	//Rectangle(hDC, m_GunInfo.fX, m_GunInfo.fY - m_GunInfo.iCY,
	//	m_GunInfo.fX + m_GunInfo.iCX,m_GunInfo.fY);

	//총 빔
	MoveToEx(hDC, m_tGun.fStartX, m_tGun.fStartY, nullptr);
	LineTo(hDC, m_tGun.fStartX, m_tGun.fStartY);
	LineTo(hDC, m_tGun.fEndX, m_tGun.fEndY);
	//
	Ellipse(hDC, rcHand.left, rcHand.top, rcHand.right, rcHand.bottom);
	Rectangle(hDC, rcLeftLeg.left, rcLeftLeg.top, rcLeftLeg.right, rcLeftLeg.bottom);
	Rectangle(hDC, rcRIghtLeg.left, rcRIghtLeg.top, rcRIghtLeg.right, rcRIghtLeg.bottom);
	Ellipse(hDC, rcRightFoot.left, rcRightFoot.top, rcRightFoot.right, rcRightFoot.bottom);
	Ellipse(hDC, rcLeftFoot.left, rcLeftFoot.top, rcLeftFoot.right, rcLeftFoot.bottom);


}

void CPlayer::Release_GameObject()
{
}

CGameObject * CPlayer::Create()
{
	CGameObject* pInstance = new CPlayer;
	if (0 > pInstance->Ready_GameObject())// 나는 실패시 음수를 반환하게끔 만들어 줄거! 
	{
		delete pInstance;
		pInstance = nullptr;
		return pInstance;
	}

	return pInstance;
}

void CPlayer::Set_BulletList(list<CGameObject*>* pBulletList)
{
	m_pBulletList = pBulletList;
}

void CPlayer::Set_ShieldtList(list<CGameObject*>* pShieldList)
{
	m_pShieldList = pShieldList;
}

void CPlayer::Set_TrackingBulletList(list<CGameObject*>* pTrackingBulletList)
{
	m_pTrackingBulletList = pTrackingBulletList;
}

void CPlayer::Update_GunInfo()
{
	m_tGun.fStartX = m_tInfo.fX + 70.f;
	m_tGun.fStartY = m_tInfo.fY + 35.f;

	float plusX = cosf(m_fAngle*DEG2RAD)*m_tGun.iSize;
	float plusY = -sinf(m_fAngle*DEG2RAD)*m_tGun.iSize;
	m_tGun.fEndX = plusX +m_tGun.fStartX;
	m_tGun.fEndY = plusY+ m_tGun.fStartY;

}


