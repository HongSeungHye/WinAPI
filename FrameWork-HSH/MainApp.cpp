#include "stdafx.h"
#include "MainApp.h"
#include "Player.h"
#include "Monster.h"
#include "CollisionManager.h"
#include "Shield.h"
#include "TrackingBullet.h"

CMainApp::CMainApp()
	: m_szFPS(L"")
	, m_iFPS(0)
	, m_dwFPSTime(0)
{
}


CMainApp::~CMainApp()
{
	Release_MainApp();
}

int CMainApp::Ready_MainApp()
{
	m_hDC = GetDC(g_hWND);
	m_dwFPSTime = GetTickCount();

	CGameObject* pObject = CPlayer::Create();	
	m_listGameObject[OBJECT::PLAYER].push_back(pObject);
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObject);
	if (pPlayer != nullptr) {
		pPlayer->Set_BulletList(&m_listGameObject[OBJECT::BULLET]);
		pPlayer->Set_ShieldtList(&m_listGameObject[OBJECT::SHIELD]);
		pPlayer->Set_TrackingBulletList(&m_listGameObject[OBJECT::TRACKINGBULLET]);
	}


	float MonsterPosX;
	float MonsterPosY;
	MonsterPosX = 400.f;
	MonsterPosY = 100.f;
	pObject = CMonster::Create(MonsterPosX, MonsterPosY);
	dynamic_cast<CMonster*>(pObject)->Set_Target(m_listGameObject[OBJECT::PLAYER].front());
	m_listGameObject[OBJECT::MONSTER].push_back(pObject);


	return READY_OK;
}

void CMainApp::Update_MainApp()
{

	for (auto& pObject : m_listGameObject[OBJECT::TRACKINGBULLET]) {
		if (m_listGameObject[OBJECT::MONSTER].empty())
		{
			pObject->Set_Dead();
		}
		else {
			static_cast<CTrackingBullet*>(pObject)->Set_Target(m_listGameObject[OBJECT::MONSTER].front());
		}
	}
		

	for (int i = 0; i < OBJECT::END; ++i)
	{
		m_listGameObject[i].erase(remove_if(m_listGameObject[i].begin(), m_listGameObject[i].end(), [](auto& iter) {
			if (iter->Update_GameObject() == OBJ_DEAD)  return true; 
			return false;
		}), m_listGameObject[i].end());
	}

	for (int i = 0; i < OBJECT::END; ++i)
	{
		for (auto& pObject : m_listGameObject[i])
			pObject->Late_Update_GameObject();
	}

	CCollisionManager::Collision_Sphere(&m_listGameObject[OBJECT::MONSTER], &m_listGameObject[OBJECT::BULLET]);
	//CCollisionManager::Collision_Rect(&m_listGameObject[OBJECT::MONSTER], &m_listGameObject[OBJECT::BULLET]);
	CCollisionManager::Collision_Sphere(&m_listGameObject[OBJECT::MONSTER], &m_listGameObject[OBJECT::SHIELD]);
	CCollisionManager::Collision_Sphere(&m_listGameObject[OBJECT::MONSTER], &m_listGameObject[OBJECT::TRACKINGBULLET]);
	CCollisionManager::Collision_SphAndRec(&m_listGameObject[OBJECT::MONSTER], &m_listGameObject[OBJECT::PLAYER]);

}

void CMainApp::Render_MainApp()
{
	++m_iFPS;
	if (m_dwFPSTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		m_iFPS = 0;
		m_dwFPSTime = GetTickCount();
	}
	Rectangle(m_hDC, 0, 0, WINCX, WINCY); //화면 다시 
	Rectangle(m_hDC, FRAMELEFT, FRAMETOP, FRAMERIGHT, FRAMEBOTTOM); //화면 다시 
	
	//글자 출력
	TCHAR szBuf[32];
	swprintf_s(szBuf, L"BulletCount : %d",
		m_listGameObject[OBJECT::BULLET].size());
	//+m_listGameObject[OBJECT::TRACKINGBULLET].size());
	TextOut(m_hDC, 50, 10, szBuf, lstrlen(szBuf));
	TextOut(m_hDC, 700, 10, m_szFPS, lstrlen(m_szFPS));

	//배경 햇님
	Ellipse(m_hDC, 650, 70, 700, 120);

	Rectangle(m_hDC, 710, 95, 740, 100);
	Rectangle(m_hDC, 615, 95, 645, 100);

	Rectangle(m_hDC, 675, 130, 680, 160);
	Rectangle(m_hDC, 675, 35, 680, 65);
	//

	for (int i = 0; i < OBJECT::END; ++i)
	{
		for (auto& pObject : m_listGameObject[i])
			pObject->Render_GameObject(m_hDC);
	}


}

void CMainApp::Release_MainApp()
{
	ReleaseDC(g_hWND, m_hDC);
	//윈도우 창에있는 dc를 해제하겠다.

	for (int i = 0; i < OBJECT::END; ++i)
	{
		for (auto& pObject : m_listGameObject[i])
		{
			if (pObject)
			{
				delete pObject;
				pObject = nullptr;
			}
		}
		m_listGameObject[i].clear();
	}

}

CMainApp * CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp;
	if (0 > pInstance->Ready_MainApp()) {
		//생성 실패
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}


