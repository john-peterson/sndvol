// license wtfpl

#pragma once

// #include <algorithm>
// #include <cctype>
// #include <cstdarg>
// #include <cstdlib>
// #include <cstring>
// #include <errno.h>
// #include <fcntl.h>
// #include <fstream>
// #include <iostream>
// #include <signal.h>
// #include <sstream>
// #include <stdio.h>
// #include <stdarg.h>
#include <string>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <vector>
#include <windows.h>
#include <shobjidl.h>
#include <propvarutil.h>
#include <propkey.h>

using namespace std;

// windows

void OutputDebugStringEx(const wchar_t* format, ...);
wstring GetLastErrorEx();
wstring WMTranslate(UINT message);
wstring WSTranslate(LONG style);
wstring WSEXTranslate(LONG style);
wstring VKToString(int KeyCode);
HWND FindWindowByTitle(wstring find, bool exact = false);
wstring GetClassNameEx(HWND hWnd);
wstring GetWindowTextEx(HWND hWnd);
void OverrideWndProc(WNDPROC pWndProc, WNDPROC WindowProc, HWND hWnd);
void ChangeStyle(HWND hWnd, LONG style);
void SetAppID(HWND hWnd, wstring appId);
