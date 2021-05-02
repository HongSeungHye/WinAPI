// FrameWork-HSH.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "FrameWork-HSH.h"
#include "MainApp.h"
#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
HWND g_hWND;


// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

//HANDLE - unsigned �������� 
// ��� ���� ���� ǥ���ϴµ� ���Ǵ� ��. 
// ������� ġ�ڸ� �ֹε�Ϲ�ȣ�� �ش��� �Ǵ� ���̴�. 

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.


    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FRAMEWORKHSH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FRAMEWORKHSH));

    MSG msg;

	CMainApp* pMainApp = CMainApp::Create();//����
	if (pMainApp == nullptr) {
		//���� ���н� ����
		return 0;
	}

	//getMessage: ��� �޽����� �߻����� �ʴ´ٸ� ���α׷��� ���ŷ���·� ����
	//PeekMessage:  �޽��� ������ false ��ȯ 

	//�ü������ �����찡 ���� ���� �帥 �ð��� ��ȯ���ִ� �Լ�
	//GetTickCount �뷫 1/1000
	DWORD dwOldTime = GetTickCount();

	msg.message = WM_NULL;

	while (msg.message!=WM_QUIT)
		//����޽����� �ƴ϶�� ������ 
    {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			//���� �޽��� �о���ϰ��� �ִٸ�    �� remove�� ����ϰ� �޽��� ���� 
			//�����ϰ� 
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg); //winproc�� ������ 
			}
		}
		//�װ� �ƴϸ� �� ���� ������ 
       //10: 0.01 ��
		if (dwOldTime + 1 < GetTickCount())
		{
			pMainApp->Update_MainApp();
			pMainApp->Render_MainApp();
			dwOldTime = GetTickCount();

		}
    }
	if (pMainApp) {
		delete pMainApp;
		pMainApp = nullptr;
	}

    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//  
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW; //���μ��� ũ�Ⱑ ���Ҷ����� â�� ���α׸��ڴ�. 
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FRAMEWORKHSH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW); //Ŀ����� 
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); //����
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_FRAMEWORKHSH); //��� �޴��� 
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.
   RECT rc = { 0,0,WINCX,WINCY };
   AdjustWindowRect(&rc,WS_OVERLAPPEDWINDOW,FALSE); //âũ�� ������
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, rc.right-rc.left, rc.bottom-rc.top, nullptr, nullptr, hInstance, nullptr);
 //						 ��������â ������ġ	//�������� â ũ��
   if (!hWnd)
   {
	   //��������?
      return FALSE;
   }
   g_hWND = hWnd;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	//callback: �ü���� ���� ȣ���Ǵ� �Լ�		//��Ű����       //�����콺
    switch (message)
    {
	//case WM_TIMER:
	//	/*if (shootBullet) {
	//		rc.left += 10;
	//		rc.right += 10;
	//		if (rc.left > WINCX) {
	//			rc={ 300,300,400,400 };
	//			shootBullet = false;
	//		}
	//	}*/
	//	//Ÿ�̸Ӹ��� ȣ�� 
	//	InvalidateRect(hWnd,nullptr,FALSE);
	//	//������ ���� false�ϸ� ȭ���� ����� �ٽñ׸��� ���� �׳� ������� �׸� 
	//	break;
	//case WM_CREATE:
	//	//�����ɶ� �� �ѹ��� ȣ��Ǵ� �޽���.
	//	SetTimer(hWnd, 0, 0, nullptr);
	//	break;
	case WM_KEYDOWN:
		switch (wParam)
		{

		//case VK_LEFT:
		//	rc.left-=10;
		//	rc.right -= 10;
		//	break;
		case VK_ESCAPE:
			//esc��������� 
			DestroyWindow(hWnd);
			break;
		default:
			break;
		}
 
   // case WM_PAINT:
   //     {
   //         PAINTSTRUCT ps;
   //         HDC hdc = BeginPaint(hWnd, &ps);
   ////         // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
			////MoveToEx(hdc, 100, 100, nullptr);// Ŀ���� (100,100) ���� �ű�
			////LineTo(hdc, 200, 100); //���׸��� 
			////LineTo(hdc, 200, 200);
			////LineTo(hdc, 100, 200);
			////LineTo(hdc, 100, 100);
			////Rectangle(hdc,200,200,300,300);
			////Ellipse(hdc, 150, 150,250, 250);	
   //         EndPaint(hWnd, &ps);  
   //     }
        break;
    case WM_DESTROY:
		//KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}