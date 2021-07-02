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

double tab[1250];
double* przysp;
double* predkosc;
double* polozenie;
double* wtlum;
int ile = 0;
fstream plik;

INT value;

HWND hwndButton;

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);

void rysuj(HDC hdc)
{
	Graphics graphics(hdc);
	POINT stary_punkt;
	MoveToEx(hdc, 20, 10, &stary_punkt);
	LineTo(hdc, 20, 650);
	MoveToEx(hdc, 20, 500, &stary_punkt);
	LineTo(hdc, 1300, 500);
	MoveToEx(hdc, 10, 20, &stary_punkt);
	LineTo(hdc, 20, 10);
	LineTo(hdc, 30, 20);
	MoveToEx(hdc, 1290, 490, &stary_punkt);
	LineTo(hdc, 1300, 500);
	LineTo(hdc, 1290, 510);
	for (int i = 0; i < 125; i++)
	{
		MoveToEx(hdc, 10 * i + 30, 495, &stary_punkt);
		LineTo(hdc, 10 * i + 30, 505);
	}
	for (int i = 0; i < 62; i++)
	{
		MoveToEx(hdc, 15, i * 10 + 30, &stary_punkt);
		LineTo(hdc, 25, i * 10 + 30);
	}
}

void wpis(int ktory)
{
	if (ktory == 1)
	{
		plik.open("outputSpring01.log", ios::in);
	}
	else if (ktory == 2)
	{
		plik.open("outputSpring02.log", ios::in);
	}
	else
	{
		plik.open("outputSpring03.log", ios::in);
	}
	double a;
	ile = 0;
	while (!plik.eof() && ile < 1250)
	{
		plik >> a >> a >> a >> a >> tab[ile] >> a >> a >> a >> a >> a >> a >> a;
		if (!plik.fail())
			ile++;
		else
			break;
	}
	plik.close();
}

void wpis2()
{
	int i = 0;
	double pred = 0, poloz = 0, suma = 0;

	for (i = 0; i < ile; i++)
		przysp[i] = tab[i] * 9.81;
	for (i = 0; i < ile; i++)
	{
		predkosc[i] = 0.04 * przysp[i] + pred;
		pred = predkosc[i];
	}

	for (i = 0; i < ile; i++)
	{
		polozenie[i] = poloz + (0.04 * predkosc[i]);
		poloz = polozenie[i];
	}
	for (i = 0; i < ile; i++)
	{
		wtlum[i] = exp((przysp[i] / polozenie[i]) * (0.5));
	}
}

void RysPredkosc(HDC hdc, int y, int t)
{
	Graphics graphics(hdc);
	HPEN CzerwonePioro, Pudelko;
	POINT stary_punkt;

	rysuj(hdc);

	CzerwonePioro = CreatePen(PS_SOLID, 1, 0x0000FF);
	Pudelko = (HPEN)SelectObject(hdc, CzerwonePioro);


	MoveToEx(hdc, 20, 500 - predkosc[0], &stary_punkt);
	for (int i = 1; i < ile; i++)
	{
		LineTo(hdc, t*i + 20, 500 - predkosc[i] * y);
	}
	SelectObject(hdc, Pudelko);
	DeleteObject(CzerwonePioro);

}

void RysPolozenie(HDC hdc, int y, int t)
{
	Graphics graphics(hdc);
	HPEN NiebieskiePioro, Pudelko;
	POINT stary_punkt;
	rysuj(hdc);

	NiebieskiePioro = CreatePen(PS_SOLID, 1, 0xFF0000);
	Pudelko = (HPEN)SelectObject(hdc, NiebieskiePioro);

	MoveToEx(hdc, 20, 500 - polozenie[0], &stary_punkt);
	for (int i = 1; i < ile ; i++)
	{
		LineTo(hdc, t*i + 20, 500 - polozenie[i] * y);
	}

	SelectObject(hdc, Pudelko);
	DeleteObject(NiebieskiePioro);
}

