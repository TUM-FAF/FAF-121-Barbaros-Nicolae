#include <windows.h>

//For more makros
#include <windowsx.h>
#include "MainWindow.h"
#include "resource.h"
#include "AboutDialog.h"

HINSTANCE hProgramInstance;

//Global variables for child window
    HWND hwndListBox;
	HWND hwndHeightScroll;
    HWND hwndWidthScroll;
	HWND hwndBackgroundScroll;
	HWND hwndLabel1;
    HWND hwndLabel2;
    HWND hwndLabel3;
	HWND hwndStaticText;
	HWND hwndButton;

char MainWindow::m_szClassName[] = "DrawMomo";
 
//MinHeight and MinWidth of the main Window
int iMinWindowHeight = 610;
int iMinWindowWidth  = 420;

//Variable for changing color of a static text
int alfa = 0;

//Timer flag
int seconds;

bool timerstart = false;
//Drawing Area
RECT Recto = {20, 200, 410, 500};

MainWindow::MainWindow(HINSTANCE hInstance)
{
    m_hInstance = hInstance; // Save Instance handle
    m_wndClass.cbSize = sizeof(WNDCLASSEX); // Must always be sizeof(WNDCLASSEX)
    m_wndClass.style = CS_DBLCLKS; // Class styles	
    m_wndClass.lpfnWndProc = MainWndProc; // Pointer to callback procedure
    m_wndClass.cbClsExtra = 0; // Extra bytes to allocate following the wndclassex structure
    m_wndClass.cbWndExtra = 0; // Extra bytes to allocate following an instance of the structure
    m_wndClass.hInstance = hInstance; // Instance of the application
    m_wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON)); // Class Icon
	m_wndClass.hCursor = LoadCursor(hInstance,MAKEINTRESOURCE(IDI_APP_CURSOR)); // Class cursor
    m_wndClass.hbrBackground = (HBRUSH) (COLOR_WINDOW); // Background brush
	m_wndClass.lpszMenuName = MAKEINTRESOURCE(IDM_MAINMENU); // Menu Resource
    m_wndClass.lpszClassName = (LPCWSTR)m_szClassName; // Name of this class
    m_wndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON)); // Small icon for this class
}
 
MainWindow::~MainWindow()
{
}

