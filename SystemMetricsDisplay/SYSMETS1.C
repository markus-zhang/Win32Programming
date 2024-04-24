#include <Windows.h>
#include "SYSMETS.H"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR	szAppName[] = TEXT("SysMets1");
	HWND			hwnd;
	MSG				msg;
	WNDCLASS		wndclass;

	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInstance;
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= szAppName;

	if (!(RegisterClass(&wndclass))) {
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(
		szAppName, TEXT("Get System Metrics No. 1"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL
	);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	// Message queue process
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static int	cxChar, cxCaps, cyChar;
	HDC			hdc;
	int			i;
	PAINTSTRUCT ps;
	TCHAR		szBuffer[10];
	TEXTMETRIC	tm;

	switch (message) {
	case WM_CREATE:
		hdc = GetDC(hwnd);

		// Text metrics remains constant for one Windows session, 
		// the best place to obtain it is at WM_CREATE
		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		// For uppercase letters, the average width of each character is calculated as:
		// - Fixed-pitch fonts have their average width equal csChar
		// - Variable-pitch fonts have their average width equal 1.5 * csChar
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
		// tmExternalLeading is the extra height to "keep the space", sometime it's 0
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		// GetDC() and ReleaseDC() must be paired in one case
		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		for (i = 0; i < NUMLINES; i++) {
			TextOut(hdc, 0, cyChar * i, sysmetrics[i].szLabel, lstrlen(sysmetrics[i].szLabel));
			// I want the 2nd section starting from 50 * average char width (good enough as none of the 1st section strings reach 50 characers)
			TextOut(hdc, 50 * cxCaps, cyChar * i, sysmetrics[i].szDesc, lstrlen(sysmetrics[i].szDesc));

			SetTextAlign(hdc, TA_RIGHT | TA_TOP);
			// The 3rd section should be 40 cxChar away from the 2nd section
			TextOut(hdc, 50 * cxCaps + 40 * cxChar, cyChar * i, szBuffer, wsprintf(szBuffer, TEXT("%5d"), GetSystemMetrics(sysmetrics[i].iIndex)));

			SetTextAlign(hdc, TA_LEFT | TA_TOP);
		}

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}