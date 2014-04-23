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