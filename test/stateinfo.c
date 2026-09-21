#define UNICODE
#define _UNICODE
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <WinDef.h>
#include "pomodoro.h"

struct ClientDimensions {
    int X_SIZE;
    int Y_SIZE;
} ClientDim;

const wchar_t *MAIN_CLASS_NAME = L"Pomodoro"; 
const wchar_t *TIMER_CLASS_NAME = L"Timer";

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) 
{
    //Main Window
    RegisterMainWindowClass(MAIN_CLASS_NAME, hInstance);
    HWND pomodoro_hwnd = CreateMainWindow(MAIN_CLASS_NAME, L"Pomodoro Timer", 800, 500, hInstance);

    ShowWindow(pomodoro_hwnd, nCmdShow);

    MSG msg = {0};

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
}

void RegisterTimerWindowClass(const wchar_t *class_name, HINSTANCE hInstance)
{
    WNDCLASS wc = {};

    wc.lpfnWndProc = TimerWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = class_name;

    RegisterClass(&wc);

}

HWND CreateTimerWindow(const wchar_t *class_name, const wchar_t *caption, int x_pos, int y_pos, int x_size, int y_size, HINSTANCE hInstance, HWND parent_hwnd)
{
    HWND timer_hwnd = CreateWindowEx(
        0,
        class_name,
        caption,
        WS_CHILD | WS_VISIBLE,
        x_pos, y_pos,
        x_size, y_size,
        parent_hwnd,
        NULL,
        hInstance,
        NULL
    );

    if (timer_hwnd == NULL) {
        return 0;
    }
    
    return timer_hwnd;
}

void RegisterMainWindowClass(const wchar_t *class_name, HINSTANCE hInstance)
{
    WNDCLASS wc = {};

    wc.lpfnWndProc = MainWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = class_name;

    RegisterClass(&wc);
}

HWND CreateMainWindow(const wchar_t *class_name, const wchar_t *caption, int x_size, int y_size, HINSTANCE hInstance)
{
    HWND main_hwnd = CreateWindowEx(
        0,
        class_name,
        caption,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        x_size, y_size,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (main_hwnd == NULL) {
        return 0;
    }

    return main_hwnd;
}

LRESULT CALLBACK TimerWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
            FillRect(hdc, &ps.rcPaint, GetStockObject(WHITE_BRUSH));
            EndPaint(hwnd, &ps);
            return 0;
        } 

        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
        {
            RECT client_window;
            GetClientRect(hwnd, &client_window);
            ClientDim.X_SIZE = client_window.right;
            ClientDim.Y_SIZE = client_window.bottom;

            //Timer Window
            RegisterTimerWindowClass(TIMER_CLASS_NAME, NULL);
            HWND timer_hwnd = CreateTimerWindow(TIMER_CLASS_NAME, NULL, 20, 20, 200, 200, NULL, hwnd);

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

