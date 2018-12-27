#include <windows.h>
#include "6_dlg_one.h"

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_INITDIALOG: return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDOK: EndDialog(hwnd, IDOK); break;
				case IDCANCEL: EndDialog(hwnd, IDCANCEL); break;
			} break;
		default: return FALSE;
	} return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_COMMAND: switch (LOWORD(wParam)) {
			case IDM_FILE_EXIT: {
				PostMessage(hwnd, WM_CLOSE, 0, 0); break;
			} break;
			case IDM_HELP_ABOUT: {
				int ret = DialogBox(GetModuleHandle(NULL),
					MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);
				if (ret == IDOK) {
					MessageBox(hwnd, "Dialog exited with IDOK.", "Notice", MB_OK|MB_ICONINFORMATION);
				} else if (ret == IDCANCEL) {
					MessageBox(hwnd, "Dialog exited with IDCANCE", "Notice", MB_OK|MB_ICONINFORMATION);
				} else if (ret == -1) {
					MessageBox(hwnd, "Dialog failed!", "Error", MB_OK|MB_ICONERROR);
				}
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