void RysPrzysp(HDC hdc, int y, int t)
{
	Graphics graphics(hdc);
	HPEN ZielonePioro, Pudelko;
	POINT stary_punkt;

	rysuj(hdc);

	ZielonePioro = CreatePen(PS_SOLID, 1, 0x00FF00);
	Pudelko = (HPEN)SelectObject(hdc, ZielonePioro);

	MoveToEx(hdc, 20, 500-przysp[0], &stary_punkt);
	for (int i = 1; i < ile; i++)
	{
		LineTo(hdc, t*i + 20, 500 - przysp[i] * y);
	}
	SelectObject(hdc, Pudelko);
	DeleteObject(ZielonePioro);
}

void RysTlum(HDC hdc, int y, int t)
{
	Graphics graphics(hdc);
	HPEN ZoltePioro, Pudelko;
	POINT stary_punkt;

	rysuj(hdc);

	ZoltePioro = CreatePen(PS_SOLID, 1, 0x0FFFF);
	Pudelko = (HPEN)SelectObject(hdc, ZoltePioro);

	MoveToEx(hdc, 20, 500-wtlum[0], &stary_punkt);
	for (int i = 1; i < ile; i++)
	{
		LineTo(hdc, t*i + 20, 500 - wtlum[i] * y);
	}
	SelectObject(hdc, Pudelko);
	DeleteObject(ZoltePioro);
}

void czysc(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE);
	else
		InvalidateRect(hWnd, drawArea, TRUE);
	hdc = BeginPaint(hWnd, &ps);
	rysuj(hdc);
	EndPaint(hWnd, &ps);
}

