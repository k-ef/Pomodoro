#define UNICODE
#define _UNICODE
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <WinDef.h>
#include "pomodoro.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) 
{
    const wchar_t *CLASS_NAME = L"Pomodoro"; 

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND pomodoro_hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Pomodoro Timer",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 500,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (pomodoro_hwnd == NULL) {
        return 0;
    }

    ShowWindow(pomodoro_hwnd, nCmdShow);

    MSG msg = {0};

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
        {
            return 0;
        } 

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }

        case WM_PAINT: 
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, GetStockObject(GRAY_BRUSH));
            EndPaint(hwnd, &ps);
            return 0;
        } 

        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

