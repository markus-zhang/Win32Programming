/*

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

int CDECL MessageBoxPrintf(const TCHAR* szCaption, const TCHAR* szFormat, ...);

static int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	int cxScreen, cyScreen;
	wchar_t wcCaption[] = L"Screen Size";


	cxScreen = GetSystemMetrics(SM_CXSCREEN);
	cyScreen = GetSystemMetrics(SM_CYSCREEN);

	MessageBoxPrintf(wcCaption, TEXT("The Screen is %i pixels wide by %i pixels high."), cxScreen, cyScreen);
	return 0;
}

int CDECL MessageBoxPrintf(const TCHAR* szCaption, const TCHAR* szFormat, ...) {
	TCHAR	szBuffer[1024];
	va_list	pArgList;

	va_start(pArgList, szFormat);

	_vsnwprintf_s(szBuffer, sizeof(szBuffer) / sizeof(TCHAR), szFormat, pArgList);

	szBuffer[1023] = 0;

	va_end(pArgList);

	return MessageBox(NULL, szBuffer, szCaption, 0);
}

*/