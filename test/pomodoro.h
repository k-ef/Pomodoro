#ifndef POMODORO_H_
#define POMODORO_H_

//Spacing
#define MARGIN 20
#define PADDING 10

//HMENU
#define PLAY_BTN 1
#define RESET_BTN 2
#define TEXTBOX 3

//Structs
struct ClientDimensions {
    LONG X;
    LONG Y;
    LONG X_SIZE;
    LONG Y_SIZE;
} ClientDim;

struct TimerDimensions {
    LONG X;
    LONG Y;
    LONG X_SIZE;
    LONG Y_SIZE;
} TimerDim;

struct NoteDimensions {
    LONG X;
    LONG Y;
    LONG X_SIZE;
    LONG Y_SIZE;
} NoteDim;

struct Time {
    int h;
    int m;
    int s;
} Time;

//Register
void RegisterChildWindowClass(const wchar_t *class_name, HINSTANCE hInstance, LRESULT(*fPtr)(HWND, UINT, WPARAM, LPARAM));
void RegisterMainWindowClass(const wchar_t *class_name, HINSTANCE hInstance);

//Create
HWND CreateChildWindow(const wchar_t *class_name, const wchar_t *caption, int x_pos, int y_pos, int x_size, int y_size, HINSTANCE hInstance, HWND parent_hwnd);
HWND CreateMainWindow(const wchar_t *class_name, const wchar_t *caption, int x_size, int y_size, HINSTANCE hInstance);
HWND CreateTimerButton(HWND parent, const wchar_t *btnText, int x_size, int y_size, HMENU hMenu, HINSTANCE hInstance);
HWND CreateTextBox(HWND parent, const wchar_t *caption, int x_size, int y_size, HMENU hMenu, HINSTANCE hInstance);

//Window procedures
LRESULT CALLBACK TimerWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK NoteWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//Helper functions
void GetTime(int h, int m, int s, wchar_t *hourStr);

#endif
