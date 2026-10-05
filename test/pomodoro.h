#ifndef POMODORO_H_
#define POMODORO_H_

#define MARGIN 20
#define PADDING 10

//Register
void RegisterChildWindowClass(const wchar_t *class_name, HINSTANCE hInstance, LRESULT(*fPtr)(HWND, UINT, WPARAM, LPARAM));
void RegisterMainWindowClass(const wchar_t *class_name, HINSTANCE hInstance);

//Create
HWND CreateChildWindow(const wchar_t *class_name, const wchar_t *caption, int x_pos, int y_pos, int x_size, int y_size, HINSTANCE hInstance, HWND parent_hwnd);
HWND CreateMainWindow(const wchar_t *class_name, const wchar_t *caption, int x_size, int y_size, HINSTANCE hInstance);

//Window procedures
LRESULT CALLBACK TimerWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK NoteWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//Helper functions
wchar_t *GetTime(int h, int m, int s);

#endif
