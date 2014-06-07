#include <windows.h>

//For more makros
#include <windowsx.h>
#include "MainWindow.h"
#include "Resource.h"
#include "AboutDialog.h"
#include "Bezier.h"

HINSTANCE hProgramInstance;
MainWindow Exo;
MyBezier myBezier;

//Global variables for child window
HWND hwndLabel3;
HWND hwndButton;
HWND hwndWidthSlider;
HWND hwndFillColor;
char MainWindow::m_szClassName[] = "DrawMomo";

//MinHeight and MinWidth of the main Window
int iMinWindowHeight = 610;
int iMinWindowWidth  = 420;



bool timerstart = false;
//Drawing Area
RECT Recto = {20, 50, 410, 500};
int alfa = 0;
int fill = 0;
MainWindow::MainWindow(HINSTANCE hInstance)
{
	m_hInstance = hInstance; // Save Instance handle
	m_wndClass.cbSize = sizeof(WNDCLASSEX); // Must always be sizeof(WNDCLASSEX)
	m_wndClass.style = CS_DBLCLKS; // Class styles	
	m_wndClass.lpfnWndProc = MainWndProc; // Pointer to callback procedure
	m_wndClass.cbClsExtra = 0; // Extra bytes to allocate following the wndclassex structure
	m_wndClass.cbWndExtra = 0; // Extra bytes to allocate following an instance of the structure
	m_wndClass.hInstance = hInstance; // Instance of the application
	m_wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_MAINCURSOR)); // Class Icon
	m_wndClass.hCursor = LoadCursor(hInstance,MAKEINTRESOURCE(IDC_MAINCURSOR)); // Class cursor
	m_wndClass.hbrBackground = CreateSolidBrush(RGB(246, 245, 243)); // Background brush
	m_wndClass.lpszMenuName = MAKEINTRESOURCE(IDM_MAINMENU); // Menu Resource
	m_wndClass.lpszClassName = (LPCWSTR)m_szClassName; // Name of this class
	m_wndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON)); // Small icon for this class
}

MainWindow::~MainWindow()
{
}

MainWindow::MainWindow()
{
	// If we declare a window class with a default constructor,
	// we need to reset the window to a nothing
}
LRESULT CALLBACK MainWindow::MainWndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc_mem;
	static HDC hdc;
	static PAINTSTRUCT ps;
	static SCROLLINFO si;
	static TEXTMETRIC tm;
	static HPEN strokePen = CreatePen(PS_SOLID, 1, RGB(255,0,0));

	//Static variables for drawing
	static bool isDrawing = FALSE;
	static int StartX, StartY;
	static int EndX, EndY;
	static UINT iButtonState;

	//Static variables for mouse Co-ordinates
	static int xMouse, yMouse;
	xMouse = GET_X_LPARAM(lParam);
	yMouse = GET_Y_LPARAM(lParam);
	static HBRUSH newbrush;

	//Child Window Handles
	MainWindow create;
	RECT rect;

	// Size and position variables
	static int iSysWidth;
	static int iSysHeight;
	static int iWinWidth;
	static int iWinHeight;
	static int cxChar;
	static int cyChar;

	static int iWidth  = 60;   // Button width
	static int iHeight = 30;   // Button height

	static int iListBoxWidth = 300;
	static int iListBoxHeight = 360;

	// Size and position variables
	static int x, y;

	hdc = GetDC(hwnd);
	GetTextMetrics(hdc, &tm);
	cxChar = tm.tmAveCharWidth;
	cyChar = tm.tmHeight;
	ReleaseDC(hwnd, hdc);

	//for Bezier
	static POINT apt[4];

	//bool variables
	bool white = false;
	bool green = false;
	bool red = false;
	bool black = false;

	hProgramInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);

	HBITMAP logo = NULL;
	BITMAP  bitmap;
	logo = (HBITMAP)LoadImage(hProgramInstance, L"standard.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(logo, sizeof(bitmap), &bitmap);

	switch (msg)
	{
	case WM_CREATE:
		{
			create.Create(hProgramInstance,hwnd,lParam,logo);
			Exo.CreateStandardToolbar(hwnd, Exo.m_hInstance);
			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDC_MAINCURSOR, TBSTATE_CHECKED | TBSTATE_ENABLED);	
		}
		break;

	case WM_GETMINMAXINFO:
		{
			LPMINMAXINFO pInfo = (LPMINMAXINFO) lParam;
			pInfo -> ptMaxTrackSize.x = 450;
			pInfo -> ptMaxTrackSize.y = 650;	
		}
		break;

	case WM_SIZE:

		iWidth  = LOWORD(lParam);
		iHeight = HIWORD(lParam);

		// Set vertical scroll bar range and page size
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = ((iMinWindowHeight - 70) / cyChar);
		si.nPage = iHeight / cyChar;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

		// Set horizontal scroll bar range and page size
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = ((iMinWindowWidth - 20) / cxChar);
		si.nPage = iWidth / cxChar;
		SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

		//Child window reposition
		MoveWindow(hwndButton,20,510,iListBoxWidth+90, iListBoxHeight-335, TRUE);
		MoveWindow(hwndWidthSlider, 20, 35, iListBoxWidth - 150, 10, TRUE);
		MoveWindow(hwndFillColor, 260, 35, iListBoxWidth - 150, 10, TRUE);
		GetWindowRect(hwnd, &rect);
		iWinWidth = rect.right - rect.left;
		iWinHeight = rect.bottom - rect.top;
		iSysWidth = GetSystemMetrics(SM_CXSCREEN);
		iSysHeight = GetSystemMetrics(SM_CYSCREEN);

		apt[0].x = iWidth / 7 ;
		apt[0].y = iHeight / 2 ;

		apt[1].x = iWidth / 5;
		apt[1].y = iHeight / 7 ;

		apt[2].x =     iWidth / 2 ;
		apt[2].y = 3 * iHeight / 4 ;

		apt[3].x = 3 * iWidth / 4 ;
		apt[3].y =     iHeight / 2 ;

		break;

	case WM_VSCROLL:
		// Get all the vertical scroll bar information
		si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;
		GetScrollInfo(hwnd, SB_VERT, &si);

		// Save the position for later comparison
		y = si.nPos;

		switch(LOWORD(wParam))
		{
		case SB_TOP:
			si.nPos = si.nMin;
			break;

		case SB_BOTTOM:
			si.nPos = si.nMax;
			break;

		case SB_LINEUP:
			si.nPos -= 1;
			break;

		case SB_LINEDOWN:
			si.nPos += 1;
			break;

		case SB_PAGEUP:
			si.nPos -= si.nPage;
			break;

		case SB_PAGEDOWN:
			si.nPos += si.nPage;
			break;

		case SB_THUMBTRACK:
			si.nPos = si.nTrackPos;
			break;

		default:
			break;
		}

		// Set the position and then retrieve it
		si.fMask = SIF_POS;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
		GetScrollInfo(hwnd, SB_VERT, &si);

		// If the position has changed, scroll the window and update it
		if(si.nPos != y) 
		{
			ScrollWindow(hwnd, 0, cyChar * (y - si.nPos), NULL, NULL);
			UpdateWindow(hwnd);
		}
		break;

	case WM_CTLCOLORSTATIC:

		SetTextColor((HDC)wParam, RGB(150, 100, 255));
		SetBkMode((HDC)wParam, TRANSPARENT);
		newbrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		DeleteObject(newbrush);
		return (LRESULT)newbrush;
		break;

	case WM_HSCROLL:
		GetWindowRect(hwnd, &rect);
		iWinWidth = rect.right - rect.left;
		iWinHeight = rect.bottom - rect.top;
		iSysWidth = GetSystemMetrics(SM_CXSCREEN);
		iSysHeight = GetSystemMetrics(SM_CYSCREEN);

		// Get all the vertical scroll bar information
		si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;
		GetScrollInfo(hwnd, SB_HORZ, &si);

		// Save the position for later comparison
		x = si.nPos;

		if(GetWindowLong((HWND)lParam, GWL_ID) == IDC_BACKGROUND_SCROLL)
		{
			switch(LOWORD(wParam))
			{
			case SB_PAGEDOWN:
				alfa += DELTA_COLOR;
				break;

			case SB_LINEDOWN:
				alfa = min(255, alfa+1);
				break;

			case SB_PAGEUP:
				alfa -= DELTA_COLOR;
				break;

			case SB_LINEUP:
				alfa = max(0, alfa-1);
				break;

			case SB_TOP:
				alfa = 0;
				break;

			case SB_BOTTOM:
				alfa = 255;
				break;

			case SB_THUMBPOSITION:
				break;

			case SB_THUMBTRACK:
				alfa = HIWORD(wParam);
				break;

			default: break;
			}
			SetScrollPos(hwndWidthSlider, SB_CTL, alfa, TRUE);
		}

		if(GetWindowLong((HWND)lParam, GWL_ID) == IDC_FILL_COLOR)
		{
			switch(LOWORD(wParam))
			{
			case SB_PAGEDOWN:
				fill += DELTA_COLOR;
				break;

			case SB_LINEDOWN:
				fill = min(255, fill+1);
				break;

			case SB_PAGEUP:
				fill -= DELTA_COLOR;
				break;

			case SB_LINEUP:
				fill = max(0, fill-1);
				break;

			case SB_TOP:
				fill = 0;
				break;

			case SB_BOTTOM:
				fill = 255;
				break;

			case SB_THUMBPOSITION:
				break;

			case SB_THUMBTRACK:
				fill = HIWORD(wParam);
				break;

			default: break;
			}
			SetScrollPos(hwndFillColor, SB_CTL, fill, TRUE);
		}

		switch(LOWORD(wParam)) 
		{
			case SB_LINELEFT:
				si.nPos -= 1;
				break;

			case SB_LINERIGHT:
				si.nPos += 1;
				break;

			case SB_PAGELEFT:
				si.nPos -= si.nPage;
				break;

			case SB_PAGERIGHT:
				si.nPos += si.nPage;
				break;

			case SB_THUMBPOSITION:
				si.nPos = si.nTrackPos;
				break;

		default:break;
		}

		// Set the position and then retrieve it
		si.fMask = SIF_POS;
		SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
		GetScrollInfo(hwnd, SB_HORZ, &si);
		// If the position has changed, scroll the window and update it
		if(si.nPos != x)
		{
			ScrollWindow(hwnd, cxChar * (x - si.nPos), 0, NULL, 0);
			UpdateWindow(hwnd);
		}
		break;

	case WM_COMMAND:

		//Initialazing OnCommand Function
		HANDLE_WM_COMMAND(hwnd, wParam, lParam, OnCommand);

		switch(LOWORD(wParam))
		{
		case IDC_CLEAR:
			{
				//Cleaning the working area
				InvalidateRect(hwnd, &Recto, FALSE);
				InvalidateRect(hwnd, &Recto, TRUE);
			}
			break;

		case IDM_FILE_NEW:

			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_FILE_NEW, TBSTATE_CHECKED | TBSTATE_ENABLED);
			white = TRUE;
			break;

		case IDM_FILE_OPEN:

			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_FILE_OPEN, TBSTATE_CHECKED | TBSTATE_ENABLED);
			green = TRUE;
			break;

		case IDM_FILE_SAVE:
			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_FILE_SAVE, TBSTATE_CHECKED | TBSTATE_ENABLED);
			black = TRUE;
			break;

		case IDM_FILE_PRINT:
			red = TRUE;
			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_FILE_PRINT, TBSTATE_CHECKED | TBSTATE_ENABLED);

			break;

		case IDM_FILE_EXIT:
			PostQuitMessage(WM_QUIT);
			break;

		case IDM_DRAW_FREEHAND:
			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_DRAW_FREEHAND, TBSTATE_CHECKED | TBSTATE_ENABLED);
			Exo.ChangeCurrentCursor(hwnd, MAKEINTRESOURCE(IDC_FREEHAND));
			break;
		case IDM_DRAW_LINE:
			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_DRAW_LINE, TBSTATE_CHECKED | TBSTATE_ENABLED);
			Exo.ChangeCurrentCursor(hwnd, MAKEINTRESOURCE(IDC_FREEHAND));
			break;

		case IDM_DRAW_POLYLINE:
			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_DRAW_POLYLINE, TBSTATE_CHECKED | TBSTATE_ENABLED);
			Exo.ChangeCurrentCursor(hwnd, MAKEINTRESOURCE(IDC_FREEHAND));
			break;
		case IDM_DRAW_RECTANGLE:
			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_DRAW_RECTANGLE, TBSTATE_CHECKED | TBSTATE_ENABLED);
			Exo.ChangeCurrentCursor(hwnd, MAKEINTRESOURCE(IDC_RECTANGLE));
			break;

		case IDM_DRAW_CIRCLE:
			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_DRAW_CIRCLE, TBSTATE_CHECKED | TBSTATE_ENABLED);
			Exo.ChangeCurrentCursor(hwnd, MAKEINTRESOURCE(IDC_CIRCLE));
			break;

		case IDM_DRAW_BEZIER:
			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_DRAW_BEZIER, TBSTATE_CHECKED | TBSTATE_ENABLED);
			Exo.ChangeCurrentCursor(hwnd, MAKEINTRESOURCE(IDC_CIRCLE));
			myBezier.DrawBezier(hdc, apt);
			break;

		case IDM_ERAZER:
			SendMessage(Exo.hWndToolbar, TB_SETSTATE, IDM_ERAZER, TBSTATE_CHECKED | TBSTATE_ENABLED);
			Exo.ChangeCurrentCursor(hwnd, MAKEINTRESOURCE(IDC_ERAZER));
			break;
		}
		break;

		//The following 3 cases are for drawing lines in my drawing area
	case WM_LBUTTONDOWN:


		if (xMouse > 20 && xMouse < 410 && yMouse > 50 && yMouse < 500 )
		{
			//Draw freehand
			if( SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_FREEHAND, 0) & TBSTATE_CHECKED )
			{
				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_NEW, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen,RGB(0,0,255), alfa);

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_OPEN, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,255,0), alfa);

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_SAVE, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,0), alfa);

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_PRINT, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(255,0,0), alfa);

				hdc = GetDC(hwnd);
				StartX = LOWORD(lParam);
				StartY = HIWORD(lParam);

				EndX = LOWORD(lParam);
				EndY = HIWORD(lParam);

				SetROP2(hdc, R2_XORPEN);

				MoveToEx(hdc, StartX, StartY, NULL);
				LineTo(hdc, EndX, EndY);
				isDrawing = TRUE;
				ReleaseDC(hwnd, hdc);
				Exo.DeleteObjectHPEN(strokePen);
			}

			// If the Line button is down, draw with it
			if( SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_LINE, 0) & TBSTATE_CHECKED )
			{
				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_NEW, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,255), alfa);

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_OPEN, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,255,0), alfa);

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_SAVE, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,0), alfa);

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_PRINT, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(255,0,0), alfa);

				hdc = GetDC(hwnd);
				StartX = LOWORD(lParam);
				StartY = HIWORD(lParam);

				EndX = LOWORD(lParam);
				EndY = HIWORD(lParam);
				MoveToEx(hdc, StartX, StartY, NULL);
				LineTo(hdc, EndX, EndY);
			}

			//Draw PolyLines
			if( SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_POLYLINE, 0) & TBSTATE_CHECKED )
			{
				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_NEW, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,255), alfa);

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_OPEN, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,255,0), alfa);

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_SAVE, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,0), alfa);

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_PRINT, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(255,0,0), alfa);

				hdc = GetDC(hwnd);
				StartX = LOWORD(lParam);
				StartY = HIWORD(lParam);

				EndX = LOWORD(lParam);
				EndY = HIWORD(lParam);
				MoveToEx(hdc, StartX, StartY, NULL);
				LineTo(hdc, EndX, EndY);
			}

			//Draw Rectangle
			if((SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_RECTANGLE, 0) & TBSTATE_CHECKED))
			{
				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_NEW, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,255), alfa);

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_OPEN, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,255,0), alfa);

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_SAVE, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,0), alfa);

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_PRINT, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(255,0,0), alfa);

				hdc = GetDC(hwnd);
				StartX = LOWORD(lParam);
				StartY = HIWORD(lParam);
				SetBkMode(hdc,TRANSPARENT);
				EndX = LOWORD(lParam);
				EndY = HIWORD(lParam);
				SetROP2(hdc, R2_NOP);

				MoveToEx(hdc, StartX, StartY, NULL);
				Rectangle(hdc, StartX, StartY, EndX, EndY);
				ReleaseDC(hwnd, hdc);
			}

			//Draw Circle
			if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_CIRCLE, 0) & TBSTATE_CHECKED)
			{
				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_NEW, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,255), alfa);

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_OPEN, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,255,0), alfa);

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_SAVE, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,0), alfa);

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_PRINT, 0) & TBSTATE_CHECKED)
					Exo.ChangeCurrentColor(hdc,strokePen, RGB(255,0,0), alfa);

				hdc = GetDC(hwnd);
				StartX = LOWORD(lParam);
				StartY = HIWORD(lParam);
				SetBkMode(hdc,TRANSPARENT);
				EndX = LOWORD(lParam);
				EndY = HIWORD(lParam);
				SetROP2(hdc, R2_NOP);

				MoveToEx(hdc, StartX, StartY, NULL);
				Ellipse(hdc, StartX, StartY, EndX, EndY);
				ReleaseDC(hwnd, hdc);
			}

			//Eraser
			if( SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_ERAZER, 0) & TBSTATE_CHECKED )
			{
				strokePen = CreatePen(PS_SOLID, alfa, RGB(246, 245, 243));
				SelectObject(hdc, strokePen);
				hdc = GetDC(hwnd);
				StartX = LOWORD(lParam);
				StartY = HIWORD(lParam);

				EndX = LOWORD(lParam);
				EndY = HIWORD(lParam);

				SetROP2(hdc, R2_XORPEN);

				MoveToEx(hdc, StartX, StartY, NULL);
				LineTo(hdc, EndX, EndY);
				isDrawing = TRUE;
				ReleaseDC(hwnd, hdc);
				DeleteObject(strokePen);
			}
			isDrawing = TRUE;
			ReleaseDC(hwnd, hdc);
		}
		break;

	case WM_MOUSEMOVE:

		if (xMouse > 20 && xMouse < 410 && yMouse > 50 && yMouse < 500 )
		{
			hdc = GetDC(hwnd);
			if(isDrawing == TRUE )
			{
				if( SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_LINE, 0) & TBSTATE_CHECKED )
				{
					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_NEW, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,255), alfa);

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_OPEN, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,255,0), alfa);

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_SAVE, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,0), alfa);

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_PRINT, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(255,0,0), alfa);

					SetROP2(hdc, R2_NOTXORPEN);
					MoveToEx(hdc, StartX, StartY, NULL);
					LineTo(hdc, EndX, EndY);
					EndX = LOWORD(lParam);
					EndY = HIWORD(lParam);
					MoveToEx(hdc, StartX, StartY, NULL);
					LineTo(hdc, EndX, EndY);						
				}				

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_FREEHAND, 0) & TBSTATE_CHECKED )
				{
					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_NEW, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,255), alfa);

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_OPEN, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,255,0), alfa);

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_SAVE, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,0), alfa);

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_PRINT, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(255,0,0), alfa);

					MoveToEx(hdc, EndX, EndY, NULL);
					EndX = LOWORD(lParam);
					EndY = HIWORD(lParam);
					LineTo(hdc, EndX, EndY);
				}

				if( SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_POLYLINE, 0) & TBSTATE_CHECKED )

				{
					if(wParam & MK_RBUTTON)
						isDrawing = false;

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_NEW, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,255), alfa);

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_OPEN, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,255,0), alfa);

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_SAVE, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,0), alfa);

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_PRINT, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(255,0,0), alfa);

					EndX = LOWORD(lParam);
					EndY = HIWORD(lParam);

					MoveToEx(hdc, StartX, StartY, NULL);
					LineTo(hdc, EndX, EndY);;
				}

				if((SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_RECTANGLE, 0) & TBSTATE_CHECKED))
				{

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_NEW, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,255), alfa);

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_OPEN, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,255,0), alfa);

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_SAVE, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,0), alfa);

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_PRINT, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(255,0,0), alfa);

					HBRUSH brush = CreateSolidBrush(RGB(fill,fill-100,145));
					SelectObject(hdc, brush);

					SetROP2(hdc, R2_NOTXORPEN);
					SetBkMode(hdc,TRANSPARENT);
					MoveToEx(hdc, StartX, StartY, NULL);
					Rectangle(hdc, StartX, StartY, EndX, EndY);
					EndX = LOWORD(lParam);
					EndY = HIWORD(lParam);
					MoveToEx(hdc, StartX, StartY, NULL);
					Rectangle(hdc, StartX, StartY, EndX, EndY);
					DeleteObject(brush);
				}

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_CIRCLE, 0) & TBSTATE_CHECKED)
				{
					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_NEW, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,255), alfa);

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_OPEN, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,255,0), alfa);

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_SAVE, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(0,0,0), alfa);

					if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_PRINT, 0) & TBSTATE_CHECKED)
						Exo.ChangeCurrentColor(hdc,strokePen, RGB(255,0,0), alfa);


					HBRUSH brush = CreateSolidBrush(RGB(fill,fill-100,145));
					SelectObject(hdc, brush);

					SetROP2(hdc, R2_NOTXORPEN);
					MoveToEx(hdc, StartX, StartY, NULL);
					Ellipse(hdc, StartX, StartY, EndX, EndY);
					EndX = LOWORD(lParam);
					EndY = HIWORD(lParam);
					MoveToEx(hdc, StartX, StartY, NULL);
					Ellipse(hdc, StartX, StartY, EndX, EndY);
					DeleteObject(brush);
				}

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_BEZIER, 0) & TBSTATE_CHECKED)
				{
					if (wParam & MK_LBUTTON || wParam & MK_RBUTTON)
					{
						HGDIOBJ original = NULL;

						//Saving the original object
						original = SelectObject(hdc,GetStockObject(DC_PEN));
						SelectObject(hdc, GetStockObject(DC_PEN));
						SetDCPenColor(hdc, RGB(246, 245, 243));
						myBezier.DrawBezier (hdc, apt) ;

						if (wParam & MK_LBUTTON)
						{
							apt[1].x = LOWORD (lParam) ;
							apt[1].y = HIWORD (lParam) ;
						}

						else  if (wParam & MK_RBUTTON)
						{
							apt[2].x = LOWORD (lParam) ;
							apt[2].y = HIWORD (lParam) ;
						}

						SelectObject (hdc, GetStockObject(BLACK_PEN)) ;
						myBezier.DrawBezier (hdc, apt) ;
						ReleaseDC (hwnd, hdc) ;
						DeleteObject(original);
					}
				}

				if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_ERAZER, 0) & TBSTATE_CHECKED )
				{
					strokePen = CreatePen(PS_SOLID, alfa, RGB(246, 245, 243));
					SelectObject(hdc, strokePen);
					MoveToEx(hdc, EndX, EndY, NULL);
					EndX = LOWORD(lParam);
					EndY = HIWORD(lParam);
					LineTo(hdc, EndX, EndY);
					Exo.DeleteObjectHPEN(strokePen);
				}
			}
			ReleaseDC(hwnd, hdc);
		}
		break;

	case WM_LBUTTONUP:

		if (xMouse > 20 && xMouse < 410 && yMouse > 50 && yMouse < 500 )
		{
			hdc = GetDC(hwnd);
			EndX = LOWORD(lParam);
			EndY = HIWORD(lParam);
			SetROP2(hdc, R2_XORPEN);
			MoveToEx(hdc, StartX, StartY, NULL);
			LineTo(hdc, EndX, EndY);

			if( SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_NEW, 0) & TBSTATE_CHECKED )
			{
				isDrawing = FALSE;
				white = FALSE;
			}

			if( SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_OPEN, 0) & TBSTATE_CHECKED )
			{
				isDrawing = FALSE;
				green = FALSE;
			}

			if( SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_SAVE, 0) & TBSTATE_CHECKED )
			{
				isDrawing = FALSE;
				black = FALSE;
			}

			if( SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_FILE_PRINT, 0) & TBSTATE_CHECKED )
			{
				isDrawing = FALSE;
				red = FALSE;
			}


			if( SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_LINE, 0) & TBSTATE_CHECKED )
			{
				isDrawing = FALSE;
			}

			if( SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_POLYLINE, 0) & TBSTATE_CHECKED)
			{
				isDrawing = FALSE;
			}

			if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_FREEHAND, 0) & TBSTATE_CHECKED )
			{
				isDrawing = FALSE;
			}

			if((SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_RECTANGLE, 0) & TBSTATE_CHECKED))
			{
				SetBkMode(hdc,TRANSPARENT);
				Rectangle(hdc, StartX, StartY, EndX, EndY);
				isDrawing = FALSE;
			}

			if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_CIRCLE, 0) & TBSTATE_CHECKED)
			{
				isDrawing = FALSE;
			}

			if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_DRAW_BEZIER, 0) & TBSTATE_CHECKED)
			{
				isDrawing = FALSE;
			}

			if(SendMessage(Exo.hWndToolbar, TB_GETSTATE, IDM_ERAZER, 0) & TBSTATE_CHECKED)
			{
				isDrawing = FALSE;
			}

			ReleaseDC(hwnd, hdc);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd , &rect);
		hdc_mem = CreateCompatibleDC(hdc);
		SelectObject(hdc_mem, logo);
		BitBlt(hdc, 15, 540, bitmap.bmWidth, bitmap.bmHeight, hdc_mem, 0, 0, SRCCOPY);

		DeleteObject(hdc_mem);
		//Creating Draw Area
		DrawEdge(hdc, &Recto, BDR_RAISEDOUTER | BDR_SUNKENINNER, BF_RECT);

		EndPaint(hwnd, &ps);
		break;

		//Handle the combinations from the keyboard input
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case KEY_S:
				isDrawing = FALSE;
				break;
			case KEY_Q:
				{
					if(GetAsyncKeyState(VK_LCONTROL))
					{
						//If Q + LCTRL then Exit
						PostQuitMessage(0);
					}
				}
				break;

			case KEY_C:
				{
					if(GetAsyncKeyState(VK_LSHIFT))
					{
						//If C + LShift then cleaning the drawingarea
						InvalidateRect(hwnd, &Recto, FALSE);
						InvalidateRect(hwnd, &Recto, TRUE);

					}
				}
				break;
			}
		}
		break;

	case WM_DESTROY:
		PostQuitMessage (0);
		DeleteObject(logo);
		DeleteObject(strokePen);
		break;

	default:
		return DefWindowProc (hwnd, msg, wParam, lParam);
	}

	return 0;
}

// Function: OnCommand
// Handles WM_COMMAND messages (Menu, toolbar, etc)
void MainWindow::OnCommand(HWND hwnd, int id, HWND hCtl, UINT codeNotify)
{
	switch(id)
	{
	case IDM_FILE_EXIT:
		PostQuitMessage(0);
		break;

	case IDM_FILE_CLEAR:
		InvalidateRect(hwnd, &Recto, FALSE);
		InvalidateRect(hwnd, &Recto, TRUE);
		break;

	case IDM_HELP_ABOUT:
		AboutDialog* dlg = new AboutDialog();
		dlg->Run(m_hInstance, hwnd);
		delete dlg; 
		dlg = NULL;
		break;
	}
}

//Create function of all Childs
void MainWindow::Create(HINSTANCE Hinst, HWND hWindow, LPARAM lParam, HBITMAP logo)
{
	hwndButton = CreateWindowEx((DWORD)NULL,
		L"BUTTON",                                               
		L"Clear",                                               
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,               
		0, 0, 0, 0,hWindow,                                                   
		(HMENU)IDC_CLEAR,                                    
		Hinst,
		NULL);
	hwndWidthSlider = CreateWindowEx((DWORD)NULL,
		L"Scrollbar",
		NULL,
		WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN,
		0, 0, 0, 0,hWindow,
		(HMENU)IDC_BACKGROUND_SCROLL,
		Hinst,
		NULL);

	//Scroll Range
	SetScrollRange(hwndWidthSlider, SB_CTL, 1, 10, TRUE);

	//Initial Position of the scroll 
	SetScrollPos(hwndWidthSlider, SB_CTL, 0, TRUE);

	hwndFillColor = CreateWindowEx((DWORD)NULL,
		L"Scrollbar",
		NULL,
		WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN,
		0, 0, 0, 0,hWindow,
		(HMENU)IDC_FILL_COLOR,
		Hinst,
		NULL);

	//Scroll Range
	SetScrollRange(hwndFillColor, SB_CTL, 1, 255, TRUE);

	//Initial Position of the scroll 
	SetScrollPos(hwndFillColor, SB_CTL, 0, TRUE);

	Hinst = ((LPCREATESTRUCT) lParam) -> hInstance;                          // handle to instance for custom cursor
	logo = (HBITMAP)LoadImage(Hinst, L"standard.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

}

bool MainWindow::Run(int nCmdShow)
{
	if(!RegisterClassEx(&m_wndClass))
		return false;
	m_hwnd = CreateWindowEx(0,(LPCWSTR)m_szClassName,
		L"DrawMomo",
		//WS_OVERLAPPEDWINDOW,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX, // Dissable Resizing and Maximizing
		0, 0, 450, 650,
		NULL, NULL,
		m_hInstance,
		NULL);

	if(!m_hwnd)
		return false;

	ShowWindow(m_hwnd, nCmdShow);

	return true;
}

MainWindow::operator HWND()
{
	// This overloaded operator allows us to use HWND anyway we want
	return m_hwnd;
}

HWND MainWindow::CreateStandardToolbar(HWND hParent, HINSTANCE hInst)
{
	const int NUMBUTTONS = 12;
	TBBUTTON tbrButtons[NUMBUTTONS];

	tbrButtons[0].iBitmap   = 0;
	tbrButtons[0].idCommand = IDM_FILE_NEW;
	tbrButtons[0].fsState   = TBSTATE_ENABLED;
	tbrButtons[0].fsStyle   = TBSTYLE_BUTTON |  TBSTYLE_GROUP |TBSTYLE_CHECK;
	tbrButtons[0].dwData    = 0L;
	tbrButtons[0].iBitmap   = 0;
	tbrButtons[0].iString   = 0;

	tbrButtons[1].iBitmap   = 1;
	tbrButtons[1].idCommand = IDM_FILE_OPEN;
	tbrButtons[1].fsState   = TBSTATE_ENABLED;
	tbrButtons[1].fsStyle   = TBSTYLE_BUTTON |  TBSTYLE_GROUP |TBSTYLE_CHECK;
	tbrButtons[1].dwData    = 0L;
	tbrButtons[1].iString   = 0;

	tbrButtons[2].iBitmap   = 2;
	tbrButtons[2].idCommand = IDM_FILE_SAVE;
	tbrButtons[2].fsState   = TBSTATE_ENABLED;
	tbrButtons[2].fsStyle   = TBSTYLE_BUTTON |  TBSTYLE_GROUP |TBSTYLE_CHECK;
	tbrButtons[2].dwData    = 0L;
	tbrButtons[2].iString   = 0;

	tbrButtons[3].iBitmap   = 3;
	tbrButtons[3].idCommand = IDM_FILE_PRINT;
	tbrButtons[3].fsState   = TBSTATE_ENABLED;
	tbrButtons[3].fsStyle   = TBSTYLE_BUTTON |  TBSTYLE_GROUP |TBSTYLE_CHECK;
	tbrButtons[3].dwData    = 0L;
	tbrButtons[3].iString   = 0;

	tbrButtons[4].iBitmap   = 0;
	tbrButtons[4].idCommand = 0;
	tbrButtons[4].fsState   = TBSTATE_ENABLED;
	tbrButtons[4].fsStyle   = TBSTYLE_SEP;
	tbrButtons[4].dwData    = 0L;
	tbrButtons[4].iString   = 0;

	tbrButtons[5].iBitmap   = 4;
	tbrButtons[5].idCommand = IDM_DRAW_FREEHAND;
	tbrButtons[5].fsState   = TBSTATE_ENABLED;
	tbrButtons[5].fsStyle   = TBSTYLE_BUTTON | TBSTYLE_GROUP | TBSTYLE_CHECK;
	tbrButtons[5].dwData    = 0L;
	tbrButtons[5].iString   = 0;

	tbrButtons[6].iBitmap   = 5;
	tbrButtons[6].idCommand = IDM_DRAW_LINE;
	tbrButtons[6].fsState   = TBSTATE_ENABLED;
	tbrButtons[6].fsStyle   = TBSTYLE_BUTTON | TBSTYLE_GROUP | TBSTYLE_CHECK;
	tbrButtons[6].dwData    = 0L;
	tbrButtons[6].iString   = 0;


	tbrButtons[7].iBitmap   = 6;
	tbrButtons[7].idCommand = IDM_DRAW_POLYLINE;
	tbrButtons[7].fsState   = TBSTATE_ENABLED;
	tbrButtons[7].fsStyle   = TBSTYLE_BUTTON | TBSTYLE_GROUP | TBSTYLE_CHECK;
	tbrButtons[7].dwData    = 0L;
	tbrButtons[7].iString   = 0;

	tbrButtons[8].iBitmap   = 7;
	tbrButtons[8].idCommand = IDM_DRAW_RECTANGLE;
	tbrButtons[8].fsState   = TBSTATE_ENABLED;
	tbrButtons[8].fsStyle   = TBSTYLE_BUTTON | TBSTYLE_GROUP | TBSTYLE_CHECK;
	tbrButtons[8].dwData    = 0L;
	tbrButtons[8].iString   = 0;

	tbrButtons[9].iBitmap   = 8;
	tbrButtons[9].idCommand = IDM_DRAW_CIRCLE;
	tbrButtons[9].fsState   = TBSTATE_ENABLED;
	tbrButtons[9].fsStyle   = TBSTYLE_BUTTON | TBSTYLE_GROUP | TBSTYLE_CHECK;
	tbrButtons[9].dwData    = 0L;
	tbrButtons[9].iString   = 0;

	tbrButtons[10].iBitmap   = 9;
	tbrButtons[10].idCommand = IDM_DRAW_BEZIER;
	tbrButtons[10].fsState   = TBSTATE_ENABLED;
	tbrButtons[10].fsStyle   = TBSTYLE_BUTTON | TBSTYLE_GROUP | TBSTYLE_CHECK;
	tbrButtons[10].dwData    = 0L;
	tbrButtons[10].iString   = 0;


	tbrButtons[11].iBitmap   = 10;
	tbrButtons[11].idCommand = IDM_ERAZER;
	tbrButtons[11].fsState   = TBSTATE_ENABLED;
	tbrButtons[11].fsStyle   = TBSTYLE_BUTTON | TBSTYLE_GROUP | TBSTYLE_CHECK;
	tbrButtons[11].dwData    = 0L;
	tbrButtons[11].iString   = 0;


	hWndToolbar = CreateToolbarEx(hParent, WS_VISIBLE | WS_CHILD | WS_BORDER,IDB_STANDARD,
		NUMBUTTONS, hInst,IDB_STANDARD, tbrButtons,
		NUMBUTTONS,
		16, 16, 16, 16,
		sizeof(TBBUTTON));

	if( hWndToolbar )
		return hWndToolbar;
	return NULL;
}

void MainWindow::ChangeCurrentColor(HDC d, HPEN strokePens, COLORREF color, int width)
{
	strokePens = CreatePen(PS_SOLID, width, color);
	SelectObject(d, strokePens);
}

void MainWindow::DeleteObjectHPEN(HPEN pen)
{
	DeleteObject(pen);
}
//---------------------------------------------------------------------------
void MainWindow::ChangeCurrentCursor(HWND hWnd, LPCTSTR cursor)
{
	HCURSOR crsCross;

	crsCross = LoadCursor(m_hInstance, cursor);
	SetClassLong(hWnd, GCL_HCURSOR, (LONG)crsCross);
}
