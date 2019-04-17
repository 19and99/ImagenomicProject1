
#include "stdafx.h"
#include "Filter.h"
#include "Resource.h"
#include <commctrl.h>
#include <string>
#include <windows.h>
#include <windowsx.h>
#include "BWConverter.h"
#include "BoxBlur.h"
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
#include <vector>

using namespace Gdiplus;

HINSTANCE g_hInst;
Bitmap* original;
Bitmap* filtered;
GenericImage* filteredGeneric;
Rect picRect;
int radius = 1;
int filter = 0;
bool show = true;

BOOL CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);

Rect fit(Rect region, int width, int height);

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

	PAINTSTRUCT ps;
	HDC hdc;
	Rect rect(20, 80, 600, 300);
	int xPos = 0;
	int yPos = 0;

	switch (message)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		Gdiplus::Graphics graphics(hdc);

		if (show) {
			graphics.DrawImage(filtered, picRect);
		}
		else {
			graphics.DrawImage(original, picRect);
		}
		Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 0), 3);
		graphics.DrawRectangle(&pen,rect);
		EndPaint(hWnd, &ps);
		return 0;
	}

	case WM_CLOSE:
		DestroyWindow(hWnd);
		return TRUE;

	case WM_LBUTTONDOWN:
		xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);
		if (xPos >= picRect.X && xPos <= (picRect.X + picRect.Width) && yPos >= picRect.Y && yPos <= (picRect.Y + picRect.Height)) {
			show = false;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return TRUE;
	case WM_LBUTTONUP:
		show = true;
		InvalidateRect(hWnd, NULL, TRUE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_RUN:
		{
			filtered = original->Clone(0,0,original->GetWidth(),original->GetHeight(),original->GetPixelFormat());
			filteredGeneric = new GenericImage(filtered);

			if (filter == 1) {
				BoxBlur BB(filteredGeneric, radius);
				BB.filter();
			}
			else if (filter == 2) {
				BWConverter BW(filteredGeneric);
				BW.filter();
			}
			
			InvalidateRect(hWnd, NULL, TRUE);
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
		case IDC_OPEN:
		{
			OPENFILENAME ofn;
			char file_name[MAX_PATH];

			ZeroMemory(&file_name, sizeof(file_name));
			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFilter = "All Files\0*.*\0jpeg\0*.jpeg\0jpg\0*.jpg\0png\0*.png\0bmp\0*.bmp\0";
			ofn.lpstrFile = file_name;
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrTitle = "Select Image";
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			GetOpenFileName(&ofn);
			
			std::string s(file_name);
			std::wstring wide_string = std::wstring(s.begin(), s.end());
			const wchar_t* result = wide_string.c_str();
			original = new Bitmap(result);
			filtered = original->Clone(0, 0, original->GetWidth(), original->GetHeight(), original->GetPixelFormat());

			picRect = fit(rect, original->GetWidth(), original->GetHeight());
			InvalidateRect(hWnd, NULL, TRUE);
			return TRUE;

		}
		}

		return FALSE;
	case WM_HSCROLL:
		switch (LOWORD(wParam)) {
		case SB_THUMBPOSITION:
			int pos = HIWORD(wParam);
			radius = (pos / 10);
			return TRUE;
		}
		return FALSE;
	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;
	}



	return FALSE;
}

Rect fit(Rect region, int width, int height) {
	Rect ret(0, 0, 0, 0);
	int rWidth = region.Width;
	int rHeight = region.Height;

	double ratio = (double)width / height;
	double rRatio = (double)rWidth / rHeight;

	if (ratio <= rRatio) {
		ret.Y = region.Y;
		ret.Height = region.Height;
		ret.Width = ratio * region.Height;
		ret.X = region.X + (region.Width - ret.Width) / 2;
	}
	else {
		ret.X = region.X;
		ret.Width = region.Width;
		ret.Height = region.Width / ratio;
		ret.Y = region.Y + (region.Height - ret.Height) / 2;
	}

	return ret;
}