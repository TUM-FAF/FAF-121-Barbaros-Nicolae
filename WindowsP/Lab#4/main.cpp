#include "objects.h"
#pragma comment( lib, "Winmm.lib" )

HWND hwnd;
HDC device;
bool gameover = false;
float positionX = 100;
float positionY = 200;
int x = 0,y = 0 ;
int count = 0;
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

//An array of Objects that is used to keep info of all the animated objects
static Objects *objects[100];

/*  Make the class name into a global variable  */
char szClassName[ ] = "CodeBlocksWindowsApp";
void DrawNyanCat(char* filename, float x,  int y)
{
    //load the bitmap image
    HBITMAP cat = (HBITMAP)LoadImage(0, "NyanCaat.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//read the bitmap's properties
	BITMAP bm;
	GetObject(cat, sizeof(BITMAP), &bm);

	//create a device context for the bitmap
	HDC hdcImage = CreateCompatibleDC(device);
	SelectObject(hdcImage, cat);

	//destination device context, x, y location on destination,  width, height of source bitmap 70, 95, Image handle, start top, left on source bitmap 15, 35, blit method
	BitBlt(device, x, y, 94, 73, hdcImage, 0, 0, SRCCOPY );

	//delete the device context and bitmap
	DeleteDC(hdcImage);
	DeleteObject((HBITMAP) cat);
}

void Game_Run()
{
	if (gameover == true) return;
	DrawNyanCat("NyanCaat.bmp", positionX,positionY);
}


void Game_End()
{
	//free the device
	ReleaseDC(hwnd, device);
}
int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = CreateSolidBrush(RGB(11, 105, 171));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Nyan RoboCat",       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           800,                 /* The programs width */
           600,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);

	//get device context for drawing
	device = GetDC(hwnd);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (!gameover)
	{
		//process Windows events
		if (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE)) // Remove the message
		{
			TranslateMessage(&messages);
			DispatchMessage(&messages);
		}

		//process the game loop
		Game_Run();
	}

	//free game resources
	Game_End();

	return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)

{   //A handle to the device context and the buffer memory
    static HDC hdc,hdcMem;
    static PAINTSTRUCT ps;
    static RECT rect;
    static HBRUSH hBrush;

    // A bitmap handle for the double buffring
    static HBITMAP hbmMem;

    // A handle to the old memory context
    static HANDLE hOld;

    // The timer delay and the initial number of objects defined
    static int timerSpeed=50,numberObjects=0;

    switch (message)                  /* handle the messages */
    {
          case WM_CREATE:

             //Play Music on Start
             PlaySound("NyanMusic.wav", NULL, SND_ASYNC);

            //Gets device context of the window and the rectangle of the client area
            hdc=GetDC(hwnd);
            GetClientRect(hwnd,&rect);

            //Generate the buffer memory using a bitmap akin memory data
            hdcMem=CreateCompatibleDC(hdc);
            hbmMem=CreateCompatibleBitmap(hdc,rect.right,rect.bottom);
            hOld = SelectObject(hdcMem,hbmMem);

            //Sets the initial timer
            SetTimer(hwnd,ID_TIMER,timerSpeed,NULL);
            break;

        case WM_SIZE:

            //Destroy the double buffer memory and handle
            SelectObject(hdcMem,hOld);
            DeleteObject(hbmMem);
            DeleteDC(hdcMem);

            //Gets device context of the window and the rectangle of the client area
            hdc=GetDC(hwnd);
            GetClientRect(hwnd,&rect);

            //Generate the buffer memory using a bitmap akin memory data
            hdcMem=CreateCompatibleDC(hdc);
            hbmMem=CreateCompatibleBitmap(hdc,rect.right,rect.bottom);
            hOld = SelectObject(hdcMem,hbmMem);
            break;
        case WM_LBUTTONDOWN:

            //Reads the center of the circle from the mouse click data
           //PlaySound("pipe.wav", NULL, SND_ASYNC);
            POINT newCenter;
            newCenter.x=LOWORD(lParam);
            newCenter.y=HIWORD(lParam);

            //Creates a new circle based on the mouse position data
            objects[numberObjects]=new Circle(newCenter,5+newCenter.x%5);
            objects[numberObjects]->Color(RGB(newCenter.x%255,newCenter.x%125+newCenter.y%125,newCenter.y%255));

            //Increments number of objects
            numberObjects++;
            break;


        case WM_MOUSEWHEEL:

            //Checks if the mousewheel was scrolled down and decreases the speed and increases otherwise
            if((short)HIWORD(wParam)<0)
            {
                timerSpeed+=10;
            }
            else
            {
                timerSpeed-=10;

            //Checks to see that the delay for the timer isn't negative
                if (timerSpeed<0) timerSpeed=1;
            }

            //Resets the timer
            KillTimer(hwnd,ID_TIMER);
            SetTimer(hwnd,ID_TIMER,timerSpeed,NULL);
            break;

        case WM_PAINT:

            //Gets the device contexd handle and the rectangle area of the client
            hdc=BeginPaint(hwnd,&ps);
            GetClientRect(hwnd,&rect);

            //Checks for interaction between all the objects in the array
            for(int i=0;i<numberObjects-1;i++) {
                for(int j=i+1;j<numberObjects;j++) {
                    Interaction(*objects[i],*objects[j]);
                }
            }
            //Fills the buffer memory background image with blue
            FillRect(hdcMem,&rect,CreateSolidBrush(RGB(11, 105, 171)));

            //Redraws all the objects in the array
            for(int i=0;i<numberObjects;i++) {
                objects[i]->Move(hdcMem,rect,hBrush);
            }
            //Switches the loaded memory buffer with the display context


            BitBlt(hdc,0,0,rect.right,rect.bottom,hdcMem,0,0,SRCPAINT);
            EndPaint(hwnd,&ps);
            break;

        case WM_KEYDOWN:
            {
            switch (wParam)
            {
                case VK_LEFT:
                    // Process the LEFT ARROW key.

                     positionX -= 1;
                     if(positionX <rect.left)
                        positionX = rect.left;
                    break;

                case VK_RIGHT:

                    // Process the RIGHT ARROW key.
                     positionX += 1;
                     if(positionX > rect.right)
                        positionX = rect.right;
                    break;

                case VK_UP:

                    // Process the UP ARROW key.
					positionY -= 1;
					if(positionY <rect.top)
                        positionY = rect.top;
                    break;

                case VK_DOWN:

                    // Process the DOWN ARROW key.
					positionY += 1;
					if(positionY >rect.bottom)
                        positionY = rect.bottom;
                    break;
                    default: break;
                    }
            }
            break;

        case WM_GETMINMAXINFO:
            {
                LPMINMAXINFO pInfo = (LPMINMAXINFO) lParam;
                pInfo -> ptMaxTrackSize.x = 800;
                pInfo -> ptMaxTrackSize.y = 600;
                pInfo -> ptMinTrackSize.x = 800;
                pInfo -> ptMinTrackSize.y = 60;
            }
		break;

        case WM_TIMER:
            //Invalidates rect area without calling the erase background message
            InvalidateRect(hwnd,NULL,FALSE);
            break;

        case WM_DESTROY:
            //Destroy the double buffer memory and handle
            SelectObject(hdcMem,hOld);
            DeleteObject(hbmMem);
            DeleteDC(hdcMem);
            //Kill the timer
            KillTimer(hwnd,ID_TIMER);

            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;

        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
