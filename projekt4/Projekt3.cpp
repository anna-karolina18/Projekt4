
#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cmath>
#include <wingdi.h>
#include <windows.h>
#include <string>

#define MAX_LOADSTRING 100


using namespace std;


HINSTANCE hInst;								
TCHAR szTitle[MAX_LOADSTRING];			
TCHAR szWindowClass[MAX_LOADSTRING];			


double tab[2485];
int calk[2485];
double przysp[2485];
double predkosc[2485];
double droga[2485];
double srednia[2485];




INT value;

HWND hwndButton;
HWND radio1;
HWND rado2;

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);


void rysuj(HDC hdc)
{
	Graphics graphics(hdc);
	POINT stary_punkt;
	MoveToEx(hdc, 20, 10, &stary_punkt);
	LineTo(hdc, 20, 650);
	MoveToEx(hdc, 20, 385, &stary_punkt);
	LineTo(hdc, 1300, 385);
	MoveToEx(hdc, 10, 20, &stary_punkt);
	LineTo(hdc, 20, 10);
	LineTo(hdc, 30, 20);
	MoveToEx(hdc, 1290, 375, &stary_punkt);
	LineTo(hdc, 1300, 385);
	LineTo(hdc, 1290, 395);
	for (int i = 0; i < 125; i++) {
		MoveToEx(hdc, 10 * i + 30, 380, &stary_punkt);
		LineTo(hdc, 10 * i + 30, 390);
	}
	for (int i = 0; i < 62; i++) {
		MoveToEx(hdc, 15, i * 10 + 30, &stary_punkt);
		LineTo(hdc, 25, i * 10 + 30);
	}
	MoveToEx(hdc, 20, 385, &stary_punkt);
}

void MyOnPaint(HDC hdc , int y , int t)
{
	Graphics graphics(hdc);
	HPEN CzerwonePioro, Pudelko;

	rysuj(hdc);

	
	CzerwonePioro = CreatePen(PS_SOLID, 1, 0x0000FF);
	Pudelko = (HPEN)SelectObject(hdc, CzerwonePioro);

	int d = 2485 / t +1;

	for (int i = 24; i < d; i++)
	{
		LineTo(hdc, i + 20, 385 - predkosc[t*i] * y);
	}
	SelectObject(hdc, Pudelko);
	DeleteObject(CzerwonePioro);

}

void MyOnPaint2(HDC hdc , int y, int t)
{

	Graphics graphics(hdc);
	HPEN NiebieskiePioro, Pudelko;

	rysuj(hdc);


	NiebieskiePioro = CreatePen(PS_SOLID, 1, 0xFF0000);
	Pudelko = (HPEN)SelectObject(hdc, NiebieskiePioro);

	int d = 2485 / t + 1;

	for (int i = 24; i < d; i++)
	{
		LineTo(hdc, i + 20, 385 - droga[t*i] * y);
	}

	SelectObject(hdc, Pudelko);
	DeleteObject(NiebieskiePioro);
}

void MyOnPaint3(HDC hdc, int y, int t)
{

	Graphics graphics(hdc);
	HPEN ZielonePioro, Pudelko;

	rysuj(hdc);


	ZielonePioro = CreatePen(PS_SOLID, 1, 0x00FF00);
	Pudelko = (HPEN)SelectObject(hdc, ZielonePioro);

	int d = 2485 / t + 1;

	for (int i = 24; i < d; i++)
	{
		LineTo(hdc, i + 20, 385 - przysp[t*i] * y);
	}
	SelectObject(hdc, Pudelko);
	DeleteObject(ZielonePioro);
}

void MyOnPaint4(HDC hdc)
{
	Graphics graphics(hdc);
	rysuj(hdc);
}

void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea , int y, int x)
{
	if (drawArea==NULL)
		InvalidateRect(hWnd, NULL, FALSE); 
	else
		InvalidateRect(hWnd, drawArea, FALSE); 
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc, y,x);
	EndPaint(hWnd, &ps);
}

void repaintWindow2(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea,int y, int x)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, FALSE); 
	else
		InvalidateRect(hWnd, drawArea, FALSE); 
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint2(hdc , y,x);
	EndPaint(hWnd, &ps);
}

void repaintWindow3(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea , int y, int x)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, FALSE); 
	else
		InvalidateRect(hWnd, drawArea, FALSE); 
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint3(hdc , y,x);
	EndPaint(hWnd, &ps);
}

void repaintWindow4(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); 
	else
		InvalidateRect(hWnd, drawArea, TRUE);
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint4(hdc);
	EndPaint(hWnd, &ps);
}


