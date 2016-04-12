// wcppchess.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "wcppchess.h"
#include "chess.h"
#include <crtdbg.h>
#include "chessui.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
Chess				*pChess = NULL;
HBITMAP bmp;
HBITMAP bmpchess;
CChessUI *pui;

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	bmp = LoadBitmap(hInstance, (LPCSTR)IDB_BOARD);
	bmpchess = LoadBitmap(hInstance, (LPCSTR)IDB_CHESS);

	pChess = new Chess();
	pChess->loadini();
	pui = new CChessUI(RGB(255,0,255));

 	// TODO:  �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WCPPCHESS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WCPPCHESS));

	// ����Ϣѭ��: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	delete pChess;
	delete pui;
	//MessageBox(NULL, "ssssssss","fffffffff",MB_OK);

	_CrtDumpMemoryLeaks();

	return (int) msg.wParam;
}



//
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WCPPCHESS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WCPPCHESS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}



//
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


void PaintBoard()
{
}

//
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	BITMAP bmpinfo;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_TEST:
			pChess->test();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// TODO:  �ڴ���������ͼ����...
		/*if (bmpchess != NULL && bmp!= NULL)
		{
			GetObject(bmp, sizeof(bmpinfo), &bmpinfo);
			HDC dc1 = CreateCompatibleDC(0);
			SelectObject(dc1, bmp);
			BitBlt(hdc, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, dc1, 0, 0, SRCCOPY);


			GetObject(bmpchess ,sizeof(bmpinfo), &bmpinfo);
			HBITMAP mask = CreateBitmap(bmpinfo.bmWidth, bmpinfo.bmHeight, 1, 1, NULL);
			HDC dc2 = CreateCompatibleDC(0);
			SelectObject(dc1, bmpchess);
			SelectObject(dc2, mask);

			SetBkColor(dc1, RGB(255, 0, 255));


			BitBlt(hdc, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, dc1, 0, 0, SRCCOPY);
			BitBlt(hdc, 0, 50, bmpinfo.bmWidth, bmpinfo.bmHeight, dc2, 0, 0, SRCCOPY);

			BitBlt(dc2, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, dc1, 0, 0, SRCCOPY);

			BitBlt(hdc, 0, 100, bmpinfo.bmWidth, bmpinfo.bmHeight, dc2, 0, 0, SRCCOPY);

			BitBlt(dc1, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, dc2, 0, 0, SRCINVERT);

			BitBlt(hdc, 0, 150, bmpinfo.bmWidth, bmpinfo.bmHeight, dc1, 0, 0, SRCCOPY);

			BitBlt(hdc, 0, 200, bmpinfo.bmWidth, bmpinfo.bmHeight, dc2, 0, 0, SRCAND);
			BitBlt(hdc, 0, 200, bmpinfo.bmWidth, bmpinfo.bmHeight, dc1, 0, 0, SRCPAINT);

			DeleteDC(dc1);
			DeleteDC(dc2);
		}*/
		pui->paintBoard(hdc);
		pui->paintChess(hdc, 5, 8);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
