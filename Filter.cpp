// ImageApp.cpp : Defines the entry point for the application.
//



#include "stdafx.h"
#include "Filter.h"
#include "Resource.h"
#include <commctrl.h>
#include <string>
#include <windows.h>
#include <windowsx.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

using namespace Gdiplus;


HINSTANCE g_hInst;
Graphics* graphics;
HWND picWND;

RECT picRect;
int h, w;
int filter = 0;

BOOL CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);

void BW(Bitmap*);

int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow) {

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	HWND dialog{};

	g_hInst = hInstance;

	dialog = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);

	if (!dialog) {
		MessageBox(NULL, "Could not create dialog", "CreateDialog", MB_ICONERROR);
		return 1;
	}
	ShowWindow(dialog, nCmdShow);
	UpdateWindow(dialog);

	graphics = new Graphics(GetDC(GetDlgItem(dialog,IDC_STATIC)));
	picWND = GetDlgItem(dialog, IDC_STATIC);
	
	GetWindowRect(picWND, &picRect);

	h = picRect.bottom - picRect.top;
	w = picRect.right - picRect.left;


	MSG msg;

	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	GdiplusShutdown(gdiplusToken);
	return (int)msg.wParam;

}



BOOL CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	Pen pen(Color(255, 255, 0, 0), 17);
	Image image(L"duck.jpg");
	Bitmap image1(L"duck.jpg");
	Rect rect(0, 0, h, w);
	
	int xPos, yPos;
	
	switch (message)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return TRUE;

	case WM_LBUTTONDOWN:
		 xPos = GET_X_LPARAM(lParam);
		 yPos = GET_Y_LPARAM(lParam);
		 if (xPos >= picRect.left && xPos <= picRect.right && yPos <= picRect.bottom && yPos >= picRect.top) {
			 graphics->DrawRectangle(&pen, rect);
		 }
	case WM_LBUTTONUP:
		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);
		if (xPos >= picRect.left && xPos <= picRect.right && yPos <= picRect.bottom && yPos >= picRect.top) {
			graphics->DrawImage(&image1, rect);
		}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case ID_RUN:
			{
				switch (filter) {
				case 0:
					{
						graphics->DrawImage(&image, rect);
						return TRUE;
					}
				case 2:
					{
					Gdiplus::Color temp;
					
					int r = 0, g = 0, b = 0,grey = 0;
						for (int i = 0; i < image1.GetWidth(); ++i) {
							for (int j = 0; j < image1.GetHeight(); ++j) {
								image1.GetPixel(i, j, &temp);
								r = temp.GetRed();
								g = temp.GetGreen();
								b = temp.GetBlue();
								grey = (r + g + b) / 3;
								Gdiplus::Color newColor(grey,grey,grey);
								image1.SetPixel(i, j, newColor);
							}
						}
						graphics->DrawImage(&image1, rect);
						return TRUE;
					}
				}

				return TRUE;
			}
			case IDC_BW:
			{
				filter = 2;
				return TRUE;
			}
			case IDC_BOXBLUR:
			{
				filter = 1;
				return TRUE;
			}
		}
		return FALSE;
	case WM_DESTROY:
			PostQuitMessage(0);
			return TRUE;
	}



		return FALSE;
}