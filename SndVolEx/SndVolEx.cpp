// SndVol.exe windows extension
// (C) John Peterson, GNU GPL 3

#include <iostream>
#include <windows.h>
#include "../../Common/Common.h"
using namespace std;

WNDPROC pWndProc = 0;
struct EnumStruct {
	HWND hBox;
};

void ShowStyle(HWND hWnd) {
	OutputDebugStringEx(L"§GWL_STYLE: %s", WSTranslate(GetWindowLong(hWnd, GWL_STYLE)).c_str());
	OutputDebugStringEx(L"§GWL_EXSTYLE: %s", WSEXTranslate(GetWindowLong(hWnd, GWL_EXSTYLE)).c_str());
}

void ChangeStyle(HWND hWnd) {
	SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
}

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam) {
	EnumStruct* s = (EnumStruct*)lParam;
	wstring title = GetWindowTextEx(hWnd);
	if (!title.compare(L"Applications")) s->hBox = hWnd;
	return true;
}
BOOL CALLBACK EnumChildProc2(HWND hWnd, LPARAM lParam) {
	EnumStruct* s = (EnumStruct*)lParam;
	wstring clsName = GetClassNameEx(hWnd);
	wstring wndName = GetWindowTextEx(hWnd);
	RECT rcBox, rc;
	GetClientRect(s->hBox, &rcBox);
	GetClientRect(hWnd, &rc);
	if (!clsName.compare(L"TileSled Window")
		|| !clsName.compare(L"#32770")) {
		//OutputDebugStringEx(L"§0x%08x: %s | %d %d %d %d\n", hWnd, GetClassNameEx(hWnd).c_str(), rc.left, rc.top, rc.right, rc.bottom);
		SetWindowPos(hWnd, 0, 0, 0, rc.right, rcBox.bottom-10, SWP_NOMOVE|SWP_NOZORDER);
	}
	if (!wndName.compare(L"&Device")) {
		//OutputDebugStringEx(L"§0x%08x: %s | %d %d %d %d\n", hWnd, GetClassNameEx(hWnd).c_str(), rc.left, rc.top, rc.right, rc.bottom);
		BOOL b = SetWindowPos(hWnd, 0, 0, 0, rc.right, rcBox.bottom, SWP_NOMOVE|SWP_NOZORDER);
		//RedrawWindow(hWnd, 0, 0, RDW_UPDATENOW);
	}
	if (!clsName.compare(L"msctls_trackbar32")) {
		//OutputDebugStringEx(L"§0x%08x: %s | %d %d %d %d\n", hWnd, GetClassNameEx(hWnd).c_str(), rc.left, rc.top, rc.right, rc.bottom);
		SetWindowPos(hWnd, 0, 0, 0, rc.right, rcBox.bottom-140, SWP_NOMOVE|SWP_NOZORDER);
	}
	if (!wndName.compare(0, 4, L"Mute")) {
		//OutputDebugStringEx(L"§0x%08x: %s | %d %d %d %d\n", hWnd, GetClassNameEx(hWnd).c_str(), rc.left, rc.top, rc.right, rc.bottom);
		SetWindowPos(hWnd, 0, 30, rcBox.bottom-70, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	}
	if (!wndName.compare(0, 13, L"Mute Speakers")) {
		//OutputDebugStringEx(L"§0x%08x: %s | %d %d %d %d\n", hWnd, GetClassNameEx(hWnd).c_str(), rc.left, rc.top, rc.right, rc.bottom);
		SetWindowPos(hWnd, 0, 42, rcBox.bottom-36, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	}
	return true;
}

void OnResize(HWND hWnd) {
	EnumStruct es;
	es.hBox = 0;
	EnumChildWindows(hWnd, EnumChildProc, (LPARAM)&es);
	EnumChildWindows(hWnd, EnumChildProc2, (LPARAM)&es);
	RedrawWindow(hWnd, 0, 0, RDW_INVALIDATE|RDW_ALLCHILDREN);
}

LRESULT WINAPI WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch(message) {		
		case WM_GETMINMAXINFO: goto def;
		case WM_NCHITTEST: goto def;
		case WM_PAINT:
		case WM_SIZE: OnResize(hWnd); break;
	}
	return CallWindowProc(pWndProc, hWnd, message, wParam, lParam);
def:
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// override wndproc
void OverrideWndProc(HWND hWnd) {
	if (!IsWindow(hWnd)) return;
	if (!(pWndProc = (WNDPROC)GetWindowLongPtr(hWnd, GWLP_WNDPROC)))
		OutputDebugStringEx(L"§pOldWndProc: %s", GetLastErrorEx().c_str());
	if (!SetWindowLongPtr(hWnd, GWLP_WNDPROC, LONG_PTR(WindowProc)))
		OutputDebugStringEx(L"§SetWindowLongPtr: %s", GetLastErrorEx().c_str());
}

DWORD WINAPI ThreadFunction(LPVOID lpParam) {
	HWND hWnd = 0;
	while (!hWnd) {
		hWnd = FindWindowByTitle(L"Volume Mixer");
		Sleep(1000/25);
	}
	ChangeStyle(hWnd);
	OverrideWndProc(hWnd);
	return 0;
}

void RunThread() {
	CreateThread(NULL, NULL, ThreadFunction, NULL, NULL, NULL);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		OutputDebugStringEx(L"§DLL_PROCESS_ATTACH\n");
		RunThread();
		break;
	case DLL_PROCESS_DETACH:
		OutputDebugStringEx(L"§DLL_PROCESS_DETACH\n");
		break;
	case DLL_THREAD_DETACH:
		OutputDebugStringEx(L"§DLL_THREAD_DETACH\n");
		break;
	}
	return TRUE;
}