// license wtfpl

// shared code

#include "common.h"

// other
wstring format(const wchar_t* format, ...) {
	const int len = 0x2000;
	wchar_t buffer[len];
	va_list argptr;
	va_start(argptr, format);
	_vsnwprintf(buffer, len, format, argptr);
	va_end(argptr);
	return wstring(buffer);
}

void OutputDebugStringEx(const wchar_t* format, ...) {
	wchar_t buffer[1024*8];
	va_list argptr;
	va_start(argptr, format);
	_vsnwprintf(buffer, 1024*8, format, argptr);
	va_end(argptr);
	OutputDebugString(buffer);
}

wstring GetLastErrorEx() {
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&lpMsgBuf, 0, NULL);
	return wstring((LPWSTR)lpMsgBuf);
}

// windows

wstring WMTranslate(UINT message) {
	switch(message) {
	case WM_ACTIVATE: return L"WM_ERASEBKGND";
	case WM_ERASEBKGND: return L"WM_ERASEBKGND";
	case WM_SETCURSOR: return L"WM_SETCURSOR";
	case WM_MOUSEACTIVATE: return L"WM_SETCURSOR";
	case WM_NOTIFY: return L"WM_SETCURSOR";
	case WM_NCMOUSEMOVE: return L"WM_NCMOUSEMOVE";
	case WM_NCLBUTTONDOWN: return L"WM_NCLBUTTONDOWN";
	case WM_NCLBUTTONUP: return L"WM_NCLBUTTONDOWN";
	case WM_NCLBUTTONDBLCLK: return L"WM_NCLBUTTONDOWN";
	case WM_NCHITTEST: return L"WM_NCHITTEST";
	case WM_CTLCOLORBTN: return L"WM_CTLCOLORBTN";
	case WM_CTLCOLORDLG: return L"WM_CTLCOLORDLG";
	case WM_MOUSEFIRST: return L"WM_MOUSEFIRST";
	case WM_CAPTURECHANGED: return L"WM_MOUSEFIRST";
	case WM_NCMOUSELEAVE: return L"WM_NCMOUSELEAVE";
	case WM_PRINTCLIENT: return L"WM_PRINTCLIENT";
	}
	return format(L"0x%x", message);
}

wstring WSTranslate(LONG style) {
	wstring s = L"";
	if(style&WS_BORDER) s += L"WS_BORDER|";
	if(style&WS_CAPTION) s += L"WS_CAPTION|";
	if(style&WS_CHILD) s += L"WS_CHILD|";
	if(style&WS_CHILDWINDOW) s += L"WS_CHILDWINDOW|";
	if(style&WS_CLIPCHILDREN) s += L"WS_CLIPCHILDREN|";
	if(style&WS_CLIPSIBLINGS) s += L"WS_CLIPSIBLINGS|";
	if(style&WS_DISABLED) s += L"WS_DISABLED|";
	if(style&WS_DLGFRAME) s += L"WS_DLGFRAME|";
	if(style&WS_GROUP) s += L"WS_GROUP|";
	if(style&WS_HSCROLL) s += L"WS_HSCROLL|";
	if(style&WS_ICONIC) s += L"WS_ICONIC|";
	if(style&WS_MAXIMIZE) s += L"WS_MAXIMIZE|";
	if(style&WS_MAXIMIZEBOX) s += L"WS_MAXIMIZEBOX|";
	if(style&WS_MINIMIZE) s += L"WS_MINIMIZE|";
	if(style&WS_MINIMIZEBOX) s += L"WS_MINIMIZEBOX|";
	if(style&WS_OVERLAPPED) s += L"WS_OVERLAPPED|";
	if(style&WS_POPUP) s += L"WS_POPUP|";
	if(style&WS_SIZEBOX) s += L"WS_SIZEBOX|";
	if(style&WS_SYSMENU) s += L"WS_SYSMENU|";
	if(style&WS_TABSTOP) s += L"WS_TABSTOP|";
	if(style&WS_THICKFRAME) s += L"WS_THICKFRAME|";
	if(style&WS_TILED) s += L"WS_TILED|";
	if(style&WS_VISIBLE) s += L"WS_VISIBLE|";
	if(style&WS_VSCROLL) s += L"WS_VSCROLL|";
	if(style&WS_OVERLAPPED
		&& style&WS_CAPTION
		&& style&WS_SYSMENU
		&& style&WS_THICKFRAME
		&& style&WS_MINIMIZEBOX
		&& style&WS_MAXIMIZEBOX) s += L" WS_OVERLAPPEDWINDOW";
	if(style&WS_POPUP
		&& style&WS_BORDER
		&& style&WS_SYSMENU) s += L" WS_POPUPWINDOW";
	if(style&WS_OVERLAPPED
		&& style&WS_CAPTION
		&& style&WS_SYSMENU
		&& style&WS_THICKFRAME
		&& style&WS_MINIMIZEBOX
		&& style&WS_MAXIMIZEBOX) s += L" WS_TILEDWINDOW";
	return s;
}

