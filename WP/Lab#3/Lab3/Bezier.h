#include <Windows.h>
#include <commctrl.h>

class MyBezier 
{
	public:
		~MyBezier();
		MyBezier();
		void DrawBezier(HDC hdc, POINT apt[]);
};