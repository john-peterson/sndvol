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

enum names {
	ID_WINDOW
	, ID_APPLICATIONS
	, ID_DEVICE
	, ID_MUTE_PROGRAM
	, ID_MUTE_ALL
};

// compare string

bool CompareString_(wstring s, wstring t, int start = -1, int end = -1) {
	if (start > -1)
		return !s.compare(start, end, t);
	else
		return !s.compare(t);
}

bool CompareStringEn(int id, wstring s) {
	switch (id) {
	case ID_APPLICATIONS: return CompareString_(s, L"Applications");
	case ID_DEVICE: return CompareString_(s, L"Device");
	case ID_MUTE_PROGRAM: return CompareString_(s, L"Mute", 0, 4);
	case ID_MUTE_ALL: return CompareString_(s, L"Mute Speakers", 0, 13);
	}
}

bool CompareStringSv(int id, wstring s) {
	switch (id) {
	case ID_APPLICATIONS: return CompareString_(s, L"Program");
	case ID_DEVICE: return CompareString_(s, L"Enhet");
	case ID_MUTE_PROGRAM: return CompareString_(s, L"Ljud av för", 0, 11);
	case ID_MUTE_ALL: return CompareString_(s, L"Stäng av ljudet för speakers");
	}
}

bool CompareString_(int id, wstring s) {
	LANGID langid = GetUserDefaultUILanguage();

	switch (langid) {
	case 1053:
		return CompareStringSv(id, s);
	default:
		return CompareStringEn(id, s);
	}
}

// return string

wstring GetStringEn(int id) {
	switch (id) {
	case ID_WINDOW: return L"Volume Mixer";
	}
}

wstring GetStringSv(int id) {
	switch (id) {
	case ID_WINDOW: return L"Volymkontrollen";
	}
}

wstring GetString(int id) {
	LANGID langid = GetUserDefaultUILanguage();

	OutputDebugStringEx(L"Language: %d", langid);

	switch (langid) {
	case 1053:
		return GetStringSv(id);
	default:
		return GetStringEn(id);
	}
}

void ShowStyle(HWND hWnd) {
	OutputDebugStringEx(L"GWL_STYLE: %s", WSTranslate(GetWindowLong(hWnd, GWL_STYLE)).c_str());
	OutputDebugStringEx(L"GWL_EXSTYLE: %s", WSEXTranslate(GetWindowLong(hWnd, GWL_EXSTYLE)).c_str());
}

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam) {
	EnumStruct* s = (EnumStruct*)lParam;
	wstring title = GetWindowTextEx(hWnd);

	if (CompareString_(ID_APPLICATIONS, title))
		s->hBox = hWnd;

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
		SetWindowPos(hWnd, 0, 0, 0, rc.right, rcBox.bottom - 10, SWP_NOMOVE|SWP_NOZORDER);
	}

	if (CompareString_(ID_DEVICE, wndName)) {
		//OutputDebugStringEx(L"§0x%08x: %s | %d %d %d %d\n", hWnd, GetClassNameEx(hWnd).c_str(), rc.left, rc.top, rc.right, rc.bottom);
		BOOL b = SetWindowPos(hWnd, 0, 0, 0, rc.right, rcBox.bottom, SWP_NOMOVE|SWP_NOZORDER);
		//RedrawWindow(hWnd, 0, 0, RDW_UPDATENOW);
	}

	if (!clsName.compare(L"msctls_trackbar32")) {
		//OutputDebugStringEx(L"§0x%08x: %s | %d %d %d %d\n", hWnd, GetClassNameEx(hWnd).c_str(), rc.left, rc.top, rc.right, rc.bottom);
		SetWindowPos(hWnd, 0, 0, 0, rc.right, rcBox.bottom - 140, SWP_NOMOVE|SWP_NOZORDER);
	}

	if (CompareString_(ID_MUTE_PROGRAM, wndName)) {
		//OutputDebugStringEx(L"§0x%08x: %s | %d %d %d %d\n", hWnd, GetClassNameEx(hWnd).c_str(), rc.left, rc.top, rc.right, rc.bottom);
		SetWindowPos(hWnd, 0, 30, rcBox.bottom - 70, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	}

	if (CompareString_(ID_MUTE_ALL, wndName)) {
		//OutputDebugStringEx(L"§0x%08x: %s | %d %d %d %d\n", hWnd, GetClassNameEx(hWnd).c_str(), rc.left, rc.top, rc.right, rc.bottom);
		SetWindowPos(hWnd, 0, 42, rcBox.bottom - 36, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
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
	if (!IsWindow(hWnd))
		return;

	if (!(pWndProc = (WNDPROC)GetWindowLongPtr(hWnd, GWLP_WNDPROC)))
		OutputDebugStringEx(L"pOldWndProc: %s", GetLastErrorEx().c_str());

	if (!SetWindowLongPtr(hWnd, GWLP_WNDPROC, LONG_PTR(WindowProc)))
		OutputDebugStringEx(L"SetWindowLongPtr: %s", GetLastErrorEx().c_str());
}

DWORD WINAPI ThreadFunction(LPVOID lpParam) {
	HWND hWnd = 0;

	while (!hWnd) {
		hWnd = FindWindowByTitle(GetString(ID_WINDOW));
		Sleep(1000/25);
	}

	ChangeStyle(hWnd, WS_OVERLAPPEDWINDOW);
	OverrideWndProc(hWnd);

	return 0;
}

void RunThread() {
	CreateThread(NULL, NULL, ThreadFunction, NULL, NULL, NULL);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		OutputDebugStringEx(L"DLL_PROCESS_ATTACH\n");
		RunThread();
		break;
	case DLL_PROCESS_DETACH:
		OutputDebugStringEx(L"DLL_PROCESS_DETACH\n");
		break;
	case DLL_THREAD_DETACH:
		OutputDebugStringEx(L"DLL_THREAD_DETACH\n");
		break;
	}
	return TRUE;
}