wstring WSEXTranslate(LONG style) {
	wstring s = L"";
	if(style&WS_EX_DLGMODALFRAME) s += L"WS_EX_DLGMODALFRAME|";
	if(style&WS_EX_NOPARENTNOTIFY) s += L"WS_EX_NOPARENTNOTIFY|";
	if(style&WS_EX_TOPMOST) s += L"WS_EX_TOPMOST|";
	if(style&WS_EX_ACCEPTFILES) s += L"WS_EX_ACCEPTFILES|";
	if(style&WS_EX_TRANSPARENT) s += L"WS_EX_TRANSPARENT|";
	if(style&WS_EX_MDICHILD) s += L"WS_EX_MDICHILD|";
	if(style&WS_EX_TOOLWINDOW) s += L"WS_EX_TOOLWINDOW|";
	if(style&WS_EX_WINDOWEDGE) s += L"WS_EX_WINDOWEDGE|";
	if(style&WS_EX_CLIENTEDGE) s += L"WS_EX_CLIENTEDGE|";
	if(style&WS_EX_CONTEXTHELP) s += L"WS_EX_CONTEXTHELP|";
	if(style&WS_EX_RIGHT) s += L"WS_EX_RIGHT|";
	if(style&WS_EX_LEFT) s += L"WS_EX_LEFT|";
	if(style&WS_EX_RTLREADING) s += L"WS_EX_RTLREADING|";
	if(style&WS_EX_LTRREADING) s += L"WS_EX_LTRREADING|";
	if(style&WS_EX_LEFTSCROLLBAR) s += L"WS_EX_LEFTSCROLLBAR|";
	if(style&WS_EX_RIGHTSCROLLBAR) s += L"WS_EX_RIGHTSCROLLBAR|";
	if(style&WS_EX_CONTROLPARENT) s += L"WS_EX_CONTROLPARENT|";
	if(style&WS_EX_STATICEDGE) s += L"WS_EX_STATICEDGE|";
	if(style&WS_EX_APPWINDOW) s += L"WS_EX_APPWINDOW|";
	return s;
}

// virtual keycodes names
wstring VKToString(int KeyCode) {
	// Default value
	wchar_t KeyStr[64] = {0};
	GetKeyNameText(MapVirtualKey(KeyCode, MAPVK_VK_TO_VSC) << 16, KeyStr, 64);
	wstring KeyString = KeyStr;

	switch(KeyCode)	{
		// Give it some help with a few keys
		case VK_END: return L"END";
		case VK_INSERT: return L"INS";
		case VK_DELETE: return L"DEL";
		case VK_PRIOR: return L"PGUP";
		case VK_NEXT: return L"PGDN";

		case VK_UP: return L"UP";
		case VK_DOWN: return L"DOWN";
		case VK_LEFT: return L"LEFT";
		case VK_RIGHT: return L"RIGHT";

		case VK_LSHIFT: return L"LEFT SHIFT";
		case VK_LCONTROL: return L"LEFT CTRL";
		case VK_RCONTROL: return L"RIGHT CTRL";
		case VK_LMENU: return L"LEFT ALT";

		default: return KeyString;
	}
}

HWND FindWindowByTitle(wstring find, bool exact) {
	wchar_t _title[256];
	HWND hWnd = GetForegroundWindow();

	while (hWnd != NULL) {
		int len = GetWindowText(hWnd, _title, 256);
		wstring title(_title);
		DWORD PID;
		GetWindowThreadProcessId(hWnd, &PID);

		if (GetCurrentProcessId() == PID) {
			if (exact) {
				if (!title.compare(find))
					break;
			} else {
				if (!title.compare(0, find.length(), find))
					break;
			}
		}
		hWnd = GetNextWindow(hWnd, GW_HWNDNEXT);
	}

	if (!hWnd)
		OutputDebugStringEx(L"Unable to find window \"%s\"", find.c_str());
	else
		OutputDebugStringEx(L"HWND: 0x%x", hWnd);

	return hWnd;
}

wstring GetClassNameEx(HWND hWnd) {
	wchar_t buf[256];
	GetClassName(hWnd, buf, 256);
	return wstring(buf);
}

wstring GetWindowTextEx(HWND hWnd) {
	wchar_t buf[256];
	GetWindowText(hWnd, buf, 256);
	return wstring(buf);
}

void OverrideWndProc(WNDPROC pWndProc, WNDPROC WindowProc, HWND hWnd) {
	if (!IsWindow(hWnd)) return;
	if (!(pWndProc = (WNDPROC)GetWindowLongPtr(hWnd, GWLP_WNDPROC)))
		OutputDebugStringEx(L"pOldWndProc: %s", GetLastErrorEx().c_str());
	if (!SetWindowLongPtr(hWnd, GWLP_WNDPROC, LONG_PTR(WindowProc)))
		OutputDebugStringEx(L"SetWindowLongPtr: %s", GetLastErrorEx().c_str());
}

void ChangeStyle(HWND hWnd, LONG style) {
	SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE|WS_OVERLAPPEDWINDOW);
}

void SetAppID(HWND hWnd, wstring appId) {
	IPropertyStore *pps;
	HRESULT hr = SHGetPropertyStoreForWindow(hWnd, IID_PPV_ARGS(&pps));
	if (SUCCEEDED(hr)) {
		PROPVARIANT pv;
		hr = InitPropVariantFromString(appId.c_str(), &pv);
		if (SUCCEEDED(hr)) {
			hr = pps->SetValue(PKEY_AppUserModel_ID, pv);
			PropVariantClear(&pv);
		}
		pps->Release();
	}
}
