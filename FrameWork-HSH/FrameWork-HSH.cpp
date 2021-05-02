// FrameWork-HSH.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "FrameWork-HSH.h"
#include "MainApp.h"
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWND;


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

//HANDLE - unsigned 정수형식 
// 어떠한 고유 값을 표현하는데 사용되는 놈. 
// 사람으로 치자면 주민등록번호에 해당이 되는 놈이다. 

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.


    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FRAMEWORKHSH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FRAMEWORKHSH));

    MSG msg;

	CMainApp* pMainApp = CMainApp::Create();//생성
	if (pMainApp == nullptr) {
		//생성 실패시 리턴
		return 0;
	}

	//getMessage: 어떠한 메시지가 발생하지 않는다면 프로그램을 블로킹상태로 만듦
	//PeekMessage:  메시지 없으면 false 반환 

	//운영체제에서 윈도우가 켜진 이후 흐른 시간을 반환해주는 함수
	//GetTickCount 대략 1/1000
	DWORD dwOldTime = GetTickCount();

	msg.message = WM_NULL;

	while (msg.message!=WM_QUIT)
		//종료메시지가 아니라면 돌린다 
    {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			//만약 메시지 읽어들일것이 있다면    ㄴ remove는 사용하고 메시지 삭제 
			//가공하고 
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg); //winproc에 보내줘 
			}
		}
		//그게 아니면 내 루프 돌려라 
       //10: 0.01 초
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
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//  
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW; //가로세로 크기가 변할때마다 창을 새로그리겠다. 
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FRAMEWORKHSH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW); //커서모양 
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); //배경색
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_FRAMEWORKHSH); //상단 메뉴바 
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   RECT rc = { 0,0,WINCX,WINCY };
   AdjustWindowRect(&rc,WS_OVERLAPPEDWINDOW,FALSE); //창크기 재조정
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, rc.right-rc.left, rc.bottom-rc.top, nullptr, nullptr, hInstance, nullptr);
 //						 ㄴ윈도우창 시작위치	//ㄴ윈도우 창 크기
   if (!hWnd)
   {
	   //생성실패?
      return FALSE;
   }
   g_hWND = hWnd;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	//callback: 운영체제에 의해 호츌되는 함수		//ㄴ키보드       //ㄴ마우스
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
	//	//타이머마다 호출 
	//	InvalidateRect(hWnd,nullptr,FALSE);
	//	//마지막 인자 false하면 화면을 지우고 다시그리지 않음 그냥 덮어씌워서 그림 
	//	break;
	//case WM_CREATE:
	//	//생성될때 단 한번만 호출되는 메시지.
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
			//esc눌렀을경우 
			DestroyWindow(hWnd);
			break;
		default:
			break;
		}
 
   // case WM_PAINT:
   //     {
   //         PAINTSTRUCT ps;
   //         HDC hdc = BeginPaint(hWnd, &ps);
   ////         // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
			////MoveToEx(hdc, 100, 100, nullptr);// 커서를 (100,100) 으로 옮김
			////LineTo(hdc, 200, 100); //선그리기 
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