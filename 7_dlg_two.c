#include <windows.h>
#include "7_dlg_two.h"

// http://www.winprog.org/tutorial/modeless_dialogs.html
HWND g_hToolbar = NULL;
BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case IDC_PRESS:
                    MessageBox(hwnd, "Hi!", "This is a message", 
                        MB_OK | MB_ICONEXCLAMATION);
                break;
                case IDC_OTHER:
                    MessageBox(hwnd, "Bye!", "This is also a message", 
                        MB_OK | MB_ICONEXCLAMATION);
                break;
            }
        break;
        default:
            return FALSE;
    }
    return TRUE;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CREATE:
	        g_hToolbar = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TOOLBAR), hwnd, ToolDlgProc);
	        if(g_hToolbar != NULL)
	            ShowWindow(g_hToolbar, SW_SHOW);
	        else
	            MessageBox(hwnd, "CreateDialog returned NULL", "Warning!", MB_OK | MB_ICONINFORMATION);
	    break;
	    case WM_COMMAND:
	        switch(LOWORD(wParam)) {   
	            case IDM_DIALOG_SHOW:
	                ShowWindow(g_hToolbar, SW_SHOW);
	            break;
	            case IDM_DIALOG_HIDE:
	                ShowWindow(g_hToolbar, SW_HIDE);
	            break;
	            //... other command handlers
	        }
	    break;
		case WM_DESTROY:
			DestroyWindow(g_hToolbar); PostQuitMessage(0); return 0;
		default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow) {
	WNDCLASS wc = { };
	wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = "myClass";
    wc.lpszMenuName =  MAKEINTRESOURCE(IDM_MYMENURESOURCE);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        "myClass",                     // Window class
        "Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}