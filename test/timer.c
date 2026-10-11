#define UNICODE
#define _UNICODE
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <WinDef.h>
#include "pomodoro.h"


const wchar_t *MAIN_CLASS_NAME = L"Pomodoro"; 
const wchar_t *TIMER_CLASS_NAME = L"Timer";
const wchar_t *NOTE_CLASS_NAME = L"Note";

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

void RegisterChildWindowClass(const wchar_t *class_name, HINSTANCE hInstance, LRESULT(*fPtr)(HWND, UINT, WPARAM, LPARAM))
{
    WNDCLASS wc = {};

    wc.lpfnWndProc = fPtr;
    wc.hInstance = hInstance;
    wc.lpszClassName = class_name;

    RegisterClass(&wc);
}

HWND CreateChildWindow(const wchar_t *class_name, const wchar_t *caption, int x_pos, int y_pos, int x_size, int y_size, HINSTANCE hInstance, HWND parent_hwnd)
{
    HWND child_hwnd = CreateWindowEx(
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

    if (child_hwnd == NULL) {
        return 0;
    }
    
    return child_hwnd;
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

HWND CreateTimerButton(HWND parent, const wchar_t *btnText, int x_size, int y_size, HMENU hMenu, HINSTANCE hInstance)
{
    HWND btn = CreateWindowEx(
        0,
        L"BUTTON",
        btnText,
        BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
        CW_USEDEFAULT, CW_USEDEFAULT,
        x_size, y_size,
        parent,
        hMenu,
        hInstance,
        NULL
    );

    if (btn == NULL) {
        return 0;
    }

    return btn;
}

LRESULT CALLBACK TimerWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
        {
            HWND playBtn_hwnd = CreateTimerButton(hwnd, L"Play", 80, 80, (HMENU)PLAY_BTN, NULL);

            //Change button placement
            RECT pos = {10, 10, 0, 0};
            int btn_x = (TimerDim.X_SIZE / 2) - 80;
            int btn_y = TimerDim.Y_SIZE - 80 - PADDING;
            MoveWindow(playBtn_hwnd, btn_x, btn_y, 80, 80, TRUE); //Probably not gonna change this but just in case

            return 0;
        } 

        case WM_NOTIFY:
        case WM_COMMAND:
        {
            printf("bruh\n"); //TODO: Functionality
            return 0;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }

        case WM_SIZE: 
        {
            // RECT TimerRect;
            // GetClientRect(hwnd, &TimerRect);
            // InvalidateRect(hwnd, &TimerRect, TRUE);
            // ValidateRect(hwnd, &TimerRect);
            break;
        }

        case WM_PAINT: 
        {
            PAINTSTRUCT ps;
            DWORD color;
            HFONT hFont, holdFont;
            LOGFONT lf;
            HDC hdc = BeginPaint(hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, GetStockObject(WHITE_BRUSH));

            //Timer text specs
            SetBkColor(hdc, (DWORD)RGB(128, 128, 128));

            hFont = CreateFontW(50, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0, 
                                0, 0, 0, 0, L"Calibri");
            holdFont = SelectObject(hdc, hFont);
            
            GetObject(holdFont, sizeof(LOGFONT), &lf);

            //Timer text
            static wchar_t hourStr[32];
            GetTime(2, 3, 4, hourStr);
            int text_x = (ps.rcPaint.right / 2) - 75; //Hardcoded because i dont want to do the calculations
            int text_y = 75 + PADDING;
            TextOutW(hdc, text_x, text_y, hourStr, lstrlenW(hourStr)); //relative to timer child window 

            SelectObject(hdc, holdFont);
            DeleteObject(hFont);

            EndPaint(hwnd, &ps);
            return 0;
        } 

        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

LRESULT CALLBACK NoteWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

        case WM_SIZE: 
        {
            // RECT TimerRect;
            // GetClientRect(hwnd, &TimerRect);
            // InvalidateRect(hwnd, &TimerRect, TRUE);
            // ValidateRect(hwnd, &TimerRect);
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
            ClientDim.X = client_window.left;
            ClientDim.Y = client_window.top;
            ClientDim.X_SIZE = client_window.right;
            ClientDim.Y_SIZE = client_window.bottom;

            //Timer Window
            TimerDim.X = MARGIN;
            TimerDim.Y = MARGIN;
            TimerDim.X_SIZE = (ClientDim.X_SIZE - MARGIN * 2) * 0.35;
            TimerDim.Y_SIZE = ClientDim.Y_SIZE - MARGIN * 2;

            RegisterChildWindowClass(TIMER_CLASS_NAME, NULL, TimerWindowProc);
            HWND timer_hwnd = CreateChildWindow(TIMER_CLASS_NAME, NULL, MARGIN, MARGIN, TimerDim.X_SIZE, TimerDim.Y_SIZE, NULL, hwnd);

            //Note Window
            LONG note_x = TimerDim.X_SIZE + MARGIN + 20;
            NoteDim.X = note_x;
            NoteDim.Y = MARGIN;
            NoteDim.X_SIZE = ClientDim.X_SIZE - MARGIN - note_x;
            NoteDim.Y_SIZE = ClientDim.Y_SIZE - MARGIN * 2;

            RegisterChildWindowClass(NOTE_CLASS_NAME, NULL, NoteWindowProc);
            HWND note_hwnd = CreateChildWindow(NOTE_CLASS_NAME, NULL, note_x, MARGIN, NoteDim.X_SIZE, NoteDim.Y_SIZE, NULL, hwnd);

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

void GetTime(int h, int m, int s, wchar_t *hourStr) {
    swprintf(hourStr, 32, L"%02d:%02d:%02d\0", h, m, s);
}
