#include <windows.h>
#include "AboutDialog.h"
#include "resource.h"
 
HINSTANCE hInstance;

AboutDialog::AboutDialog()
{
}
 
AboutDialog::~AboutDialog()
{
}
 
// Function: Run
// Returns: Result of the DialogBox
int AboutDialog::Run(HINSTANCE hInstance, HWND hParent)
{
   int retval = DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUT), hParent, DialogProc);
	
   return retval;
}
 
// Function: DialogProc
// Handles the messages for the About dialog

BOOL CALLBACK AboutDialog::DialogProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int retVal = false;
    switch(msg)
    {
		case WM_INITDIALOG:
			retVal = true;
		break;

		case WM_COMMAND:
			
			if(LOWORD(wParam) == IDOK)
				EndDialog(hwnd, TRUE);
		break;
		
		case WM_CLOSE:
			EndDialog(hwnd, TRUE);
		break;
    }
   return retVal;
}