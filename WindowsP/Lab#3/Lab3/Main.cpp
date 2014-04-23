/*=========================================================================================
*
*In order to make sure that the Application is working please add the following library
*comctl32.lib to the library section of your properties.
*For Visual Studio Express 2012: 
*Project -> Properties -> Linker -> Input -> Additional Dependencies 
* 
*Now this project is up to building
*
*
*
*==========================================================================================*/


#include <windows.h>
#include "MainWindow.h"
 
//Defining static member variables 
HINSTANCE MainWindow::m_hInstance = 0;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{

    MSG msg;
    MainWindow *winMain = new MainWindow(hInst);
    if(!winMain->Run(nCmdShow))
    {
        delete winMain;
        return 1; 
    }
 
    // Run the message loop. It will run until GetMessage() returns 0
    while (GetMessage (&msg, NULL, 0, 0))
    {
        // Translate virtual-key messages into character messages
        TranslateMessage(&msg);

        // Send message to WindowProcedure
        DispatchMessage(&msg);
    }
 
    delete winMain;
 
    return msg.wParam;
}