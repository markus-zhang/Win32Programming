#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
// #include "SYSMETS.H"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR	szAppName[] = TEXT("Windows Size Demo");
	HWND			hwnd;
	MSG				msg;
	WNDCLASS		wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!(RegisterClass(&wndclass))) {
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(
		szAppName, TEXT("Get System Metrics No. 1"),
		WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
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

	RECT rect;
	static int width = 0;
	static int height = 0;
	static TCHAR buffer[100];

	switch (message) {
	case WM_CREATE:
		// Get initial Windows size

		static TCHAR szAppName[] = TEXT("Windows Size Demo");

		if (GetWindowRect(hwnd, &rect))
		{
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
			_stprintf_s(buffer, 50, _T("Initial width: %d, Initial height: %d"), width, height);
			// printf("Initial width: %d, Initial height: %d", width, height);
			// MessageBox(hwnd, buffer, szAppName, MB_OK);
		}
		else
		{
			MessageBox(NULL, TEXT("GetWindowRect() failed!"), szAppName, MB_ICONERROR);
			return 0;
		}

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

	case WM_SIZE:
		if (GetWindowRect(hwnd, &rect))
		{
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
			ZeroMemory(buffer, sizeof(buffer));
			_stprintf_s(buffer, 50, _T("Initial width: %d, Initial height: %d"), width, height);
			// printf("Initial width: %d, Initial height: %d", width, height);
			// MessageBox(hwnd, buffer, szAppName, MB_OK);
		}
		else
		{
			MessageBox(NULL, TEXT("GetWindowRect() failed!"), szAppName, MB_ICONERROR);
			return 0;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		// TextOut(hdc, 0, cyChar * 0, bufferWidth, lstrlen(bufferWidth));
		// TextOut(hdc, 50 * cxCaps, cyChar * 1, bufferHeight, lstrlen(bufferHeight));
		TextOut(hdc, 0, cyChar * 0, buffer, _tcslen(buffer));

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}