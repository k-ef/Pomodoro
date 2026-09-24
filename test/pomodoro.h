#ifndef POMODORO_H_
#define POMODORO_H_

void RegisterChildWindowClass(const wchar_t *class_name, HINSTANCE hInstance, LRESULT(*fPtr)(HWND, UINT, WPARAM, LPARAM));
HWND CreateChildWindow(const wchar_t *class_name, const wchar_t *caption, int x_pos, int y_pos, int x_size, int y_size, HINSTANCE hInstance, HWND parent_hwnd);
void RegisterMainWindowClass(const wchar_t *class_name, HINSTANCE hInstance);
HWND CreateMainWindow(const wchar_t *class_name, const wchar_t *caption, int x_size, int y_size, HINSTANCE hInstance);
LRESULT CALLBACK TimerWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK NoteWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif
