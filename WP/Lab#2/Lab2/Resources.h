#ifndef RESOURCES_H
#define RESOURCES_H


#include <windows.h>
#include <iostream>
#include <commctrl.h>
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */

void AddMenus(HWND);


#define EMERALD  RGB(46, 204, 113)
#define Orange  RGB(200, 204, 0)
#define IDM_FILE_NEW 1
#define IDM_FILE_OPEN 2
#define IDM_FILE_QUIT 3
#define ID_MAIN_BUTTON	10
#define ID_CHECKED_BUTTON 100
#define IDI_ICON 101
void ChangeBKColor(HWND hwnd,COLORREF Color);
  void CreateControls(HWND hwnd);
  void UpdateLabel(HWND Window);
#endif