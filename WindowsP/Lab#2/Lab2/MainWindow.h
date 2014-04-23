#include <Windows.h>

class MainWindow
{
	public:
		MainWindow(HINSTANCE hInstance);
		~MainWindow();
		MainWindow();
		static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void OnCommand(HWND hwnd, int id, HWND hCtl, UINT codeNotify);
		bool Run(int nCmdShow);
		void MainWindow::Create(HINSTANCE Hinst , HWND hwnd);
		

	private:
		WNDCLASSEX m_wndClass;
		static HINSTANCE m_hInstance;
		HWND m_hwnd;
		static char m_szClassName[];
};
		