#include <windows.h>
#include "6_dlg_one.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_COMMAND: switch (LOWORD(wParam)) {
			case IDM_FILE_EXIT: {
				PostMessage(hwnd, WM_CLOSE, 0, 0); break;
			} break;
		} break;
		case WM_DESTROY: PostQuitMessage(0); return 0;
		default: return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	const char CLASS_NAME[] = "MyWindow";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.lpszMenuName =  MAKEINTRESOURCE(IDM_MYMENURESOURCE); 
	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Learn to Program Windows", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,NULL,hInstance,NULL);
	if (hwnd == NULL) return 0;

	ShowWindow(hwnd, nCmdShow);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}