MainWindow::MainWindow()
{

}
LRESULT CALLBACK MainWindow::MainWndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	MainWindow Ex;
	HDC hdc;
	PAINTSTRUCT ps;
	SCROLLINFO si;
	TEXTMETRIC tm;
	
	//Static variables for drawing
	static bool isDrawing = FALSE;
	static int StartX, StartY;
	static int EndX, EndY;
	
	//Static variables for mouse Co-ordinates
	static int xMouse, yMouse;
	xMouse = GET_X_LPARAM(lParam);
    yMouse = GET_Y_LPARAM(lParam);
	HBRUSH newbrush;

	//Child Window Handles
	MainWindow create;
	RECT rect;

    // Size and position variables
    int iSysWidth;
    int iSysHeight;
    int iWinWidth;
    int iWinHeight;
	int cxChar;
    int cyChar;

	int iWidth  = 60;   // Button width
    int iHeight = 30;   // Button height
	
    int iListBoxWidth = 300;
    int iListBoxHeight = 360;

	// Size and position variables
	int x, y;

	hdc = GetDC(hwnd);
    GetTextMetrics(hdc, &tm);
    cxChar = tm.tmAveCharWidth;
    cyChar = tm.tmHeight;
    ReleaseDC(hwnd, hdc);

	hProgramInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);

    switch (msg)
    {
	case WM_CREATE:
		
		create.Create(hProgramInstance,hwnd);
		break;



		//Set Default Cursor Over all created Child
		case WM_SETCURSOR:

			if (LOWORD(lParam) == HTCLIENT)
			{
				SetCursor(LoadCursor(hProgramInstance, MAKEINTRESOURCE(IDI_APP_CURSOR)));
				return TRUE;
			}
		 
        break;

		//Minimum width and Height
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
            MoveWindow(hwndListBox, 20, 540, 390, 40, TRUE);

            MoveWindow(hwndLabel1, 10, 40, iListBoxWidth + 80, 20, TRUE);   //4-th parameter is height of the item

            MoveWindow(hwndBackgroundScroll, 10, 60, iListBoxWidth + 110, 10, TRUE);

            MoveWindow(hwndLabel2, 10, 80, iListBoxWidth + 60, 20, TRUE);

            MoveWindow(hwndWidthScroll, 10, 100, iListBoxWidth + 110, 10, TRUE);

            MoveWindow(hwndLabel3, 10, 120, iListBoxWidth + 60, 20, TRUE);

            MoveWindow(hwndHeightScroll, 10, 140, iListBoxWidth + 110, 10, TRUE);

			MoveWindow(hwndButton,20,510,iListBoxWidth+90, iListBoxHeight-335, TRUE);

			MoveWindow(hwndStaticText, 160, 170, 150, 30, TRUE);

            GetWindowRect(hwnd, &rect);
            iWinWidth = rect.right - rect.left;
            iWinHeight = rect.bottom - rect.top;
            iSysWidth = GetSystemMetrics(SM_CXSCREEN);
            iSysHeight = GetSystemMetrics(SM_CYSCREEN);

            // Set width scrollbar position
            SetScrollPos(hwndWidthScroll, SB_CTL, (iWinWidth * 100 / iSysWidth), TRUE);

            // Set height scrollbar position
            SetScrollPos(hwndHeightScroll, SB_CTL, (iWinHeight * 100 / iSysHeight), TRUE);
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
				if(si.nPos != y) {
					ScrollWindow(hwnd, 0, cyChar * (y - si.nPos), NULL, NULL);
					UpdateWindow(hwnd);
				}
            break;

			 case WM_CTLCOLORSTATIC:
				 
				SetTextColor((HDC)wParam, RGB(alfa, 0, 255 - alfa));
				SetBkMode((HDC)wParam, TRANSPARENT);
				newbrush = (HBRUSH)GetStockObject(NULL_BRUSH);
                return (LRESULT)newbrush;
			break;

			case WM_HSCROLL:
				GetWindowRect(hwnd, &rect);
				iWinWidth = rect.right - rect.left;
				iWinHeight = rect.bottom - rect.top;
				iSysWidth = GetSystemMetrics(SM_CXSCREEN);
				iSysHeight = GetSystemMetrics(SM_CYSCREEN);
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

					   SetScrollPos(hwndBackgroundScroll, SB_CTL, alfa, TRUE);
					   InvalidateRect(hwndStaticText, NULL, TRUE);

					}

					if(GetWindowLong((HWND)lParam, GWL_ID) == IDC_WIDTH_SCROLL)
					{
						si.cbSize = sizeof(si);
						si.fMask = SIF_ALL;
						GetScrollInfo(hwndWidthScroll, SB_CTL, &si);
						x = si.nPos;

						switch(LOWORD(wParam)) 
						{
							case SB_LINELEFT:
								si.nPos -= 1;
							break;
						
							case SB_LINERIGHT:
								si.nPos += 1;
							break;
						
							case SB_THUMBPOSITION:
								si.nPos = si.nTrackPos;
							break;
						
							default: break;
						}
					
						si.fMask = SIF_POS;
						SetScrollInfo(hwndWidthScroll, SB_CTL, &si, TRUE);
						GetScrollInfo(hwndWidthScroll, SB_CTL, &si);
					
						if(si.nPos != x)
						{
							SetScrollPos(hwndWidthScroll, SB_CTL, si.nPos, TRUE);
						}
					
						// Set window width
						MoveWindow(hwnd, rect.left, rect.top, (si.nPos * iSysWidth / 100), iWinHeight, TRUE);
						break;
					}

					if(GetWindowLong((HWND)lParam, GWL_ID) == IDC_HEIGHT_SCROLL)
					{
						si.cbSize = sizeof(si);
						si.fMask = SIF_ALL;
						GetScrollInfo(hwndHeightScroll, SB_CTL, &si);
						x = si.nPos;
					
						switch(LOWORD(wParam))
						{
							case SB_LINELEFT:
								si.nPos -= 1;
							break;
						
							case SB_LINERIGHT:
								si.nPos += 1;
							break;
						
							case SB_THUMBPOSITION:
								si.nPos = si.nTrackPos;
							break;
						
							default: break;
						}
					
						si.fMask = SIF_POS;
						SetScrollInfo(hwndHeightScroll, SB_CTL, &si, TRUE);
						GetScrollInfo(hwndHeightScroll, SB_CTL, &si);
					
						if(si.nPos != x)
						{
							SetScrollPos(hwndHeightScroll, SB_CTL, si.nPos, TRUE);
						}
					
						// Set window height
						MoveWindow(hwnd, rect.left, rect.top, iWinWidth, (si.nPos * iSysHeight / 100), TRUE);
						break;
					}

					// Get all the vertical scroll bar information
					si.cbSize = sizeof(si);
					si.fMask = SIF_ALL;
					GetScrollInfo(hwnd, SB_HORZ, &si);

					// Save the position for later comparison
					x = si.nPos;
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
					}
			break;

			//By pressing LeftButton, co-ordinates of the mouse will be inserted in  a LB
			case WM_LBUTTONDBLCLK:
				char str[256];
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				wsprintf((LPWSTR)str, L"Co-ordinates are \nX=%i and Y=%i", pt.x, pt.y);
				SendDlgItemMessage(hwnd, IDC_LIST_BOX, LB_ADDSTRING, 0, (LPARAM)str);
				SendMessage(hwndListBox, WM_SETTEXT, NULL, NULL);
			break;

			//The following 3 cases are for drawing lines in my drawing area
			case WM_LBUTTONDOWN:

					if (xMouse > 20 && xMouse < 410 && yMouse > 200 && yMouse < 500 )
					{
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
					}
			break;

			case WM_MOUSEMOVE:

				if (xMouse > 20 && xMouse < 410 && yMouse > 200 && yMouse < 500 )
				{
					hdc = GetDC(hwnd);

					if(isDrawing == TRUE )
					{
						SetROP2(hdc, R2_NOTXORPEN);
						MoveToEx(hdc, StartX, StartY, NULL);
						LineTo(hdc, EndX, EndY);
						EndX = LOWORD(lParam);
						EndY = HIWORD(lParam);
						MoveToEx(hdc, StartX, StartY, NULL);
						LineTo(hdc, EndX, EndY);
					}

					ReleaseDC(hwnd, hdc);
				}
			break;

			case WM_LBUTTONUP:

				if (xMouse > 20 && xMouse < 410 && yMouse > 200 && yMouse < 500 )
				{
					hdc = GetDC(hwnd);
					EndX = LOWORD(lParam);
					EndY = HIWORD(lParam);
					SetROP2(hdc, R2_XORPEN);
					MoveToEx(hdc, StartX, StartY, NULL);
					LineTo(hdc, EndX, EndY);
					isDrawing = FALSE;
					ReleaseDC(hwnd, hdc);
				}
			break;

	
			case WM_PAINT:

				HFONT hFontOld;
				HFONT CustomFont;
				CustomFont = CreateFont(-12, 0, 0, 0, FW_DONTCARE, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"Mangal");
				hdc = BeginPaint(hwnd, &ps);
				GetClientRect(hwnd , &rect);
				hFontOld = (HFONT)SelectObject(hdc, CustomFont);
				
				//Sending message to the static text about changing defaultfont to customFont
				SendMessage(hwndLabel1, WM_SETFONT, WPARAM(CustomFont), TRUE);
				SendMessage(hwndLabel2, WM_SETFONT, WPARAM(CustomFont), TRUE);
				SendMessage(hwndLabel3, WM_SETFONT, WPARAM(CustomFont), TRUE);

				DeleteObject(SelectObject(hdc,hFontOld));

				//Creating Draw Area
				DrawEdge(hdc, &Recto, BDR_RAISEDOUTER | BDR_SUNKENINNER, BF_RECT);
				
				EndPaint(hwnd, &ps);
			break;

			//Shows Pressed Keys
			case WM_CHAR:
				
				//Created an array
				TCHAR chCharCode[255];
				wsprintf((LPWSTR)chCharCode, L"Key %c ", (TCHAR)wParam);

				//Shows the pressed key into ListBox
				SendDlgItemMessage(hwnd, IDC_LIST_BOX, LB_ADDSTRING, 0, (LPARAM)chCharCode);
				SendMessage(hwndListBox, WM_SETTEXT, NULL, NULL);

				//Shows a simple box with pressed key
				MessageBox(hwnd, (LPCWSTR)chCharCode, L"KeyboardInput", MB_OK);
			break;
			

			//Handle the combinations from the keyboard input
			case WM_KEYDOWN:
				{
					switch(wParam)
						{
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

			//Displaying an messagebox when you press X button of the mainWindow
			case WM_CLOSE:

				MessageBoxA(NULL, "GoTo File -> Exit", "QUIT ERROR", MB_OK | MB_ICONINFORMATION);

			break;

			case WM_DESTROY:
			   // PostQuitMessage (0);
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
void MainWindow::Create(HINSTANCE Hinst, HWND hWindow)
{
	hwndListBox = CreateWindowEx((DWORD)NULL,
									TEXT("ListBox"),
									NULL,
									WS_CHILD | WS_VISIBLE | WS_BORDER| WS_VSCROLL| WS_HSCROLL,
									0, 0, 0, 0, hWindow,
									(HMENU)IDC_LIST_BOX,
									Hinst,
									NULL);
		

		 hwndLabel1 = CreateWindowEx((DWORD)NULL,
									TEXT("static"),
									TEXT("Color"),
									WS_CHILD | WS_VISIBLE | SS_LEFT,
									0, 0, 0, 0, hWindow,
									(HMENU)IDC_LABEL1,
									Hinst,
									NULL);

		 hwndLabel2 = CreateWindowEx((DWORD)NULL,
									TEXT("static"),
									TEXT("Window Width"),
									WS_CHILD | WS_VISIBLE | SS_LEFT,
									0, 0, 0, 0, hWindow,
									(HMENU)IDC_LABEL2,
									Hinst,
									NULL);

		 hwndLabel3 = CreateWindowEx((DWORD)NULL,
									TEXT("static"),
									TEXT("Window Height"),
									WS_CHILD | WS_VISIBLE | SS_LEFT,
									0, 0, 0, 0,
									hWindow,
									(HMENU)IDC_LABEL3,
									Hinst,
									NULL);

		hwndBackgroundScroll = CreateWindowEx((DWORD)NULL,
										   	 L"Scrollbar",
											 NULL,
											 WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN,
											 0, 0, 0, 0,hWindow,
											 (HMENU)IDC_BACKGROUND_SCROLL,
											 Hinst,
											 NULL);

		 //Scroll Range
         SetScrollRange(hwndBackgroundScroll, SB_CTL, 0, 255, TRUE);
		 
		 //Initial Position of the scroll 
         SetScrollPos(hwndBackgroundScroll, SB_CTL, 125, TRUE);

		 hwndWidthScroll = CreateWindowEx((DWORD)NULL,
										 L"Scrollbar",
										 NULL,
										 WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN,
										 0, 0, 0, 0, hWindow,
										 (HMENU)IDC_WIDTH_SCROLL,
										 Hinst,
										 NULL);
		  //Scroll Range
          SetScrollRange(hwndWidthScroll, SB_CTL, 0, 100, TRUE);

          hwndHeightScroll = CreateWindowEx((DWORD)NULL,
									       L"Scrollbar",
										   NULL,
										   WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN,
										   0, 0, 0, 0, hWindow,
										   (HMENU)IDC_HEIGHT_SCROLL,
										   Hinst,
										   NULL);
		   //Scroll Range
           SetScrollRange(hwndHeightScroll, SB_CTL, 0, 100, TRUE);


		   hwndStaticText = CreateWindowEx((DWORD)NULL,
										  L"static",
										  L"DrawingArea",
										  WS_VISIBLE|WS_CHILD,
                                          0, 0, 0, 0, hWindow,
										  (HMENU)IDC_STATIC_TEXT,
										  Hinst,
										  NULL);

			   hwndButton = CreateWindowEx((DWORD)NULL,
										   L"BUTTON",                                               
										   L"Clear",                                               
										   WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,               
										   0, 0, 0, 0,hWindow,                                                   
										   (HMENU)IDC_CLEAR,                                    
										   Hinst,
										   NULL);
	
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