int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	double a;
	int i = 0;
	string linia;



	fstream plik;
	plik.open("C:/Users/karol/Desktop/dane/outputRobotForwardA02.log");
	if (!plik.good())
		return false;



	while (true)
	{
		plik >> a >> a >> a >> tab[i] >> a >> a >> a >> a >> a >> a >> a >> a;
		if (!plik.fail())
			i++;
		else
			break;

	}
	plik.close();

	double pred = 0, drog = 0;
	double suma = 0; int n = 25;

	for (n = 25; n < 2485; n++)
	{
		suma = 0;
		for (i = n - 25; i < n; i++)
		{
			suma = suma + tab[i] * 9.81;
		}
		srednia[n] = suma / 25;
	}
	for (i = 25; i < 2485; i++)
		przysp[i] = tab[i] * 9.81 - srednia[i];
	for (i = 25; i < 2485; i++)
	{
		predkosc[i] = 0.04 * przysp[i] + pred;
		pred = predkosc[i];
	}

	for (i = 25; i < 2485; i++)
	{
		droga[i] = drog + abs(0.04 * predkosc[i]);
		drog = droga[i];
	}

	MSG msg;
	HACCEL hAccelTable;

	value = 0;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);


	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance;

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);


	hwndButton = CreateWindow(TEXT("button"), TEXT("y=0,1"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP ,
		100, 700, 100, 30, hWnd, (HMENU)ID_RBUTTON1, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("y=0,05"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		250, 700, 100, 30, hWnd, (HMENU)ID_RBUTTON2, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("t=0,8s"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
		500, 700, 100, 30, hWnd, (HMENU)ID_RBUTTON3, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("t=1,2s"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		650, 700, 100, 30, hWnd, (HMENU)ID_RBUTTON4, GetModuleHandle(NULL), NULL);


	hwndButton = CreateWindow(TEXT("button"),                  
		TEXT("v"),                  
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  
		900, 700,                                  
		80, 50,                              
		hWnd,                                 
		(HMENU)ID_BUTTON1,                  
		hInstance,                            
		NULL);                               

	hwndButton = CreateWindow(TEXT("button"),                      
		TEXT("s"),                  
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  
		1000, 700,                                 
		80, 50,                             
		hWnd,                                 
		(HMENU)ID_BUTTON2,                   
		hInstance,                         
		NULL);                               


	hwndButton = CreateWindow(TEXT("button"),                
		TEXT("a"),                  
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  
		1100, 700,                                 
		80, 50,                              
		hWnd,                              
		(HMENU)ID_BUTTON3,                   
		hInstance,                           
		NULL);


	hwndButton = CreateWindow(TEXT("button"),                     
		TEXT("Clear"),                  
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
		1200, 700,                                 
		80, 50,                            
		hWnd,                                 
		(HMENU)ID_BUTTON4,                
		hInstance,                            
		NULL);


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	int y=0;
	UINT a,b,c,d;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_RBUTTON1:
			repaintWindow4(hWnd, hdc, ps, NULL);
			break;
		case ID_RBUTTON2:
			repaintWindow4(hWnd, hdc, ps, NULL);
			break;
		case ID_RBUTTON3:
			repaintWindow4(hWnd, hdc, ps, NULL);
			break;
		case ID_RBUTTON4:
			repaintWindow4(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON1 :
			a = IsDlgButtonChecked(hWnd, 210);
			b = IsDlgButtonChecked(hWnd, 211);
			c = IsDlgButtonChecked(hWnd, 212);
			d = IsDlgButtonChecked(hWnd, 213);
			if( a == BST_CHECKED && c ==BST_CHECKED)
			repaintWindow(hWnd, hdc, ps, NULL, 100,2);
			if(b == BST_CHECKED && c == BST_CHECKED) 
			repaintWindow(hWnd, hdc, ps, NULL, 50,2);
			if (a == BST_CHECKED && d == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 100,3);
			if (b == BST_CHECKED && d == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 50,3);
			break;
		case ID_BUTTON2 :
			a = IsDlgButtonChecked(hWnd, 210);
			b = IsDlgButtonChecked(hWnd, 211);
			c = IsDlgButtonChecked(hWnd, 212);
			d = IsDlgButtonChecked(hWnd, 213);
			if (a == BST_CHECKED && c == BST_CHECKED)
				repaintWindow2(hWnd, hdc, ps, NULL, 100, 2);
			if (b == BST_CHECKED && c == BST_CHECKED)
				repaintWindow2(hWnd, hdc, ps, NULL, 50, 2);
			if (a == BST_CHECKED && d == BST_CHECKED)
				repaintWindow2(hWnd, hdc, ps, NULL, 100, 3);
			if (b == BST_CHECKED && d == BST_CHECKED)
				repaintWindow2(hWnd, hdc, ps, NULL, 50, 3);
			break;
		case ID_BUTTON3:
			a = IsDlgButtonChecked(hWnd, 210);
			b = IsDlgButtonChecked(hWnd, 211);
			c = IsDlgButtonChecked(hWnd, 212);
			d = IsDlgButtonChecked(hWnd, 213);
			if (a == BST_CHECKED && c == BST_CHECKED)
				repaintWindow3(hWnd, hdc, ps, NULL, 100, 2);
			if (b == BST_CHECKED && c == BST_CHECKED)
				repaintWindow3(hWnd, hdc, ps, NULL, 50, 2);
			if (a == BST_CHECKED && d == BST_CHECKED)
				repaintWindow3(hWnd, hdc, ps, NULL, 100, 3);
			if (b == BST_CHECKED && d == BST_CHECKED)
				repaintWindow3(hWnd, hdc, ps, NULL, 50, 3);
			break;
		case ID_BUTTON4:
			repaintWindow4(hWnd, hdc, ps, NULL);
			break;

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
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