void repaintWindow(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, int y, int t, int ktorywykres)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, FALSE);
	else
		InvalidateRect(hWnd, drawArea, FALSE);
	hdc = BeginPaint(hWnd, &ps);
	switch (ktorywykres)
	{
	case 1:
		RysPredkosc(hdc, y, t);
		break;
	case 2:
		RysPrzysp(hdc, y, t);
		break;
	case 3:
		RysPolozenie(hdc, y, t);
		break;
	case 4:
		RysTlum(hdc, y, t);
		break;
	}
	EndPaint(hWnd, &ps);
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

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
		CW_USEDEFAULT, 0, 1520, 800, NULL, NULL, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("y=0,2"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
		100, 700, 100, 30, hWnd, (HMENU)ID_RBUTTON1, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("y=2"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		220, 700, 100, 30, hWnd, (HMENU)ID_RBUTTON2, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("t=0,2s"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
		500, 700, 100, 30, hWnd, (HMENU)ID_RBUTTON3, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("t=0,4s"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		620, 700, 100, 30, hWnd, (HMENU)ID_RBUTTON4, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Plik 1"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
		1400, 200, 100, 30, hWnd, (HMENU)ID_RBUTTON5, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Plik 2"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		1400, 250, 100, 30, hWnd, (HMENU)ID_RBUTTON6, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Plik 3"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		1400, 300, 100, 30, hWnd, (HMENU)ID_RBUTTON7, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("v"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1000, 700, 100, 30, hWnd, (HMENU)ID_BUTTON1, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("d"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1120, 700, 100, 30, hWnd, (HMENU)ID_BUTTON2, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("a"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1240, 700, 100, 30, hWnd, (HMENU)ID_BUTTON3, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Clear"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1360, 700, 100, 30, hWnd, (HMENU)ID_BUTTON4, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("e^(-k)"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		880, 700, 100, 30, hWnd, (HMENU)ID_BUTTON5, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	UINT a, b, c, d;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_RBUTTON1:
			czysc(hWnd, hdc, ps, NULL);
			break;
		case ID_RBUTTON2:
			czysc(hWnd, hdc, ps, NULL);
			break;
		case ID_RBUTTON3:
			czysc(hWnd, hdc, ps, NULL);
			break;
		case ID_RBUTTON4:
			czysc(hWnd, hdc, ps, NULL);
			break;
		case ID_RBUTTON5:
			czysc(hWnd, hdc, ps, NULL);
			wpis(1);
			break;
		case ID_RBUTTON6:
			czysc(hWnd, hdc, ps, NULL);
			wpis(2);
			break;
		case ID_RBUTTON7:
			czysc(hWnd, hdc, ps, NULL);
			wpis(3);
			break;
		case ID_BUTTON1:
			przysp = new double[ile];
			predkosc = new double[ile];
			polozenie = new double[ile];
			wtlum = new double[ile];
			wpis2();
			a = IsDlgButtonChecked(hWnd, 210);
			b = IsDlgButtonChecked(hWnd, 211);
			c = IsDlgButtonChecked(hWnd, 212);
			d = IsDlgButtonChecked(hWnd, 213);
			if (a == BST_CHECKED && c == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 50, 2, 1);
			if (b == BST_CHECKED && c == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 5, 2, 1);
			if (a == BST_CHECKED && d == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 50, 1, 1);
			if (b == BST_CHECKED && d == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 5, 1, 1);
			delete[] przysp;
			delete[] predkosc;
			delete[] polozenie;
			delete[] wtlum;
			break;
		case ID_BUTTON2:
			przysp = new double[ile];
			predkosc = new double[ile];
			polozenie = new double[ile];
			wtlum = new double[ile];
			wpis2();
			a = IsDlgButtonChecked(hWnd, 210);
			b = IsDlgButtonChecked(hWnd, 211);
			c = IsDlgButtonChecked(hWnd, 212);
			d = IsDlgButtonChecked(hWnd, 213);
			if (a == BST_CHECKED && c == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 50, 2, 3);
			if (b == BST_CHECKED && c == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 5, 2, 3);
			if (a == BST_CHECKED && d == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 50, 1, 3);
			if (b == BST_CHECKED && d == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 5, 1, 3);
			delete[] przysp;
			delete[] predkosc;
			delete[] polozenie;
			delete[] wtlum;
			break;
		case ID_BUTTON3:
			przysp = new double[ile];
			predkosc = new double[ile];
			polozenie = new double[ile];
			wtlum = new double[ile];
			wpis2();
			a = IsDlgButtonChecked(hWnd, 210);
			b = IsDlgButtonChecked(hWnd, 211);
			c = IsDlgButtonChecked(hWnd, 212);
			d = IsDlgButtonChecked(hWnd, 213);
			if (a == BST_CHECKED && c == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 50, 2, 2);
			if (b == BST_CHECKED && c == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 5, 2, 2);
			if (a == BST_CHECKED && d == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 50, 1, 2);
			if (b == BST_CHECKED && d == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 5, 1, 2);
			delete[] przysp;
			delete[] predkosc;
			delete[] polozenie;
			delete[] wtlum;
			break;
		case ID_BUTTON4:
			czysc(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON5:
			przysp = new double[ile];
			predkosc = new double[ile];
			polozenie = new double[ile];
			wtlum = new double[ile];
			wpis2();
			a = IsDlgButtonChecked(hWnd, 210);
			b = IsDlgButtonChecked(hWnd, 211);
			c = IsDlgButtonChecked(hWnd, 212);
			d = IsDlgButtonChecked(hWnd, 213);
			if (a == BST_CHECKED && c == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 50, 2, 4);
			if (b == BST_CHECKED && c == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 5, 2, 4);
			if (a == BST_CHECKED && d == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 50, 1, 4);
			if (b == BST_CHECKED && d == BST_CHECKED)
				repaintWindow(hWnd, hdc, ps, NULL, 5, 1, 4);
			delete[] przysp;
			delete[] predkosc;
			delete[] polozenie;
			delete[] wtlum;
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
