#include <Windows.h>
#include <commctrl.h>
class MainWindow
{
	public:
		MainWindow(HINSTANCE hInstance);
		~MainWindow();
		MainWindow();
		static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void OnCommand(HWND hwnd, int id, HWND hCtl, UINT codeNotify);
		bool Run(int nCmdShow);
		void Create(HINSTANCE Hinst , HWND hwnd, LPARAM lParam, HBITMAP logo);
		operator HWND();


	HWND CreateStandardToolbar(HWND hParent, HINSTANCE hInst);
	HWND hWndToolbar;
	void ChangeCurrentCursor(HWND hWnd, LPCTSTR cursor);
	void ChangeCurrentColor(HDC d, HPEN strokePens, COLORREF color, int width);
	void DeleteObjectHPEN(HPEN pen);

	private:
		WNDCLASSEX m_wndClass;
		static HINSTANCE m_hInstance;
		HWND m_hwnd;
		static char m_szClassName[];
};


