#pragma once

class CGameObject;
class CMainApp final
{
private:
	CMainApp(); //무분별한 생성을 막기위해 클래스 내부에서 생성을 하겠다. 
public:
	~CMainApp();

	int Ready_MainApp();
	void Update_MainApp();
	void Render_MainApp();
	void Release_MainApp();

	static CMainApp* Create();

private:
	HDC m_hDC;
	TCHAR m_szFPS[32];
	int	m_iFPS;
	DWORD m_dwFPSTime;

	list<CGameObject*> m_listGameObject[OBJECT::END];

	
};

