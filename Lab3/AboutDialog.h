#include <windows.h>
#include "Resource.h"
 
// Class: AboutDialog
// Draws the About Dialog
class AboutDialog
{
public:
    AboutDialog();
    ~AboutDialog();
    static BOOL CALLBACK DialogProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    int Run(HINSTANCE hInstance, HWND hParent);
 
private:
    HWND m_hwnd;
};